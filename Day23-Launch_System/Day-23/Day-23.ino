/*
 * 30 Days - Lost in Space
 * Day 23 - Launch System
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
 * - #define macros
 * - rounding up calculated values
 * - elapsed time without using delay() calls.
 * - firstPage()/nextPage() graphics loop to save memory
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
 * But "#define" *does* have some capabilities that "const" doesn't.  The one we
 * use today is the use of parameters, turning our constant into a simple, in-line
 * function.
 *
 * Since #define performs simple text substitution this method executes faster since
 * it doesn't have any overhead to call and return a function.
 *
 * WARNING: #define macros CAN cause bugs if the variable passed in is used in multiple
 * places in the macro because the text inside the call is simply replaced in the macro.
 *
 * These examples perform a simple calculation returning the minutes or seconds from
 * a number representing milliseconds, rounded UP to the next highest second by adding
 * 999 milliseconds.  This allows our counter to return 00:01 until the instant the
 * counter reaches zero.
 */
#define numberOfMinutes(_milliseconds_) (((_milliseconds_ + 999) / 1000) / 60)
#define numberOfSeconds(_milliseconds_) (((_milliseconds_ + 999) / 1000) % 60)

// Pin connections for our 4 digit counter
#define COUNTER_DISPLAY_CLK_PIN 5
#define COUNTER_DISPLAY_DIO_PIN 4
// Construct counter_display handle.
TM1637Display counter_display(COUNTER_DISPLAY_CLK_PIN, COUNTER_DISPLAY_DIO_PIN);

/*
 * This constructor for our OLED differs from the one used for the previous
 * days, changing the "_F_" to "_2_".  This indicates that instead of using
 * a full sized buffer to draw to our OLED display a smaller, 256 byte buffer
 * will be used along with the firstPage()/nextPage() calls.  This gives us
 * more memory for other variables, though the display may update slower.
 */
U8G2_SH1106_128X64_NONAME_2_HW_I2C lander_display(U8G2_R0, /* reset=*/U8X8_PIN_NONE);

const byte LANDER_HEIGHT = 25;  // height of our lander image, in bits
const byte LANDER_WIDTH = 20;   // width of our lander image, in bits

// Define 7 Segment display values to spell out "dOnE"
const uint8_t DONE[] = {
  SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,          // d
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,  // O
  SEG_C | SEG_E | SEG_G,                          // n
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G           // E
};

// Define amount of time (in milliseconds) to count down.
const unsigned long COUNTDOWN_MILLISECONDS = 5 * 1000;

// *********************************************
void setup() {
  Serial.begin(9600);

  // Configure counter display
  counter_display.setBrightness(7);  // Set maximum brightness (value is 0-7)
  counter_display.clear();           // Clear the display

  // Configure OLED display
  lander_display.begin();                     // Initialize OLED display
  lander_display.setFont(u8g2_font_6x10_tr);  // Set text font
  lander_display.setFontRefHeightText();
  lander_display.setFontPosTop();

  /*
   * Display starting status on our lander's OLED display.
   *
   * The U8g2 library for Arduino uses a technique called "page buffering" to draw on
   * displays connected to microcontrollers with limited RAM. Here's a short explanation
   * of how it works:
   *
   * firstPage(): This function starts the drawing routine. It initializes the buffer with
   *              the first "page" or segment of the display.
   * nextPage(): After drawing the first page, this function is called in a loop. Each call
   *             loads the next segment into the buffer and allows you to draw additional
   *             content. This process repeats until the entire display content is drawn over
   *             multiple pages.
   * Looping: The combination of firstPage() and nextPage() is typically used inside a loop.
   *          The loop continues until nextPage() returns false, indicating that all pages
   *          have been drawn.
   *
   * By drawing the display in segments, the library conserves RAM, making it feasible to use
   * graphics displays with microcontrollers that have limited memory resources.
   */
  lander_display.firstPage();
  do {
    byte y_offset = drawString(0, 0, "Exploration Lander");
    drawString(0, y_offset, "Liftoff Sequence");

    // Status on bottom line of OLED display
    drawString(0, lander_display.getDisplayHeight() - lander_display.getMaxCharHeight(), "Countdown Active");
    // Draw a picture of our lander int bottom right corner
    displayLander(lander_display.getDisplayWidth() - LANDER_WIDTH,
                  lander_display.getDisplayHeight() - LANDER_HEIGHT);
  } while (lander_display.nextPage());

  // blink the countdown on our timer before beginning the countdown
  for (int i = 0; i < 4; i++) {
    counter_display.clear();
    delay(200);
    displayCounter(COUNTDOWN_MILLISECONDS);
    delay(200);
  }
  Serial.println("Countdown started..: ");
}

// *********************************************
void loop() {
  // Initialize static variables first time through loop() that will retain values
  // between loop() executions.
  static unsigned long timeRemaining = COUNTDOWN_MILLISECONDS;
  static unsigned long countdown_start_time = millis();

  Serial.println(timeRemaining);  // Display milliseconds remaining on serial console
  displayCounter(timeRemaining);  // Display minutes:seconds on counter display

  // If timeRemaining has reached 0 display ending values
  if (timeRemaining == 0) {
    Serial.println("Done!!");           // indicate completion on serial console
    counter_display.setSegments(DONE);  // "dOnE" on our counter

    // Now update our OLED display with ending screen using firstPage()/nextPage()
    lander_display.firstPage();
    do {
      // Each time we display a line of text on our display the y_offset
      // is updated to point to the next available point for drawing.
      // Display first two lines
      byte y_offset = drawString(0, 0, "Exploration Lander");
      y_offset = drawString(0, y_offset, "Liftoff ABORTED");

      // Set y_offset to point four lines above bottom of display
      y_offset = lander_display.getDisplayHeight() - (4 * lander_display.getMaxCharHeight());
      // Display last four lines
      y_offset = drawString(0, y_offset, "Thrusters: OFF");
      y_offset = drawString(0, y_offset, "Systems: OFF");
      y_offset = drawString(0, y_offset, "Confirm: OFF");
      drawString(0, y_offset, "Countdown ABORT");
      // Draw a picture of our lander in bottom right corner
      displayLander(lander_display.getDisplayWidth() - LANDER_WIDTH,
                    lander_display.getDisplayHeight() - LANDER_HEIGHT);
    } while (lander_display.nextPage());

    // Stop here by looping forever.
    while (1)
      ;
  }

  // Update our remaining time by subtracting the start time from current
  // execution time (in milliseconds).  If our elapsed time is greater
  // than our countdown time then set remaining time to 0.
  unsigned long elapsed_time = millis() - countdown_start_time;
  if (elapsed_time < COUNTDOWN_MILLISECONDS) {
    timeRemaining = COUNTDOWN_MILLISECONDS - elapsed_time;
  } else {
    timeRemaining = 0;
  }
}

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

// Draw test on our lander display at x, y, returning new y
// value that is immediately below the new line of text.
byte drawString(byte x, byte y, char *string) {
  lander_display.drawStr(x, y, string);
  return (y + lander_display.getMaxCharHeight());  // return new y_offset on display
}

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
