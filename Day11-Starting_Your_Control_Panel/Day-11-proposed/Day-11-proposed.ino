/*
 * 30 Days - Lost in Space
 * Day 8 - A Better Way to Do Things
 *
 * Learn more at https://inventr.io/adventure
 *
 * Today we introduce you to a 4x4 button Keypad.  This keypad is very similar to
 * what is found on a calculator or even a digital phone.  This keypad uses only 8
 * pins 
 *
 * Alex Eschenauer
 * David Schmidt
 * Greg Lyzenga
 */

/*
 * Arduino concepts introduced/documented in this lesson.
 * - float:   Variable type for decimal numbers that include a decimal point
 * - return:  Used by functions to return a single value
 * - else if: Control structure for making multiple if decisions together
 *
 * Parts and electronics concepts introduced in this lesson.
 */

// Explicitly include Arduino.h
#include "Arduino.h"

/*
 * COMMENT library use and install instructions here.'
 * COMMENT HOW TO FIND LIBRARY DOCUMENTATION
 */
#include <Keypad.h>

// Our keypad has 4 rows, each with 4 columns.
const byte ROWS = 4;
const byte COLS = 4;

// Since the keypad has 4 rows of 4 columns each we use a two dimensional array to
// identify the BUTTONS.
/*
 * COMMENT TWO DIMENSIONAL ARRAYS.  ZERO INDEX
 * COMMENT CHARACTER TYPE (AND SINGLE QUOTE USE)
 */ 
const char BUTTONS[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

// These arrays define constant arrays showing which pins are connected to each row/column
const byte ROW_PINS[ROWS] = { 5, 4, 3, 2 };
const byte COL_PINS[COLS] = { 6, 7, 8, 9 };

// Using the Keypad.h Library, we are going to define a custom keypad.
// In order to do that, it needs to know the following:
// What the keys are (a 2D Array of characters (char)),
// what pins are being used (2 thru 9),
// how many rows there are (4), and how many columns (4).
// NOTE: this also does the proper pinMode() commands so we don't need them in our setup()
Keypad heroKeypad = Keypad(makeKeymap(BUTTONS), ROW_PINS, COL_PINS, ROWS, COLS);

void setup() {
  Serial.begin(9600);  // Begin monitoring via the serial monitor
}

void loop() {
  // heroKeypad.waitForKey() will wait here until any button is pressed
  char pressedButton = heroKeypad.waitForKey();  // Wait until a button is pressed

  // Display the character (from our BUTTONS array) for the button that was pressed.
  Serial.println(pressedButton);
}