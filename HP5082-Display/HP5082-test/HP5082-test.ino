/*
ESP32 C3 SUPERMINI -> HP5082

+3.3V -> Pin 3  (Common Anode)
+3.3V -> Pin 14  (Common Anode)

IO0 -> Pin 1 
IO1 -> Pin 13
IO2 -> Pin 10
IO3 -> Pin 8
IO4 -> Pin 7
IO5 -> Pin 2
IO6 -> Pin 11
IO7 -> Pin 6

NC -> Pin 9
*/

const int seg[] = { 0, 1, 2, 3, 4, 5, 6, 7 };  // A,B,C,D,E,F,G,DP
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
