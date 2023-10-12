/*
 * 30 Days - Lost in Space
 * Day 18 - The Surface Seems So Much Closer
 *
 * Learn more at https://inventr.io/adventure
 *
 * TBD
 *
 * Alex Eschenauer
 * David Schmidt
 * Greg Lyzenga
 */

/*
 * Arduino concepts introduced/documented in this lesson.
 * - 
 *
 * Parts and electronics concepts introduced in this lesson.
 * - 
 */

// Explicitly include Arduino.h
#include "Arduino.h"

// Include TM1637 library file
#include <TM1637Display.h>

// Install BasicEncoder library by Peter Harrison

// Include BasicEncoder library file
#include <BasicEncoder.h>
 
// Rotary Encoder Inputs
const byte ROTARY_ENCODER_CLK_PIN = 2;
const byte ROTARY_ENCODER_DT_PIN = 3;
 
// Create RotaryEncoder instance (which initializes counter to 0)
BasicEncoder depth_encoder(ROTARY_ENCODER_CLK_PIN, ROTARY_ENCODER_DT_PIN);

// Define the display connection pins:
const byte DISPLAY_CLK_PIN = 6;
const byte DISPLAY_DIO_PIN = 5;
 
// Create display object of type TM1637Display:
TM1637Display OurDisplay = TM1637Display(DISPLAY_CLK_PIN, DISPLAY_DIO_PIN);
 
// Create array that turns all segments on:
const uint8_t data[] = {0xff, 0xff, 0xff, 0xff};
 
// Create array that turns all segments off:
const uint8_t blank[] = {0x00, 0x00, 0x00, 0x00};
 
// You can set the individual segments per digit to spell words or create other symbols:
const uint8_t done[] = {
  SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,           // d
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,   // O
  SEG_C | SEG_E | SEG_G,                           // n
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G            // E
};

int previousCounter = 0;

void setup() {
  // Setup Serial Monitor
  Serial.begin(9600);

  // Clear the display:
  OurDisplay.clear();
 // delay(1000);
  OurDisplay.setBrightness(7);
  OurDisplay.showNumberDec(0);
 
  // Call Interrupt Service Routine (ISR) updateEncoder() when any high/low change
  // is seen on A (ROTARY_ENCODER_CLK_PIN) interrupt  (pin 2), or B (ROTARY_ENCODER_DT_PIN) interrupt (pin 3)
  attachInterrupt(digitalPinToInterrupt(ROTARY_ENCODER_CLK_PIN), updateEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ROTARY_ENCODER_DT_PIN), updateEncoder, CHANGE);
}
 
void loop() {
  if (depth_encoder.get_change()) {
    int counter = depth_encoder.get_count();
    OurDisplay.showNumberDec(counter);
    delay(50);
 
    // Since BasicEncoder can be clicked multiple times per loop via interrupts we
    // track when counter has passed milestones THIS time through the loop.  We do
    // by testing whether the previous counter was less than the milestone and current
    // counter is greater or equal.

    // 
    if(previousCounter < 50 && counter >= 50) {
      OurDisplay.setSegments(data);
      delay(2000);
      OurDisplay.clear();
    }
 
    if(previousCounter < 75 && counter >= 75) {
      OurDisplay.setSegments(data);
      delay(2000);
      OurDisplay.clear();
    }
 
    if(previousCounter < 100 && counter >= 100) {
      OurDisplay.setSegments(done);
      delay(3000);
      OurDisplay.clear();
      delay(1000);
      OurDisplay.setSegments(done);
      delay(3000);
      OurDisplay.clear();
    }
    previousCounter = counter;  // save counter for next time through the loop
  }
}

void updateEncoder() {
  depth_encoder.service();
}
