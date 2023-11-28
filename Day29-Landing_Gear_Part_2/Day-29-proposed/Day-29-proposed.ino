/*
 * 30 Days - Lost in Space
 * Day 28 - Landing Gear
 *
 * Congratulations, Explorer!  Today is the day you (hopefully) rejoin
 * the mother ship.  Now, space is BIG, and your docking bay is a small
 * target.
 *
 * Today we will add our thrusters and steering into your controls so that
 * you can initiate your final burn to the mother ship and control the
 * approach to successfully enter the docking bay for a successful landing.
 *
 * You will first need to ensure that our control panel is in a known state
 * by turning off all of the control switches.  Once that is complete you
 * will enable each system in turn by switching all three switches on.
 *
 * Then the display will change to our Approach/Landing display.  The current
 * speed of the lander is displayed in the upper right corner.  On the left
 * side of the display is our target radar.  The distance to the mother ship
 * is shown on our 4 digiti display.
 *
 * In the center of the radar display there is a center point indicating
 * what direction our lander is pointed.  You may also see another point
 * which is the radar return for the mother ship.  Instabilities in our
 * (damaged) lander may cause that target to move, and your job will be
 * to steer the lander during approach to ensure a safe landing.
 *
 * We will use our button matrix to control our steering thrusters, using
 * 8 of our buttons.  In addition, we will use 2 of the buttons for Gear Down
 * and Gear Up and two more for Thrust Up and Thrust Down.
 * 
 * We'll lable the buttons with U for Up, D for Down, L for Left and R for Right.
 * UL means move Up and Left.  The gear buttons are GD and GU (Gear Down and
 * Gear Up) and Thrust controls are labeled T+ and T- for Thrust Up and Thrust
 * Down.
 *
 * UL |  U | UR | GD
 * -----------------
 *  L |    |  R | GU
 * -----------------
 * DL |  D | DR | T+
 * -----------------
 *    |    |    | T-
 *
 * Once you see the radar display you can begin to add thrust using the T+
 * button.  As the speed of our lander increases you will see the distance
 * to our mother ship decrease.
 *
 * If the mother ship drifts off-center you will see arrows appear on the
 * outside of the display to indicate which steering thruster to fire.  Just
 * press the appropriate button until the arrows disappear to keep the
 * mother ship centered.
 *
 * Remember to give yourself enough time to REDUCE your speed as you approach
 * the mother ship.  You must land with a speed of 2 or less for a safe landing!
 *
 * As you near the mother ship you will get a reminder to lower your landing
 * gear.  Use the Gear Down button (upper right) to lower the gear.
 *
 * Keep the mother ship centered, speed low enough and land with your gear down
 * to be safely re-united with the mother ship.
 * 
 * NOTE:
 * The original plan was for us to add our rotary encoder to our design to
 * control the thrusters, but as sometimes happens when working with complex
 * devices our plans needed to change.  It turns out that there is some type
 * of conflict that prevents our rotary encoder from working correctly when
 * it's added to the switches, OLED display and 4-digit counter.
 *
 * However, we have unused buttons on the button matrix so we will use
 * those to control our thrust.
 *
 * Learn more at https://inventr.io/adventure
 *
 * Alex Eschenauer
 * David Schmidt
 * Greg Lyzenga
 */

/*
 * Arduino concepts introduced/documented in this lesson.
 * - Random numbers (randomSeed() and random())
 * - sprintf()
 *
 * Parts and electronics concepts introduced in this lesson.
 * - 
 */

// Explicitly include Arduino.h
#include "Arduino.h"

// ************************************************
//    Setup for OLED display and graphics library
// Include files for Graphics library used for our OLED display.
// Extensive documentation for this library can be found at https://github.com/olikraus/u8g2
#include <U8g2lib.h>  // Include file for the U8g2 library.
#include "Wire.h"     // Sometimes required for I2C communications.

// Use _2_ version of constructor and firstPage()/nextPage() for OLED
// graphics to save memory.
U8G2_SH1106_128X64_NONAME_2_HW_I2C lander_display(U8G2_R0, /* reset=*/U8X8_PIN_NONE);

