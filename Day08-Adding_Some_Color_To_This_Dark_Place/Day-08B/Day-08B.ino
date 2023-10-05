/*
 * 30 Days - Lost in Space
 * Day 8B - Adding some color to this dark place (Common Anode version)
 *
 * Learn more at https://inventr.io/adventure
 *
 * Previously we have used different color LEDs with our HERO, but when we require
 * more output, or desire a color different from the available colors we use a more
 * flexible "RGB LED".  RGB LEDs have a red, a green and a blue LED packaged into a
 * single LED package.  By using something called Pulse Width Modulation (PWM) we
 * can vary the intensity of each LED and come up a wide variety of colors.
 *
 * NOTE: On rare occasions a different type of RGB LED has been found by users,
 *       cause either by supplier mixup or because the customer used an outside
 *       source and received a different part.
 *
 *       The part in the inventr.io kit is a "Common Cathode" RGB LED, where the
 *       common lead is connected to GND.  In a "Common Anode" RGB LED the common
 *       lead is connected to Vcc (5V on the HERO) and each color is connected to
 *       GND in order to light the part.  This sketch modifies the code to work
 *       with Common Anode RGB LEDs.
 *
 *       Since we created our own function to control the LEDs, all of the changes
 *       necessary to control a Common Anode RGB LED can be made in a single place
 *       instead of having to change all values used in the loop().  See additional
 *       notes in the displayColor() method at the end of the sketch.
 *
 * Alex Eschenauer
 * David Schmidt
 * Greg Lyzenga
 */

/*
 * Arduino concepts introduced/documented in this lesson.
 * - analogWrite(): Used to control a PWM pin, giving a variable intensity
 * - Passing variables into functions
 *
 * Parts and electronics concepts introduced in this lesson.
 * - Common Cathode (single grounded pin) RGB LED.
 */

// Explicitly include Arduino.h
#include "Arduino.h"

/*
 * Each color in an RGB LED is controlled with a different pin on our HERO board.
 *
 * NOTE: Only pins 3, 5, 6, 9, 10 and 11 on the HERO board support PWM which is
 *       indicated on the board by preceding those pin numbers on the HERO board
 *       with a tilde ('~') character.  Only those pins support PWM and analogWrite().
 */
const byte RED_PIN = 11;    // pin controlling the red leg of our RGB LED
const byte GREEN_PIN = 10;  // pin ccontrolling the green leg of our RGB LED
const byte BLUE_PIN = 9;    // pin ccontrolling the blue leg of our RGB LED

/*
 * Define a set of constants to represent 4 different brightness levels for our
 * RGB LED using PWM pins and analogWrite().  PWM can set values ranging from 0
 * to 255 which we will demonstrate by adding 64 (roughly 1/4 of that range) to
 * each preceding value.
 *
 * NOTE: this also demonstrates that our constants can be computed using an expression
 *       that includes any previouly defined constant.  However, the expression cannot
 *       include variables or values that could change during execution.
 */
const byte OFF = 0;                 // Selected color is OFF
const byte DIM = 64;                // Selected color is 1/4 intensity
const byte BRIGHTER = DIM + 64;     // Selected color is 1/2 intensity
const byte BRIGHT = BRIGHTER + 64;  // Selected color is 3/4 intensity
const byte BRIGHTEST = 255;         // Selected color is maximum intensity (255)

// We can change this constant here, in one place, to change how long each color is displayed.
const unsigned int COLOR_DELAY = 500;  // show each color for 500 milliseconds

void setup() {
  // Set each of our PWM pins as OUTPUT pins
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
}

// Each time through loop() we display some of the color variations available
// using an RGB LED.
void loop() {
  // First demonstrate our different PWM levels by slowly brightening our red LED
  displayColor(OFF, OFF, OFF);  // OFF!
  delay(COLOR_DELAY);
  displayColor(DIM, OFF, OFF);  // Display red LED at 1/4 intensity
  delay(COLOR_DELAY);
  displayColor(BRIGHTER, OFF, OFF);  // Display red LED at 1/2 intensity
  delay(COLOR_DELAY);
  displayColor(BRIGHT, OFF, OFF);  // Display red LED at 3/4 intensity
  delay(COLOR_DELAY);
  displayColor(BRIGHTEST, OFF, OFF);  // Display red LED at FULL intensity
  delay(COLOR_DELAY);

  // Display our other two LED colors at half intensity
  displayColor(OFF, BRIGHT, OFF);  // Display the green LED
  delay(COLOR_DELAY);
  displayColor(OFF, OFF, BRIGHT);  // Display the blue LED
  delay(COLOR_DELAY);

  // Now show various colors (at half intensity) by mixing our three colors
  displayColor(BRIGHT, BRIGHT, OFF);  // Display yellow by mixing red and green LEDs
  delay(COLOR_DELAY);
  displayColor(OFF, BRIGHT, BRIGHT);  // Display cyan by mixing green and blue LEDs
  delay(COLOR_DELAY);
  displayColor(BRIGHT, OFF, BRIGHT);  // Display magenta by mixing red and blue LEDs
  delay(COLOR_DELAY);

  // Display all of our LEDs to get white.
  displayColor(BRIGHT, BRIGHT, BRIGHT);  // white
  delay(COLOR_DELAY);
}

/*
 * displayColor() is a function that accepts three parameters representing the desired
 * intensity for each of the LEDs in the RGB LED.
 *
 * Each parameter passed must have a type (here we match what analogWrite() will use) and
 * a name to be used inside the function to refer to the parameter.  The parameters can all
 * be included on a single line like:
 * void displayColor( byte red_intensity, byte green_intensity, byte blue_intensity) {
 * 
 * However, if we display each parameter on it's own line we can add a comment to each
 * for additional clarity.
 */
void displayColor(
  byte red_intensity,    // red LED intensity (0-255)
  byte green_intensity,  // green LED intensity (0-255)
  byte blue_intensity    // blue LED intensity (0-255)
) {
  /*
   * With a Common Anode RGB LED the LEDs light up when the output pin is connected
   * to GND and dark when voltage is applied.  To easily adapt our code for a common
   * anode RGB LED, we need to "invert" our intensity value. Since the maximum value
   * for analogWrite() is 255, we can subtract our desired intensity from 255 to get
   * the new value for a common anode RGB LED.
   */
  analogWrite(RED_PIN, 255 - red_intensity);      // Set red LED intensity using PWM
  analogWrite(GREEN_PIN, 255 - green_intensity);  // Set green LED intensity using PWM
  analogWrite(BLUE_PIN, 255 - blue_intensity);    // Set blue LED intensity using PWM
}