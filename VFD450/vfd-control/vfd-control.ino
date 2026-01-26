#define TX_PIN 21

String textToDisplay = "";

void setup() {
  Serial1.begin(9600, SERIAL_8N1, -1, TX_PIN);
  delay(2000);
  vfdFullClear();
}

void loop() {
  while (Serial.available() > 0) {
    char character = Serial.read();
    if (character == '\n') {
      vfdRefresh(textToDisplay);
      textToDisplay = "";
    } else {
      if (character != '\r') {
        textToDisplay += character;
      }
    }
  }
}

void vfdRefresh(String text) {
  if (text.length() > 40) {
    text = text.substring(0, 40);
  }

  Serial1.print(text);
  int remaining = 40 - text.length();
  for (int i = 0; i < remaining; i++) {
    Serial1.print(" ");
  }
}

void vfdFullClear() {
  for (int i = 0; i < 80; i++) {
    Serial1.print(" ");
  }
}