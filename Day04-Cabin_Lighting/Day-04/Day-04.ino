/*
 * 30 Days - Lost in Space
 * Day 3 - I'm Worried About Your Battery Levels
 *
 * Learn more at https://inventr.io/adventure
 *
 * Since our lander has more than one light, let's extend our previous project by
 * adding multiple lights and use all three switches on our DIP switch module.  Each
 * time through our loop() code we'll check each switch, and set the corresponding
 * light's state appropriately.
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
const uint8_t RED_LED_PIN = 10;    // pin controlling the Red LED
const uint8_t BLUE_LED_PIN = 11;   // pin controlling the Blue LED
const uint8_t GREEN_LED_PIN = 12;  // pin controlling the Green LED

// We will use a different input pin for each of our DIP switches and
// we'll label them using the color of the LED that each switch will control.
const uint8_t RED_LED_SWITCH_PIN = 2;    // Red LED controlled by switch 1
const uint8_t BLUE_LED_SWITCH_PIN = 3;   // Blue LED controlled by switch 2
const uint8_t GREEN_LED_SWITCH_PIN = 4;  // Green LED controlled by switch 3

// the setup function runs once when you press reset or power the board
void setup() {
  // Configure our LED control pins as OUTPUT pins
  pinMode(RED_LED_PIN, OUTPUT);    // pin controlling the red LED
  pinMode(BLUE_LED_PIN, OUTPUT);   // pin controlling the blue LED
  pinMode(GREEN_LED_PIN, OUTPUT);  // pin controlling the green LED
  // Configure the switch pins as INPUT pins
  pinMode(RED_LED_SWITCH_PIN, INPUT);    // pin connected to switch 1 (red LED)
  pinMode(BLUE_LED_SWITCH_PIN, INPUT);   // pin connected to switch 2 (blue LED)
  pinMode(GREEN_LED_SWITCH_PIN, INPUT);  // pin connected to switch 3 (green LED)
}

// Each time through loop() we will check each switch in turn and set each light's
// state appropriately.
void loop() {
  // Control red LED based on setting on switch 1
  if (digitalRead(RED_LED_SWITCH_PIN) == HIGH) {  // if switch is on (HIGH voltage)
    digitalWrite(RED_LED_PIN, HIGH);              // turn on LED by providing HIGH voltage (5v)
  } else {
    digitalWrite(RED_LED_PIN, LOW);  // turn off LED by setting output to LOW (zero volts)
  }

  // Control blue LED based on setting on switch 2
  if (digitalRead(BLUE_LED_SWITCH_PIN) == HIGH) {  // if switch is on (HIGH voltage)
    digitalWrite(BLUE_LED_PIN, HIGH);              // turn on LED by providing HIGH voltage (5v)
  } else {
    digitalWrite(BLUE_LED_PIN, LOW);  // turn off LED by setting output to LOW (zero volts)
  }

  // Control green LED based on setting on switch 3
  if (digitalRead(GREEN_LED_SWITCH_PIN) == HIGH) {  // if switch is on (HIGH voltage)
    digitalWrite(GREEN_LED_PIN, HIGH);              // turn the LED on (HIGH is the voltage level)
  } else {
    digitalWrite(GREEN_LED_PIN, LOW);  // turn off LED by setting output to LOW (zero volts)
  }
}