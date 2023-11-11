/*
 * 30 Days - Lost in Space
 * Day 9 - A Better Way to Do Things
 *
 * Learn more at https://inventr.io/adventure
 *
 * Now that we know how to measure our battery charging rate and we know how to display
 * multiple colors with the RGB LED, let's combine those two concepts to display different
 * colors as our battery charges to give a good indication of our current battery state.
 *
 * Alex Eschenauer
 * David Schmidt
 * Greg Lyzenga
 */

/*
 * Arduino concepts introduced/documented in this lesson.
 * - float:   Variable type for decimal numbers that include a decimal point
 * - else if: Control structure for making multiple if decisions together
 *
 * Parts and electronics concepts introduced in this lesson.
 */

// Explicitly include Arduino.h
#include "Arduino.h"

// Our photoresistor will give us a reading of the current light level on this analog pin
const byte PHOTORESISTOR_PIN = A0;  // Photoresistor analog pin

// RGB LED pins
const byte RED_PIN = 11;    // pin controlling the red leg of our RGB LED
const byte GREEN_PIN = 10;  // pin ccontrolling the green leg of our RGB LED
const byte BLUE_PIN = 9;    // pin ccontrolling the blue leg of our RGB LED

const unsigned long BATTERY_CAPACITY = 50000;  // Maximum battery capacity

/*
 * Display a color on our RGB LED by providing an intensity for
 * our red, green and blue LEDs.
 */
void displayColor(
  byte red_intensity,    // red LED intensity (0-255)
  byte green_intensity,  // green LED intensity (0-255)
  byte blue_intensity    // blue LED intensity (0-255)
) {
  analogWrite(RED_PIN, red_intensity);      // write red LED intensity using PWM
  analogWrite(GREEN_PIN, green_intensity);  // write green LED intensity using PWM
  analogWrite(BLUE_PIN, blue_intensity);    // write blue LED intensity using PWM
}

void setup() {
  // Declare the RGB LED pins as outputs:
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  // Start serial monitor
  Serial.begin(9600);
}

void loop() {
  // Use static because we need this variable to maintain it's value across
  // multiple loop() runs.
  static unsigned long battery_level = 0;  // Current battery charge level (set to 0 first time used)

  battery_level += analogRead(PHOTORESISTOR_PIN);  // Add current "charge amount" to our battery

  // We can't charge the battery higher than it's capacity, set level as full if it goes over
  if (battery_level > BATTERY_CAPACITY) {
    battery_level = BATTERY_CAPACITY;
  }

  /*
   * IMPORTANT NOTE:
   * If you perform an operation using integer arithemetic each value is not
   * automatically converted to a floating point (decimal) number.
   *
   * In the calculation below, if we divide the integer battery value by the
   * integer battery capacity (battery_level / BATTERY_CAPACITY) then the result
   * would ALWAYS be 0, even if that 0 gets converted afterwards to a float (0.0).
   *
   * To avoid this, we use the "(float)" declaration before each of our values to
   * instruct the compiler to FIRST convert the value to floating point and then
   * perform the calculation using floating point math.
   *
   * If our current_battery_level is less than the battery capacity the initial
   * calculation gives us a number from 0.0 to 1.0.  We then multiple by 100 to
   * get a percentage value from 0.0 up to 100.0.
   */

  // Compute battery charge percentage from our function
  float percentage = ((float)battery_level / (float)BATTERY_CAPACITY) * 100;

  if (percentage >= 50.0) {     // battery level is OK, display green
    displayColor(0, 128, 0);  // display green
  } else if (percentage >= 25.0 && percentage < 50.0) {
    displayColor(128, 80, 0);  // display yellow-ish/amber for early warning
  } else {                     // Level must be less than 25%, display "pulsating" red
    // To pulsate the red light we briefly turn the LED off and then display red, giving it
    // a pulsating effect.
    displayColor(0, 0, 0);    // Turn off our LED
    delay(20);                // ...and delay briefly
    displayColor(128, 0, 0);  // then display red
  }
  Serial.print(percentage);  // Display our floating point percentage (like 12.34) WITHOUT a newline
  Serial.println("%");       // then display the percent sign ("%") with a newline.

  delay(100);  // Delay 1/10 of a second so displayed values don't scroll too fast
}