/*
 * Again we'll use separate files to store our bitmap images.
 *
 * To create a new file, simply click the "..." to the right of the tab bar with
 * our sketch name and select "New Tab".  Enter the name for the new file and
 * click the tab to edit.  This lets us move all of our bitmaps into a separate
 * file so we don't have to scroll through them.
 */
#include "radar_arrows.h"
#include "small_landing_gear_bitmaps.h"
#include "ending_bitmaps.h"

// Create an array of pointers to each of the bitmap images.
// For a smoother animation you could simply add additional bitmaps
// into the sequence below and the code will automatically adjust.
const static char* LANDER_BITMAPS[] = {
  LANDING_GEAR_1,  // Gear up
  LANDING_GEAR_2,  // Gear lowering
  LANDING_GEAR_3,  // Gear lowering
  LANDING_GEAR_4,  // Gear down
};

// Calculate how many gear bitmaps we have by dividing the total size of the
// array by the size of a single item in the array.
const int GEAR_BITMAP_COUNT = sizeof(LANDER_BITMAPS) / sizeof(LANDER_BITMAPS[0]);

// Gear states with defined values used to change bitmap index.
enum GEAR_STATE {
  GEAR_IDLE = 0,      // Landing gear idle.  Don't change index when added to current
  GEAR_LOWERING = 1,  // Lowering gear, adds one to index for next "lowoer" bitmap
  GEAR_RAISING = -1   // Raising gear, subtracts one from index, showing gear retracting
};

// ************************************************
//   Setup for 4-digit, 7-segment speed display
#include <TM1637Display.h>
const byte DISTANCE_DISPLAY_DIO_PIN = 4;
const byte DISTANCE_DISPLAY_CLK_PIN = 5;
// Construct distance display handle.
TM1637Display distance_display(DISTANCE_DISPLAY_CLK_PIN, DISTANCE_DISPLAY_DIO_PIN);

// ************************************************
//   Setup for DIP switch pins.
//
// We will need almost all pins for Day 29, so here we show that we can use ANALOG
// pins as digitial pins when digital pins are scarce.
const byte CONFIRM_LEVER_PIN = A2;  // switch for bit 0 of our 3 bit value
const byte SYSTEMS_LEVER_PIN = A1;  // switch for bit 1 of our 3 bit value
const byte THRUST_LEVER_PIN = A0;   // switch for bit 2 of our 3 bit value

// ************************************************
//   Setup for our 4x4 button matrix.
#include <Keypad.h>  // 4x4 button matrix keypad library
const byte CONTROL_ROW_COUNT = 4;
const byte CONTROL_COLUMN_COUNT = 4;

const byte COLUMN_PINS[CONTROL_COLUMN_COUNT] = { 10, 11, 12, 13 };
const byte ROW_PINS[CONTROL_ROW_COUNT] = { 9, 8, 7, 6 };

// The Keypad library isn't restricted to just returning numbers or letters.
// Since we will be using the button matrix to control our lander we define
// an enum with our commands and then set up the buttons to return those
// values.
enum LANDER_CONTROLS {
  UNUSED,
  STEER_UP,
  STEER_DOWN,
  STEER_LEFT,
  STEER_RIGHT,
  STEER_UP_RIGHT,
  STEER_UP_LEFT,
  STEER_DOWN_RIGHT,
  STEER_DOWN_LEFT,
  LOWER_GEAR,
  RAISE_GEAR,
  RAISE_SPEED,
  LOWER_SPEED,
};

// Define our button array using constants to be returned for each button
char control_buttons[CONTROL_ROW_COUNT][CONTROL_COLUMN_COUNT] = {
  { STEER_UP_LEFT, STEER_UP, STEER_UP_RIGHT, LOWER_GEAR },         // 1st row
  { STEER_LEFT, UNUSED, STEER_RIGHT, RAISE_GEAR },                 // 2nd row
  { STEER_DOWN_LEFT, STEER_DOWN, STEER_DOWN_RIGHT, RAISE_SPEED },  // 3rd row
  { UNUSED, UNUSED, UNUSED, LOWER_SPEED },                         // 4th row
};

