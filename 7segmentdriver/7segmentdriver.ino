#include "7segmentdriver.h"

SevenSegmentDriver display;

const uint8_t pins[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };  // a,b,c,d,e,f,g,dp
bool isCommonCathode = false;

void setup() {
  display.begin(pins, isCommonCathode);
}

void loop() {
  display.colsRowsLoading();
}