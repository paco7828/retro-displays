#include <DLDisplay.h>

#define CLR 0
#define ADDR0 3
#define ADDR1 2
#define WR 1
#define BL 4
#define D0 5
#define D1 6
#define D2 7
#define D3 8
#define D4 9
#define D5 10
#define D6 20

DLDisplay display(CLR, ADDR0, ADDR1, WR, BL, D0, D1, D2, D3, D4, D5, D6);
const char message[] = "    HELLO WORLD!    ";

void setup()
{
    display.begin();
}

void loop()
{
    display.scrollText(message, 300);
}