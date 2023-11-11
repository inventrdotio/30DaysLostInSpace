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
 * Arduino concepts introduced/documented in this lesson.
 * - const: Better than #define for defining constants that do not change
 * - byte: A data type representing an unsigned 8 bit integer (values from 0 to 255)
 *         Equivalent to "unsigned char" or "uint8_t" which are sometimes seen.
 *
 * Parts and electronics concepts introduced in this lesson.
 * - Use of breadboard "power rails" to allow us to use one 5V and one GND pin on
 *   HERO to connect to multiple components on our breadboard.
 */

#include "Arduino.h"  // include information about our HERO

/*
 * #define vs. const
 *
 * Until now we have been using #define to define our constants.  When the C language
 * was first created that was the only way to define constants.  However, because
 * of the way #define operates there were instances where the use of #define can
 * cause and hide bugs in programs.
 *
 * Becasuse of this, the language maintainers added a new C commands named "const".
 * For most Arduino programs it operates much the same, though it does contain some
 * additional type information that can help communicate how it is to be used.
 *
 * You will see both used in Arduino code and libraries.  However the general
 * language calls for preferring the use of "const" over using #define.  Our first
 * sketches have used #define so that you are familiar with them and see how they
 * work, but from this lesson on we will be using the preferred "const" expression
 * to define our constants.
 *
 * Here, on Day 4 we will show *both* versions, with the #define version commented
 * out to prevent compile errors.  This will help you learn the difference between
 * them.  After today the sketches will only use the preferred "const" versions.
 */

// Each lander light will be controlled using a different pin on our HERO.
// We will use three different color LEDs to make it more clear which switch
// controls which light.

/*
 * The "const" declaration adds another word that will indicate what type of value
 * is to be represented.  Since pins are small numbers they fit into a "byte", which
 * is an unsigned integer value that can hold values from 0 to 255.
 *
 * Other types you may sometimes see in various Arduino code are "uint8_t" or
 * "unsigned char" which are the same as "byte".  We will use the term "byte"
 * in our lessons to indicate 8 bit unsigned integers.
 */
// #define CABIN_LIGHTS_PIN 10             // pin controlling the cabin lights
// #define STORAGE_LIGHTS_PIN 11           // pin controlling the storage lights
// #define COCKPIT_LIGHTS_PIN 12           // pin controlling the exterior lights
const byte CABIN_LIGHTS_PIN = 10;    // pin controlling the cabin lights
const byte STORAGE_LIGHTS_PIN = 11;  // pin controlling the storage lights
const byte COCKPIT_LIGHTS_PIN = 12;  // pin controlling the exterior lights

// We will use a different input pin for each of our DIP switches and
// we'll label them using the color of the LED that each switch will control.
// #define CABIN_LIGHTS_SWITCH_PIN 2             // cabin lights controlled by switch 1
// #define STORAGE_LIGHTS_SWITCH_PIN 3           // storage lights controlled by switch 2
// #define COCKPIT_LIGHTS_SWITCH_PIN 4           // exterior lights controlled by switch 3
const byte CABIN_LIGHTS_SWITCH_PIN = 2;    // cabin lights controlled by switch 1
const byte STORAGE_LIGHTS_SWITCH_PIN = 3;  // storage lights controlled by switch 2
const byte COCKPIT_LIGHTS_SWITCH_PIN = 4;  // exterior lights controlled by switch 3

// the setup function runs once when you press reset or power the board
void setup() {
  // Configure our LED control pins as OUTPUT pins
  pinMode(CABIN_LIGHTS_PIN, OUTPUT);    // pin controlling the cabin lights
  pinMode(STORAGE_LIGHTS_PIN, OUTPUT);  // pin controlling the storage lights
  pinMode(COCKPIT_LIGHTS_PIN, OUTPUT);  // pin controlling the exterior lights

  // Configure the switch pins as INPUT pins
  pinMode(CABIN_LIGHTS_SWITCH_PIN, INPUT);    // pin connected to switch 1 (cabin lights)
  pinMode(STORAGE_LIGHTS_SWITCH_PIN, INPUT);  // pin connected to switch 2 (storage lights)
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