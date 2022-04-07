const uint8_t blue = 23;
#include <Wire.h> // Only needed for Arduino 1.6.5 and earlier
//#include "SSD1306.h" // alias for `#include "SSD1306Wire.h"`
// SSD1306 display(0x3c, 21, 22);
#include "SH1106.h"
SH1106 display(0x3c, 21, 22);
int n = 0;

#include "FS.h"
#include "SD.h"
#include "SPI.h"

#define SCK 14
#define MISO 2
#define MOSI 15
#define CS 13
char string[25];

void writeFile(fs::FS &fs, const char *path, const char *message)
{
    Serial.printf("Writing file: %s\n", path);

    File file = fs.open(path, FILE_WRITE);
    if (!file)
    {
        Serial.println("Failed to open file for writing");
        return;
    }
    if (file.print(message))
    {
        Serial.println("File written");
    }
    else
    {
        Serial.println("Write failed");
    }
    file.close();
}

void appendFile(fs::FS &fs, const char *path, const char *message)
{
    Serial.printf("Appending to file: %s\n", path);

    File file = fs.open(path, FILE_APPEND);
    if (!file)
    {
        Serial.println("Failed to open file for appending");
        return;
    }
    if (file.print(message))
    {
        Serial.println("Message appended");
    }
    else
    {
        Serial.println("Append failed");
    }
    file.close();
}

void readFile(fs::FS &fs, const char *path)
{
    Serial.printf("Reading file: %s\n", path);

    File file = fs.open(path);
    if (!file)
    {
        Serial.println("Failed to open file for reading");
        return;
    }

    Serial.print("Read from file: ");
    while (file.available())
    {
        Serial.write(file.read());
    }
    file.close();
}

void SDCardSetup()
{
    Serial.begin(115200);
    Serial.println("Mounting");
    // SPIClass spi = SPIClass(VSPI);
    spi.begin(SCK, MISO, MOSI, CS);

    if (!SD.begin(CS, spi, 80000000))
    {
        Serial.println("Card Mount Failed");
        return;
    }
    uint8_t cardType = SD.cardType();

    if (cardType == CARD_NONE)
    {
        Serial.println("No SD card attached");
        return;
    }

    Serial.print("SD Card Type: ");
    if (cardType == CARD_MMC)
    {
        Serial.println("MMC");
    }
    else if (cardType == CARD_SD)
    {
        Serial.println("SDSC");
    }
    else if (cardType == CARD_SDHC)
    {
        Serial.println("SDHC");
    }
    else
    {
        Serial.println("UNKNOWN");
    }

    uint64_t cardSize = SD.cardSize() / (1024 * 1024);
    Serial.printf("SD Card Size: %lluMB\n", cardSize);

    writeFile(SD, "/hello.txt", "Hello ");

    for (int i = 10 - 1; i >= 0; i--)
    {
        sprintf(string, "line %d\n", i);
        Serial.println(i);
        appendFile(SD, "/hello.txt", string);
        delay(2000);
    }

    readFile(SD, "/hello.txt");
    // deleteFile(SD, "/foo.txt");
    // renameFile(SD, "/hello.txt", "/foo.txt");
    // readFile(SD, "/foo.txt");
    Serial.printf("Total space: %lluMB\n", SD.totalBytes() / (1024 * 1024));
    Serial.printf("Used space: %lluMB\n", SD.usedBytes() / (1024 * 1024));
}

void setup()
{
    Serial.begin(115200);
    pinMode(blue, OUTPUT);
    display.init();

    display.flipScreenVertically();
    display.setFont(ArialMT_Plain_10);
    Serial.println(" Finish Scren start sd");
    
    SDCardSetup();
}
// char string[25];
void drawFontFaceDemo(int n)
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
