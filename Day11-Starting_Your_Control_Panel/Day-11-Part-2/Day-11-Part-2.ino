/*
 * 30 Days Lost in Space
 * https://inventr.io/adventure
 *
 * Log entry - Day 11
 *
 * Code written by Alexander Eschenauer for the 30 Day Adventure Kit
 */

#include <Arduino.h>
#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;

char buttons[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

byte rowPins[ROWS] = { 9, 8, 7, 6 };
byte colPins[COLS] = { 5, 4, 3, 2 };

// Using the Keypad.h Library, we are going to define a custom keypad.
// In order to do that, it needs to know the following:
// What the keys are (a 2D Array of characters (char)),
// what pins are being used (2 thru 9),
// how many rows there are (4), and how many columns (4).
Keypad customKeypad = Keypad(makeKeymap(buttons), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);  // Begin monitoring via the serial monitor
}

void loop() {
}