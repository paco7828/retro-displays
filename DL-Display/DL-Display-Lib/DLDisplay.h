#ifndef DLDISPLAY_H
#define DLDISPLAY_H

#include <Arduino.h>

class DLDisplay
{
private:
    int clr, addr0, addr1, wr, bl, d0, d1, d2, d3, d4, d5, d6;

    byte asciiToDL(char c);
    void selectAddr(byte segment);
    void setDataPins(byte data);

public:
    DLDisplay(int clr, int addr0, int addr1, int wr, int bl, int d0, int d1, int d2,
              int d3, int d4, int d5, int d6);

    void begin();
    void displayChar(char c);
    void displayText(const char message[4]);
    void clear();
    void blink(int blinkDelay);
    void scrollText(const char message[], int scrollDelay);
    void fullTest();
};

#endif