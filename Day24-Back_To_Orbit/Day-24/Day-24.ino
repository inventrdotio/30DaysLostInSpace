/*
 * 30 Days - Lost in Space
 * Day 24 - Back To Orbit
 *
 * Explorer, the day has arrived!  Let's get that lander up into space again.
 * We will initialize our systems by setting our Thruster, Systems and Confirmation
 * switches to "off" and then enable our countdown by turning each of them on in
 * turn.
 *
 * Once everything has been turned on the countdown will begin (so be sure you're
 * all buckled in tight!).  If you see anything abnormal during the countdown you
 * can abort the liftoff by turning off any of the switches.  Simply turn them all
 * off again to re-initialize the sequence.
 *
 * Once the countdown reaches zero the ship will liftoff, placing the lander into
 * a random orbit.  Once the engines fire, the liftoff CANNOT be aborted!
 *
 * Let's get you back into space, Explorer, and next week we'll work to get your
 * fragile lander back to your mother ship!
 *
 * Learn more at https://inventr.io/adventure
 *
 * Alex Eschenauer
 * David Schmidt
 * Greg Lyzenga
 */

/*
 * Arduino concepts introduced/documented in this lesson.
 * - enum
 * - ternary operation
 *
 * Parts and electronics concepts introduced in this lesson.
 * - 
 */

// Explicitly include Arduino.h
#include "Arduino.h"

// Include file for 4 digit - 7 segment display library
#include <TM1637Display.h>

// Extensive documentation for this library can be found at https://github.com/olikraus/u8g2
#include <U8g2lib.h>  // Include file for the U8g2 library.
#include "Wire.h"     // Sometimes required for I2C communications.

// Define macros to convert milliseonds to minutes or seconds, rounded UP to next second.
#define numberOfMinutes(_milliseconds_) (((_milliseconds_ + 999) / 1000) / 60)
#define numberOfSeconds(_milliseconds_) (((_milliseconds_ + 999) / 1000) % 60)

// Pin connections for our 4 digit counter
const byte COUNTER_DISPLAY_DIO_PIN = 4;
const byte COUNTER_DISPLAY_CLK_PIN = 5;
// Construct counter_display handle.
TM1637Display counter_display(COUNTER_DISPLAY_CLK_PIN, COUNTER_DISPLAY_DIO_PIN);

// Define pins for our DIP switches
const byte THRUST_LEVER_PIN = 9;
const byte SYSTEMS_LEVER_PIN = 8;
const byte CONFIRM_LEVER_PIN = 7;

// Define pin for buzzer
const byte BUZZER_PIN = 6;

// Use _2_ version of constructor and firstPage()/nextPage() for OLED
// graphics to save memory.
U8G2_SH1106_128X64_NONAME_2_HW_I2C lander_display(U8G2_R0, /* reset=*/U8X8_PIN_NONE);

// Define size of our lander graphic so it can be accurately placed on display
const byte LANDER_HEIGHT = 25;  // height of our lander image, in bits
const byte LANDER_WIDTH = 20;   // width of our lander image, in bits

// Define 7 Segment display values to spell out "dOnE"
const uint8_t DONE[] = {
  SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,          // d
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,  // O
  SEG_C | SEG_E | SEG_G,                          // n
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G           // E
};

// Define amount of time (in milliseconds) to count down.  To ensure
// that the calculation is done as an unsigned long we append "UL" to
// the values below.  Without this the calculation is done in 16 bit
// arithmetic which causes the value to wrap and be incorrect.
const unsigned long COUNTDOWN_MILLISECONDS = 70UL * 1000UL;

/*
 * The Arduino C++ provides the "enum" command to define multiple, related
 * values where distinguishing between the different values is important, but
 * the actual values aren't.
 *
 * Each name is given it's own value (starting with 0) which can be seen by
 * hovering your mouse over each name below.
 *
 * Enums provide a number of benefits over manually defining a set of constants:
 * 1) An enum groups related constants in a way that clearly defines that they
 *    are variants of a single concept (in this case, the state of our liftoff
 *    sequence).
 * 2) An enum gives an exhaustive list off all valid states and no other values
 *    are valid.
 * 3) An enum creates a new type, and a variable containing an enum value can
 *    ONLY be assigned values defined in the enum.
 */
