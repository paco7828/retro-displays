#include <VQC10.h>

/*
VQC10 -> Arduino Uno connections:

1 - D1  -> A4
2 - CP1 -> A0
3 - GND -> GND
4 - Z1  -> D5
5 - CP2 -> A1
6 - GND -> GND
7 - NC  -> NC
8 - D2  -> A5
9 - CP3 -> A2
10 - GND -> GND
11 - Z2  -> D7
12 - CP4 -> A3
13 - GND -> GND
14 - VCC -> 5V
15 - D3  -> D8
16 - GND -> GND
17 - Z3  -> D9
18 - Z4  -> D10
19 - Z5  -> D6
20 - Z6  -> D12
21 - Z7  -> D13
22 - D4  -> D3
23 - D5  -> D4
24 - GND -> GND
*/ 


static VQC10<> LED({
  { A0, A1, A2, A3 },          // Digits = cpx
  { A4, A5, 8, 3, 4 },         // Columns = Dx
  { 5, 7, 9, 10, 6, 12, 13 },  // Rows = Zx
});

void setup() {
  LED.begin();
}

void loop() {
  // Loop through all chars
  for (uint8_t c = 0x20; c <= 0x7E; c++) {
    LED.show(0, c);
    LED.show(1, c);
    LED.show(2, c);
    LED.show(3, c);

    // Show for 300ms
    unsigned long start = millis();
    while (millis() - start < 300) {
      LED.loop();
    }
  }

  // Test end message
  LED.show(0, '!');
  LED.show(1, 'O');
  LED.show(2, 'K');
  LED.show(3, '!');
  unsigned long start = millis();
  while (millis() - start < 2000) {
    LED.loop();
  }

  // Stop after test has ended
  while (true)
    ;
}