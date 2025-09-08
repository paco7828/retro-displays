#include <FEMDisplay.h>

FEMDisplay display;

byte segPins[8] = {2, 3, 4, 5, 6, 7, 8, 9}; // A, B, C, D, E, F, G, DP

void setup()
{
    display.begin(segPins, true); // true = common cathode
    display.showNumber(5);
}

void loop()
{
}
