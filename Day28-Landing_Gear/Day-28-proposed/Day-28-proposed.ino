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
const static char* SWITCH_BITMAPS[] = {
  LANDING_1,
  LANDING_2,
  LANDING_3,
  LANDING_4,
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
// pins as digitial pins when necessary.
const byte CONFIRM_LEVER_PIN = A2;  // switch for bit 0 of our 3 bit value
const byte SYSTEMS_LEVER_PIN = A1;  // switch for bit 1 of our 3 bit value
const byte THRUST_LEVER_PIN = A0;   // switch for bit 2 of our 3 bit value

// ************************************************
// Setup for our 4x4 button matrix.
#include <Keypad.h>  // 4x4 button matrix keypad library
const byte ROWS = 4;
const byte COLS = 4;

byte colPins[ROWS] = { 10, 11, 12, 13 };
byte rowPins[COLS] = { 9, 8, 7, 6 };

char buttons[ROWS][COLS] = {
  { '1', '2', '3', 'A' },  // 1st row
  { '4', '5', '6', 'B' },  // 2nd row
  { '7', '8', '9', 'C' },  // 3rd row
  { '*', '0', '#', 'D' }   // 4th row
};

Keypad myAwesomePad = Keypad(makeKeymap(buttons), rowPins, colPins, ROWS, COLS);

// ************************************************
// Here are the states our code will run through.  We'll build on this later to
// perform the actual approach flight and landing in the mother ship bay.
enum APPROACH_STATE {
  APPROACH_INIT,    // Ensure all switches are off to begin
  APPROACH_PREFLIGHT, // 
  // APPROACH_IN_FLIGHT,
  APPROACH_FINAL,  // Lower landing gear!
  // APPROACH_TOO_FAST,
  // APPROACH_DOCKED
};

const int GEAR_BITMAP_COUNT = sizeof(SWITCH_BITMAPS) / sizeof(SWITCH_BITMAPS[0]);
enum GEAR_STATE {
  GEAR_IDLE = 0,
  GEAR_LOWERING = 1,
  GEAR_RAISING = -1
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
  static int current_gear_bitmap = 0;  // Start with image of lander with gear up
  static enum APPROACH_STATE approach_state = APPROACH_INIT;
  // APPROACH_FINAL; //
  static enum GEAR_STATE gear_state = GEAR_IDLE;
  static char last_key = -1;  // key previously seen

  // Read current values of all of our switches as booleans ("on" is true, "off" is false)
  bool thrust_lever = digitalRead(THRUST_LEVER_PIN);
  bool systems_lever = digitalRead(SYSTEMS_LEVER_PIN);
  bool confirm_lever = digitalRead(CONFIRM_LEVER_PIN);
  // Serial.println(approach_state);
  // Serial.print("  Switches: ");
  // Serial.print(thrust_lever);
  // Serial.print(", ");
  // Serial.print(systems_lever);
  // Serial.print(", ");
  // Serial.println(confirm_lever);

  switch (approach_state) {
    case APPROACH_INIT:
      // Serial.println("case APPROACH_INIT");
      if (!thrust_lever && !systems_lever && !confirm_lever) {
        approach_state = APPROACH_PREFLIGHT;
      }
      break;
    case APPROACH_PREFLIGHT:
      // Serial.println("case APPROACH_PREFLIGHT");
      if (thrust_lever && systems_lever && confirm_lever) {
        approach_state = APPROACH_FINAL;
      }
      break;
    // case APPROACH_IN_FLIGHT:
    //   Serial.println("case APPROACH_IN_FLIGHT");
    //   approach_state = APPROACH_FINAL;
    //   break;
    case APPROACH_FINAL:
      // Serial.println("case APPROACH_FINAL");
      char customKey = myAwesomePad.getKey();
      if (customKey && customKey != last_key) {
        Serial.println(customKey);
        last_key = customKey;
      }

      switch (customKey) {
        case 'A':  // Lower landing gear
          gear_state = GEAR_LOWERING;
          break;
        case 'B':  // Gear down
          gear_state = GEAR_RAISING;
      }
      break;
  }
  // if (gear_state != GEAR_IDLE) {
  current_gear_bitmap += gear_state;
  if (current_gear_bitmap == 0 || current_gear_bitmap == GEAR_BITMAP_COUNT - 1) {
    gear_state = GEAR_IDLE;
  }

  // Display calculated switch value on our 4 digit display
  // bitmap_number_display.showNumberDecEx(switch_value);

  // Display selected bitmap on our OLED lander display
  lander_display.firstPage();
  do {
    switch (approach_state) {
      case APPROACH_INIT:
      case APPROACH_PREFLIGHT:
        preflightDisplay(approach_state, thrust_lever, systems_lever, confirm_lever);
        break;
      case APPROACH_FINAL:
        finalDisplay(current_gear_bitmap);
        break;
    }

  } while (lander_display.nextPage());

  delay(100);
}

void preflightDisplay(enum APPROACH_STATE approach_state,
                      bool thruster_lever,
                      bool systems_lever,
                      bool confirm_lever) {
  lander_display.setFontPosTop();
  byte y_offset = drawString(0, 0, "Exploration Lander");
  y_offset = drawString(0, y_offset, "Approach Sequence");
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
  drawString(0, y_offset, (String("Countdown ") + liftoffStateToString(approach_state)).c_str());
}

void finalDisplay(int current_gear_bitmap) {
  // Flash lander bitmap if gear isn't down
  // display current gear bitmap as gear lowers

  // .drawXBMP() displays each bitmap centered in the display based
  // on it's size.

  // Calculate our x and y offsets for our bitmap graphics
  byte x_offset = (lander_display.getDisplayWidth() - LANDING_GEAR_BITMAP_WIDTH) / 2;
  byte y_offset = (lander_display.getDisplayHeight() - LANDING_GEAR_BITMAP_HEIGHT) / 2;

  lander_display.drawXBMP(x_offset, y_offset,
                          LANDING_GEAR_BITMAP_WIDTH, LANDING_GEAR_BITMAP_HEIGHT,
                          SWITCH_BITMAPS[current_gear_bitmap]);
}

// "helper" function that returns a different string for each enum state.
String liftoffStateToString(enum APPROACH_STATE approach_state) {
  switch (approach_state) {
    case APPROACH_INIT:
      return ("Init");
      break;
    case APPROACH_PREFLIGHT:
      return ("Preflight");
      break;
      // case COUNTDOWN:
      //   return ("Active");
      //   break;
      // case LIFTOFF:
      //   return ("Complete");
      //   break;
      // case ABORT:
      //   return ("ABORT");
      //   break;
  }
}

// Draw a line of text on our OLED display at x, y, returning new y
// value that is immediately below the new line of text.
byte drawString(byte x, byte y, char* string) {
  lander_display.drawStr(x, y, string);
  return (y + lander_display.getMaxCharHeight());  // return new y_offset on display
}