// Create lander button control object.
Keypad lander_controls = Keypad(makeKeymap(control_buttons), ROW_PINS, COLUMN_PINS,
                                CONTROL_ROW_COUNT, CONTROL_COLUMN_COUNT);

// ************************************************
// Here are the states our code will run through to perform the actual
// approach flight and landing in the mother ship bay.
enum APPROACH_STATE {
  APPROACH_INIT,       // Ensure all switches are off to begin
  APPROACH_PREFLIGHT,  // Wait for all switches to be enabled
  APPROACH_IN_FLIGHT,  // Begin to approach mother ship
  APPROACH_FINAL       // Lower landing gear!
};

// Use this value for our starting distance (just made up)
const int INITIAL_DISTANCE = 1394;  // how far to mother ship

// Maximum size of mother ship docking bay.  Initial display of
// mother ship is small dot, but expands to this size as we approach
//
// Odd nmumbers used to make it easy to center (same size to either
// size of center point).
const byte MAX_MOTHER_SHIP_WIDTH = 21;
const byte MAX_MOTHER_SHIP_HEIGHT = 15;

// ************************************************
//                     SETUP()
// ************************************************
void setup(void) {
  Serial.begin(9600);  // Initialize Serial console in case you want debut messages

  // We use random numbers to move the target mother ship randomly.
  // In order to get different random numbers each time we use this
  // function which reads from our UNCONNECTED analog pin which is
  // floating and thus will return different numbers.
  randomSeed(analogRead(A3));

  // Configure OLED display
  lander_display.begin();                     // initialize lander display
  lander_display.setFont(u8g2_font_6x10_tr);  // Set text font
  lander_display.setFontRefHeightText();      // Define how max text height is calculated
  lander_display.setFontPosTop();             // Y coordinate for text is at top of tallest character

  // Configure counter display
  distance_display.setBrightness(7);  // Set maximum brightness (value is 0-7)
  distance_display.clear();           // Clear the display

  // Configure DIP switch pins
  pinMode(CONFIRM_LEVER_PIN, INPUT);  // switch for bit 0 of our 3 bit value
  pinMode(SYSTEMS_LEVER_PIN, INPUT);  // switch for bit 1 of our 3 bit value
  pinMode(THRUST_LEVER_PIN, INPUT);   // switch for bit 2 of our 3 bit value
}

