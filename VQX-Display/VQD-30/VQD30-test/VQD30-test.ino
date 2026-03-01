#define SER   0
#define RCLK  1
#define SCLK  2

const uint8_t SEGMENT_PINS[9] = {3,4,5,21,7,8,9,10,20};

const uint8_t NUMBERS[10] = {
  0b00111111, // 0
  0b00000110, // 1
  0b01011011, // 2
  0b01001111, // 3
  0b01100110, // 4
  0b01101101, // 5
  0b01111101, // 6
  0b00000111, // 7
  0b01111111, // 8
  0b01101111, // 9
};

#define SEG_A  0b00000001
#define SEG_B  0b00000010
#define SEG_C  0b00000100
#define SEG_D  0b00001000
#define SEG_E  0b00010000
#define SEG_F  0b00100000
#define SEG_G  0b01000000
#define SEG_DP 0b10000000

uint8_t buffer[9] = {0};

void latch(uint8_t adat) {
  digitalWrite(RCLK, LOW);
  shiftOut(SER, SCLK, MSBFIRST, adat);
  digitalWrite(RCLK, HIGH);
}

void refresh() {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) digitalWrite(SEGMENT_PINS[j], HIGH);
    latch(buffer[i]);
    digitalWrite(SEGMENT_PINS[i], LOW);
    delayMicroseconds(1500);
    latch(0);
  }
}

void refreshFor(uint32_t ms) {
  uint32_t start = millis();
  while (millis() - start < ms) refresh();
}

void displayNumber(int numValue) {
  for (int i = 8; i >= 0; i--) {
    if (numValue == 0 && i == 8) {
      buffer[i] = NUMBERS[0];
    } else if (numValue > 0) {
      buffer[i] = NUMBERS[numValue % 10];
      numValue /= 10;
    } else {
      buffer[i] = 0x00;
    }
  }
}

void animKnstophtRider(int repeats) {
  for (int k = 0; k < repeats; k++) {
    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) buffer[j] = 0;
      buffer[i] = SEG_G;
      if (i > 0) buffer[i-1] = SEG_G * 0;
      refreshFor(60);
    }
    for (int i = 7; i >= 1; i--) {
      for (int j = 0; j < 9; j++) buffer[j] = 0;
      buffer[i] = SEG_G;
      refreshFor(60);
    }
  }
}

void roundAnimation(int repeats) {
  uint8_t order[] = {SEG_A, SEG_B, SEG_C, SEG_D, SEG_E, SEG_F, SEG_G};
  for (int k = 0; k < repeats; k++) {
    uint8_t active = 0;
    for (int s = 0; s < 7; s++) {
      active |= order[s];
      for (int i = 0; i < 9; i++) buffer[i] = active;
      refreshFor(80);
    }
    for (int s = 6; s >= 0; s--) {
      active &= ~order[s];
      for (int i = 0; i < 9; i++) buffer[i] = active;
      refreshFor(80);
    }
  }
}

void rotateAnimation(int repeats) {
  uint8_t usedSegments[] = {SEG_A, SEG_B, SEG_C, SEG_D, SEG_E, SEG_F};
  for (int k = 0; k < repeats * 6; k++) {
    for (int i = 0; i < 9; i++) buffer[i] = usedSegments[k % 6];
    refreshFor(60);
  }
}

void animSzamlalo(int start, int stop, int steps) {
  for (int n = start; n <= stop; n += steps) {
    displayNumber(n);
    refreshFor(50);
  }
}

void blinkingAnimation(int repeats) {
  for (int k = 0; k < repeats; k++) {
    for (int i = 0; i < 9; i++) buffer[i] = 0xFF;
    refreshFor(150);
    for (int i = 0; i < 9; i++) buffer[i] = 0x00;
    refreshFor(150);
  }
}

void cascadeAnimation() {
  for (int i = 0; i < 9; i++) buffer[i] = 0;
  for (int i = 0; i < 9; i++) {
    buffer[i] = NUMBERS[8];
    refreshFor(80);
  }
  for (int i = 0; i < 9; i++) {
    buffer[i] = 0;
    refreshFor(80);
  }
}

void setup() {
  pinMode(SER,  OUTPUT);
  pinMode(RCLK, OUTPUT);
  pinMode(SCLK, OUTPUT);
  for (int i = 0; i < 9; i++) {
    pinMode(SEGMENT_PINS[i], OUTPUT);
    digitalWrite(SEGMENT_PINS[i], HIGH);
  }
  latch(0);
}

void loop() {
  animKnstophtRider(3);
  rotateAnimation(4);
  roundAnimation(2);
  cascadeAnimation();
  blinkingAnimation(4);
  animSzamlalo(0, 999999999, 1234567);
  
  displayNumber(123456789);
  refreshFor(3000);
}