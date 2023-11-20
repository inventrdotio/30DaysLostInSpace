/*
 * 30 Days - Lost in Space
 * Day 28 - Landing Gear
 *
 * Now that the safety of the mother ship is in sight we need to consider
 * our final landing.  While the lander has landing gear, it (of course) was
 * controlled from the failed computer.
 *
 * We'll start by confirming all switches are in the OFF position and then
 * enable our approach code.  Currently the approach code will only excersize
 * the landing gear, but we'll build on that later to perform our approach
 * and landing at the mother ship.
 *
 * We'll add your 16 button matrix to our control panel and use two
 * of the buttons to raise and lower the landing gear.  You'll need
 * confirmation of the gear position, so we'll use the OLED to display
 * our gear status using bitmaps.
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
 * - using analog pins as digital pins
 * - switches to binary
 * - creating include files
 * - enum with defined values
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
// ************************************************
#include "landing_gear_bitmaps.h"

// Create an array of pointers to each of the bitmap images.
// For a smoother animation you could simply add additional bitmaps
// into the sequence below and the code will automatically adjust.
const static char* LANDER_BITMAPS[] = {
  LANDING_1,  // Gear up
  LANDING_2,  // Gear started lowering
  LANDING_3,  // Gear lowered further
  LANDING_4,  // Gear down.
};

// Calculate how many gear bitmaps we have by dividing the total size of the
// array by the size of a single item in the array.
const int GEAR_BITMAP_COUNT = sizeof(LANDER_BITMAPS) / sizeof(LANDER_BITMAPS[0]);

/*
 * Enums with defined values
 *
 * If you don't give an enum item a value the system will define one for you.  This is
 * often the case when these are just used to define the entire set of possible values
 * and distinguish between them.
 *
 * However, you CAN assign a value to each item in an enum.  We will use this in our
 * code so that we can add the current state to the index to which bitmap is displayed.
 * When we raise the gear we will "add" -1 to the index, causing the index to go down
 * towards 0 (our "gear raised" bitmap).
 */
enum GEAR_STATE {
  GEAR_IDLE = 0,      // Landing gear idle.  Don't change index when added to current
  GEAR_LOWERING = 1,  // Lowering gear, adds one to index for next "lowoer" bitmap
  GEAR_RAISING = -1   // Raising gear, subtracts one from index, showing gear retracting
};

// ************************************************
// Include file for 4 digit - 7 segment display library
#include <TM1637Display.h>
const byte BITMAP_NUMBER_DISPLAY_DIO_PIN = 2;
const byte BITMAP_NUMBER_DISPLAY_CLK_PIN = 3;
// Construct bitmap_number_display handle.
TM1637Display bitmap_number_display(BITMAP_NUMBER_DISPLAY_CLK_PIN, BITMAP_NUMBER_DISPLAY_DIO_PIN);

// ************************************************
// Define pins for our DIP switches
// We will need almost all pins for Day 29, so here we show that we can use ANALOG
// pins as digitial pins when digital pins are scarce.
const byte CONFIRM_LEVER_PIN = A2;  // switch for bit 0 of our 3 bit value
const byte SYSTEMS_LEVER_PIN = A1;  // switch for bit 1 of our 3 bit value
const byte THRUST_LEVER_PIN = A0;   // switch for bit 2 of our 3 bit value

// ************************************************
// Setup for our 4x4 button matrix.
#include <Keypad.h>  // 4x4 button matrix keypad library
const byte CONTROL_ROW_COUNT = 3;
const byte CONTROL_COLUMN_COUNT = 4;

const byte COLLUMN_PINS[CONTROL_COLUMN_COUNT] = { 10, 11, 12, 13 };
const byte ROW_PINS[CONTROL_ROW_COUNT] = { 9, 8, 7 };

// The Keypad library isn't restricted to just returning numbers or letters.
// Since we will be using the button matrix to control our lander we define
// an enum with our commands and then set up the buttons to return those
// values.
enum LANDER_CONTROLS {
  UNUSED,
  LOWER_GEAR,
  RAISE_GEAR,
};

