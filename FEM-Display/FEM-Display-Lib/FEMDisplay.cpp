#include "FEMDisplay.h"

// Define cathode digits
const byte FEMDisplay::COM_CATHODE_NUMBERS[10][8] = {
    {1, 1, 1, 1, 1, 1, 0, 0}, // 0
    {0, 1, 1, 0, 0, 0, 0, 0}, // 1
    {1, 1, 0, 1, 1, 0, 1, 0}, // 2
    {1, 1, 1, 1, 0, 0, 1, 0}, // 3
    {0, 1, 1, 0, 0, 1, 1, 0}, // 4
    {1, 0, 1, 1, 0, 1, 1, 0}, // 5
    {1, 0, 1, 1, 1, 1, 1, 0}, // 6
    {1, 1, 1, 0, 0, 0, 0, 0}, // 7
    {1, 1, 1, 1, 1, 1, 1, 0}, // 8
    {1, 1, 1, 1, 0, 1, 1, 0}  // 9
};

// Constructor
FEMDisplay::FEMDisplay()
{
    COMMON_CATHODE = true;
}

// Initialize display
void FEMDisplay::begin(byte segmentPins[8], bool commonCathode)
{
    COMMON_CATHODE = commonCathode;

    // Copy pin numbers
    for (int i = 0; i < 8; i++)
    {
        SEGMENT_PINS[i] = segmentPins[i];
        pinMode(SEGMENT_PINS[i], OUTPUT);
    }

    // If common anode -> invert cathode bit table
    if (!COMMON_CATHODE)
    {
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                COM_ANODE_NUMBERS[i][j] = COM_CATHODE_NUMBERS[i][j] ? 0 : 1;
            }
        }
    }

    displayOff();
}

// Turn display off
void FEMDisplay::displayOff()
{
    for (int i = 0; i < 8; i++)
    {
        digitalWrite(SEGMENT_PINS[i], LOW);
    }
}

// Show number
void FEMDisplay::showNumber(byte number)
{
    if (number > 9)
        number = 9;

    for (int i = 0; i < 8; i++)
    {
        byte val;
        if (COMMON_CATHODE)
        {
            val = COM_CATHODE_NUMBERS[number][i];
        }
        else
        {
            val = COM_ANODE_NUMBERS[number][i];
        }
        digitalWrite(SEGMENT_PINS[i], val);
    }
}