// ************************************************
//                     LOOP()
// ************************************************
void loop(void) {
  // Static variables that will retain state between loop() executions
  static unsigned long approach_start_time = 0;               // time thrusters are first fired
  static int current_gear_bitmap_index = 0;                   // Image of lander with gear up
  static enum APPROACH_STATE approach_state = APPROACH_INIT;  // Initial approach state
  static enum GEAR_STATE gear_state = GEAR_IDLE;              // Inital landing gear state
  static int lander_distance = INITIAL_DISTANCE;
  static int lander_speed = 0;  // Initial lander speed relative to mother ship
  // These will track the "drift" of the mother ship from center of radar
  static int mother_ship_x_offset = 0;
  static int mother_ship_y_offset = 0;

  // Read current values of all of our switches as booleans ("on" is true, "off" is false)
  bool thrust_lever = digitalRead(THRUST_LEVER_PIN);
  bool systems_lever = digitalRead(SYSTEMS_LEVER_PIN);
  bool confirm_lever = digitalRead(CONFIRM_LEVER_PIN);

  /*
   * Primary control state machine.
   *
   * Based on the current state of our approach to the lander, handle each
   * state's decisions, changing state when appropriate.
   */
  switch (approach_state) {

    // INIT state - Display switch status and ensure all are "OFF"
    case APPROACH_INIT:
      // All switches must be "off" before our approach sequence can be started
      // Since we save these as boolean (true/false) we can do this check on one
      // line that could be read as "if thrust is not true and systems is not true
      // and confirm is not true then..."
      if (!thrust_lever && !systems_lever && !confirm_lever) {
        // All switches are now off, ready for pre-flight
        approach_state = APPROACH_PREFLIGHT;  // Change state to Preflight
      }
      break;

    // PREFLIGHT state - All switches off.  Switch all on to begin approach
    case APPROACH_PREFLIGHT:
      // Once we have enabled thrusters and systems and confirmed we're ready
      // then switch to in-flight radar display.
      if (thrust_lever && systems_lever && confirm_lever) {  // All switches are "on"
        approach_state = APPROACH_IN_FLIGHT;                 // change to in-flight state
      }
      break;

    // FINAL state - Lower gear, we're about to land!
    case APPROACH_FINAL:
      // Check to see if a gear change button is pressed.  Do NOT wait for a key.
      // NOTE - code then drops into in-flight state!!
      // VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV

    // IN-FLIGHT state - Add thrust to move closer to mother ship.
    // (Remember, you will have to REDUCE thrust as you get closer)
    case APPROACH_IN_FLIGHT:

      switch (controlButtonPressed()) {
        case RAISE_SPEED:
          lander_speed++;  // increase velocity
          // If this is first time increasing speed then save the start time
          if (approach_start_time == 0) {
            approach_start_time = millis();
          }
          break;
        case LOWER_SPEED:
          // lower speed unless stopped
          if (lander_speed > 0) {
            lander_speed--;
          }
          break;
        case LOWER_GEAR:                           // Lower landing gear unless already lowered
          if (approach_state == APPROACH_FINAL) {  // Only works on final approach
            // Lowering gear is an animation created by changing bitmaps each frame
            // until the gear is completely lowered.
            if (current_gear_bitmap_index != GEAR_BITMAP_COUNT - 1) {
              gear_state = GEAR_LOWERING;  // increases bitmap index until lowered
            }
          }
          break;
        case RAISE_GEAR:  // Raise landing gear unless already raised
          // Raising gear is an animation created by changing the bitmap index
          // each frame until gear is up.
          if (current_gear_bitmap_index != 0) {  // Ignore if gear is already up
            gear_state = GEAR_RAISING;
          }
        case STEER_UP:
          mother_ship_y_offset++;  // Steer lander one pixel UP
          break;
        case STEER_DOWN:
          mother_ship_y_offset--;  // Steer lander one pixel DOWN
          break;
        case STEER_LEFT:
          mother_ship_x_offset++;  // Steer lander one pixel LEFT
          break;
        case STEER_RIGHT:
          mother_ship_x_offset--;  // Steer lander one pixel RIGHT
          break;
        case STEER_UP_RIGHT:
          mother_ship_x_offset--;  // Steer lander one pixel UP and RIGHT
          mother_ship_y_offset++;
          break;
        case STEER_UP_LEFT:
          mother_ship_x_offset++;  // Steer lander one pixel UP and LEFT
          mother_ship_y_offset++;
          break;
        case STEER_DOWN_RIGHT:
          mother_ship_x_offset--;  // Steer lander one pixel DOWN and RIGHT
          mother_ship_y_offset--;
          break;
        case STEER_DOWN_LEFT:
          mother_ship_x_offset++;  // Steer lander one pixel DOWN and LEFT
          mother_ship_y_offset--;
          break;
      }

      // Here we compute the drift of the mother ship using random numbers.
      // The mother ship cannot drift off the display, done by setting a
      // maximum drift.
      const byte MAX_DRIFT = 18;

      mother_ship_x_offset += getRandomDrift();  // returns -1, 0 or 1
      mother_ship_y_offset += getRandomDrift();  // returns -1, 0 or 1
      // Ensure mother ship doesn't drift off our radar display
      if (mother_ship_x_offset > MAX_DRIFT) mother_ship_x_offset = MAX_DRIFT;
      if (mother_ship_x_offset < -MAX_DRIFT) mother_ship_x_offset = -MAX_DRIFT;
      if (mother_ship_y_offset > MAX_DRIFT) mother_ship_y_offset = MAX_DRIFT;
      if (mother_ship_y_offset < -MAX_DRIFT) mother_ship_y_offset = -MAX_DRIFT;

      // Prepare for landing on final approach
      if (lander_distance < (INITIAL_DISTANCE / 10)) {
        approach_state = APPROACH_FINAL;  // on final approach - enable gear and warn
      }
      break;
  }

  // Because we specified our gear states as 0, 1 or -1 we can change bitmaps by
  // simply adding the gear state to our current gear bitmap index.
  current_gear_bitmap_index += gear_state;

  // If the gear animation has completed (index is either 0 or the index of our last bitmap)
  // then we change the gear state to IDLE to complete animation.
  if (current_gear_bitmap_index == 0 || current_gear_bitmap_index == GEAR_BITMAP_COUNT - 1) {
    gear_state = GEAR_IDLE;
  }

  // Update our lander display (OLED) using firstPage()/nextPage() methods which
  // use a smaller buffer to save memory.  Draw the exact SAME display each time
  // through this loop!
  lander_display.firstPage();
  do {
    switch (approach_state) {
      // Display switch status for INIT and PREFLIGHT states.
      case APPROACH_INIT:
      case APPROACH_PREFLIGHT:
        displayPreFlight(approach_state, thrust_lever, systems_lever, confirm_lever);
        break;

      case APPROACH_FINAL:
        displayFinal(current_gear_bitmap_index);
      case APPROACH_IN_FLIGHT:
        displayInFlight(lander_distance, lander_speed,
                        mother_ship_x_offset, mother_ship_y_offset);
        break;
    }
  } while (lander_display.nextPage());

  lander_distance -= lander_speed;  // Adjust distance by current speed

  // END OF FLIGHT!
  //
  // When we reach the mother ship (distance <= 0) then determine success
  // or failure and display finaly screen alternating with last radar image.
  char* ending_bitmp;
  if (lander_distance <= 0) {
    // Check to see if our lander landed inside the mother ship target box.
    if (abs(mother_ship_x_offset) < ((MAX_MOTHER_SHIP_WIDTH + 1) / 2)
        && abs(mother_ship_y_offset) < ((MAX_MOTHER_SHIP_HEIGHT + 1) / 2)) {
      lander_distance = 0;
      // We hit the target.  Now check speed to see if we were slow enough
      if (lander_speed <= 2) {  // Max safe landing speed is 2

        // Speed OK, but did we remember to lower the landing gear?
        if (current_gear_bitmap_index == GEAR_BITMAP_COUNT - 1) {  // Gear is down!
          ending_bitmp = ENDING_BITMAP_SUCCESS;                    // SUCCESS!
        } else {
          // Oops, gear is up.  Damage to lander, but we survived.
          ending_bitmp = ENDING_BITMAP_NO_GEAR;
        }
      } else {
        // Speed is too fast!  Lander AND mother ship destroyed.  (Ouch!)
        ending_bitmp = ENDING_BITMAP_TOO_FAST;
      }
    } else {
      // Missed the mother ship.  No fuel for another try.  Bye!
      ending_bitmp = ENDING_BITMAP_MISSED_MOTHER_SHIP;
    }

    // Show final distance
    distance_display.showNumberDec(0);

    // Calculate elapsed time (in ms) from first thrust.
    unsigned long elapsed_time = millis() - approach_start_time;

    // Now format to fractional seconds (SS.SSS) using sprintf
    char buffer[20];  // buffer long enough for final display line.

    // Since elapse time is a long integer we can get the number of seconds
    // by simply dividing by 1000 and the fractional portion is dropped.  The
    // Modulo operator ('%') returns the REMAINDER after dividing left side by
    // the value on the right.  This gives us the fractional number seconds.
    // Sprintf() uses "lu" to indicate that the value is a "unsigned long"
    // ("lu" does NOT work!).
    sprintf(buffer, "%4lu.%03lu Sec", elapsed_time / 1000, elapsed_time % 1000);

    // Final display.  Alternate between splash screen with time and
    // final radar view.
    do {
      lander_display.firstPage();
      do {
        lander_display.drawStr(0, 0, buffer);
        lander_display.drawXBMP(0, 10, ENDING_BITMAP_WIDTH, ENDING_BITMAP_HEIGHT, ending_bitmp);
      } while (lander_display.nextPage());
      delay(2000);

      lander_display.firstPage();
      do {
        displayFinal(current_gear_bitmap_index);
        displayInFlight(lander_distance, lander_speed,
                        mother_ship_x_offset, mother_ship_y_offset);
      } while (lander_display.nextPage());
      delay(2000);
    } while (true);  // repeat this final display until HERO is reset
    // NEVER REACHED.  THIS IS OUR FINAL EXECUTION OF LOOP();
  }
  delay(100);  // Delay 1/10 second before next loop
}

