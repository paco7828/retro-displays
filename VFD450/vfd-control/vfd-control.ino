#include <WiFi.h>
#include <WebServer.h>
#include <DNSServer.h>
#include <esp_wifi.h>
#include <functional>
#include <map>
#include <time.h>

const char* ssid = "";
const char* password = "";
const char* ntpServer = "pool.ntp.org";

#define VFD_TX 21
#define VFD_RESET 10
#define BAUDRATE 9600

enum Mode { CLOCK,
            TEXT,
            ANIM_SCANNER,
            ANIM_NOISE };
Mode currentMode = CLOCK;
String userMessage = "HELLO";
int animFrame = 0;
int animDir = 1;

void runCharTest() {
  for (int c = 0x01; c <= 0xFE; c++) {
    for (int i = 0; i < 40; i++) {
      Serial1.write((uint8_t)c);
    }
    delay(150);
  }
}

String translateToVFD(String input) {
  String output = "";
  for (int i = 0; i < input.length(); i++) {
    unsigned char c = input[i];
    if (c == 0xC3) {
      unsigned char next = input[++i];
      if (next == 0xA1) output += (char)0xA0;       // á -> á (0xA0)
      else if (next == 0x81) output += (char)0xA0; // Á -> á
      else if (next == 0xA9) output += (char)0x60;  // é -> é (0x60)
      else if (next == 0xAD) output += (char)0xA1;  // í -> í (0xA1)
      else if (next == 0xB3) output += (char)0xA2;  // ó -> ó (0xA2)
      else if (next == 0xB6) output += (char)0x7C;  // ö -> ö (0x7C)
      else if (next == 0xBA) output += (char)0xA3;  // ú -> ú (0xA3)
      else if (next == 0xBC) output += (char)0x7E;  // ü -> ü (0x7E)
      else if (next == 0x89) output += (char)0x40;  // É -> É (0x40)
      else if (next == 0x96) output += (char)0x5C;  // Ö -> Ö (0x5C)
      else if (next == 0x9C) output += (char)0x5E;  // Ü -> Ü (0x5E)
    } else if (c == 0xC5) {
      unsigned char next = input[++i];
      if (next == 0x91) output += (char)0x7C;       // ő -> ö
      else if (next == 0x90) output += (char)0x5C;  // Ő -> Ö
      else if (next == 0xB1) output += (char)0x7E;  // ű -> ü
      else if (next == 0xB0) output += (char)0x5E;  // Ű -> Ü
    } else {
      output += (char)c;
    }
  }
  return output;
}

void sendToVFD(String message) {
  String clean = translateToVFD(message);
  String buffer = "\r" + clean;
  while (buffer.length() < 40) buffer += " ";
  if (buffer.length() > 40) buffer = buffer.substring(0, 40);
  Serial1.print(buffer);
}

void connectWithAnimation() {
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(ssid, password);

  int pos = 0;
  while (WiFi.status() != WL_CONNECTED) {
    String line1 = "  WiFi csatlakozás  ";
    String line2 = " ";
    for (int i = 0; i < 18; i++) line2 += (i == pos) ? (char)0xDB : (char)0xC4;
    line2 += " ";

    sendToVFD(line1 + line2);
    delay(150);
    pos++;
    if (pos >= 18) pos = 0;
  }

  sendToVFD("      WIFI OK!          RENDSZER KéSZ   ");
  delay(1500);
}

void displayTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    sendToVFD("NTP SZINKRON...                         ");
    return;
  }

  const char* napok[] = { "Vas", "Hét", "Ked", "Sze", "Csü", "Pén", "Szo" };

  char timeStr[9];
  strftime(timeStr, sizeof(timeStr), "%H:%M:%S", &timeinfo);

  char dateStr[12];
  strftime(dateStr, sizeof(dateStr), "%Y.%m.%d-", &timeinfo);

  String line1 = "   Time  " + String(timeStr) + "      ";
  String line2 = String(dateStr) + String(napok[timeinfo.tm_wday]);

  while (line2.length() < 20) line2 += " ";

  sendToVFD(line1 + line2);
}

