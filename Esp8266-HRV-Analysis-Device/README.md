| SPI   |MOSI   |MISO   |CLK    |CS     | 
| :---: | :---: | :---: | :---: | :---: |
| VSPI|GPIO 23|GPIO 19|GPIO 18|GPIO 5| 
| HSPI|GPIO 13|GPIO 12|GPIO 14|GPIO 15| 

| SD    |Names  |Pins   |
| :---: | :---: | :---: |
|SD3    |CS     |IO13   |
|CMD    |MOSI   |IO15   |
|CLK    |SCK    |IO14   |
|SD0    |MISO   |IO2    |

    #define SCK  14
    #define MISO  2
    #define MOSI  15
    #define CS  13

https://github.com/ThingPulse/esp8266-oled-ssd1306
https://techtutorialsx.com/2017/12/02/esp32-arduino-interacting-with-a-ssd1306-oled-display/

# Esp8266-HRV-Analysis-Device
This device is built to acquire pulse samples of a subject and perform simple calcultions to output parameters like Avg BPM, Avg IBI, SDNN, RMSSD. The result is also stored in Sd card for later use. An Oled display(SSD1306) is used for UI and outputs a neat graphics of readings taken by the max30100 pulse oximeter sensor. Esp8366 was chosen for further integration with Internet Servers/Clouds for easy access.