// ************************************************
//             Preflight display
// ************************************************
// Update lander display with the status of our switches for INIT and PREFLIGHT states
void displayPreFlight(enum APPROACH_STATE approach_state,
                      bool thruster_lever,
                      bool systems_lever,
                      bool confirm_lever) {
  // Display all text referenced from upper left bit X, Y
  lander_display.setFontPosTop();

  // Draw title lines at top of display, updating y_offset afterwards
  byte y_offset = drawString(0, 0, "Exploration Lander");
  y_offset = drawString(0, y_offset, "Approach Sequence");

  // Set y_offset to point four lines above bottom of display
  y_offset = lander_display.getDisplayHeight() - (4 * lander_display.getMaxCharHeight());
  // Display status of each switch
  y_offset = drawString(0, y_offset,
                        (String("Thrusters: ") + String(thruster_lever ? "ON" : "OFF")).c_str());
  y_offset = drawString(0, y_offset,
                        (String("Systems  : ") + String(systems_lever ? "ON" : "OFF")).c_str());
  y_offset = drawString(0, y_offset,
                        (String("Confirm  : ") + String(confirm_lever ? "ON" : "OFF")).c_str());

  // Display final status line
  drawString(0, y_offset, (String("Countdown ") + liftoffStateToString(approach_state)).c_str());
}

