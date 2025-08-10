/*
ESP32 C3 SUPERMINI -> HCMS-2915
5V        -> Pin 3, Pin 10 (V_LED)
3.3V      -> Pin 22 (V_LOGIC), Pin 21 (SEL - tied high for internal oscillator)
GND       -> Pin 7 (GND_LED), Pin 20 (GND_LOGIC)
GPIO4     -> Pin 14 (DATA IN)
GPIO5     -> Pin 17 (CLOCK)
GPIO6     -> Pin 18 (CHIP ENABLE)
GPIO7     -> Pin 15 (REGISTER SELECT)
GPIO8     -> Pin 24 (RESET)
GPIO9     -> Pin 19 (BLANK)
*/

// Pin definitions for ESP32 C3 SUPERMINI
#define DATA_IN_PIN 4
#define CLOCK_PIN   5
#define CE_PIN      6
#define RS_PIN      7
#define RESET_PIN   8
#define BLANK_PIN   9

// Display constants
#define CHARS_PER_DISPLAY 8
#define DOTS_PER_CHAR     40 // 5 cols × 8 rows
#define TOTAL_DOTS        (CHARS_PER_DISPLAY * DOTS_PER_CHAR) // 320 bits
#define TOTAL_BYTES       (TOTAL_DOTS / 8) // 40 bytes

// Control register constants
#define CONTROL_WORD_0 0x00
#define CONTROL_WORD_1 0x80

// Brightness levels
#define BRIGHTNESS_0   0x40
#define BRIGHTNESS_25  0x45
#define BRIGHTNESS_50  0x4A
#define BRIGHTNESS_75  0x4E
#define BRIGHTNESS_100 0x4F

// --- Pixel buffer ---
uint8_t dotData[TOTAL_BYTES];

// --- Utility: clear all pixels ---
void clearBuffer() {
  memset(dotData, 0, TOTAL_BYTES);
}

// --- Utility: set or clear a single pixel ---
void setPixel(int dotIndex, bool on) {
  int byteIndex = dotIndex / 8;
  int bitPos = 7 - (dotIndex % 8); // MSB first
  if (on) dotData[byteIndex] |= (1 << bitPos);
  else    dotData[byteIndex] &= ~(1 << bitPos);
}

// --- Send control register ---
void writeControlRegister(uint8_t controlWord) {
  digitalWrite(RS_PIN, HIGH);  // Control register
  digitalWrite(CE_PIN, LOW);

  for (int i = 7; i >= 0; i--) {
    digitalWrite(DATA_IN_PIN, (controlWord >> i) & 1);
    digitalWrite(CLOCK_PIN, HIGH);
    delayMicroseconds(1);
    digitalWrite(CLOCK_PIN, LOW);
    delayMicroseconds(1);
  }

  digitalWrite(CE_PIN, HIGH);
  digitalWrite(RS_PIN, LOW); // Back to dot register
}

// --- Send dot register ---
void writeDotRegister(uint8_t *data, int length) {
  digitalWrite(RS_PIN, LOW); // Dot register
  digitalWrite(CE_PIN, LOW);

  // Send MSB first, starting from last byte (rightmost char)
  for (int i = length - 1; i >= 0; i--) {
    for (int b = 7; b >= 0; b--) {
      digitalWrite(DATA_IN_PIN, (data[i] >> b) & 1);
      digitalWrite(CLOCK_PIN, HIGH);
      delayMicroseconds(1);
      digitalWrite(CLOCK_PIN, LOW);
      delayMicroseconds(1);
    }
  }

  digitalWrite(CE_PIN, HIGH);
}

// --- Brightness setting ---
void setBrightness(int level) {
  uint8_t brightness;
  switch (level) {
    case 0: brightness = BRIGHTNESS_0; break;
    case 1: brightness = BRIGHTNESS_25; break;
    case 2: brightness = BRIGHTNESS_50; break;
    case 3: brightness = BRIGHTNESS_75; break;
    case 4: brightness = BRIGHTNESS_100; break;
    default: brightness = BRIGHTNESS_50; break;
  }
  writeControlRegister(brightness);
}

// --- Display initialization ---
void initDisplay() {
  // Reset
  digitalWrite(RESET_PIN, LOW);
  delay(10);
  digitalWrite(RESET_PIN, HIGH);
  delay(10);

  // Clear
  clearBuffer();
  writeDotRegister(dotData, TOTAL_BYTES);

  // Brightness
  setBrightness(2);

  // Serial mode
  writeControlRegister(CONTROL_WORD_1 | 0x00);
}

// --- Tests ---
void rowByRowScanTest() {
  for (int row = 1; row <= 7; row++) {
    for (int charIndex = 0; charIndex < CHARS_PER_DISPLAY; charIndex++) {
      for (int col = 0; col < 5; col++) {
        clearBuffer();
        int dotIndex = charIndex * DOTS_PER_CHAR + col * 8 + row;
        setPixel(dotIndex, true);
        writeDotRegister(dotData, TOTAL_BYTES);
        delay(30);
      }
    }
  }
}

void columnByColumnScanTest() {
  for (int charIndex = 0; charIndex < CHARS_PER_DISPLAY; charIndex++) {
    for (int col = 0; col < 5; col++) {
      for (int row = 1; row <= 7; row++) {
        clearBuffer();
        int dotIndex = charIndex * DOTS_PER_CHAR + col * 8 + row;
        setPixel(dotIndex, true);
        writeDotRegister(dotData, TOTAL_BYTES);
        delay(30);
      }
    }
  }
}

void allPixelsOn() {
  memset(dotData, 0xFF, TOTAL_BYTES);
  writeDotRegister(dotData, TOTAL_BYTES);
}

void clearDisplay() {
  clearBuffer();
  writeDotRegister(dotData, TOTAL_BYTES);
}

void blankDisplay(bool blank) {
  digitalWrite(BLANK_PIN, blank ? HIGH : LOW);
}

// --- Arduino setup ---
void setup() {
  pinMode(DATA_IN_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(CE_PIN, OUTPUT);
  pinMode(RS_PIN, OUTPUT);
  pinMode(RESET_PIN, OUTPUT);
  pinMode(BLANK_PIN, OUTPUT);

  digitalWrite(DATA_IN_PIN, LOW);
  digitalWrite(CLOCK_PIN, LOW);
  digitalWrite(CE_PIN, HIGH);
  digitalWrite(RS_PIN, LOW);
  digitalWrite(RESET_PIN, HIGH);
  digitalWrite(BLANK_PIN, LOW);

  initDisplay();
}

// --- Arduino loop ---
void loop() {
  rowByRowScanTest();
  delay(500);

  columnByColumnScanTest();
  delay(500);

  allPixelsOn();
  delay(1000);
  clearDisplay();
  delay(500);
}
