constexpr byte SEGMENT_PINS[8] = {
  0,  // A
  1,  // B
  2,  // C
  3,  // D
  4,  // E
  5,  // F
  6,  // G
  7,  // DP (Decimal Point)
};

// Common Cathode: 0 = OFF, 1 = ON
// Decimal point off
constexpr byte NUMBERS[10][8] = {
  { 1, 1, 1, 1, 1, 1, 0, 0 },  // 0 -> A, B, C, D, E, F
  { 0, 1, 1, 0, 0, 0, 0, 0 },  // 1 -> B, C
  { 1, 1, 0, 1, 1, 0, 1, 0 },  // 2 -> A, B, D, E, G
  { 1, 1, 1, 1, 0, 0, 1, 0 },  // 3 -> A, B, C, D, G
  { 0, 1, 1, 0, 0, 1, 1, 0 },  // 4 -> B, C, F, G
  { 1, 0, 1, 1, 0, 1, 1, 0 },  // 5 -> A, C, D, F, G
  { 1, 0, 1, 1, 1, 1, 1, 0 },  // 6 -> A, C, D, E, F, G
  { 1, 1, 1, 0, 0, 0, 0, 0 },  // 7 -> A, B, C
  { 1, 1, 1, 1, 1, 1, 1, 0 },  // 8 -> A, B, C, D, E, F, G
  { 1, 1, 1, 1, 0, 1, 1, 0 }   // 9 -> A, B, C, D, F, G
};

void setup() {
  // Set segment pins as outputs
  for (int i = 0; i < sizeof(SEGMENT_PINS) / sizeof(SEGMENT_PINS[0]); i++) {
    pinMode(SEGMENT_PINS[i], OUTPUT);
  }

  // Turn display off
  displayOff();
}

void loop() {
  // Show numbers from 0-9
  for (int i = 0; i < 10; i++) {
    showNumber(i);
    delay(500);
  }
}

void showNumber(byte number) {
  for (int i = 0; i < sizeof(NUMBERS[0]) / sizeof(NUMBERS[0][0]); i++) {
    digitalWrite(SEGMENT_PINS[i], NUMBERS[number][i]);
  }
}

void displayOff() {
  for (int i = 0; i < sizeof(SEGMENT_PINS) / sizeof(SEGMENT_PINS[0]); i++) {
    digitalWrite(SEGMENT_PINS[i], LOW);
  }
}