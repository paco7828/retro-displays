/*
1 - C & D (common anode)
2 - D segment
3 - C segment
4 - Decimal Point segment
5 - B segment
6 - A segment
7 - A & B & Decimal Point (common anode)

--- By default, all functions turn the Decimal Point OFF ---
*/
const uint8_t SEG_A = 0;
const uint8_t SEG_B = 1;
const uint8_t SEG_C = 2;
const uint8_t SEG_D = 3;
const uint8_t SEG_DP = 4;

const uint8_t SEGMENTS[5] = { SEG_A, SEG_B, SEG_C, SEG_D, SEG_DP };

void setup() {
  pinMode(SEG_A, OUTPUT);
  pinMode(SEG_B, OUTPUT);
  pinMode(SEG_C, OUTPUT);
  pinMode(SEG_D, OUTPUT);
  pinMode(SEG_DP, OUTPUT);
  clearDisplay();
}

void loop() {
  showPlusOne();
}

void showOne() {
  displayPattern(0b00111);
}

void showPlusOne() {
  displayPattern(0b01111);
}

void showMinusOne() {
  displayPattern(0b00111);
}

void showPlus() {
  displayPattern(0b01100);
}

void showMinus() {
  displayPattern(0b00100);
}

void clearDisplay() {
  displayPattern(0b00000);
}

void displayPattern(uint8_t p) {
  digitalWrite(SEG_A, (p & (1 << 0)) ? LOW : HIGH);
  digitalWrite(SEG_B, (p & (1 << 1)) ? LOW : HIGH);
  digitalWrite(SEG_C, (p & (1 << 2)) ? LOW : HIGH);
  digitalWrite(SEG_D, (p & (1 << 3)) ? LOW : HIGH);
  digitalWrite(SEG_DP, (p & (1 << 4)) ? LOW : HIGH);
}