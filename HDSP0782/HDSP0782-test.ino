#include <Arduino.h>

const uint8_t PIN_X1 = 5; // Input 1 -> IO5
const uint8_t PIN_X2 = 0; // Input 2 -> IO0
const uint8_t PIN_X4 = 1; // Input 4 -> IO1
const uint8_t PIN_X8 = 2; // Input 8 -> IO2
const uint8_t PIN_BL = 3; // Blanking Control -> IO3
const uint8_t PIN_LE = 4; // Latch Enable -> IO4

// Kiírás a kijelzőre
void writeToDisplay(uint8_t number, bool blank)
{
    digitalWrite(PIN_BL, blank ? HIGH : LOW);
    digitalWrite(PIN_LE, LOW);
    digitalWrite(PIN_X1, number & 0x01);
    digitalWrite(PIN_X2, (number >> 1) & 0x01);
    digitalWrite(PIN_X4, (number >> 2) & 0x01);
    digitalWrite(PIN_X8, (number >> 3) & 0x01);
    digitalWrite(PIN_LE, HIGH);
}

void setup()
{
    pinMode(PIN_X1, OUTPUT);
    pinMode(PIN_X2, OUTPUT);
    pinMode(PIN_X4, OUTPUT);
    pinMode(PIN_X8, OUTPUT);
    pinMode(PIN_BL, OUTPUT);
    pinMode(PIN_LE, OUTPUT);

    digitalWrite(PIN_LE, HIGH);
    digitalWrite(PIN_BL, LOW);
}

void loop()
{
    // (0-9, A-F)
    for (uint8_t i = 0; i <= 15; i++)
    {
        writeToDisplay(i, false);
        delay(800);
    }
}