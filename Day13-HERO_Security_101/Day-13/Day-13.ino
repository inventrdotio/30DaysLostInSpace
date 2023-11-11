/*
 * 30 Days - Lost in Space
 * Day 13 - HERO Security 101
 *
 * Learn more at https://inventr.io/adventure
 *
 * Playing tones was fun, but now it's time to get back to business.  Let's use
 * the 4x4 button keypad input a Personal Identification Number (PIN) to unlock
 * access to the lander's control panel.
 *
 * Alex Eschenauer
 * David Schmidt
 * Greg Lyzenga
 */

/*
 * Arduino concepts introduced/documented in this lesson.
 * - return:  Used by functions to return a single value and return immediately
 *            to the caller of the function.
 * - boolean type: bool is used for a value that can be "true" or "false"
 *                 NOTE: when testing values for true/false the value 0 is considered
 *                       "false" and any non-zero value is considered "true".
 *
 * Parts and electronics concepts introduced in this lesson.
 */

// Explicitly include Arduino.h
#include "Arduino.h"

// Include Keypad library#include <Keypad.h>
#include <Keypad.h>

// Our HERO keypad has 4 rows, each with 4 columns.
const byte ROWS = 4;
const byte COLS = 4;

const byte PIN_LENGTH = 4;    // PIN code is 4 button presses
char current_pin[PIN_LENGTH] = { '0', '0', '0', '0' }; // Initial PIN is four zeros.

// Define what characters will be returned by each button
const char BUTTONS[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

// Define row and column pins connected to the keypad
const byte ROW_PINS[ROWS] = { 5, 4, 3, 2 };
const byte COL_PINS[COLS] = { 6, 7, 8, 9 };

Keypad heroKeypad = Keypad(makeKeymap(BUTTONS), ROW_PINS, COL_PINS, ROWS, COLS);

const byte BUZZER_PIN = 10;  // pin 10 drives the buzzer

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);

  Serial.begin(9600);  // Begin monitoring via the serial monitor
  delay(200);          // Delay a brief period to let things settle before displaying prompt.
  Serial.println("Press * to enter new PIN or # to access the system.");
}

void loop() {
  char button_character = heroKeypad.waitForKey();

  // Serial.println(button_character);
  tone(BUZZER_PIN, 880, 100);

  if (button_character == '#') {  // button to access system
    bool access_allowed = validatePIN();
    if (access_allowed) {
      Serial.println("Welcome, authorized user. You may now begin using the system.");
    } else {
      Serial.println("Access Denied.");
      Serial.println("\nPress * to enter new PIN or # to access the system.");
    }
  }

  if (button_character == '*') {  // button to change PIN
    bool access_allowed = validatePIN();

    if (access_allowed) {
      Serial.println("Welcome, authorized user. Please Enter a new PIN: ");

      for (int i = 0; i < PIN_LENGTH; i++) {
        button_character = heroKeypad.waitForKey();
        tone(BUZZER_PIN, 880, 100);

        current_pin[i] = button_character;
        Serial.print("*");
      }

      Serial.println();  // add new line after last asterisk so next message is on next line
      Serial.println("PIN Successfully Changed!");
    } else {
      Serial.println("Access Denied. Cannot change PIN without the old or default.");
      Serial.println("\nPress * to enter new PIN or # to access the system.");
    }
  }
}

/*
 * This function prompts the user to enter a PIN and returns true or false depending
 * on whether the PIN matches our saved PIN.
 *
 * NOTE: this function introduces the concept of a function that returns a single
 *       value.  First, we must indicate what type of value that will be returned
 *       in the initial function declaration.  The "bool" at the beginning of
 *       the declaration indicates that this function will return a "boolean" value
 *       of either true or false.
 */

bool validatePIN() {
  Serial.println("Enter PIN to continue.");

  for (int i = 0; i < PIN_LENGTH; i++) {
    char button_character = heroKeypad.waitForKey();
    tone(BUZZER_PIN, 880, 100);

    if (current_pin[i] != button_character) {
      Serial.println();  // start next message on new line
      Serial.print("WRONG PIN DIGIT: ");
      Serial.println(button_character);
      return false;  // return false and exit function
    }
    Serial.print("*");
  }

  Serial.println();  // add new line after last asterisk so next message is on next line
  Serial.println("Device Successfully Unlocked!");
  return true;
}
