/*
  (PD3535 -> ESP32-C3 Supermini):
   20-VCC    -> 5V
   10-GND    -> GND
    1-RD     -> 3.3V
    3-CLKSEL -> 3.3V
    4-RST    -> 3.3V
    5-CE1    -> 3.3V
    6-CE0    -> GND
   
   11-WR    -> GPIO 0
    9-A0    -> GPIO 1
    8-A1    -> GPIO 2
    7-A2    -> GPIO 3
   19-D0    -> GPIO 4
   18-D1    -> GPIO 5
   17-D2    -> GPIO 6
   16-D3    -> GPIO 7
   15-D4    -> GPIO 8
   14-D5    -> GPIO 9
   13-D6    -> GPIO 10
   12-D7    -> GPIO 20
 */

const int wrPin = 0;
const int addrPins[3] = {1, 2, 3}; // A0, A1, A2
const int dataPins[8] = {4, 5, 6, 7, 8, 9, 10, 20}; // D0-D7

void setup() {
  pinMode(wrPin, OUTPUT);
  digitalWrite(wrPin, HIGH);
  
  for(int i = 0; i < 3; i++) {
    pinMode(addrPins[i], OUTPUT);
  }
  for(int i = 0; i < 8; i++) {
    pinMode(dataPins[i], OUTPUT);
  }

  writeReg(0x00, 0b10000000); 
  delay(2);
  writeReg(0x00, 0b00000011); 
}

void loop() {
  for (int c = 32; c < 128; c++) {
    for (uint8_t addr = 4; addr <= 7; addr++) {
      writeReg(addr, c);
    }
    delay(150);
  }
}

void writeReg(uint8_t addr, uint8_t data) {
  for(int i = 0; i < 3; i++) {
    digitalWrite(addrPins[i], (addr >> i) & 0x01);
  }

  for(int i = 0; i < 8; i++) {
    digitalWrite(dataPins[i], (data >> i) & 0x01);
  }

  digitalWrite(wrPin, LOW);
  delayMicroseconds(1);
  digitalWrite(wrPin, HIGH);
  delayMicroseconds(1);
}