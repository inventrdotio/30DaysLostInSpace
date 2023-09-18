/*
 * 30 Days - Lost in Space
 * Day 4 - Cabin Lighting
 *
 * Learn more at https://inventr.io/adventure
 *
 * In addition to our cabin lights we have lights in the storage room and even some
 * exterior lights.  Let's extend our previous project by adding the others and use
 * all three switches on our DIP switch module.  Each time through our loop() code we'll
 * check each switch, and set the corresponding light's state appropriately.
 *
 * Alex Eschenauer
 * David Schmidt
 * Greg Lyzenga
 */

/*
 * No new Arduino concepts are introduced in this lesson.
 *
 * Parts and electronics concepts introduced in this lesson.
 * - Use of breadboard "power rails" to allow us to use one 5V and one GND pin on
 *   HERO to connect to multiple components on our breadboard.
 */

#include "Arduino.h"  // include information about our HERO

// Each lander light will be controlled using a different pin on our HERO.
// We will use three different color LEDs to make it more clear which switch
// controls which light.
const uint8_t CABIN_LIGHTS_PIN = 10;    // pin controlling the cabin lights
const uint8_t STORAGE_LIGHTS_PIN = 11;   // pin controlling the storage lights
const uint8_t COCKPIT_LIGHTS_PIN = 12;  // pin controlling the exterior lights

// We will use a different input pin for each of our DIP switches and
// we'll label them using the color of the LED that each switch will control.
const uint8_t CABIN_LIGHTS_SWITCH_PIN = 2;    // cabin lights controlled by switch 1
const uint8_t STORAGE_LIGHTS_SWITCH_PIN = 3;   // storage lights controlled by switch 2
const uint8_t COCKPIT_LIGHTS_SWITCH_PIN = 4;  // exterior lights controlled by switch 3

// the setup function runs once when you press reset or power the board
void setup() {
  // Configure our LED control pins as OUTPUT pins
  pinMode(CABIN_LIGHTS_PIN, OUTPUT);    // pin controlling the cabin lights
  pinMode(STORAGE_LIGHTS_PIN, OUTPUT);   // pin controlling the storage lights
  pinMode(COCKPIT_LIGHTS_PIN, OUTPUT);  // pin controlling the exterior lights
  // Configure the switch pins as INPUT pins
  pinMode(CABIN_LIGHTS_SWITCH_PIN, INPUT);    // pin connected to switch 1 (cabin lights)
  pinMode(STORAGE_LIGHTS_SWITCH_PIN, INPUT);   // pin connected to switch 2 (storage lights)
  pinMode(COCKPIT_LIGHTS_SWITCH_PIN, INPUT);  // pin connected to switch 3 (exterior lights)
}

// Each time through loop() we will check each switch in turn and set each light's
// state appropriately.
void loop() {
  // Control cabin lights based on setting on switch 1
  if (digitalRead(CABIN_LIGHTS_SWITCH_PIN) == HIGH) {  // if switch is on (HIGH voltage)
    digitalWrite(CABIN_LIGHTS_PIN, HIGH);              // turn on LED by providing HIGH voltage (5v)
  } else {
    digitalWrite(CABIN_LIGHTS_PIN, LOW);  // turn off LED by setting output to LOW (zero volts)
  }

  // Control storage lights based on setting on switch 2
  if (digitalRead(STORAGE_LIGHTS_SWITCH_PIN) == HIGH) {  // if switch is on (HIGH voltage)
    digitalWrite(STORAGE_LIGHTS_PIN, HIGH);              // turn on LED by providing HIGH voltage (5v)
  } else {
    digitalWrite(STORAGE_LIGHTS_PIN, LOW);  // turn off LED by setting output to LOW (zero volts)
  }

  // Control exterior lights based on setting on switch 3
  if (digitalRead(COCKPIT_LIGHTS_SWITCH_PIN) == HIGH) {  // if switch is on (HIGH voltage)
    digitalWrite(COCKPIT_LIGHTS_PIN, HIGH);              // turn the LED on (HIGH is the voltage level)
  } else {
    digitalWrite(COCKPIT_LIGHTS_PIN, LOW);  // turn off LED by setting output to LOW (zero volts)
  }
}