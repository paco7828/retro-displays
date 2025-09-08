#pragma once

#include <Arduino.h>

class FEMDisplay
{
private:
    // Segment codes for common cathode
    static const byte COM_CATHODE_NUMBERS[10][8];

    // Segment codes for common anode (calculated at runtime)
    byte COM_ANODE_NUMBERS[10][8];

    // Segment pin mapping
    byte SEGMENT_PINS[8];

    // Display type flag
    bool COMMON_CATHODE;

public:
    FEMDisplay();

    void begin(byte segmentPins[8], bool commonCathode = true);
    void displayOff();
    void showNumber(byte number);
};

#endif
