// TIL309 BCD pins
const int pinA = 2;
const int pinB = 3;
const int pinC = 4;
const int pinD = 5;
const int pinDP = 6;

void setup() {
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinC, OUTPUT);
  pinMode(pinD, OUTPUT);
  pinMode(pinDP, OUTPUT);
  
  digitalWrite(pinDP, LOW); // DP off
}

void displayBCD(int value) {
  digitalWrite(pinA, (value & 1) ? HIGH : LOW);
  digitalWrite(pinB, (value & 2) ? HIGH : LOW);
  digitalWrite(pinC, (value & 4) ? HIGH : LOW);
  digitalWrite(pinD, (value & 8) ? HIGH : LOW);
}

void loop() {
  // 0-9
  for (int i = 0; i <= 9; i++) {
    displayBCD(i);
    delay(1000);
  }
}