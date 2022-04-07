const uint8_t blue = 23;
#include <Wire.h>    // Only needed for Arduino 1.6.5 and earlier
//#include "SSD1306.h" // alias for `#include "SSD1306Wire.h"`
//SSD1306 display(0x3c, 21, 22);
#include "SH1106.h"
SH1106 display(0x3c, 21, 22);
int n = 0;
void setup()
{
    Serial.begin(115200);
    pinMode(blue, OUTPUT);
    display.init();

    display.flipScreenVertically();
    display.setFont(ArialMT_Plain_10);
}
char string[25];
void drawFontFaceDemo(int  n)
{
    // Font Demo1
    // create more fonts at http://oleddisplay.squix.ch/
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_10);
    display.drawString(0, 0, "Test");
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 10, "Hi Raj!!");
    display.setFont(ArialMT_Plain_24);
    sprintf(string, "%d", n);
    display.drawString(0, 26, string);
}

void loop()
{
    digitalWrite(blue, 1);
    delay(100);
    digitalWrite(blue, 0);
    delay(100);
    digitalWrite(blue, 1);
    delay(100);

    n++;

    Serial.print("n = ");
    Serial.print(n);
    Serial.println(" Times");
    display.clear();
    drawFontFaceDemo(n);
    display.display();
    digitalWrite(blue, 0);
    delay(700);
}
