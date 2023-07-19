/*
 * 30 Days - Lost in Space
 * Day 3 - I'm Worried About Your Battery Levels
 *
 * Learn more at https://inventr.io/adventure
 *
 * A light that is always on is also always drawing power, and right now your
 * battery power is limitted.  Let's find a way to control your light so that
 * we can turn it off when it's not needed, and save battery power that you'll
 * be needing in the days ahead.
 *
 * Alex Eschenauer
 * David Schmidt
 */

/*
 * Arduino concepts introduced/documented in this lesson.
 * - Dual Inline Package (DIP) switches.
 * - Resistors
 * - const (https://www.arduino.cc/reference/en/language/variables/variable-scope-qualifiers/const/)
 */

#include "Arduino.h"  // include information about our HERO

const uint_8 LIGHT_SWITCH_PIN = 2;
const uint_8 LANDER_LIGHTS_PIN = 12;

void setup() {
  pinMode(LANDER_LIGHTS_PIN, OUTPUT);
  pinMode(LIGHT_SWITCH_PIN, INPUT);
}

void loop() {
  if (digitalRead(LIGHT_SWITCH_PIN) == 1) {
    digitalWrite(LANDER_LIGHTS_PIN, HIGH);  // 5V
  } else {
    digitalWrite(LANDER_LIGHTS_PIN, LOW);  // GROUND
  }
}