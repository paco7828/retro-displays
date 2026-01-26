String bejovoSzo = "";

void setup() {
  Serial.begin(9600);
  delay(2000);
  vfdTeljesTorles();
  vfdFrissites("RENDSZER KESZ");
}

void loop() {
  while (Serial.available() > 0) {
    char karakter = Serial.read();
    if (karakter == '\n') {
      vfdFrissites(bejovoSzo);
      bejovoSzo = "";
    } else {
      if (karakter != '\r') {
        bejovoSzo += karakter;
      }
    }
  }
}

void vfdFrissites(String szoveg) {
  if (szoveg.length() > 40) {
    szoveg = szoveg.substring(0, 40);
  }
  Serial.print(szoveg);
  int maradek = 40 - szoveg.length();
  for (int i = 0; i < maradek; i++) {
    Serial.print(" ");
  }
}

void vfdTeljesTorles() {
  for (int i = 0; i < 80; i++) {
    Serial.print(" ");
  }
}