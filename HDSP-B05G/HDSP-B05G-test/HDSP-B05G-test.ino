#define SEG_A 0
#define SEG_B 1
#define SEG_C 2
#define SEG_D 3
#define SEG_E 4
#define SEG_F 5
#define SEG_G 6

#define DIGIT1 7
#define DIGIT2 8
#define DIGIT3 9
#define DIGIT4 10

const int segmentPins[7] = { SEG_A, SEG_B, SEG_C, SEG_D, SEG_E, SEG_F, SEG_G };
const int digitPins[4] = { DIGIT1, DIGIT2, DIGIT3, DIGIT4 };

// Segment map for numbers 0–9
const byte numbers[10][7] = {
  { 1, 1, 1, 1, 1, 1, 0 },  // 0
  { 0, 1, 1, 0, 0, 0, 0 },  // 1
  { 1, 1, 0, 1, 1, 0, 1 },  // 2
  { 1, 1, 1, 1, 0, 0, 1 },  // 3
  { 0, 1, 1, 0, 0, 1, 1 },  // 4
  { 1, 0, 1, 1, 0, 1, 1 },  // 5
  { 1, 0, 1, 1, 1, 1, 1 },  // 6
  { 1, 1, 1, 0, 0, 0, 0 },  // 7
  { 1, 1, 1, 1, 1, 1, 1 },  // 8
  { 1, 1, 1, 1, 0, 1, 1 }   // 9
};

int currentNumber = 1;
unsigned long lastUpdate = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting 7-segment display...");

  // Initialize segment pins with explicit mode setting
  for (int i = 0; i < 7; i++) {
    pinMode(segmentPins[i], OUTPUT);
    digitalWrite(segmentPins[i], LOW);  // Start with segments off
  }

  // Initialize digit pins
  for (int i = 0; i < 4; i++) {
    pinMode(digitPins[i], OUTPUT);
    digitalWrite(digitPins[i], HIGH);  // Common cathode - HIGH disables digit
  }

  // Brief delay to ensure pins are properly initialized
  delay(100);

  // Test first digit specifically
  testFirstDigit();
}

void loop() {
  // Change number every second
  if (millis() - lastUpdate > 1000) {
    currentNumber++;
    if (currentNumber > 9) currentNumber = 0;
    lastUpdate = millis();
    Serial.print("Displaying: ");
    Serial.println(currentNumber);
  }

  // Improved multiplexing with proper timing
  for (int d = 0; d < 4; d++) {
    // Clear all digits first
    for (int i = 0; i < 4; i++) {
      digitalWrite(digitPins[i], HIGH);
    }

    // Set segments for current number
    for (int i = 0; i < 7; i++) {
      digitalWrite(segmentPins[i], numbers[currentNumber][i] ? HIGH : LOW);
    }

    // Enable current digit
    digitalWrite(digitPins[d], LOW);

    // Hold for display persistence
    delay(4);
  }
}

void showDigit(int n, int d) {
  // First clear all digits
  clearDisplay();

  // Set segment pattern
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentPins[i], numbers[n][i] ? HIGH : LOW);
  }

  // Enable the specific digit (LOW enables for common cathode)
  digitalWrite(digitPins[d], LOW);
}

void clearDisplay() {
  // Disable all digits
  for (int d = 0; d < 4; d++) {
    digitalWrite(digitPins[d], HIGH);
  }
}

// Test function specifically for the first digit
void testFirstDigit() {
  Serial.println("Testing first digit segments...");

  // Disable all digits
  for (int i = 0; i < 4; i++) {
    digitalWrite(digitPins[i], HIGH);
  }

  // Test each segment on first digit only
  for (int seg = 0; seg < 7; seg++) {
    // Clear all segments
    for (int i = 0; i < 7; i++) {
      digitalWrite(segmentPins[i], LOW);
    }

    // Turn on one segment
    digitalWrite(segmentPins[seg], HIGH);

    // Enable first digit only
    digitalWrite(DIGIT1, LOW);

    Serial.print("Segment ");
    Serial.print((char)('A' + seg));
    Serial.println(" ON");

    delay(500);
  }

  // Clear display
  for (int i = 0; i < 4; i++) {
    digitalWrite(digitPins[i], HIGH);
  }
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentPins[i], LOW);
  }

  Serial.println("First digit test complete");
  delay(1000);
}