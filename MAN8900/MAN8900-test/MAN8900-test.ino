// Set if display is common anode or cathode
#define COMMON_ANODE true

// Pin mapping for segments
const byte segmentPins[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
// Index: DP=0, A=1, B=2, C=3, D=4, E=5, F=6, G=7

// Variable to store number of segments
const byte segmentsCount = sizeof(segmentPins) / sizeof(segmentPins[0]);

// Common Anode: 0 = ON, 1 = OFF
byte COM_ANODE_DIGITS[10][8] = {
  // DP, A,  B,  C,  D,  E,  F,  G
  { 1, 0, 0, 0, 0, 0, 0, 1 },  // 0
  { 0, 1, 0, 0, 1, 1, 1, 1 },  // 1
  { 1, 0, 0, 1, 0, 0, 1, 0 },  // 2
  { 0, 0, 0, 0, 0, 1, 1, 0 },  // 3
  { 1, 1, 0, 0, 1, 1, 0, 0 },  // 4
  { 0, 0, 1, 0, 0, 1, 0, 0 },  // 5
  { 1, 0, 1, 0, 0, 0, 0, 0 },  // 6
  { 0, 0, 0, 0, 1, 1, 1, 1 },  // 7
  { 1, 0, 0, 0, 0, 0, 0, 0 },  // 8
  { 0, 0, 0, 0, 0, 1, 0, 0 }   // 9
};

// Common Cathode: 0 = OFF, 1 = ON
byte COM_CATHODE_DIGITS[10][8] = {};

void setup() {
  // Set pinmode for all segments
  for (byte i = 0; i < sizeof(segmentPins) / sizeof(segmentPins[0]); i++) {
    pinMode(segmentPins[i], OUTPUT);
  }

  // Fill common cathode digits with reversed numbers from common anode digits
  for (byte i = 0; i < sizeof(COM_ANODE_DIGITS) / sizeof(COM_ANODE_DIGITS[0]); i++) {
    for (byte j = 0; j < sizeof(COM_ANODE_DIGITS[i]) / sizeof(COM_ANODE_DIGITS[i][0]); j++) {
      byte currDigit = COM_ANODE_DIGITS[i][j] ? 0 : 1;
      COM_CATHODE_DIGITS[i][j] = currDigit;
    }
  };
}

void loop() {
  // All segments off
  turnOffSegments();

  // Test segments one by one
  testSegments();

  // Show all possible numbers
  for (byte num = 0; num < 10; num++) {
    displayDigit(num);
    delay(500);
  }
}

// Function to display a digit
void displayDigit(byte num) {
  for (byte seg = 0; seg < 8; seg++) {
    digitalWrite(segmentPins[seg], COMMON_ANODE ? COM_ANODE_DIGITS[num][seg] : COM_CATHODE_DIGITS[num][seg]);
  }
}

// Function to turn off all segments
void turnOffSegments() {
  for (byte i = 0; i < sizeof(segmentPins) / sizeof(segmentPins[0]); i++) {
    digitalWrite(segmentPins[i], COMMON_ANODE ? HIGH : LOW);
  }
}

// Function to light up all segments one by one
void testSegments() {
  for (byte i = 0; i < sizeof(segmentPins) / sizeof(segmentPins[0]); i++) {
    digitalWrite(segmentPins[i], COMMON_ANODE ? LOW : HIGH);
    delay(200);
    digitalWrite(segmentPins[i], COMMON_ANODE ? HIGH : LOW);
  }
}
