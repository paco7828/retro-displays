/*
TIL309 -> Arduino Uno

1-QB -> Not connected
2-QC -> Not connected
3-QD -> Not connected
4-QA -> Not connected
5-LS# -> GND
6-C -> D4
7-D -> D5
8-GND -> GND
9-NC -> Not connected
10-B -> D3
11-Bl# -> 5V
12-DP -> D6
13-LT# -> 5V
14-QDP -> Not connected
15-A -> D9
16-VCC -> 5V

*/
const int pinA = 9;  // LSB
const int pinB = 3;
const int pinC = 4;
const int pinD = 5;   // MSB
const int pinDP = 6;  // DP

void setup() {
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinC, OUTPUT);
  pinMode(pinD, OUTPUT);
  pinMode(pinDP, OUTPUT);

  clearDisplay();
}

void sendRawBCD(int value) {
  digitalWrite(pinA, (value & 1) ? HIGH : LOW);
  digitalWrite(pinB, (value & 2) ? HIGH : LOW);
  digitalWrite(pinC, (value & 4) ? HIGH : LOW);
  digitalWrite(pinD, (value & 8) ? HIGH : LOW);
}

// Numbers 0-9
void displayNumber(int num) {
  if (num >= 0 && num <= 9) {
    sendRawBCD(num);
  }
}

// Characters (A, C, E, F, -)
void displayChar(char c) {
  switch (toUpperCase(c)) {
    case 'A': sendRawBCD(10); break;
    case '-': sendRawBCD(11); break;
    case 'C': sendRawBCD(12); break;
    case 'E': sendRawBCD(14); break;
    case 'F': sendRawBCD(15); break;
    case ' ': clearDisplay(); break;  // Szóközre kikapcsol
  }
}

void setDecimalPoint(bool state) {
  digitalWrite(pinDP, state ? HIGH : LOW);
}

void clearDisplay() {
  sendRawBCD(13);  // Blanking
  setDecimalPoint(false);
}

void loop() {
  for (int i = 0; i <= 9; i++) {
    displayNumber(i);
    delay(500);
  }

  displayChar('A');
  delay(500);
  displayChar('C');
  delay(500);
  displayChar('E');
  delay(500);
  displayChar('F');
  delay(500);
  displayChar('-');
  delay(500);

  setDecimalPoint(true);
  delay(500);
  setDecimalPoint(false);

  clearDisplay();
  delay(500);
}