enum LIFTOFF_STATE {
  INIT,       // Waiting for all switches to be "OFF"
  PENDING,    // Waiting for all switchs to be turned "ON"
  COUNTDOWN,  // Counting down to liftoff
  LIFTOFF,    // Ship is lifting off
  ABORT       // Countdown aborted
};

// *********************************************
void setup() {
  Serial.begin(9600);

  // Configure counter display
  counter_display.setBrightness(7);  // Set maximum brightness (value is 0-7)
  counter_display.clear();           // Clear the display

  // Configure OLED display
  lander_display.begin();                     // Initialize OLED display
  lander_display.setFont(u8g2_font_6x10_tr);  // Set text font
  lander_display.setFontRefHeightText();      // Define how max text height is calculated
  lander_display.setFontPosTop();             // Y coordinate for text is at top of tallest character

  // Configure DIP switch pins
  pinMode(THRUST_LEVER_PIN, INPUT);   // Thrust lever pin
  pinMode(SYSTEMS_LEVER_PIN, INPUT);  // Sysstems lever pin
  pinMode(CONFIRM_LEVER_PIN, INPUT);  // Confirmation lever pin

  lander_display.clearDisplay();  // Clear OLED display
}

// *********************************************
// *              LOOP()                       *
// *********************************************

// To keep beeping and animations steady we will attempt to have each loop
// take the same amount of time.  Occasionally loops may take longer, but
// this constant defines the minimum time each loop will take to run.
const unsigned long MIN_LOOP_TIME = 200;  // minimum 200 ms time per loop

