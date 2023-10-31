/*
 * 30 Days - Lost in Space
 * Day 22 - Hello New World!
 *
 * Even our new OLED display is a bit small if we have large amounts of
 * information to display.  But this new display isn't limited to JUST
 * text!  It is a 128x64 pixel display and we can turn any of them on/off
 * to display whatever we like, including graphics.
 *
 * Today we'll run a "readiness check" on our new display to test out its
 * full capabilities.
 *
 * Learn more at https://inventr.io/adventure
 *
 * Alex Eschenauer
 * David Schmidt
 * Greg Lyzenga
 */

/*
 * Arduino concepts introduced/documented in this lesson.
 * - 
 * - 
 * - 
 *
 * Parts and electronics concepts introduced in this lesson.
 * - 
 */

// Explicitly include Arduino.h
#include "Arduino.h"
#include "Wire.h"

// Include file for 4 digit - 7 segment display library
#include <TM1637Display.h>

/*
 * Extensive documentation for this library can be found at https://github.com/olikraus/u8g2
 * for those wanting to dive deeper, but we will explain all of the functions
 * used in these lessons.
 */
#include <U8g2lib.h>  // Include file for the U8g2 library.

/*
 * #define macros
 *
 * We started the first few lessons of this course showing how "#define" works since
 * it's still often used, but on Day 4 we introduced the newer and better "const"
 * and have been using it since to define all of our constants.
 *
 * But "#define" *does* have some capabilities that "const" doesn't, and we're going
 * to use of those today.  
 */
#define numberOfMinutes(_time_) (((_time_ + 999) / 1000) / 60)
#define numberOfSeconds(_time_) (((_time_ + 999) / 1000) % 60)

// 7 SEGMENT PIN ASSIGNMENTS
#define CLKsev 5
#define DIOsev 4

// DEFINE DISPLAY OBJECTS
// Construct our lander_display handle using the same constructor from Day 21
U8G2_SH1106_128X64_NONAME_2_HW_I2C lander_display(U8G2_R0, /* reset=*/U8X8_PIN_NONE);
TM1637Display counter_display(5, 4);

const byte LANDER_HEIGHT = 25;  // height of our lander image, in bits
const byte LANDER_WIDTH = 20;   // width of our lander image, in bits

// HANDY CONSTANTS
// const uint8_t OFF[] = { 0, 0, 0, 0 };
const uint8_t DONE[] = {
  SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,          // d
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,  // O
  SEG_C | SEG_E | SEG_G,                          // n
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G           // E
};

// GLOBAL VARIABLES
const unsigned long COUNTDOWN_TIME = 70000;

// *********************************************
void setup() {
  Serial.begin(9600);
  // Set brightness
  counter_display.setBrightness(7);
  // Clear the display
  counter_display.clear();

  lander_display.begin();
  lander_display.setFont(u8g2_font_6x10_tr);
  // lander_display.setFont(u8g2_font_tallpixelextended_tr);
  lander_display.setFontRefHeightExtendedText();
  lander_display.setFontPosTop();

  lander_display.firstPage();
  do {
    byte y_offset = drawString(0, 0, "Exploration Lander");
    y_offset = drawString(0, y_offset, "Liftoff Sequence");
    drawString(0, lander_display.getDisplayHeight() - lander_display.getMaxCharHeight(), "Countdown Active");
    displayLander(lander_display.getDisplayWidth() - LANDER_WIDTH,
                  lander_display.getDisplayHeight() - LANDER_HEIGHT);
  } while (lander_display.nextPage());

  // blink starting value 3 times
  for (int i = 0; i < 4; i++) {
    counter_display.clear();
    delay(200);
    displayCounter(COUNTDOWN_TIME);
    delay(200);
  }
  Serial.println("Countdown started..: ");
}

// *********************************************
void loop() {
  static unsigned long timeRemaining = COUNTDOWN_TIME;
  static unsigned long countdown_start_time = millis();

  Serial.println(timeRemaining);
  displayCounter(timeRemaining);

  if (timeRemaining == 0) {
    Serial.println("Done!!");
    counter_display.setSegments(DONE);
    lander_display.firstPage();
    do {
      byte y_offset = drawString(0, 0, "Exploration Lander");
      y_offset = drawString(0, y_offset, "Liftoff ABORTED");

      // lander_display.setFontPosCenter();  // Y coordinate relative to center of font height
      y_offset = lander_display.getDisplayHeight() - (4 * lander_display.getMaxCharHeight());
      y_offset = drawString(0, y_offset, "Thrusters: OFF");
      y_offset = drawString(0, y_offset, "Systems: OFF");
      y_offset = drawString(0, y_offset, "Confirm: OFF");

      // lander_display.setFontPosBottom();
      drawString(0, y_offset, "Countdown ABORT");
      displayLander(lander_display.getDisplayWidth() - LANDER_WIDTH,
                    lander_display.getDisplayHeight() - LANDER_HEIGHT);
      // draw();
    } while (lander_display.nextPage());
    while (1)
      ;
  }

  // Update the time remaining
  unsigned long elapsed_time = millis() - countdown_start_time;
  if (elapsed_time < COUNTDOWN_TIME) {
    timeRemaining = COUNTDOWN_TIME - elapsed_time;
  } else {
    timeRemaining = 0;
  }
}
// *********************************************

// Display milliseconds as minutes:seconds (MM:SS)
void displayCounter(unsigned long milliseconds) {
  // To display the countdown in mm:ss format, separate the parts
  byte minutes = numberOfMinutes(milliseconds);
  byte seconds = numberOfSeconds(milliseconds);

  // Display the minutes in the first two places, with colon
  counter_display.showNumberDecEx(minutes, 0b01000000, true, 2, 0);
  // This displays the seconds in the last two places
  counter_display.showNumberDecEx(seconds, 0, true, 2, 2);
}

// Use the .drawStr() method to draw a string in the display centered
// horizontally between the given X coordinate and the maximum X.
// Y coordinate is unchanged and text is displayed relative to the
// current font positioning mode (Top, Center, Bottom).
// byte drawCenteredString(byte x, byte y, char *string) {
//   byte centered_x = x + ((lander_display.getDisplayWidth() - x) - lander_display.getStrWidth(string)) / 2;
//   lander_display.drawStr(centered_x, y, string);
// }

byte drawString(byte x, byte y, char *string) {
  lander_display.drawStr(0, y, string);
  return (y + lander_display.getMaxCharHeight());  // return new y_offset on display
}

// OLED Display output
// void draw(void) {
//   // graphic commands to redraw the complete screen should be placed here
//   lander_display.setFont(u8g_font_6x10);


//   lander_display.drawStr(0, 22, "LIFTOFF!!");
//   lander_display.drawStr(0, 44, "End of sim");
// }

// Draw an image of our lander drawn with frames and triangles
// at location x_location, y_location (relative to the upper left corner).
void displayLander(byte x_location, byte y_location) {
  lander_display.drawFrame(x_location + 7, y_location, 6, 5);        // ship top
  lander_display.drawFrame(x_location + 5, y_location + 4, 10, 20);  // ship center
  lander_display.drawFrame(x_location, y_location + 6, 6, 16);       // left pod
  lander_display.drawFrame(x_location + 14, y_location + 6, 6, 16);  // right pod
  lander_display.drawTriangle(x_location + 2, y_location + 21,
                              x_location, y_location + 25,
                              x_location + 4, y_location + 25);  // left nozzle
  lander_display.drawTriangle(x_location + 18, y_location + 21,
                              x_location + 15, y_location + 25,
                              x_location + 20, y_location + 25);  // right nozzle
}
