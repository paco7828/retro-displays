// Pin definitions
#define CLR 0
#define WR 1
#define A0 3
#define A1 4
#define D0 5
#define D1 6
#define D2 7
#define D3 8
#define D4 9
#define D5 10
#define D6 20

// Address definitions for 4-character positions (single display)
#define CHAR_POS_0 0  // Rightmost character
#define CHAR_POS_1 1
#define CHAR_POS_2 2
#define CHAR_POS_3 3  // Leftmost character

// Character mapping structure
struct CharMapping {
  uint8_t ascii_code;
  uint8_t hdlx_code;
  const char* description;
};

// Complete character mapping array
const CharMapping char_map[] = {
  // Special characters (Row 0)
  { 0xEC, 0x00, "ì" },
  { 0x18, 0x01, "arrow up" },
  { 0x1A, 0x02, "arrow right" },
  { 0x19, 0x03, "arrow bottom" },
  { 0x1B, 0x04, "arrow left" },
  { 0xA8, 0x05, "¿" },
  { 0xE0, 0x06, "à" },
  { 0xD8, 0x07, "Ø" },
  { 0xF8, 0x08, "ø" },
  { 0xF2, 0x09, "ò" },
  { 0xF9, 0x0A, "ù" },
  { 0xF1, 0x0B, "ñ" },
  { 0xE7, 0x0C, "ç" },
  { 0xEA, 0x0D, "ê" },
  { 0xC9, 0x0E, "É" },
  { 0xE9, 0x0F, "é" },

  // More special characters (Row 1)
  { 0xE8, 0x10, "è" },
  { 0xC6, 0x11, "Æ" },
  { 0xE6, 0x12, "æ" },
  { 0xC0, 0x13, "Ȧ" },
  { 0xE0, 0x14, "ȧ" },
  { 0xC4, 0x15, "Ä" },
  { 0xE4, 0x16, "ä" },
  { 0xD6, 0x17, "Ö" },
  { 0xF6, 0x18, "ö" },
  { 0xDC, 0x19, "Ü" },
  { 0xFC, 0x1A, "ü" },
  { 0xB0, 0x1B, "°C" },
  { 0xB0, 0x1C, "°F" },
  { 0xDF, 0x1D, "ß" },
  { 0xA3, 0x1E, "£" },
  { 0xA5, 0x1F, "¥" },

  // Standard ASCII printable characters (Row 2-3)
  { ' ', 0x20, "space" },
  { '!', 0x21, "!" },
  { '"', 0x22, "\"" },
  { '#', 0x23, "#" },
  { '$', 0x24, "$" },
  { '%', 0x25, "%" },
  { '&', 0x26, "&" },
  { '\'', 0x27, "'" },
  { '(', 0x28, "(" },
  { ')', 0x29, ")" },
  { '*', 0x2A, "*" },
  { '+', 0x2B, "+" },
  { ',', 0x2C, "," },
  { '-', 0x2D, "-" },
  { '.', 0x2E, "." },
  { '/', 0x2F, "/" },

  // Numbers 0-9
  { '0', 0x30, "0" },
  { '1', 0x31, "1" },
  { '2', 0x32, "2" },
  { '3', 0x33, "3" },
  { '4', 0x34, "4" },
  { '5', 0x35, "5" },
  { '6', 0x36, "6" },
  { '7', 0x37, "7" },
  { '8', 0x38, "8" },
  { '9', 0x39, "9" },
  { ':', 0x3A, ":" },
  { ';', 0x3B, ";" },
  { '<', 0x3C, "<" },
  { '=', 0x3D, "=" },
  { '>', 0x3E, ">" },
  { '?', 0x3F, "?" },

  // Uppercase letters A-Z (Row 4-5)
  { '@', 0x40, "@" },
  { 'A', 0x41, "A" },
  { 'B', 0x42, "B" },
  { 'C', 0x43, "C" },
  { 'D', 0x44, "D" },
  { 'E', 0x45, "E" },
  { 'F', 0x46, "F" },
  { 'G', 0x47, "G" },
  { 'H', 0x48, "H" },
  { 'I', 0x49, "I" },
  { 'J', 0x4A, "J" },
  { 'K', 0x4B, "K" },
  { 'L', 0x4C, "L" },
  { 'M', 0x4D, "M" },
  { 'N', 0x4E, "N" },
  { 'O', 0x4F, "O" },
  { 'P', 0x50, "P" },
  { 'Q', 0x51, "Q" },
  { 'R', 0x52, "R" },
  { 'S', 0x53, "S" },
  { 'T', 0x54, "T" },
  { 'U', 0x55, "U" },
  { 'V', 0x56, "V" },
  { 'W', 0x57, "W" },
  { 'X', 0x58, "X" },
  { 'Y', 0x59, "Y" },
  { 'Z', 0x5A, "Z" },
  { '[', 0x5B, "[" },
  { '\\', 0x5C, "\\" },
  { ']', 0x5D, "]" },
  { '^', 0x5E, "^" },
  { '_', 0x5F, "_" },

  // Lowercase letters a-z (Row 6-7)
  { '`', 0x60, "`" },
  { 'a', 0x61, "a" },
  { 'b', 0x62, "b" },
  { 'c', 0x63, "c" },
  { 'd', 0x64, "d" },
  { 'e', 0x65, "e" },
  { 'f', 0x66, "f" },
  { 'g', 0x67, "g" },
  { 'h', 0x68, "h" },
  { 'i', 0x69, "i" },
  { 'j', 0x6A, "j" },
  { 'k', 0x6B, "k" },
  { 'l', 0x6C, "l" },
  { 'm', 0x6D, "m" },
  { 'n', 0x6E, "n" },
  { 'o', 0x6F, "o" },
  { 'p', 0x70, "p" },
  { 'q', 0x71, "q" },
  { 'r', 0x72, "r" },
  { 's', 0x73, "s" },
  { 't', 0x74, "t" },
  { 'u', 0x75, "u" },
  { 'v', 0x76, "v" },
  { 'w', 0x77, "w" },
  { 'x', 0x78, "x" },
  { 'y', 0x79, "y" },
  { 'z', 0x7A, "z" },
  { '{', 0x7B, "{" },
  { '|', 0x7C, "tall :" },
  { '}', 0x7D, "}" },
  { '~', 0x7E, "~" },
  { 0xDB, 0x7F, "grid" }
};