// ************************************************
//   In-Flight display (including final approach)
// ************************************************
// Radar display for steering into mother ship docking bay.
void displayInFlight(int lander_distance,
                     int lander_speed,
                     int mother_ship_x_offset,
                     int mother_ship_y_offset) {

  // Mother ship initially appears as a single dot, but expands into a rectangle
  // as we get closer.  Scaled based on the maximum width, from 1 to MAX.
  //
  // Divide distance to mother ship into segments.  The number of segments is
  // one less than the width of our mother ship.
  const unsigned int SEGMENT_SIZE = INITIAL_DISTANCE / (MAX_MOTHER_SHIP_WIDTH - 1);
  byte segment_number = lander_distance / SEGMENT_SIZE;  // from (width - 1) to 0

  // subtract segment number from width/height to get visible width (minimum 1)
  int mother_ship_width = MAX_MOTHER_SHIP_WIDTH - segment_number;
  int mother_ship_height = MAX_MOTHER_SHIP_HEIGHT - segment_number;
  if (mother_ship_height < 1) {
    mother_ship_height = 1;  // Always at least 1 pixel high
  }

  // Display distance to mother ship on our distance display
  distance_display.showNumberDec(lander_distance);

  // coordinates of the center of our radar display
  const byte RADAR_CENTER_X = (lander_display.getDisplayWidth() / 2 / 2);  // center of left half
  const byte RADAR_CENTER_Y = (lander_display.getDisplayHeight() / 2);     // Vertical center
  const byte RADAR_RADIUS = 25;

  // Display bitmaps with 0 bits set to transparent.  This allows us to overlay
  // our arrows over the radar circle cleanly.
  lander_display.setBitmapMode(1);

  // Draw radar display circle and center pointer dot.
  lander_display.drawCircle(RADAR_CENTER_X, RADAR_CENTER_Y, RADAR_RADIUS);
  lander_display.drawPixel(RADAR_CENTER_X, RADAR_CENTER_Y);

  //====================================================================
  //====================================================================

  /*
   * As the mother ship's radar return drifts on the screen this section
   * of the code will display an arrow on the outside of the radar circle.
   *
   * The first constants can be changed so that the arrows don't appear
   * until the target pointer is outside the landing bay box, but currently
   * the arrows appear after small amounts of drift.
   *
   * The coordinates for the arrows were originally generated by ChatGPT
   * and then individually tweeked for perfect location.  Because of this
   * the coordinates will need to be manually adjusted if the radius of
   * the circle is changed.
   */
  const int DRIFT_BEFORE_ARROW_X = 2;  // try (mother_ship_width / 2) - 2; for late arrows
  const int DRIFT_BEFORE_ARROW_Y = 2;  // try (mother_ship_height / 2) - 2; for late arrows

  // Outer set of if/else statements check for left/right drift (X coordinate)
  if (mother_ship_x_offset < -DRIFT_BEFORE_ARROW_X) {  // left of center
    // Inner set of if/else statements check for up/down drift (Y coordinate)
    if (mother_ship_y_offset < -DRIFT_BEFORE_ARROW_Y) {                             // above center
      lander_display.drawXBMP(9, 9, ARROW_SIZE_X, ARROW_SIZE_Y, ARROW_UP_LEFT);     // Up-Left
    } else if (mother_ship_y_offset > DRIFT_BEFORE_ARROW_Y) {                       // below center
      lander_display.drawXBMP(8, 45, ARROW_SIZE_X, ARROW_SIZE_Y, ARROW_DOWN_LEFT);  // Down-Left
    } else {                                                                        // close to center in Y direction
      lander_display.drawXBMP(1, 27, ARROW_SIZE_X, ARROW_SIZE_Y, ARROW_LEFT);       // Left
    }
  } else if (mother_ship_x_offset > DRIFT_BEFORE_ARROW_X) {                           // Right of center
    if (mother_ship_y_offset < -DRIFT_BEFORE_ARROW_Y) {                               // above center
      lander_display.drawXBMP(45, 8, ARROW_SIZE_X, ARROW_SIZE_Y, ARROW_UP_RIGHT);     // Up-Right
    } else if (mother_ship_y_offset > DRIFT_BEFORE_ARROW_Y) {                         // below center
      lander_display.drawXBMP(45, 45, ARROW_SIZE_X, ARROW_SIZE_Y, ARROW_DOWN_RIGHT);  // Down-Right
    } else {                                                                          // close to center in Y direction
      lander_display.drawXBMP(53, 27, ARROW_SIZE_X, ARROW_SIZE_Y, ARROW_RIGHT);       // Right
    }
  } else {                                                                      // close to center in X direction
    if (mother_ship_y_offset < -DRIFT_BEFORE_ARROW_Y) {                         // above center
      lander_display.drawXBMP(27, 1, ARROW_SIZE_X, ARROW_SIZE_Y, ARROW_UP);     // Up
    } else if (mother_ship_y_offset > DRIFT_BEFORE_ARROW_Y) {                   // below center
      lander_display.drawXBMP(27, 53, ARROW_SIZE_X, ARROW_SIZE_Y, ARROW_DOWN);  // Down
    }                                                                           // else NO arrow as we're close to target
  }

  // We will use sprintf() to format the lander speed line
  char buffer[9];                                                               // Length of line plus one for terminating null.
  sprintf(buffer, "SPD: %2d", lander_speed);                                    // format speed into buffer
  int width = lander_display.getStrWidth(buffer);                               // width of string in pixels
  lander_display.drawStr(lander_display.getDisplayWidth() - width, 0, buffer);  // display in upper right

  // Now draw the image of the mother ship as a rectangle, sized based on distance and
  // offset the x/y coordinates so that ship offset is always from the CENTER of the
  // mother ship.
  byte x_offset = RADAR_CENTER_X + mother_ship_x_offset - (mother_ship_width / 2);
  byte y_offset = RADAR_CENTER_Y + mother_ship_y_offset - (mother_ship_height / 2);
  lander_display.drawFrame(x_offset, y_offset, mother_ship_width, mother_ship_height);
}

