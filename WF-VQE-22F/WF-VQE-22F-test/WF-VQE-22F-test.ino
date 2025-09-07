/*
A1 -> 0
B1 -> 1
C1 -> 2
D1 -> 3
E1 -> 4
F1 -> Not used in this test (decimal point)

A2 -> 5
B2 -> 6
C2 -> 7
D2 -> 8
E2 -> 9
F2 -> 10
G2 -> 20
H2 -> Not used in this test (decimal point)
*/

// First digit pins
constexpr byte FIRST_DIGIT_PINS[5] = { 0, 1, 2, 3, 4 };

// Second digit pins
constexpr byte SECOND_DIGIT_PINS[7] = { 5, 6, 7, 8, 9, 10, 20 };

// Common Anode: 0 = ON, 1 = OFF
constexpr byte FIRST_SYMBOLS[5][5] = {
  // A, B, C, D, E, F
  { 0, 0, 1, 1, 1 },  // 1 -> A, B
  { 1, 1, 0, 0, 0 },  // + -> C, D, E
  { 1, 1, 0, 1, 1 },  // - -> C
  { 0, 0, 0, 0, 0 },  // +1 -> A, B, C, D, E
  { 0, 0, 0, 1, 1 },  // -1 -> A, B, C
};

// Common Anode: 0 = ON, 1 = OFF
constexpr byte SECOND_NUMBERS[10][7] = {
  // A, B, C, D, E, F, G
  { 0, 0, 0, 0, 0, 0, 1 },  // 0 -> A, B, C, D, E, F
  { 1, 0, 0, 1, 1, 1, 1 },  // 1 -> B, C
  { 0, 0, 1, 0, 0, 1, 0 },  // 2 -> A, B, D, E, G
  { 0, 0, 0, 0, 1, 1, 0 },  // 3 -> A, B, C, D, G
  { 1, 0, 0, 1, 1, 0, 0 },  // 4 -> B, C, F, G
  { 0, 1, 0, 0, 1, 0, 0 },  // 5 -> A, C, D, F, G
  { 0, 1, 0, 0, 0, 0, 0 },  // 6 -> A, C, D, E, F, G
  { 0, 0, 0, 1, 1, 1, 1 },  // 7 -> A, B, C
  { 0, 0, 0, 0, 0, 0, 0 },  // 8 -> A, B, C, D, E, F, G
  { 0, 0, 0, 0, 1, 0, 0 },  // 9 -> A, B, C, D, F, G
};

void setup() {
  // Set pins as output
  // First digit pins
  for (int i = 0; i < sizeof(FIRST_DIGIT_PINS) / sizeof(FIRST_DIGIT_PINS[0]); i++) {
    pinMode(FIRST_DIGIT_PINS[i], OUTPUT);
  }

  // Second digit pins
  for (int i = 0; i < sizeof(SECOND_DIGIT_PINS) / sizeof(SECOND_DIGIT_PINS[0]); i++) {
    pinMode(SECOND_DIGIT_PINS[i], OUTPUT);
  }

  // Turn display off
  displayOff();
}

void loop() {
  delay(1000);
  showFirstSymbol(3);
  showSecondNumber(8);
  delay(1000);
  displayOff();
}

// Function to display symbols on first digit
void showFirstSymbol(byte symbolIndex) {
  for (int i = 0; i < sizeof(FIRST_SYMBOLS[symbolIndex]) / sizeof(FIRST_SYMBOLS[symbolIndex][0]); i++) {
    digitalWrite(FIRST_DIGIT_PINS[i], FIRST_SYMBOLS[symbolIndex][i]);
  }
}

// Function to display numbers on second digit
void showSecondNumber(byte number) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(SECOND_DIGIT_PINS[i], SECOND_NUMBERS[number][i]);
  }
}


void displayOff() {
  // First digit pins
  for (int i = 0; i < sizeof(FIRST_DIGIT_PINS) / sizeof(FIRST_DIGIT_PINS[0]); i++) {
    digitalWrite(FIRST_DIGIT_PINS[i], HIGH);
  }

  // Second digit pins
  for (int i = 0; i < sizeof(SECOND_DIGIT_PINS) / sizeof(SECOND_DIGIT_PINS[0]); i++) {
    digitalWrite(SECOND_DIGIT_PINS[i], HIGH);
  }
}