const int CHAR_MAP_SIZE = sizeof(char_map) / sizeof(char_map[0]);

void displayTemperature(int temp, bool celsius = true);

void setup() {
  Serial.begin(9600);

  // Initialize all pins as outputs
  pinMode(CLR, OUTPUT);
  pinMode(WR, OUTPUT);
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);

  // Set initial states
  digitalWrite(WR, HIGH);   // Write disabled
  digitalWrite(CLR, HIGH);  // Clear disabled

  // Clear display on startup
  clearDisplay();
  delay(500);

  Serial.println("HDLX-2416 Single Display Driver");
  Serial.println("Now supports proper character mapping!");
  Serial.println("Test with: displayText(\"Hi!\");");
}

void loop() {
  // Example usage - you can modify this
  displayText("Hi! ");
  delay(2000);

  displayTemperature(25, true);  // 25.5°C
  delay(2000);

  displayText("$5  ");
  delay(2000);

  scrollText("Hello World! This is a scrolling message.");
  delay(1000);

  clearDisplay();
  delay(1000);
}

// Function to find HDLX code for a given ASCII character
uint8_t asciiToHDLX(char c) {
  uint8_t charCode = (uint8_t)c;

  // Search through the character mapping
  for (int i = 0; i < CHAR_MAP_SIZE; i++) {
    if (char_map[i].ascii_code == charCode) {
      return char_map[i].hdlx_code;
    }
  }
  // If character not found, return space
  return 0x20;  // Space character
}

// Function to display temperature with proper degree symbol (4 chars max)
void displayTemperature(int temp, bool celsius) {
  char tempStr[5];  // 4 chars + null terminator

  if (celsius) {
    snprintf(tempStr, 5, "%dC", temp);
  } else {
    snprintf(tempStr, 5, "%dF", temp);
  }

  displayText(tempStr);

  // Replace the 'C' or 'F' with the special degree symbol
  int len = strlen(tempStr);
  for (int i = 0; i < len; i++) {
    if (tempStr[i] == 'C') {
      displayCode(3 - i, 0x1B);  // °C symbol
      break;
    } else if (tempStr[i] == 'F') {
      displayCode(3 - i, 0x1C);  // °F symbol
      break;
    }
  }
}

