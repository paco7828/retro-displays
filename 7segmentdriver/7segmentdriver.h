class SevenSegmentDriver {
private:
  uint8_t segmentPins[8];
  const uint8_t numberOfSegments = 8;  // dp included
  bool commonCathode;

  const uint8_t digits[10] = {
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

  const uint8_t letters[26] = {
    0b1110111,  // A  - a,b,c,e,f,g
    0b1111100,  // b  - c,d,e,f,g
    0b0111001,  // C  - a,d,e,f
    0b1011110,  // d  - b,c,d,e,g
    0b1111001,  // E  - a,d,e,f,g
    0b1110001,  // F  - a,e,f,g
    0b1111101,  // G  - a,c,d,e,f,g
    0b1110100,  // h  - c,e,f,g
    0b0000100,  // i  - c
    0b0011110,  // J  - b,c,d,e
    0b1110110,  // k  - b,c,e,f,g
    0b0111000,  // L  - d,e,f
    0b0110110,  // m  - b,c,e,f
    0b1010100,  // n  - c,e,g
    0b1011100,  // o  - c,d,e,g
    0b1110011,  // P  - a,b,e,f,g
    0b1100111,  // q  - a,b,c,f,g
    0b1010000,  // r  - e,g
    0b1101101,  // S  - a,c,d,f,g
    0b1111000,  // t  - d,e,f,g
    0b0111110,  // U  - b,c,d,e,f
    0b0011100,  // v  - c,d,e
    0b0011110,  // w  - b,c,d,e
    0b1110110,  // X  - b,c,e,f,g
    0b1101110,  // Y  - b,c,d,f,g
    0b1011011   // Z  - a,b,d,e,g
  };

  static const uint8_t CODE_UNDERSCORE = 0b0001000;  // d
  static const uint8_t CODE_DASH = 0b1000000;        // g
  static const uint8_t CODE_EQUALS = 0b1001000;      // d,g
  static const uint8_t CODE_DEGREE = 0b1100011;      // a,b,f,g

  // Animations frames
  static constexpr uint8_t circularLoadingFrames[] = { 1, 1, 1, 1, 1, 1, 0, 0 };
  static constexpr uint8_t snakeLoadingFrames[] = { 0, 5, 6, 2, 3, 4, 6, 1 };
  static const uint8_t snakeLoadingFramesLength = sizeof(snakeLoadingFrames) / sizeof(snakeLoadingFrames[0]);

  void segmentOn(uint8_t segmentPin) {
    digitalWrite(segmentPin, commonCathode ? HIGH : LOW);
  }

  void segmentOff(uint8_t segmentPin) {
    digitalWrite(segmentPin, commonCathode ? LOW : HIGH);
  }

  void testSequence() {
    loadSegments();
    deloadSegments();
    countFromTo(0, 9, 300);
    countFromTo(9, 0, 300);
  }

public:
  void begin(const uint8_t pins[8], bool isCommonCathode = false) {
    memcpy(this->segmentPins, pins, numberOfSegments * sizeof(uint8_t));
    this->commonCathode = isCommonCathode;
    for (uint8_t i = 0; i < numberOfSegments; i++) {
      pinMode(this->segmentPins[i], OUTPUT);
    }
    allOff();
    this->testSequence();
    allOff();
  }

  void displayCode(uint8_t code, bool decimalActive = false, int delayBetween = 0) {
    for (uint8_t i = 0; i < 7; i++) {
      bool on = code & (1 << i);
      if (on) {
        this->segmentOn(segmentPins[i]);
      } else {
        this->segmentOff(segmentPins[i]);
      }
      delay(delayBetween);
    }
    if (decimalActive) {
      this->segmentOn(segmentPins[7]);
    } else {
      this->segmentOff(segmentPins[7]);
    }
  }

  void displayNumber(uint8_t number, bool decimalActive = false, int delayBetween = 0) {
    if (number > 9) {
      return;
    }
    displayCode(digits[number], decimalActive, delayBetween);
  }

  // --- Special characters ---

  void showUnderscore(bool decimalActive = false) {
    displayCode(CODE_UNDERSCORE, decimalActive);
  }

  void showDash(bool decimalActive = false) {
    displayCode(CODE_DASH, decimalActive);
  }

  void showEquals(bool decimalActive = false) {
    displayCode(CODE_EQUALS, decimalActive);
  }

  void showDegree(bool decimalActive = false) {
    displayCode(CODE_DEGREE, decimalActive);
  }

  // --- Letters ---

  bool showLetter(char letter, bool decimalActive = false) {
    char upper = (letter >= 'a' && letter <= 'z') ? letter - 32 : letter;
    if (upper >= 'A' && upper <= 'Z') {
      displayCode(letters[upper - 'A'], decimalActive);
      return true;
    }
    // Unsupported char
    allOff();
    return false;
  }

  void allOff() {
    for (int i = 0; i < numberOfSegments; i++) {
      this->segmentOff(segmentPins[i]);
    }
  }

  void allOn() {
    for (int i = 0; i < numberOfSegments; i++) {
      this->segmentOn(segmentPins[i]);
    }
  }

  void decimalOn() {
    segmentOn(this->segmentPins[7]);
  }

  void decimalOff() {
    segmentOff(this->segmentPins[7]);
  }

  // --- Animations ---

  void snakeLoading(int delayBetween = 100) {
    for (uint8_t i = 0; i < snakeLoadingFramesLength; i++) {
      allOff();
      this->segmentOn(segmentPins[snakeLoadingFrames[i]]);
      delay(delayBetween);
    }
  }

  void colsRowsLoading(int delayBetween = 250) {
    // a, d, g
    allOff();
    this->segmentOn(segmentPins[0]);
    this->segmentOn(segmentPins[3]);
    this->segmentOn(segmentPins[6]);
    delay(delayBetween);

    // b, c, e, f
    allOff();
    this->segmentOn(segmentPins[1]);
    this->segmentOn(segmentPins[2]);
    this->segmentOn(segmentPins[4]);
    this->segmentOn(segmentPins[5]);
    delay(delayBetween);
  }

  void diagonalSwitchLoading(int delayBetween = 250) {
    // a, b, d, e
    allOff();
    this->segmentOn(segmentPins[0]);
    this->segmentOn(segmentPins[1]);
    this->segmentOn(segmentPins[3]);
    this->segmentOn(segmentPins[4]);
    delay(delayBetween);

    // a, c, d, f
    allOff();
    this->segmentOn(segmentPins[0]);
    this->segmentOn(segmentPins[2]);
    this->segmentOn(segmentPins[3]);
    this->segmentOn(segmentPins[5]);
    delay(delayBetween);
  }

  void topCircularLoading(int delayBetween = 150) {
    const uint8_t topOrder[] = { 0, 1, 6, 5 };  // a, b, g, f
    for (uint8_t i = 0; i < 4; i++) {
      allOff();
      this->segmentOn(segmentPins[topOrder[i]]);
      delay(delayBetween);
    }
  }

  void bottomCircularLoading(int delayBetween = 150) {
    const uint8_t bottomOrder[] = { 2, 3, 4, 6 };  // c, d, e, g
    for (uint8_t i = 0; i < 4; i++) {
      allOff();
      this->segmentOn(segmentPins[bottomOrder[i]]);
      delay(delayBetween);
    }
  }

  void circularLoading(int delayBetween = 100) {
    for (uint8_t i = 0; i < numberOfSegments; i++) {
      allOff();
      if (circularLoadingFrames[i]) {
        this->segmentOn(segmentPins[i]);
        delay(delayBetween);
      }
    }
  }

  void loadSegments(int loadDelay = 150) {
    allOff();
    for (uint8_t i = 0; i < numberOfSegments; i++) {
      this->segmentOn(segmentPins[i]);
      delay(loadDelay);
    }
  }

  void deloadSegments(int deloadDelay = 150) {
    for (uint8_t i = 0; i < numberOfSegments; i++) {
      this->segmentOff(segmentPins[i]);
      delay(deloadDelay);
    }
  }

  void countFromTo(uint8_t fromNumber, uint8_t toNumber, int delayBetween = 500) {
    if (fromNumber < toNumber) {
      for (uint8_t i = fromNumber; i <= toNumber; i++) {
        displayNumber(i);
        delay(delayBetween);
      }
    } else if (fromNumber > toNumber) {
      for (int16_t i = fromNumber; i >= (int16_t)toNumber; i--) {
        displayNumber(i);
        delay(delayBetween);
      }
    } else {
      displayNumber(fromNumber);
    }
  }
};