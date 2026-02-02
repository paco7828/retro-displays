// Pins
const uint8_t SER = 0;
const uint8_t RCLK = 1;
const uint8_t SRCLK = 2;

void setup() {
  pinMode(SER, OUTPUT);
  pinMode(RCLK, OUTPUT);
  pinMode(SRCLK, OUTPUT);
}

void loop() {
  shiftOut595(0b0000000000000000);
}

void displayDigit(uint8_t number, uint8_t digitNum) {
  shiftOut595(digitPatterns[number]);
}

void shiftOut595(uint8_t data) {
  digitalWrite(RCLK, LOW);
  for (int i = 7; i >= 0; i--) {
    digitalWrite(SRCLK, LOW);
    digitalWrite(SER, (data >> i) & 1);
    digitalWrite(SRCLK, HIGH);
  }
  digitalWrite(RCLK, HIGH);
}
