int currentCode = 0;

void setup() {
  Serial.begin(9600);
  delay(2000); 
  for(int i=0; i<80; i++) Serial.print(" ");
}

void loop() {
  if (Serial.available() > 0) {
    while(Serial.available() > 0) { Serial.read(); delay(5); } 

    currentCode++;
    if (currentCode > 255) currentCode = 0;

    vfdRefresh();
  }
}

void vfdRefresh() {
  Serial.print("HEX:");
  if (currentCode < 16) Serial.print("0");
  Serial.print(currentCode, HEX);
  Serial.print("->");
  Serial.write(currentCode);
  for (int i = 0; i < 31; i++) {
    Serial.print(" ");
  }
}