/*
Arduino Uno -> 3015F Minitron

+5V -> Pin 2  (Common)
+5V -> Pin 5  (Common)
+5V -> Pin 10 (Common)
+5V -> Pin 12 (Common)
+5V -> Pin 13 (Common)

GND -> GND

Digital 2 -> Pin 15 (A)
Digital 3 -> Pin 14 (B)
Digital 4 -> Pin 11 (C)
Digital 5 -> Pin 7  (D)
Digital 6 -> Pin 6  (E)
Digital 7 -> Pin 3  (F)
Digital 8 -> Pin 4  (G)
Digital 9 -> Pin 9  (Decimal point)

NC -> Pin 1, 8, 16
*/

const int seg[] = { 9, 3, 4, 5, 6, 7, 8, 10 };  // A,B,C,D,E,F,G,DP
const int segments = sizeof(seg) / sizeof(seg[0]);
const int delayValue = 120;

// A,B,C,D,E,F,G
const byte digits[10] = {
  0b0111111,  // 0
  0b0000110,  // 1
  0b1011011,  // 2
  0b1001111,  // 3
  0b1100110,  // 4
  0b1101101,  // 5
  0b1111101,  // 6
  0b0000111,  // 7
  0b1111111,  // 8
  0b1101111   // 9
};

void allOff() {
  for (int i = 0; i < segments; i++) {
    digitalWrite(seg[i], HIGH);
  }
}

void showDigit(int d) {
  for (int i = 0; i < 7; i++) {
    if (digits[d] & (1 << i))
      digitalWrite(seg[i], LOW);
    else
      digitalWrite(seg[i], HIGH);
  }
  digitalWrite(seg[7], HIGH);
}

void setup() {
  for (int i = 0; i < segments; i++) {
    pinMode(seg[i], OUTPUT);
  }
  allOff();
}

void loop() {

  for (int i = 0; i < segments; i++) {
    allOff();
    digitalWrite(seg[i], LOW);
    delay(delayValue);
  }

  for (int i = 0; i < segments; i++) {
    digitalWrite(seg[i], LOW);
    delay(delayValue);
  }

  for (int i = 0; i < segments; i++) {
    digitalWrite(seg[i], HIGH);
    delay(delayValue);
  }

  for (int i = 0; i < 10; i++) {
    showDigit(i);
    delay(300);
  }

  for (int i = 9; i >= 0; i--) {
    showDigit(i);
    delay(300);
  }
}