// Function to display a character code at specific position
void displayCode(uint8_t position, uint8_t code) {
  // Set address (position 0-3)
  digitalWrite(A1, (position >> 1) & 1);
  digitalWrite(A0, position & 1);

  // Set data (7-bit code)
  digitalWrite(D0, code & 1);
  digitalWrite(D1, (code >> 1) & 1);
  digitalWrite(D2, (code >> 2) & 1);
  digitalWrite(D3, (code >> 3) & 1);
  digitalWrite(D4, (code >> 4) & 1);
  digitalWrite(D5, (code >> 5) & 1);
  digitalWrite(D6, (code >> 6) & 1);

  // Write pulse
  digitalWrite(WR, LOW);
  delayMicroseconds(1);  // Minimum 75ns according to datasheet
  digitalWrite(WR, HIGH);
  delayMicroseconds(1);
}

// Enhanced writeCharacter function using the character mapping
void writeCharacter(uint8_t position, char character) {
  uint8_t hdlx_code = asciiToHDLX(character);
  displayCode(position, hdlx_code);
}

// Enhanced displayText function with proper character mapping (4 characters max)
void displayText(const char* text) {
  int textLen = strlen(text);

  // Display: 4 characters (positions 0-3)
  for (int i = 0; i < 4; i++) {
    int pos = 3 - i;  // Flip position: 0 = leftmost, 3 = rightmost
    if (i < textLen) {
      writeCharacter(pos, text[i]);
    } else {
      writeCharacter(pos, ' ');  // Fill with spaces
    }
  }
}

// Function to display special characters by name
void displaySpecial(const char* specialName, uint8_t position) {
  if (strcmp(specialName, "degree_c") == 0) {
    displayCode(position, 0x1B);  // °C
  } else if (strcmp(specialName, "degree_f") == 0) {
    displayCode(position, 0x1C);  // °F
  } else if (strcmp(specialName, "arrow_up") == 0) {
    displayCode(position, 0x01);
  } else if (strcmp(specialName, "arrow_right") == 0) {
    displayCode(position, 0x02);
  } else if (strcmp(specialName, "arrow_down") == 0) {
    displayCode(position, 0x03);
  } else if (strcmp(specialName, "arrow_left") == 0) {
    displayCode(position, 0x04);
  } else if (strcmp(specialName, "pound") == 0) {
    displayCode(position, 0x1E);  // £
  } else if (strcmp(specialName, "yen") == 0) {
    displayCode(position, 0x1F);  // ¥
  } else {
    displayCode(position, 0x20);  // Default to space
  }
}

// Function to clear the display
void clearDisplay() {
  digitalWrite(CLR, LOW);
  delayMicroseconds(20);  // Hold for minimum 10μs
  digitalWrite(CLR, HIGH);
  delayMicroseconds(2);  // Wait for clear disable time
}

// Enhanced scrollText function with proper character mapping (4 chars display)
void scrollText(const char* text) {
  int textLen = strlen(text);

  // Add padding spaces to make scrolling smoother
  char paddedText[textLen + 8];
  strcpy(paddedText, "    ");  // 4 leading spaces
  strcat(paddedText, text);
  strcat(paddedText, "    ");  // 4 trailing spaces

  int paddedLen = strlen(paddedText);

  for (int startPos = 0; startPos < paddedLen - 3; startPos++) {
    char displayBuffer[5] = "    ";  // 4 chars + null terminator

    // Fill display buffer with 4 characters starting at startPos
    for (int i = 0; i < 4; i++) {
      if (startPos + i < paddedLen) {
        displayBuffer[i] = paddedText[startPos + i];
      } else {
        displayBuffer[i] = ' ';
      }
    }
    displayBuffer[4] = '\0';

    displayText(displayBuffer);
    delay(200);  // Scroll speed
  }
}

// Function to print available characters for reference
void printCharacterMap() {
  Serial.println("Available Characters:");
  Serial.println("====================");
  for (int i = 0; i < CHAR_MAP_SIZE; i++) {
    Serial.print("ASCII Code: ");
    Serial.print(char_map[i].ascii_code);
    Serial.print(" -> 0x");
    if (char_map[i].hdlx_code < 0x10) Serial.print("0");
    Serial.print(char_map[i].hdlx_code, HEX);
    Serial.print(" (");
    Serial.print(char_map[i].description);
    Serial.println(")");
  }
}