// TIL311 x1 – egyetlen chip tesztelése

const uint8_t PIN_B = 0;        // pin2
const uint8_t PIN_A = 1;        // pin3
const uint8_t PIN_STROBE = 2;  // pin5
const uint8_t PIN_BLANK = 3;   // pin8, PWM
const uint8_t PIN_D = 9;        // pin12
const uint8_t PIN_C = 10;        // pin13

const uint32_t PWM_FREQ = 5000;
const uint8_t PWM_RES = 8;

void til311Init() {
  pinMode(PIN_A, OUTPUT);
  pinMode(PIN_B, OUTPUT);
  pinMode(PIN_C, OUTPUT);
  pinMode(PIN_D, OUTPUT);
  pinMode(PIN_STROBE, OUTPUT);
  digitalWrite(PIN_STROBE, HIGH);  // hold
  ledcAttach(PIN_BLANK, PWM_FREQ, PWM_RES);
  ledcWrite(PIN_BLANK, 0);  // teljes fényerő
}

void til311Write(uint8_t value) {
  digitalWrite(PIN_A, value & 0x01);
  digitalWrite(PIN_B, (value >> 1) & 0x01);
  digitalWrite(PIN_C, (value >> 2) & 0x01);
  digitalWrite(PIN_D, (value >> 3) & 0x01);
  digitalWrite(PIN_STROBE, LOW);
  delayMicroseconds(1);
  digitalWrite(PIN_STROBE, HIGH);
}

void til311Brightness(uint8_t percent) {  // 0-100, teszteld ezt is
  ledcWrite(PIN_BLANK, map(percent, 0, 100, 255, 0));
}

void setup() {
  til311Init();
  til311Write(0);
}

void loop() {
  for (uint8_t v = 0; v <= 0xF; v++) {
    til311Write(v);
    delay(1000);
  }
}