void runScanner() {
  String track = "-------------------";
  track[animFrame] = (char)0xDB;
  sendToVFD("   IDLE SCANNER     [" + track + "]");

  animFrame += animDir;
  if (animFrame >= 18 || animFrame <= 0) animDir *= -1;
}

void runNoise() {
  String noise = "";
  for (int i = 0; i < 39; i++) noise += (char)(rand() % 4 + 0xB0);
  sendToVFD(noise);
}

class BetterCaptivePortal {
private:
  WebServer server;
  DNSServer dnsServer;
  bool apRunning;
  std::map<String, String> formData;
  std::function<void(std::map<String, String>&)> onFormSubmit;
  String customHTML;
  bool hasCustomHTML;
  const IPAddress localIP = IPAddress(4, 3, 2, 1);
  const IPAddress gateway = IPAddress(4, 3, 2, 1);
  const IPAddress subnet = IPAddress(255, 255, 255, 0);

  void handleRoot() {
    String html = R"rawliteral(
<!DOCTYPE html><html><head><meta charset="UTF-8"><meta name="viewport" content="width=device-width, initial-scale=1">
<style>body{background:#111;color:#0f0;font-family:monospace;text-align:center;padding:20px;}
input,select,button{background:#222;color:#0f0;border:1px solid #0f0;padding:10px;margin:10px;width:80%;}
button{cursor:pointer;font-weight:bold;}</style></head>
<body><h1>VFD CONTROL</h1><form action="/save" method="POST">
<label>MOD:</label><br><select name="mode">
<option value="0">ORA (NTP)</option><option value="1">EGYEDI SZOVEG</option>
<option value="2">SCANNER ANIM</option><option value="3">ZAJ ANIM</option></select><br>
<label>SZOVEG (Max 39 char):</label><br><input type="text" name="txt" maxlength="39"><br>
<button type="submit">BEALLITAS</button></form></body></html>)rawliteral";
    server.send(200, "text/html", html);
  }

  void handleSave() {
    if (server.hasArg("mode")) {
      int m = server.arg("mode").toInt();
      currentMode = (Mode)m;
    }
    if (server.hasArg("txt") && server.arg("txt").length() > 0) {
      userMessage = server.arg("txt");
    }
    server.send(200, "text/html", "<html><body style='background:#111;color:#0f0;'>OK! Frissites...<script>setTimeout(()=>window.location.href='/',1000);</script></body></html>");
  }

public:
  BetterCaptivePortal()
    : server(80), apRunning(false), hasCustomHTML(false) {}

  void begin() {
    WiFi.softAPConfig(localIP, gateway, subnet);
    WiFi.softAP("VFD-VEZERLO", "");
    server.on("/", [this]() {
      handleRoot();
    });
    server.on("/save", HTTP_POST, [this]() {
      handleSave();
    });
    server.onNotFound([this]() {
      handleRoot();
    });
    server.begin();
    dnsServer.start(53, "*", localIP);
    apRunning = true;
  }

  void handle() {
    if (!apRunning) return;
    dnsServer.processNextRequest();
    server.handleClient();
  }
};

BetterCaptivePortal portal;

void setup() {
  Serial.begin(115200);
  pinMode(VFD_RESET, OUTPUT);
  digitalWrite(VFD_RESET, HIGH);
  delay(200);
  digitalWrite(VFD_RESET, LOW);
  delay(1000);

  Serial1.begin(BAUDRATE, SERIAL_8E1, -1, VFD_TX);
  delay(1000);

  //runCharTest();

  connectWithAnimation();
  configTzTime("CET-1CEST,M3.5.0,M10.5.0/3", ntpServer);

  portal.begin();
}

unsigned long lastUpdate = 0;
void loop() {
  portal.handle();

  unsigned long now = millis();
  int interval = (currentMode == CLOCK || currentMode == TEXT) ? 1000 : 100;

  if (now - lastUpdate >= interval) {
    switch (currentMode) {
      case CLOCK: displayTime(); break;
      case TEXT: sendToVFD(userMessage); break;
      case ANIM_SCANNER: runScanner(); break;
      case ANIM_NOISE: runNoise(); break;
    }
    lastUpdate = now;
  }
}