void loop() {
  // Initialize static variables first time through loop().  Any values set
  // during execution will be retained between loop() executions.
  static unsigned long timeRemaining = COUNTDOWN_MILLISECONDS;  // Time remaining before liftoff
  static unsigned long countdown_start_time;                    // millis() value when countdown begins
  static enum LIFTOFF_STATE liftoff_state = INIT;               // Begin sequence in INIT state

  // Here we define a value that is toggled between true/false ever time through the loop
  // This can be used to create a beeping tone or could be used to blink text.
  static bool loop_toggle = true;  // if our loop_toggle is true this time through the loop

  unsigned long loop_start_time = millis();  // save time that this loop begins

  // Read current values of all of our switches as booleans ("on" is true, "off" is false)
  bool thrust_lever = digitalRead(THRUST_LEVER_PIN);
  bool systems_lever = digitalRead(SYSTEMS_LEVER_PIN);
  bool confirm_lever = digitalRead(CONFIRM_LEVER_PIN);

  // Update OLED display with the current status of our liftoff sequence.
  updateLanderDisplay(liftoff_state, thrust_lever, systems_lever, confirm_lever);

  /*
   * This is the primary decision part of our loop.  It makes decisions based on the
   * current state of our liftoff sequence, switching states as different events are
   * detected.
   *
   * NOTE: Normally this section of code would done in a switch/case construct.  However
   *       a bug in the compiler caused certain cases to NEVER execute.  Because of this
   *       bug (hopefully fixed soon) we use the less clear if/else if/else format.
   *
   * A switch/case version would look like:
   * switch(liftoff_state) {
   *   case INIT:
   *     // code for INIT state
   *     break;
   *   [...]
   *   case ABORT:
   *     // code for ABORT state
   *     break;
   * }
   */

  if (liftoff_state == INIT) {  // INIT state
    // INIT state requires that all switches start out as "off".

    // If all three switches are OFF (false) we can turn off the beeping
    // and change state to PENDING.
    if (!thrust_lever && !systems_lever && !confirm_lever) {
      noTone(BUZZER_PIN);
      liftoff_state = PENDING;
    } else {  // not all switches are "off"
      // Play low, "beeping" tone to indicate switches aren't all "off"
      if (loop_toggle) {        // if our loop_toggle is true this time through the loop
        tone(BUZZER_PIN, 100);  // play short tone entire loop
      } else {
        noTone(BUZZER_PIN);  // turn off tone this time through the loop
      }
    }
    // end of INIT state
  } else if (liftoff_state == PENDING) {
    // Now wait for all switches to be turned ON to initiate countdown.
    if (thrust_lever && systems_lever && confirm_lever) {
      // blink the countdown on our timer before beginning the countdown
      for (int i = 0; i < 3; i++) {
        counter_display.clear();
        delay(MIN_LOOP_TIME);
        displayCounter(COUNTDOWN_MILLISECONDS);
        delay(MIN_LOOP_TIME);
      }
      countdown_start_time = millis();  // Save current millis() when countdown begins
      liftoff_state = COUNTDOWN;
    }
    // end of PENDING state
  } else if (liftoff_state == COUNTDOWN) {
    // Update our remaining time by subtracting the countdown start time from current
    // execution time (in milliseconds).  If this value is greater than our countdown
    // time then our countdown is complete and we set time remaining to 0 to prevent
    // the time remaining from going negative.
    unsigned long elapsed_time = millis() - countdown_start_time;
    if (elapsed_time > COUNTDOWN_MILLISECONDS) {  // Countdown complete!
      timeRemaining = 0;                          // No time remaining
      liftoff_state = LIFTOFF;                    // initiate liftoff state
    } else {
      timeRemaining = COUNTDOWN_MILLISECONDS - elapsed_time;  // decrease time remaining
    }

    // if any switch is turned off during countdown then we abort takeoff.
    if (!thrust_lever || !systems_lever || !confirm_lever) {
      liftoff_state = ABORT;
    }
    displayCounter(timeRemaining);  // Display countdown time in minutes:seconds on counter display
    // end of COUNTDOWN state
  } else if (liftoff_state == LIFTOFF) {  // Liftoff!
    counter_display.setSegments(DONE);    // Display "dOnE" on our counter

    // Play TADA! tones followed by sound of our thrusters firing
    tone(BUZZER_PIN, 300);
    delay(200);
    tone(BUZZER_PIN, 500);
    delay(400);
    tone(BUZZER_PIN, 38, 5000);  // Play engines for first 5 seconds

    // Animate final display forever.  This while loop runs until HERO is reset or
    // new code is uploaded.  During liftoff the ship graphic moves up the right
    // side of the display, so we need to update the OLED display repeately.
    while (true) {
      updateLanderDisplay(liftoff_state, true, true, true);
    }
    // THIS LINE IS NEVER REACHED
    // end of LIFTOFF state
  } else if (liftoff_state == ABORT) {
    // If countdown was aborted we play an alert tone and delay before
    // moving state back to our original INIT state.
    tone(BUZZER_PIN, 100, 1000);
    delay(5000);           // show display for 5 seconds
    liftoff_state = INIT;  // set state back to INIT (waiting switches to be all OFF)
  }

  // If loop has taken LESS than our minimum loop time then delay the remaining
  // time to keep loops at least that long.
  unsigned long loop_time = millis() - loop_start_time;
  if (loop_time < MIN_LOOP_TIME) {
    delay(MIN_LOOP_TIME - loop_time);  // delay remaining time
  }

  // Toggle our loop toggle between true/false each time through main loop.
  loop_toggle = !loop_toggle;
}

// *********************************************
// *          Update OLED display              *
// *********************************************
const byte MAX_LANDER_SPEED = 5;