// ************************************************
// When lander is about to land we'll add an image of the lander
// with landing gear status along with gear prompt messages.
void displayFinal(int current_gear_bitmap_index) {
  int gear_down_index = GEAR_BITMAP_COUNT - 1;  // index of the LAST bitmap image

  // Coordinates below  manually adjusted to display in upper right
  // two lines below the speed line.
  byte x_offset = (lander_display.getDisplayWidth() / 2) + 11;
  byte y_offset = lander_display.getMaxCharHeight() * 2;  // offset to third line
  if (current_gear_bitmap_index == 0) {                   // Gear is up.  Prompt to lower
    lander_display.drawStr(x_offset, y_offset, "Drop gear");
  } else if (current_gear_bitmap_index < gear_down_index) {  // Gear is lowering
    lander_display.drawStr(x_offset, y_offset, "Lowering");
  } else {
    lander_display.drawStr(x_offset, y_offset, "Gear OK");  // Gear is down ()
  }

  // Calculate our x and y offsets to center our bitmap graphics
  // Get offsets to lower-right area of screen.  Height allows 3 lines of text above
  x_offset = (lander_display.getDisplayWidth() / 2);  // 64
  x_offset += ((lander_display.getDisplayWidth() - x_offset) - LANDING_GEAR_BITMAP_WIDTH) / 2;
  y_offset = lander_display.getDisplayHeight() - (lander_display.getMaxCharHeight() * 3);
  y_offset += ((lander_display.getDisplayHeight() - y_offset) - LANDING_GEAR_BITMAP_HEIGHT) / 2;

  // Draw current bitmap centered in lower right quadrant
  lander_display.drawXBMP(x_offset, y_offset,
                          LANDING_GEAR_BITMAP_WIDTH, LANDING_GEAR_BITMAP_HEIGHT,
                          LANDER_BITMAPS[current_gear_bitmap_index]);
}

