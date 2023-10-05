/*
 * 30 Days - Lost in Space
 * Day 14 - Advanced Security Panel
 *
 * Learn more at https://inventr.io/adventure
 *
 * Time to enhance our security system, taking it from functional to fabulous.  We'll
 * add in our RGB LED to give us visual feedback and also expand the tones that play
 * to give us audible feedback as you enter your PIN.
 *
 * IMPORTANT NOTE: The wiring for this sketch builds on the Day 13 wiring. But the
 *                 addition of the RGB LED requires us to MOVE some of the Day 13
 *                 wires.  This is because the RGB LED only works when connected to
 *                 pins that support Pulse Width Modulation (PWM).  HERO pins that
 *                 support PWM have a tilde ('~') preceeding their pin numbers.
 *
 *                 If you look at the Day 13 diagrams you see that we used PWM pins
 *                 for the keypad and buzzer, leaving only one available.  Pins 12
 *                 and 13 are still available so we'll move the wires on pins 9 and 10
 *                 (PWM pins) to 12 and 13.
 *
 *                 Pin 13 is also used while the Arduino IDE is uploading sketches, and
 *                 if you connect the buzzer to THAT pin you get noise every time you
 *                 upload a new sketch (try it!).  So the buzzer will now be on pin 12
 *                 and the keypad wire on pin 9 will move to pin 13.
 *
 *                 Because we used constants, we only need to make two small changes
 *                 from the Day 13 sketch instead of hunting down and changing each use.
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

// Include Keypad library
#include <Keypad.h>

// Our HERO keypad has 4 rows, each with 4 columns.
const byte ROWS = 4;
const byte COLS = 4;

const byte PIN_LENGTH = 4;                           // PIN code is 4 button presses
char password[PIN_LENGTH] = { '0', '0', '0', '0' };  // Initial password is four zeros.

// Define what characters will be returned by each button
const char BUTTONS[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

// Define row and column pins connected to the keypad
const byte ROW_PINS[ROWS] = { 5, 4, 3, 2 };
const byte COL_PINS[COLS] = { 6, 7, 8, 13 };  // NOTE wire moved from Day 13's sketch to pin 13

// Create our keypad object from the keypad configuration above
Keypad heroKeypad = Keypad(makeKeymap(BUTTONS), ROW_PINS, COL_PINS, ROWS, COLS);

const byte BUZZER_PIN = 12;  // NOTE that pin 12 drives the buzzer now

const byte RED_PIN = 11;    // PWM pin controlling the red leg of our RGB LED
const byte GREEN_PIN = 10;  // PWM pin ccontrolling the green leg of our RGB LED
const byte BLUE_PIN = 9;    // PWM pin ccontrolling the blue leg of our RGB LED

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  // playInputTone();
  // delay(5000);
  displayColor(128, 0, 0);
  // delay(1000);
  // playErrorTone();
  // delay(5000);
  // displayColor(0, 128, 0);
  // delay(1000);
  // displayColor(0, 0, 128);
  // delay(1000);

  Serial.begin(9600);  // Begin monitoring via the serial monitor
  Serial.println("Press * to set new password or # to access the system.");
}

void loop() {
  char button_character = heroKeypad.getKey();

  if (button_character == '#') {  // button to access system
    playInputTone();
    bool access_allowed = validatePIN();
    if (access_allowed) {
      Serial.println("Welcome, authorized user. You may now begin using the system.");
    } else {
      Serial.println("Access Denied.");
      Serial.println("\nPress * to enter new PIN or # to access the system.");
    }
  }

  if (button_character == '*') {  // button to change password
    playInputTone();
    bool access_allowed = validatePIN();

    if (access_allowed) {
      displayColor(128, 80, 0);
      Serial.println("Welcome, authorized user. Please Enter a new password: ");

      for (int i = 0; i < PIN_LENGTH; i++) {
        button_character = heroKeypad.waitForKey();
        if (i < (PIN_LENGTH - 1)) {
          playInputTone();
          displayColor(128, 80, 0);
        }

        password[i] = button_character;
        Serial.print("*");
      }

      Serial.println();  // add new line after last asterisk so next message is on next line
      Serial.println("PIN Successfully Changed!");
      playSuccessTone();
    } else {
      Serial.println("Access Denied. Cannot change PIN without entering current PIN first.");
      Serial.println("\nPress * to enter new PIN or # to access the system.");
    }
  }
}

// Enter PIN and return false for bad PIN or true for good PIN
bool validatePIN() {
  // displayColor(0, 0, 128);    // Blue when we're expecting a PIN input
  Serial.println("Enter PIN to continue.");

  for (int i = 0; i < PIN_LENGTH; i++) {
    char button_character = heroKeypad.waitForKey();

    if (password[i] != button_character) {
      playErrorTone();
      Serial.println();  // start next message on new line
      Serial.print("WRONG PIN DIGIT: ");
      Serial.println(button_character);
      return false;  // return false and exit function
    }
    if (i < (PIN_LENGTH - 1)) {
      playInputTone();
    }
    Serial.print("*");
  }

  playSuccessTone();
  Serial.println();  // add new line after last asterisk so next message is on next line
  Serial.println("Device Successfully Unlocked!");
  return true;
}

// Display a color by providing Red, Green and Blue intensities (0-255)
void displayColor(byte red_intensity, byte green_intensity, byte blue_intensity) {
  analogWrite(RED_PIN, red_intensity);      // Set red LED intensity using PWM
  analogWrite(GREEN_PIN, green_intensity);  // Set green LED intensity using PWM
  analogWrite(BLUE_PIN, blue_intensity);    // Set blue LED intensity using PWM
}

void playInputTone() {
  displayColor(0, 0, 0);
  tone(BUZZER_PIN, 880, 200);
  delay(200);
  displayColor(0, 0, 128);
  // delay(50);
  // noTone(BUZZER_PIN);
}

void playSuccessTone() {
  displayColor(0, 0, 0);
  tone(BUZZER_PIN, 300, 200);  // Frequency = 1000Hz, Duration = 200ms
  delay(200);                  // Short pause between tones

  tone(BUZZER_PIN, 500, 500);  // Frequency = 1500Hz, Duration = 200ms
  delay(500);
  displayColor(0, 128, 0);
}

void playErrorTone() {
  displayColor(0, 0, 0);
  tone(BUZZER_PIN, 300, 200);  // Frequency = 300Hz, Duration = 200ms
  delay(200);                  // Short pause between tones

  // tone(BUZZER_PIN, 250, 200);  // Frequency = 250Hz, Duration = 200ms
  // delay(200);  // Short pause between tones

  tone(BUZZER_PIN, 200, 500);  // Frequency = 200Hz, Duration = 200ms
  delay(500);                  // Pause after playing to separate from next sound
  displayColor(128, 0, 0);
  // delay(50);
  // noTone(BUZZER_PIN);
}