void updateLanderDisplay(enum LIFTOFF_STATE liftoff_state,
                         bool thruster_lever,
                         bool systems_lever,
                         bool confirm_lever) {
  static int lander_height = lander_display.getDisplayHeight() - LANDER_HEIGHT;
  static byte current_lander_speed = 1;

  // Use the firstPage()/nextPage() commands to update our display using smaller
  // data buffer.  Only a portion of the display is updated each time through
  // this loop.  The SAME display should be drawn each time through this "do" loop.
  lander_display.firstPage();
  do {
    lander_display.setFontPosTop();
    byte y_offset = drawString(0, 0, "Exploration Lander");
    y_offset = drawString(0, y_offset, "Liftoff Sequence");

    if (liftoff_state == LIFTOFF) {
      const char LIFTOFF_TEXT[] = "Liftoff!";
      // Display liftoff in center of available space
      byte y_center = y_offset + ((lander_display.getDisplayHeight() - y_offset) / 2);
      // Serial.println(y_center);
      lander_display.setFontPosCenter();  // display text vertically centered
      static byte text_width = lander_display.getStrWidth(LIFTOFF_TEXT);
      static byte x_left = ((lander_display.getDisplayWidth() - LANDER_WIDTH) / 2) - (text_width / 2);
      lander_display.drawStr(x_left, y_center, LIFTOFF_TEXT);
    } else if (liftoff_state == ABORT) {
      const char ABORT_TEXT[] = "ABORTED!";
      // Display liftoff in center of available space
      byte y_center = y_offset + ((lander_display.getDisplayHeight() - y_offset) / 2);
      lander_display.setFontPosCenter();  // display text vertically centered
      static byte text_width = lander_display.getStrWidth(ABORT_TEXT);
      static byte x_left = ((lander_display.getDisplayWidth() - LANDER_WIDTH) / 2) - (text_width / 2);
      lander_display.drawStr(x_left, y_center, ABORT_TEXT);
    } else {
      // Set y_offset to point four lines above bottom of display
      y_offset = lander_display.getDisplayHeight() - (4 * lander_display.getMaxCharHeight());
      // Display last four lines
      y_offset = drawString(0, y_offset,
                            (String("Thrusters: ") + String(thruster_lever ? "ON" : "OFF")).c_str());
      y_offset = drawString(0, y_offset,
                            (String("Systems  : ") + String(systems_lever ? "ON" : "OFF")).c_str());
      y_offset = drawString(0, y_offset,
                            (String("Confirm  : ") + String(confirm_lever ? "ON" : "OFF")).c_str());

      // Set y_offset to display text at bottom of display.
      y_offset = lander_display.getDisplayHeight() - lander_display.getMaxCharHeight();
      drawString(0, y_offset, (String("Countdown ") + liftoffStateToString(liftoff_state)).c_str());
    }
    // Draw a picture of our lander on right side of display.  During the liftoff this
    // will be animated by changing the lander_height variable OUTSIDE the "do" loop.
    displayLander(lander_display.getDisplayWidth() - LANDER_WIDTH,
                  lander_height);
  } while (lander_display.nextPage());

  // Set height of lander image on screen to animate liftoff image, increasing speed
  // to MAX during liftoff.  This value is only changed OUTSIDE the firstPage()/nextPage()
  // loop and sets the new height for the lander to be drawn the NEXT time the OLED
  // display is updated.
  if (liftoff_state == LIFTOFF) {
    // Move our lander graphic up on the display based on our current speed
    lander_height -= current_lander_speed;
    // If the graphic has moved entirely off the top of the display we reset
    // the height to make it re-appear at the bottom.
    if (lander_height < -LANDER_HEIGHT) {
      lander_height = lander_display.getDisplayHeight();  // start again at bottom of screen
    }
    // To accellerate, increase the movement speed until we reach our maximum speed
    if (current_lander_speed < MAX_LANDER_SPEED) {
      current_lander_speed += 1;
    }
  }
}

// "helper" function that returns a different string for each enum state.
String liftoffStateToString(enum LIFTOFF_STATE liftoff_state) {
  switch (liftoff_state) {
    case INIT:
      return ("Init");
      break;
    case PENDING:
      return ("Pending");
      break;
    case COUNTDOWN:
      return ("Active");
      break;
    case LIFTOFF:
      return ("Complete");
      break;
    case ABORT:
      return ("ABORT");
      break;
  }
}

// Display milliseconds on our counter as minutes:seconds (MM:SS)
void displayCounter(unsigned long milliseconds) {
  // To display the countdown in mm:ss format, separate the parts
  byte minutes = numberOfMinutes(milliseconds);
  byte seconds = numberOfSeconds(milliseconds);

  // Display the minutes in the first two places, with colon
  counter_display.showNumberDecEx(minutes, 0b01000000, true, 2, 0);
  // This displays the seconds in the last two places
  counter_display.showNumberDecEx(seconds, 0, true, 2, 2);
}

// Draw a line of text on our OLED display at x, y, returning new y
// value that is immediately below the new line of text.
byte drawString(byte x, byte y, char *string) {
  lander_display.drawStr(x, y, string);
  return (y + lander_display.getMaxCharHeight());  // return new y_offset on display
}

// Draw an image of our lander drawn with frames and triangles
// at location x_location, y_location (relative to the upper left corner).
void displayLander(byte x_location, int y_location) {
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
