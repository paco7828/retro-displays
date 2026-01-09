/*
 * HDSP-B05G Fast Test - ESP32-C3 SuperMini
 * High-speed multiplexed display with multiple test modes
 */

#define SEG_A 0
#define SEG_B 1
#define SEG_C 2
#define SEG_D 3
#define SEG_E 4
#define SEG_F 5
#define SEG_G 6
#define SEG_DP 7

#define DIGIT1 20
#define DIGIT2 21
#define DIGIT3 8
#define DIGIT4 10

const int segmentPins[8] = {SEG_A, SEG_B, SEG_C, SEG_D, SEG_E, SEG_F, SEG_G, SEG_DP};
const int digitPins[4] = {DIGIT1, DIGIT2, DIGIT3, DIGIT4};

const byte numbers[10][7] = {
  {1,1,1,1,1,1,0}, // 0
  {0,1,1,0,0,0,0}, // 1
  {1,1,0,1,1,0,1}, // 2
  {1,1,1,1,0,0,1}, // 3
  {0,1,1,0,0,1,1}, // 4
  {1,0,1,1,0,1,1}, // 5
  {1,0,1,1,1,1,1}, // 6
  {1,1,1,0,0,0,0}, // 7
  {1,1,1,1,1,1,1}, // 8
  {1,1,1,1,0,1,1}  // 9
};

int displayDigits[4] = {0, 0, 0, 0};
bool showColon = false;
int testMode = 0;
unsigned long lastUpdate = 0;
int counter = 0;

void setup() {
  Serial.begin(115200);
  
  // Fast pin initialization
  for (int i = 0; i < 8; i++) {
    pinMode(segmentPins[i], OUTPUT);
    digitalWrite(segmentPins[i], LOW);
  }
  
  for (int i = 0; i < 4; i++) {
    pinMode(digitPins[i], OUTPUT);
    digitalWrite(digitPins[i], HIGH);
  }
  
  Serial.println("\n=== HDSP-B05G Fast Test ===");
  Serial.println("Press 1-6 to change test mode:");
  Serial.println("1 - Fast counter (0-9999)");
  Serial.println("2 - Clock display (12:34)");
  Serial.println("3 - All 8s test");
  Serial.println("4 - Counting up slowly");
  Serial.println("5 - Random numbers");
  Serial.println("6 - Segment chase");
  Serial.println("\nPress C to toggle colon ON/OFF\n");
}

void loop() {
  // Check for mode changes
  if (Serial.available()) {
    char c = Serial.read();
    if (c >= '1' && c <= '6') {
      testMode = c - '1';
      counter = 0;
      Serial.print("Mode changed to: ");
      Serial.println(testMode + 1);
    }
    else if (c == 'C' || c == 'c') {
      showColon = !showColon;
      Serial.print("Colon: ");
      Serial.println(showColon ? "ON" : "OFF");
    }
  }
  
  // Update display based on mode
  unsigned long now = millis();
  
  switch (testMode) {
    case 0: // Fast counter
      if (now - lastUpdate > 50) {
        counter++;
        if (counter > 9999) counter = 0;
        setNumber(counter);
        lastUpdate = now;
      }
      break;
      
    case 1: // Clock display
      if (now - lastUpdate > 500) {
        showColon = !showColon; // Auto-blink in clock mode
        lastUpdate = now;
      }
      displayDigits[0] = 1;
      displayDigits[1] = 2;
      displayDigits[2] = 3;
      displayDigits[3] = 4;
      break;
      
    case 2: // All 8s
      for (int i = 0; i < 4; i++) displayDigits[i] = 8;
      showColon = true;
      break;
      
    case 3: // Slow counter
      if (now - lastUpdate > 1000) {
        counter++;
        if (counter > 9999) counter = 0;
        setNumber(counter);
        lastUpdate = now;
      }
      break;
      
    case 4: // Random
      if (now - lastUpdate > 100) {
        for (int i = 0; i < 4; i++) {
          displayDigits[i] = random(10);
        }
        lastUpdate = now;
      }
      break;
      
    case 5: // Segment chase
      segmentChase();
      return;
  }
  
  // Fast multiplexing
  refreshDisplay();
}

void refreshDisplay() {
  for (int d = 0; d < 4; d++) {
    // Disable all digits
    digitalWrite(DIGIT1, HIGH);
    digitalWrite(DIGIT2, HIGH);
    digitalWrite(DIGIT3, HIGH);
    digitalWrite(DIGIT4, HIGH);
    
    // Set segments
    for (int i = 0; i < 7; i++) {
      digitalWrite(segmentPins[i], numbers[displayDigits[d]][i]);
    }
    
    // Show colon (decimal points on digits 2 and 3)
    if (showColon && (d == 1 || d == 2)) {
      digitalWrite(SEG_DP, HIGH);
    } else {
      digitalWrite(SEG_DP, LOW);
    }
    
    // Enable current digit
    digitalWrite(digitPins[d], LOW);
    
    delayMicroseconds(1500); // Fast refresh
  }
}

void setNumber(int num) {
  displayDigits[0] = (num / 1000) % 10;
  displayDigits[1] = (num / 100) % 10;
  displayDigits[2] = (num / 10) % 10;
  displayDigits[3] = num % 10;
  showColon = false;
}

void segmentChase() {
  static int currentSeg = 0;
  static unsigned long lastChange = 0;
  
  if (millis() - lastChange > 100) {
    currentSeg++;
    if (currentSeg > 7) currentSeg = 0;
    lastChange = millis();
  }
  
  for (int d = 0; d < 4; d++) {
    digitalWrite(DIGIT1, HIGH);
    digitalWrite(DIGIT2, HIGH);
    digitalWrite(DIGIT3, HIGH);
    digitalWrite(DIGIT4, HIGH);
    
    // Clear all segments
    for (int i = 0; i < 8; i++) {
      digitalWrite(segmentPins[i], LOW);
    }
    
    // Light one segment
    digitalWrite(segmentPins[currentSeg], HIGH);
    
    // Enable digit
    digitalWrite(digitPins[d], LOW);
    
    delayMicroseconds(1500);
  }
}