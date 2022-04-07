#include <mySD.h>
//#include <SPI.h>
//#include <Wire.h>
//#include "SSD1306Wire.h"

File root;
#include "SH1106.h"
SH1106 display(0x3c, 21, 22);
//  OLED screen text rows:
#define row1 0 //  y=0 is top row of size 1 text
#define row2 10
#define row3 20
#define row4 30
#define row5 40
#define row6 50 //  row7 at 70 is too low

//  SPI port #2:  SD Card Adapter
#define SD_CLK 14
#define SD_MISO 2
#define SD_MOSI 15
#define SD_CS 13

#define Select LOW    //  Low CS means that SPI device Selected
#define DeSelect HIGH //  High CS means that SPI device Deselected


void setup()
{
    // set output pins

    pinMode(SD_CS, OUTPUT);
    Serial.begin(115200);
    while (!Serial)
        ; //  wait to connect to computer

    display.init();
    display.flipScreenVertically();
    display.setFont(ArialMT_Plain_10);
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.clear();
    display.display();

    Serial.print("Initializing SD card...");
    digitalWrite(SD_CS, Select); //  SELECT (Low) SD Card SPI
                                 
    if (!SD.begin(SD_CS, SD_MOSI, SD_MISO, SD_CLK))
    {
        Serial.println("initialization failed!");
        //  now what?
    }
    else
    {
        Serial.println("initialization done.");
        display.drawString(5, row1, "SD Card OK!");
        display.display();
        delay(1000);
    }
    /* open "test.txt" for writing */
    root = SD.open("test.txt", FILE_WRITE);
    if (root)
    {
        root.println("Hello world!");
        root.flush();
        root.close();
    }
    else
    { //  file open error
        Serial.println("error opening test.txt");
    }
    display.drawString(5, row2, "Wrote in test.txt");
    display.display();
    delay(100);
    /* after writing, then reopen the file and read it */
    root = SD.open("test.txt");
    if (root)
    { /* read from the file to the end of it */
        while (root.available())
        { // read the file
            Serial.write(root.read());
        }
        root.close();
    }
    else
    {
        Serial.println("error opening test.txt");
    }
    display.drawString(5, row3, "Read from test.txt");
    display.display();
    delay(100);
    //  done testing the SD Card
    digitalWrite(SD_CS, DeSelect);
    //  SD.end();
    delay(100);
}

void loop()
{
}