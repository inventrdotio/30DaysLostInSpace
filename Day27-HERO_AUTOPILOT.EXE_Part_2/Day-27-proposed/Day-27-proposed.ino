/*
 * 30 Days - Lost in Space
 * Day 27 - Fun With Bitmaps, Part 2
 *
 * OK, now we know how to display bitmaps that cover the entire display,
 * but it would be very inefficient to pre-draw every possible display.
 *
 * Instead, we can reduce the size of our bitmaps to whatever size is
 * desired and then display the partial bitmaps.
 *
 * In addition, we won't just be displaying all the bitmaps in a loop so
 * we need a way to *select* which bitmaps are being displayed.
 *
 * Let's use our DIP switches to display one of eight different bitmaps.
 * Since we only have three switches we'll read each as a bit in a binary
 * number.  This way three switches can give us eight distinct values.
 *
 * We'll also add our 4 digit 7 segment display to show which picture
 * is currently being displayed.
 *
 * Learn more at https://inventr.io/adventure
 *
 * Alex Eschenauer
 * David Schmidt
 * Greg Lyzenga
 */

/*
 * Arduino concepts introduced/documented in this lesson.
 * - partial bitmaps
 * - switches to binary
 * - creating include files
 *
 * Parts and electronics concepts introduced in this lesson.
 * - 
 */

// Explicitly include Arduino.h
#include "Arduino.h"

// Extensive documentation for this library can be found at https://github.com/olikraus/u8g2
#include <U8g2lib.h>  // Include file for the U8g2 library.
#include "Wire.h"     // Sometimes required for I2C communications.

// Use _2_ version of constructor and firstPage()/nextPage() for OLED
// graphics to save memory.
U8G2_SH1106_128X64_NONAME_2_HW_I2C lander_display(U8G2_R0, /* reset=*/U8X8_PIN_NONE);

/*
 * Yesterday we showed a way to move our large bitmap declarations so that
 * our setup() and loop() code was near the top of our sketch using "forward
 * declarations".
 *
 * However, it turns out there's a simpler way, and we've seen it used many
 * times in the past.  We can simply MOVE our declarations into one or more
 * include files and then include them at the top of our sketch before we
 * reference them.
 *
 * To create a new file, simply click the "..." to the right of the tab bar with
 * our sketch name and select "New Tab".  Enter the name for the new file and
 * click the tab to edit.  This lets us move all of our bitmaps into a separate
 * file so we don't have to scroll through them.
 */
#include "switch_bitmaps.h"

const static char* SWITCH_BITMAPS[] = {
  ZERO,
  ONE,
  TWO,
  THREE,
  FOUR,
  FIVE,
  SIX,
  SEVEN,
};

// Include file for 4 digit - 7 segment display library
#include <TM1637Display.h>
const byte COUNTER_DISPLAY_DIO_PIN = 2;
const byte COUNTER_DISPLAY_CLK_PIN = 3;
// Construct counter_display handle.
TM1637Display counter_display(COUNTER_DISPLAY_CLK_PIN, COUNTER_DISPLAY_DIO_PIN);

// Define pins for our DIP switches
const byte THRUST_LEVER_PIN = A0;
const byte SYSTEMS_LEVER_PIN = A1;
const byte CONFIRM_LEVER_PIN = A2;

// ************************************************
void setup(void) {
  Serial.begin(9600);
  // Configure counter display
  counter_display.setBrightness(7);  // Set maximum brightness (value is 0-7)
  counter_display.clear();           // Clear the display
  // Configure DIP switch pins
  pinMode(THRUST_LEVER_PIN, INPUT);   // Thrust lever pin
  pinMode(SYSTEMS_LEVER_PIN, INPUT);  // Sysstems lever pin
  pinMode(CONFIRM_LEVER_PIN, INPUT);  // Confirmation lever pin

  lander_display.begin();  // initialize lander display
}

// ************************************************
void loop(void) {

  byte x_offset = (lander_display.getDisplayWidth() - BITMAP_WIDTH) / 2;

  byte switch_value = digitalRead(CONFIRM_LEVER_PIN) == HIGH ? 1 : 0;
  switch_value |= (digitalRead(SYSTEMS_LEVER_PIN) == HIGH ? 1 : 0) << 1;
  switch_value |= (digitalRead(THRUST_LEVER_PIN) == HIGH ? 1 : 0) << 2;

  // Serial.println(switch_value);
  counter_display.showNumberDecEx(switch_value);

  lander_display.firstPage();
  do {
    // .drawXBMP() displays each bitmap starting at the upper left corner
    // (0, 0) that has width of 128 and height of 64.
    lander_display.drawXBMP(x_offset, 0, BITMAP_WIDTH, BITMAP_HEIGHT, BITMAP_WIDTH[switch_value]);
  } while (lander_display.nextPage());

  delay(100);
}
