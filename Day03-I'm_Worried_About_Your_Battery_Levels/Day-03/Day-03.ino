/*
 * 30 Days - Lost in Space
 * Day 3 - I'm Worried About Your Battery Levels
 *
 * Learn more at https://inventr.io/adventure
 *
 * A light that is always on is also always drawing power, and right now your
 * battery power is limited.  Let's find a way to control your light so that
 * we can turn it off when it's not needed, and save battery power that you'll
 * be needing in the days ahead.
 *
 * Alex Eschenauer
 * David Schmidt
 */

/*
 * Arduino concepts introduced/documented in this lesson.
 * - if statement (https://www.arduino.cc/reference/en/language/structure/control-structure/if/)
 * - else control structure (https://www.arduino.cc/reference/en/language/structure/control-structure/else/)
 * - comparison operator == (https://www.arduino.cc/reference/en/language/structure/comparison-operators/equalto/)
 * - digitalRead() (https://www.arduino.cc/reference/en/language/functions/digital-io/digitalread/)
 *
 * Parts and electronics concepts introduced in this lesson.
 * - Dual Inline Package (DIP) switches.
 * - Resistors
 */

#include "Arduino.h"  // include information about our HERO

#define CABIN_LIGHTS_PIN 12        // Control our lander's lights using the HERO's pin 12
#define CABIN_LIGHTS_SWITCH_PIN 2  // Connect our light switch to pin 2

// setup() gets called ONCE when our sketch is first run (after upload, when power is
// restored, or when the HERO's reset button is pressed)
void setup() {
  pinMode(CABIN_LIGHTS_PIN, OUTPUT);        // Set light control pin as an OUTPUT
  pinMode(CABIN_LIGHTS_SWITCH_PIN, INPUT);  // Since we read from the switch, this pin is an INPUT
}

// After setup() is executed once the loop() function is called.  Every time it completes it
// is immediately called again, over and over again.
void loop() {
/*
  // First version of our loop.  It works, but could be shorter, more efficient and
  // more understandable.  Commented out but left in to show how we can incrementally
  // improve our code.

  byte switch_setting;

  switch_setting = digitalRead(CABIN_LIGHTS_SWITCH_PIN);   // Read state of light switch

  if (switch_setting == HIGH) {
    digitalWrite(CABIN_LIGHTS_PIN, HIGH);  // if switch is ON then turn on our lander's light
  }

  if (switch_setting == LOW) {
    digitalWrite(CABIN_LIGHTS_PIN, LOW);  // if switch is OFF then turn off lander's light
  }
*/

/*
  // Second version of our loop.  Better.  Define the variable and set it in the same statement
  // and then use the else statement to show that we should always execute ONE of our two
  // actions.

  byte switch_setting = digitalRead(CABIN_LIGHTS_SWITCH_PIN);

  if (switch_setting == HIGH) {
    digitalWrite(CABIN_LIGHTS_PIN, HIGH);  // Switch is ON, turn on our lander's light
  } else {
    digitalWrite(CABIN_LIGHTS_PIN, LOW);  // Switch is OFF, turn off lander's light
  }
*/

  // Final version!  Since we only use our value once, just do our digitalRead once and
  // remove the (now unnecessary) variable.  Clean, fast and less likely to allow bugs
  // to be introduced.

  // Each time loop() begins digitalRead() reads the input pin attached to the switch and
  // compares the value read to HIGH (switch is ON)
  if (digitalRead(CABIN_LIGHTS_SWITCH_PIN) == HIGH) {
    digitalWrite(CABIN_LIGHTS_PIN, HIGH);  // Switch is ON, turn on our lander's light
  } else {
    digitalWrite(CABIN_LIGHTS_PIN, LOW);  // Switch is OFF, turn off lander's light
  }
}