// ************************************************
// "helper" function that returns a different string for each enum state.
String liftoffStateToString(enum APPROACH_STATE approach_state) {
  switch (approach_state) {
    case APPROACH_INIT:
      return ("Init");
      break;
    case APPROACH_PREFLIGHT:
      return ("Preflight");
      break;
  }
}

// ************************************************
// Draw a line of text on our OLED display at x, y, returning new y
// value that is immediately below the new line of text.
byte drawString(byte x, byte y, char* string) {
  lander_display.drawStr(x, y, string);
  return (y + lander_display.getMaxCharHeight());  // return new y_offset on display
}

// They Keypad library only returns a button value when it is initially
// pressed.  We wish to continue to get the same value for as long as
// a button is pressed.  This function keeps track of the last button
// pressed and returns it until the button is released or another
// button is pressed.
enum LANDER_CONTROLS controlButtonPressed() {
  static char last_key = NO_KEY;

  char current_key = lander_controls.getKey();
  if (current_key != NO_KEY) {
    last_key = current_key;  // New key seen, save as last
  }

  // If the button is released reset to NO_KEY
  if (lander_controls.getState() == RELEASED) {
    last_key = NO_KEY;
    current_key = NO_KEY;
  } else {
    current_key = last_key;  // button still pressed so return last button seen.
  }
  return (current_key);
}

const byte DRIFT_CONTROL = 3;  // Must be > 1.  Higher numbers slow drift rate

int getRandomDrift() {
  // Random(low, high) returns a random number from low to ONE LESS THAN high.
  // We use -1, 0 or 1 for the drift.  To *slow* the drift we can increae the
  // number of values that indicate "no drift" by generating numbers higher
  // than 1 and if the random number is higher we set drift to 0.
  // With a drift control of 3 we get random numbers (-1, 0, 1, 2) and if 2 we
  // change to 0, doubleing the times we get NO drift.
  int drift = random(-1, DRIFT_CONTROL);
  if (drift > 1) {  // Values over 1 are changed to 0
    drift = 0;
  }
  return (drift);
}