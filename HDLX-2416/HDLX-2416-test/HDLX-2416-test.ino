/*
 * HDLX-2416 Four Character 5x7 Smart Alphanumeric Display Test Code
 * 
 * This code demonstrates all major features of the HDLX-2416 display:
 * - Character display
 * - Brightness control
 * - Blanking
 * - Clear function
 * - Scrolling text
 * - Character set demonstration
 * 
 * Connections (based on provided connection file):
 * HDLX-2416 Pin -> Arduino Pin
 * 1  CE1#  -> GND (always enabled)
 * 2  CE2#  -> GND (always enabled) 
 * 3  CLR#  -> IO0  (Digital Pin 0)
 * 4  CUE   -> NC   (Not connected - cursor disabled)
 * 5  CU#   -> NC   (Not connected - always ASCII mode)
 * 6  WR#   -> IO1  (Digital Pin 1)
 * 7  A1    -> IO3  (Digital Pin 3)
 * 8  A0    -> IO2  (Digital Pin 2)
 * 9  VCC   -> 5V
 * 10 GND   -> GND
 * 11 D0    -> IO4  (Digital Pin 4)
 * 12 D1    -> IO5  (Digital Pin 5)
 * 13 D2    -> IO6  (Digital Pin 6)
 * 14 D3    -> IO7  (Digital Pin 7)
 * 15 D6    -> IO8  (Digital Pin 8)
 * 16 D5    -> IO9  (Digital Pin 9)
 * 17 D4    -> IO10 (Digital Pin 10)
 * 18 BL#   -> IO20 (Digital Pin 20 - or use different pin if needed)
 */

// Pin definitions
#define CLR_PIN 0
#define WR_PIN 1
#define A0_PIN 3
#define A1_PIN 2
#define D0_PIN 4
#define D1_PIN 5
#define D2_PIN 6
#define D3_PIN 7
#define D6_PIN 8
#define D5_PIN 9
#define D4_PIN 10
#define BL_PIN 20  // Adjust if pin 20 not available on your board

// Address definitions for 4-character positions
#define CHAR_POS_0 0  // Rightmost character
#define CHAR_POS_1 1
#define CHAR_POS_2 2
#define CHAR_POS_3 3  // Leftmost character

// Control register address (when CU = 0)
#define CONTROL_REG 0

void setup() {
  Serial.begin(9600);
  Serial.println("HDLX-2416 Display Test Starting...");

  // Initialize all pins as outputs
  pinMode(CLR_PIN, OUTPUT);
  pinMode(WR_PIN, OUTPUT);
  pinMode(A0_PIN, OUTPUT);
  pinMode(A1_PIN, OUTPUT);
  pinMode(D0_PIN, OUTPUT);
  pinMode(D1_PIN, OUTPUT);
  pinMode(D2_PIN, OUTPUT);
  pinMode(D3_PIN, OUTPUT);
  pinMode(D4_PIN, OUTPUT);
  pinMode(D5_PIN, OUTPUT);
  pinMode(D6_PIN, OUTPUT);
  pinMode(BL_PIN, OUTPUT);

  // Set initial states
  digitalWrite(WR_PIN, HIGH);   // Write disabled
  digitalWrite(CLR_PIN, HIGH);  // Clear disabled
  digitalWrite(BL_PIN, HIGH);   // Display enabled (not blanked)

  // Clear display on startup
  clearDisplay();
  delay(500);

  Serial.println("Display initialized!");
}

void loop() {
  // Test sequence
  Serial.println("Starting test sequence...");

  // Test 1: Basic character display
  Serial.println("Test 1: Basic Characters");
  displayText("TEST");
  delay(2000);

  // Test 2: Numbers
  Serial.println("Test 2: Numbers");
  displayText("1234");
  delay(2000);

  // Test 3: Mixed characters
  Serial.println("Test 3: Mixed Characters");
  displayText("A1B2");
  delay(2000);

  // Test 4: Special characters
  Serial.println("Test 4: Special Characters");
  displayText("!@#$");
  delay(2000);

  // Test 5: Brightness control demonstration
  Serial.println("Test 5: Brightness Control");
  displayText("BRIT");
  for (int level = 0; level <= 7; level++) {
    setBrightness(level);
    Serial.print("Brightness level: ");
    Serial.println(level);
    delay(1000);
  }
  setBrightness(0);  // Return to full brightness

  // Test 6: Blanking test
  Serial.println("Test 6: Blanking Test");
  displayText("BLNK");
  for (int i = 0; i < 5; i++) {
    digitalWrite(BL_PIN, LOW);  // Blank display
    delay(300);
    digitalWrite(BL_PIN, HIGH);  // Unblank display
    delay(300);
  }

  // Test 7: Individual character update
  Serial.println("Test 7: Individual Character Update");
  clearDisplay();
  for (int pos = 0; pos < 4; pos++) {
    writeCharacter(pos, 'A' + pos);
    delay(500);
  }
  delay(1000);

  // Test 8: Scrolling text demo
  Serial.println("Test 8: Scrolling Text");
  scrollText("HELLO WORLD! THIS IS A SCROLLING MESSAGE    ");

  // Test 9: Character set demonstration
  Serial.println("Test 9: Character Set Demo");
  demonstrateCharacterSet();

  // Test 10: Clear display
  Serial.println("Test 10: Clear Display");
  clearDisplay();
  delay(2000);

  Serial.println("Test sequence complete. Restarting...\n");
  delay(1000);
}