char buttons[CONTROL_ROW_COUNT][CONTROL_COLUMN_COUNT] = {
  { UNUSED, UNUSED, UNUSED, LOWER_GEAR },  // 1st row
  { UNUSED, UNUSED, UNUSED, RAISE_GEAR },  // 2nd row
  { UNUSED, UNUSED, UNUSED, UNUSED },      // 3rd row
};

Keypad lander_controls = Keypad(makeKeymap(buttons), ROW_PINS, COLLUMN_PINS,
                                CONTROL_ROW_COUNT, CONTROL_COLUMN_COUNT);

// ************************************************
// Here are the states our code will run through.  We'll build on this later to
// perform the actual approach flight and landing in the mother ship bay.
enum APPROACH_STATE {
  APPROACH_INIT,       // Ensure all switches are off to begin
  APPROACH_PREFLIGHT,  // Wait for all switches to be enabled
  APPROACH_FINAL,      // Lower landing gear!
};

// ************************************************
void setup(void) {
  Serial.begin(9600);

  // Configure counter display
  bitmap_number_display.setBrightness(7);  // Set maximum brightness (value is 0-7)
  bitmap_number_display.clear();           // Clear the display

  // Configure DIP switch pins
  pinMode(CONFIRM_LEVER_PIN, INPUT);  // switch for bit 0 of our 3 bit value
  pinMode(SYSTEMS_LEVER_PIN, INPUT);  // switch for bit 1 of our 3 bit value
  pinMode(THRUST_LEVER_PIN, INPUT);   // switch for bit 2 of our 3 bit value

  lander_display.begin();                     // initialize lander display
  lander_display.setFont(u8g2_font_6x10_tr);  // Set text font
  lander_display.setFontRefHeightText();      // Define how max text height is calculated
  lander_display.setFontPosTop();             // Y coordinate for text is at top of tallest character
}

// ************************************************
void loop(void) {
  static int current_gear_bitmap_index = 0;                   // Start with image of lander with gear up
  static enum APPROACH_STATE approach_state = APPROACH_INIT;  // Initial approach state
  static enum GEAR_STATE gear_state = GEAR_IDLE;              // Inital landing gear state

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
        approach_state = APPROACH_PREFLIGHT;
      }
      break;

    // PREFLIGHT state - All switches off, ensure all switches are on to begin
    case APPROACH_PREFLIGHT:
      // Once we have enabled thrusters and systems and confirmed we're ready
      // then today we'll just test the landing gear for now (final approach).
      if (thrust_lever && systems_lever && confirm_lever) {  // All switches are "on"
        approach_state = APPROACH_FINAL;                     // for now just enable landing gear testing
      }
      break;

    // FINAL state - Lower gear, we're about to land!
    case APPROACH_FINAL:
      // Check to see if a gear change button is pressed.  Do NOT wait for a key.
      char customKey = lander_controls.getKey();

      // To test landing gear we only check for gear change buttons, ignoring all
      // other buttons for now.
      switch (customKey) {
        case LOWER_GEAR:  // Lower landing gear unless already lowered
          if (current_gear_bitmap_index != GEAR_BITMAP_COUNT - 1) {
            gear_state = GEAR_LOWERING;
          }
          break;
        case RAISE_GEAR:  // Raise landing gear unless already raised
          if (current_gear_bitmap_index != 0) {
            gear_state = GEAR_RAISING;
          }
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

      // Display current lander bitmap, showing gear status.
      case APPROACH_FINAL:
        displayFinal(current_gear_bitmap_index);
        break;
    }
  } while (lander_display.nextPage());

  delay(100);  // Delay 1/10 second before next loop
}

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
// When lander is about to land we'll display a "final approach" display showing
// the landing gear status.
void displayFinal(int current_gear_bitmap_index) {
  // Calculate our x and y offsets to center our bitmap graphics
  byte x_offset = (lander_display.getDisplayWidth() - LANDING_GEAR_BITMAP_WIDTH) / 2;
  byte y_offset = (lander_display.getDisplayHeight() - LANDING_GEAR_BITMAP_HEIGHT) / 2;

  // Draw current bitmap centered in display.
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