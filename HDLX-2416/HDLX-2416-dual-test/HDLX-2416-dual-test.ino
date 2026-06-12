// Pin definitions
#define CLR 0
#define WR 1
#define A0 2
#define A1 3
#define D0 4
#define D1 5
#define D2 6
#define D3 7
#define D4 10
#define D5 9
#define D6 8
#define CE1_1 20  // Screen 2 (chars: 4-7)
#define CE1_2 21  // Screen 1 (chars: 0-3)

// Character mapping structure
struct CharMapping {
  uint8_t ascii_code;
  uint8_t hdlx_code;
  const char* description;
};

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
void clearDisplay();
void displayText(const char* text);
void displayCode(uint8_t global_position, uint8_t code);
void writeCharacter(uint8_t position, char character);
void scrollText(const char* text);

void setup() {
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
  pinMode(CE1_1, OUTPUT);
  pinMode(CE1_2, OUTPUT);

  digitalWrite(WR, HIGH);   
  digitalWrite(CLR, HIGH);  
  digitalWrite(CE1_1, HIGH); 
  digitalWrite(CE1_2, HIGH); 

  clearDisplay();
  delay(500);
}

void loop() {
  displayText("--------");
  delay(2000);

  displayTemperature(23, true);  
  delay(2000);

  scrollText("Kijelzo OK! Hello World!!");
  delay(1000);

  clearDisplay();
  delay(1000);
}

uint8_t asciiToHDLX(char c) {
  uint8_t charCode = (uint8_t)c;
  for (int i = 0; i < CHAR_MAP_SIZE; i++) {
    if (char_map[i].ascii_code == charCode) {
      return char_map[i].hdlx_code;
    }
  }
  return 0x20; 
}

void displayCode(uint8_t global_position, uint8_t code) {
  uint8_t chip_pos = global_position % 4;
  uint8_t ce_pin = (global_position >= 4) ? CE1_1 : CE1_2;

  digitalWrite(A1, (chip_pos >> 1) & 1);
  digitalWrite(A0, chip_pos & 1);

  digitalWrite(D0, code & 1);
  digitalWrite(D1, (code >> 1) & 1);
  digitalWrite(D2, (code >> 2) & 1);
  digitalWrite(D3, (code >> 3) & 1);
  digitalWrite(D4, (code >> 4) & 1);
  digitalWrite(D5, (code >> 5) & 1);
  digitalWrite(D6, (code >> 6) & 1);

  digitalWrite(ce_pin, LOW);

  digitalWrite(WR, LOW);
  delayMicroseconds(1);
  digitalWrite(WR, HIGH);
  
  digitalWrite(ce_pin, HIGH);
  delayMicroseconds(1);
}

void writeCharacter(uint8_t position, char character) {
  uint8_t hdlx_code = asciiToHDLX(character);
  displayCode(position, hdlx_code);
}

void displayText(const char* text) {
  int textLen = strlen(text);

  for (int i = 0; i < 8; i++) {
    int pos = 7 - i;
    if (i < textLen) {
      writeCharacter(pos, text[i]);
    } else {
      writeCharacter(pos, ' ');
    }
  }
}

void displayTemperature(int temp, bool celsius) {
  char tempStr[9];  

  if (celsius) {
    snprintf(tempStr, 9, "%dC", temp);
  } else {
    snprintf(tempStr, 9, "%dF", temp);
  }

  displayText(tempStr);

  int len = strlen(tempStr);
  for (int i = 0; i < len; i++) {
    if (tempStr[i] == 'C') {
      displayCode(7 - i, 0x1B);
      break;
    } else if (tempStr[i] == 'F') {
      displayCode(7 - i, 0x1C);
      break;
    }
  }
}

void clearDisplay() {
  digitalWrite(CE1_1, LOW);
  digitalWrite(CE1_2, LOW);
  
  digitalWrite(CLR, LOW);
  delayMicroseconds(20);
  digitalWrite(CLR, HIGH);
  
  digitalWrite(CE1_1, HIGH);
  digitalWrite(CE1_2, HIGH);
  delayMicroseconds(2);
}

void scrollText(const char* text) {
  int textLen = strlen(text);

  char paddedText[textLen + 16];
  strcpy(paddedText, "        ");
  strcat(paddedText, text);
  strcat(paddedText, "        ");

  int paddedLen = strlen(paddedText);

  for (int startPos = 0; startPos < paddedLen - 7; startPos++) {
    char displayBuffer[9] = "        ";

    for (int i = 0; i < 8; i++) {
      if (startPos + i < paddedLen) {
        displayBuffer[i] = paddedText[startPos + i];
      } else {
        displayBuffer[i] = ' ';
      }
    }
    displayBuffer[8] = '\0';

    displayText(displayBuffer);
    delay(200);
  }
}