/* <- Any text between a slash/asterisk and an asterisk/slash is a comment and does not affect the code generated.
 * <- This asterisk is NOT required in a multi-line comment, but is only here to make the comment look nice.
 *
 * 30 Days - Lost in Space
 * Day 2 - It's Really Dark in Here
 *
 * Learn more at https://inventr.io/adventure
 *
 * A light-emitting diode (LED) is a semiconductor device that emits light
 * when an electric current is passed through it. LEDs are small, efficient,
 * and long-lasting, making them ideal for a wide range of applications such
 * as indicator lights, digital displays, and lighting. They are available
 * in a variety of colors and sizes.
 *
 * Alex Eschenauer
 * David Schmidt
 */

/*
 * Lesson concepts:
 * - Circuit (must be complete, no leaks)
 * - Current / Amperes
 * - Voltage / Volts
 * - Resistance / Ohms
 * - Ohms Law (Current = Voltage / Resistance)
 *
 * Arduino/HERO concepts:
 * - Breadboard
 * - 5V pins
 * - GND (Ground) pins
 *
 * Arduino language concepts introduced/documented in this lesson.
 * - Arduino language.  Based on C++.  Optimized for use with microcontrollers and providing a simplified programming
 *   interface for hardware-specific tasks.
 * - Block Comments (like this one)  (https://www.arduino.cc/reference/en/language/structure/further-syntax/blockcomment/)
 * - Single Line comments (https://www.arduino.cc/reference/en/language/structure/further-syntax/singlelinecomment/)
 * - #include (https://www.arduino.cc/reference/en/language/structure/further-syntax/include/)
 * - #define (https://www.arduino.cc/reference/en/language/structure/further-syntax/define/)
 * - const (https://www.arduino.cc/reference/en/language/variables/variable-scope-qualifiers/const/)
 * - setup() (https://www.arduino.cc/reference/en/language/structure/sketch/setup/)
 * - loop() (https://www.arduino.cc/reference/en/language/structure/sketch/loop/)
 * - pinMode() (https://www.arduino.cc/reference/en/language/functions/digital-io/pinmode/)
 */

/*
 * #include is used to include code and defines from other files.  While Arduino automtically
 * includes "Arduino.h", other IDEs do not so it's a good idea to include it at the top of
 * all of your Arduino sketches.
 *
 * Incidently, when blink.ino used the constant LED_BUILTIN, that was defined when the Arduino IDE
 * automatically included Arduino.h.
 */
#include "Arduino.h"

/*
 * Yesterday we got the built in LED (LED_BUILTIN) to light up.  But that tiny LED won't light
 * up our ship.  Today we'll show how to connected up an external light (using the LED for
 * testing) so we'll need to use another pin on our HERO to turn on our lander's lights.
 *
 * In the Arduino language we use constants to give names to values used later in our code.
 * There are many benefits to using these constants and here are a few:
 * * Readability - When you give a name to a constant it makes the code more readable.  For
 *                 For example, the LED_BUILTIN constant from Blink.ion let us write
 *                 "digitalWrite(LED_BUILDIN, HIGH);" instead of "digitalWrite(13, HIGH);".
 * * Maintainability - If you use a constant in multiple places in your sketch and later find
 *                     that the value needs to be changed (like if a different pin must be used)
 *                     then you can just change the constant in one place rather than finding
 *                     every place in the code.
 * * Avoiding Hardcoding - What if your sketch used the value "7" in many places?  Some for
 *                         a pin number, but other times for something like the number of
 *                         days in a week.  If you had to change the pin number used it would
 *                         require you to carefully change JUST the value when it's used as a pin.
 *                         But by using constants, you can just change the value for the pin
 *                         constant without affecting the use of the other constant.
 * * Memory efficiency - Constants don't use up valuable RAM space, making our sketches smaller
 *                       allowing us to write larger sketches.
 *
 * In order to emphasize that these names are constants that cannot be change, they are
 * usually named with all capital letters.  While this isn't required, it's good practice
 * and helps emphasize that these values do not change while your code is running.
 *
 * We can give a name to our pin two different ways.  The easiest and most common way used
 * in most sketches that you'll see is to use #define.  However, #define can occasionally cause
 * odd compile problems AND it doesn't give you any hint what TYPE of data it defines.
 *
 * Though not as simple to use, the "const" statement is better as it allows us to define the TYPE
 * of data represented and doesn't have the potential compile problems.  Here we'll show both so
 * that you can recognize them when you see them.  They are both equivalent in this sketch so if
 * you like you can uncomment the #define (by removing the '//') and commenting out the "const"
 * (by adding '//' to the beginning of the line).
 */
// #define CABIN_LIGHTS_PIN 12           // The HERO Board Pin to wire to our LED
const uint8_t CABIN_LIGHTS_PIN = 12;  // The HERO Board Pin to wire to our LED

// The setup() function is called when a sketch starts. Use it to initialize variables, pin
// modes, start using libraries, etc. The setup() function will only run once, after each
// powerup or reset of the Arduino board.
void setup() {
  pinMode(CABIN_LIGHTS_PIN, OUTPUT);  // set digital pin defined by CABIN_LIGHTS_PIN as an output pin.
}

// After setup() is executed once the loop() function is called.  Every time it completes it
// is immediately called again, over and over again.
void loop() {
  digitalWrite(CABIN_LIGHTS_PIN, HIGH);  // Turn on ship's lights
  delay(1000);                           // Delay one second
  digitalWrite(CABIN_LIGHTS_PIN, LOW);   // Turn off ship's lights briefly
  delay(100);                            // Shorter delay for off time (1/10 of a second)
}