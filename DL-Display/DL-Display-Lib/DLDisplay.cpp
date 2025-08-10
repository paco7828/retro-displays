#include "DLDisplay.h"

DLDisplay::DLDisplay(int clr, int addr0, int addr1, int wr, int bl, int d0, int d1, int d2,
                     int d3, int d4, int d5, int d6)
    : clr(clr), addr0(addr0), addr1(addr1), wr(wr), bl(bl),
      d0(d0), d1(d1), d2(d2), d3(d3), d4(d4), d5(d5), d6(d6) {}

void DLDisplay::begin()
{
    pinMode(this->clr, OUTPUT);
    pinMode(this->addr0, OUTPUT);
    pinMode(this->addr1, OUTPUT);
    pinMode(this->wr, OUTPUT);
    pinMode(this->bl, OUTPUT);
    pinMode(this->d0, OUTPUT);
    pinMode(this->d1, OUTPUT);
    pinMode(this->d2, OUTPUT);
    pinMode(this->d3, OUTPUT);
    pinMode(this->d4, OUTPUT);
    pinMode(this->d5, OUTPUT);
    pinMode(this->d6, OUTPUT);

    digitalWrite(this->clr, HIGH);
    digitalWrite(this->bl, HIGH);
    digitalWrite(this->wr, HIGH);
}

byte DLDisplay::asciiToDL(char c)
{
    if (c >= ' ' && c <= '_')
    {
        return c;
    }
    return 0x20; // Space character
}

void DLDisplay::selectAddr(byte segment)
{
    switch (segment)
    {
    case 1:
        digitalWrite(this->addr0, HIGH);
        digitalWrite(this->addr1, HIGH);
        break;
    case 2:
        digitalWrite(this->addr0, LOW);
        digitalWrite(this->addr1, HIGH);
        break;
    case 3:
        digitalWrite(this->addr0, HIGH);
        digitalWrite(this->addr1, LOW);
        break;
    case 4:
        digitalWrite(this->addr0, LOW);
        digitalWrite(this->addr1, LOW);
        break;
    }
}

void DLDisplay::setDataPins(byte data)
{
    digitalWrite(this->d0, data & 0x01);
    digitalWrite(this->d1, data & 0x02);
    digitalWrite(this->d2, data & 0x04);
    digitalWrite(this->d3, data & 0x08);
    digitalWrite(this->d4, data & 0x10);
    digitalWrite(this->d5, data & 0x20);
    digitalWrite(this->d6, data & 0x40);
}

void DLDisplay::displayChar(char c)
{
    byte data = this->asciiToDL(c);
    setDataPins(data);
    digitalWrite(this->wr, LOW);
    digitalWrite(this->wr, HIGH);
}

void DLDisplay::displayText(const char message[4])
{
    for (int i = 0; i < 4; i++)
    {
        this->selectAddr(i + 1);
        this->displayChar(message[i]);
    }
}

void DLDisplay::clear()
{
    digitalWrite(this->clr, LOW);
    delay(15);
    digitalWrite(this->clr, HIGH);
}

void DLDisplay::blink(int blinkDelay)
{
    delay(blinkDelay);
    digitalWrite(this->bl, LOW);
    delay(blinkDelay);
    digitalWrite(this->bl, HIGH);
}

void DLDisplay::scrollText(const char message[], int scrollDelay)
{
    int length = strlen(message);
    for (int i = 0; i < length; i++)
    {
        this->clear();
        for (int j = 0; j < 4; j++)
        {
            int charIndex = i + j;
            if (charIndex < length)
            {
                this->selectAddr(j + 1);
                this->displayChar(message[charIndex]);
            }
        }
        delay(scrollDelay);
    }
}

void DLDisplay::fullTest()
{
    // Test all printable ASCII characters from space (32) to underscore (95)
    // Display each character repeated 4 times (e.g., "AAAA", "BBBB", etc.)
    
    for (char c = ' '; c <= '_'; c++)
    {
        char testPattern[5] = {c, c, c, c, '\0'};
        this->clear();
        this->displayText(testPattern);
        delay(500);
    }
    this->clear();
}