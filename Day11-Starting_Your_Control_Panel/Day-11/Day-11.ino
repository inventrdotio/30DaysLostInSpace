/*
 * 30 Days - Lost in Space
 * Day 11 - Starting your control panel
 *
 * Learn more at https://inventr.io/adventure
 *
 * Today we introduce you to a 4x4 button Keypad.  This keypad is very similar to
 * what is found on a calculator or even a digital phone.  This keypad uses only 8
 * pins to encode 16 buttons by dividing the keypad into rows and columns.  When
 * a button is pressed it can be identified by finding which row pin and which column
 * pin are pressed.
 *
 * We simplify this process by using a library written for decoding similar keypads.
 *
 * Alex Eschenauer
 * David Schmidt
 * Greg Lyzenga
 */

/*
 * Arduino concepts introduced/documented in this lesson.
 * - libraries: Code provided by others that we can use in our sketches
 * - char type: Represents a single character like 'A', 'd', '4' or '*'.
 * - arrays:    Variables of the same type arranged as a list where each item
 *              can be accessed using an index.  Arrays can be one dimensional
 *              like a list (with one index) or two dimensional like a spreadsheet
 *              table with rows and columns (using row and column indexes).
 *
 * Parts and electronics concepts introduced in this lesson.
 */

// Explicitly include Arduino.h
#include "Arduino.h"

/*
 * Instead of writing all the code necessary to check all 8 pins and calculate
 * which button is pressed we will use a "library" that has already been written
 * for us and simply call functions in that library.
 *
 * Please refer to the lesson and lesson videos to load the Keypad library into
 * your Arduino IDE before you use it for the first time.
 *
 * In order to use the Keypad library we include the file "Keypad.h".
 */
#include <Keypad.h>

// Our keypad has 4 rows, each with 4 columns.
const byte ROWS = 4;
const byte COLS = 4;

/*
 * A one dimensional array is like a list of similar variables.  We use an "index" number
 * to access each item.  To access values in an array we use the name of the array followed
 * immediately by the index in square brackets: name[index].  The index can either be a
 * constant ("name[3]") or a variable containing a value:
 *
 * byte my_index = 3;
 * name[my_index] = value;
 *
 * Indexes start with zero, not one.  Think of the index as a number *added* to the first
 * location.  So, to access the first item in our array we add 0.  To access the second
 * item in the array we add 1.
 *
 * In our first array below, ROW_PINS[0] is set to 5 and ROW_PINS[2] is 3.
 */

// These constant arrays contain the pins connected to the keypad's row and column pins.
const byte ROW_PINS[ROWS] = { 5, 4, 3, 2 };
const byte COL_PINS[COLS] = { 6, 7, 8, 9 };

/*
  * Character Type (char)
  *
  * In Arduino C++ we have previousluy used strings of characters using double quotes ("my
  * string").  But for a single character we need to use single quotes to indicate that there
  * is just ONE character ('A').
  */

/*
 * Two dimensional array
 *
 * A two dimensional array combines multiple rows of one-dimensional array into a table
 * using two indexes using square brackets.  To access any item in the array the first
 * index is added to the row, and then the second index is added to the column.
 *
 * In the BUTTONS array below BUTTONS[0][0] is set to the character '1' and BUTTONS[2][3]
 * is set to the character 'C'.
 */

// Since the keypad has 4 rows of 4 columns each we use a two dimensional array to
// configure what character will be returned when each button is pressed.
const char BUTTONS[ROWS][COLS] = {
  { '1', '2', '3', 'A' },  // Row 0
  { '4', '5', '6', 'B' },  // Row 1
  { '7', '8', '9', 'C' },  // Row 2
  { '*', '0', '#', 'D' }   // Row 3
};

/*
 * Using the Keypad.h Library, we are going to define a custom keypad to return
 * the characters we wish when each key is pressed.
 *
 * To do this, we create a heroKeypad object configured with our BUTTONS array,
 * the pins used for the rows and columns and lastly how many rows and how many
 * columns are on our kepad.
 *
 * NOTE: this also does the proper pinMode() commands so we don't need them in our setup()
 */
Keypad heroKeypad = Keypad(makeKeymap(BUTTONS), ROW_PINS, COL_PINS, ROWS, COLS);

void setup() {
  Serial.begin(9600);  // Initialize the serial monitor
}

void loop() {
  // heroKeypad.waitForKey() will wait here until any button is pressed and
  // returns the character we defined in our BUTTONS array.
  char pressedButton = heroKeypad.waitForKey();  // Wait until a button is pressed

  // Display the character returned for the button that was pressed.
  Serial.println(pressedButton);
}