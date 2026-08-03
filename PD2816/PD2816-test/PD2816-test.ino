/*
  PD-2816 -> ESP32
  Pin 23, 24 (VCC) -> 5V
  Pin 12 (GND) -> GND
  Pin 15-22 (D0-D7) -> IO0 - IO7
  Pin 2 (A0) -> IO8
  Pin 3 (A1) -> IO9
  Pin 4 (A2) -> IO10
  Pin 5 (A3) -> IO20
  Pin 14 (WR) -> IO21
  Pin 6 (CE1) -> GND
  Pin 7 (CE2) -> 3.3V
  Pin 10 (RD) -> 3.3V
  Pin 9 (CLK SEL) -> 3.3V
  Pin 1 (RST) -> 3.3V
 */

const int dataPins[] = {0, 1, 2, 3, 4, 5, 6, 7};
const int pinA0 = 8;
const int pinA1 = 9;
const int pinA2 = 10;
const int pinA3 = 20;
const int pinWR = 21;

void writeBus(uint8_t data) {
    for (int i = 0; i < 8; i++) {
        digitalWrite(dataPins[i], (data >> i) & 0x01);
    }
}

void sendControlWord(uint8_t cmd) {
    digitalWrite(pinA3, LOW);
    writeBus(cmd);
    digitalWrite(pinWR, LOW);
    delayMicroseconds(1);
    digitalWrite(pinWR, HIGH);
}

void writeDigit(uint8_t digitIndex, uint8_t asciiChar) {
    digitalWrite(pinA3, HIGH);
    digitalWrite(pinA0, (digitIndex & 0x01));
    digitalWrite(pinA1, (digitIndex & 0x02) >> 1);
    digitalWrite(pinA2, (digitIndex & 0x04) >> 2);
    writeBus(asciiChar);
    digitalWrite(pinWR, LOW);
    delayMicroseconds(1);
    digitalWrite(pinWR, HIGH);
}

void setup() {
    for (int i = 0; i < 8; i++) {
        pinMode(dataPins[i], OUTPUT);
    }
    pinMode(pinA0, OUTPUT);
    pinMode(pinA1, OUTPUT);
    pinMode(pinA2, OUTPUT);
    pinMode(pinA3, OUTPUT);
    pinMode(pinWR, OUTPUT);
    
    digitalWrite(pinWR, HIGH);
    sendControlWord(0x03);
    sendControlWord(0x80); 
    delay(10);
    sendControlWord(0x03);
}

void loop() {
    for (uint8_t c = 0x20; c <= 0x5F; c++) {
        for (int i = 0; i < 8; i++) {
            writeDigit(i, c);
        }
        delay(150);
    }
}