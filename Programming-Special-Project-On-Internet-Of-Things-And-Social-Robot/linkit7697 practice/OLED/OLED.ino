#include <SeeedOLED.h>
#include <Wire.h>

void setup()
{
    Wire.begin();
    SeeedOled.init();
    SeeedOled.deactivateScroll();
    SeeedOled.setPageMode();
}

void loop()
{
    SeeedOled.clearDisplay();
    SeeedOled.setTextXY(0, 0);
    SeeedOled.putNumber(54321);
    SeeedOled.setTextXY(1, 0);
    SeeedOled.putFloat(3.1415);
    SeeedOled.setTextXY(2, 0);
    SeeedOled.putString("hello");
    delay(1000);
}