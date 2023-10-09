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
 * - Binary notation (0b00000001)
 * - logical OR
 * - 
 *
 * Parts and electronics concepts introduced in this lesson.
 * - 4-digit 7-segment display
 */

// Explicitly include Arduino.h
#include "Arduino.h"

// Include the .h file for the 4-digit 7-segment display library
#include <TM1637Display.h>
// Define the connections pins:
#define CLK 6
#define DIO 5
// Create display object of type TM1637Display:
TM1637Display display = TM1637Display(CLK, DIO);
// Create array that turns all segments on:
const byte data[] = { 0xff, 0xff, 0xff, 0xff };
// Create array that turns all segments off:
const byte blank[] = { 0x00, 0x00, 0x00, 0x00 };
// You can set the individual segments per digit to spell words or create other symbols:
const byte done[] = {
  SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,          // d
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,  // O
  SEG_C | SEG_E | SEG_G,                          // n
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G           // E
};

void setup() {
  // Clear the display:
  display.clear();
  delay(1000);
}

void loop() {
  // Set the brightness:
  display.setBrightness(7);
  // All segments on:
  display.setSegments(data);
  delay(1000);
  display.clear();
  delay(1000);

  // Microwave after a power outage
  for( int i=0; i < 4; i++) {
    display.showNumberDecEx(1200, 0b01000000);
    delay(500);
    display.clear();
    delay(500);
  }
  // Show counter:
  for (int i = -100; i <= 100; i++) {
    display.showNumberDec(i);
    delay(50);
  }
  delay(1000);

  display.clear();
  delay(1000);

  display.setSegments(done);
  while (1)
    ;
}