// Function to write a single character to specified position
void writeCharacter(uint8_t position, char character) {
  // Set address
  digitalWrite(A1_PIN, (position >> 1) & 1);
  digitalWrite(A0_PIN, position & 1);

  // Set data (7-bit ASCII)
  uint8_t ascii = (uint8_t)character;
  digitalWrite(D0_PIN, ascii & 1);
  digitalWrite(D1_PIN, (ascii >> 1) & 1);
  digitalWrite(D2_PIN, (ascii >> 2) & 1);
  digitalWrite(D3_PIN, (ascii >> 3) & 1);
  digitalWrite(D4_PIN, (ascii >> 4) & 1);
  digitalWrite(D5_PIN, (ascii >> 5) & 1);
  digitalWrite(D6_PIN, (ascii >> 6) & 1);

  // Write pulse (minimum 75ns according to datasheet)
  digitalWrite(WR_PIN, LOW);
  delayMicroseconds(1);  // Much longer than minimum for safety
  digitalWrite(WR_PIN, HIGH);
  delayMicroseconds(1);
}

// Function to display a 4-character string (fixed addressing)
void displayText(const char* text) {
  for (int i = 0; i < 4; i++) {
    // Flip position: 0 = leftmost, 3 = rightmost
    int pos = 3 - i;
    if (i < strlen(text)) {
      writeCharacter(pos, text[i]);
    } else {
      writeCharacter(pos, ' ');  // Fill with spaces
    }
  }
}

// Function to clear the entire display
void clearDisplay() {
  digitalWrite(CLR_PIN, LOW);
  delayMicroseconds(20);  // Hold for minimum 10μs
  digitalWrite(CLR_PIN, HIGH);
  delayMicroseconds(2);  // Wait for clear disable time
}

// Function to set brightness (0 = brightest, 7 = dimmest)
// Note: This requires CU pin to be connected and controlled
// For this demo, we'll simulate it by writing to control register
void setBrightness(uint8_t level) {
  // This is a simplified version - actual implementation would need
  // CU pin control to write to control register
  // For demo purposes, we'll use the BL pin for some dimming effect
  if (level > 4) {
    // Simulate dimming with PWM on BL pin for higher levels
    int pwmValue = map(level, 5, 7, 200, 50);
    analogWrite(BL_PIN, pwmValue);
  } else {
    digitalWrite(BL_PIN, HIGH);  // Full brightness for levels 0-4
  }
}

// Function to scroll text across the display
void scrollText(const char* text) {
  int textLen = strlen(text);

  for (int startPos = 0; startPos < textLen; startPos++) {
    char displayBuffer[5] = "    ";  // 4 chars + null terminator

    // Fill display buffer with 4 characters starting at startPos
    for (int i = 0; i < 4; i++) {
      if (startPos + i < textLen) {
        displayBuffer[i] = text[startPos + i];
      } else {
        displayBuffer[i] = ' ';
      }
    }

    displayText(displayBuffer);
    delay(200);  // Scroll speed

    // Break if we've scrolled past the end with spaces
    if (startPos > textLen) break;
  }
}

// Function to demonstrate various characters from the ASCII set
void demonstrateCharacterSet() {
  // Numbers 0-9
  Serial.println("Displaying numbers...");
  for (char c = '0'; c <= '9'; c++) {
    char temp[5];
    sprintf(temp, "%c%c%c%c", c, c, c, c);
    displayText(temp);
    delay(500);
  }

  // Letters A-Z
  Serial.println("Displaying uppercase letters...");
  for (char c = 'A'; c <= 'Z'; c += 4) {
    char temp[5];
    sprintf(temp, "%c%c%c%c", c, c + 1, c + 2, c + 3);
    displayText(temp);
    delay(800);
  }

  // Letters a-z (if supported)
  Serial.println("Displaying lowercase letters...");
  for (char c = 'a'; c <= 'z'; c += 4) {
    char temp[5];
    sprintf(temp, "%c%c%c%c", c, c + 1, c + 2, c + 3);
    displayText(temp);
    delay(800);
  }

  // Special characters
  Serial.println("Displaying special characters...");
  const char* specials[] = { "!@#$", "%^&*", "()_+", "[]{}", "|\\:;", "\"'<>", ",.?/" };
  int numSpecials = sizeof(specials) / sizeof(specials[0]);

  for (int i = 0; i < numSpecials; i++) {
    displayText(specials[i]);
    delay(800);
  }
}