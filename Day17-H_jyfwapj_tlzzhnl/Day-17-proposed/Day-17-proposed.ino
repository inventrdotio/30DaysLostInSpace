#include <Arduino.h>
#include <TM1637Display.h>
// Module connection pins (Digital Pins)
#define CLK 6
#define DIO 5
// The amount of time (in milliseconds) between tests
#define TEST_DELAY   2000
TM1637Display display(CLK, DIO);
void setup()
{
}
void loop()
{
 display.setBrightness(0x0f);
 uint8_t data[] = { 0x0, 0x0, 0x0, 0x0 };
 display.setSegments(data);
 display.showNumberDec(23, false, 3, 1);
 delay(TEST_DELAY);
 display.setSegments(data);
 display.showNumberDec(353, true, 3, 1);
 delay(TEST_DELAY);
 display.setSegments(data);
 display.showNumberDec(1688, true, 4, 0);
 delay(TEST_DELAY);
}