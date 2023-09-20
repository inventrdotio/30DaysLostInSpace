/*
 * 30 Days - Lost in Space
 * Day 6 - Time to Fix the Battery
 *
 * Learn more at https://inventr.io/adventure
 *
 * We will need to find an additional source of power as our battery will not last long
 * without some recharging.  We do have solar panels so let's work on how the HERO can
 * monitor the power coming from those panels using a "photo-resistor" to simulate the
 * variable power available to our Lander.
 *
 * Alex Eschenauer
 * David Schmidt
 * Greg Lyzenga
 */

/*
 * Arduino concepts introduced/documented in this lesson.
 * - Serial Monitor: Allows the HERO to display text in an Arduino IDE window.
 * - Serial.begin(): Used to initialize the Serial Monitor.
 * - Serial.print(): Display some text in the Arduino IDE Serial Monitor window.
 * - Serial.println(): Display test in the Serial Monitor followed by a newline.
 * - analogRead(): Read a value from an analog pin that is based on how much voltage is on the pin (0-5v)
 *
 * Parts and electronics concepts introduced in this lesson.
 * - Analog pins: Pins on the HERO that can read many different values instead of just HIGH/LOW.
 * - Photo Resistor: Changes it's resistance depending on how much light it senses.
 */

/* We start by including this line of code, which helps our HERO work properly with the Arduino program. */
#include "Arduino.h"

// Our photoresistor will give us a reading of the current light level on this analog pin
const uint8_t PHOTORESISTOR_PIN = A0;  // we pick an analog pin (defined in Arduino.h)

// These two constants set the minimum and maximum delay times for oue blinking LED
const uint16_t MIN_DELAY = 50;   // 50 ms shortest blink delay
const uint16_t MAX_DELAY = 500;  // 500 ms longest blink delay

/*
 * As our loop() function is repeatedly called we need to keep track of the darkest
 * light reading and our brightest so that we can set our blink rate based on changing
 * light levels from darkest seen to brightest.
 *
 * These need to be defined outside of loop() so that they will retain their values
 * between loop() runs.  Because they are always available, they are called "global"
 * variables.
 *
 * Note that they have NO initial value, and we will set that in our setup() function.
 */
uint16_t darkest_light;    // this is the lowest value returned by the photoresistor
uint16_t brightest_light;  // this is the highest value returned by the photoresistor

// One time setup
void setup() {
  // We will blink our build in LED based on amount of light received from our photoresistor
  pinMode(LED_BUILTIN, OUTPUT);       // output since we will control the built in LED
  pinMode(PHOTORESISTOR_PIN, INPUT);  // input value from analog pin connected to photoresistor

  /*
   * To show you the exact value being read on the analog pin we will print the exact number
   * using our Arduino IDE's "Serial Monitor".  This is a window displayed under the sketch that
   * can display text sent to it from the HERO.
   *
   * The speed that this data is sent/received must match between the Arduino IDE and HERO.  We
   * configure this speed for the HERO to send data using the Serial.begin() function.  Throughout
   * this course we will use a typical value of 9600 "baud", which is 9,600 bit of information per
   * second.
   */
  Serial.begin(9600);  // This initializes the Serial Monitor and sets the speed to 9600 bits per second

  /*
   * We don't know what to expect for an initial light level from our photoresistor so
   * we will set our darkest and brightest value by reading the current photoresistor value
   * when setup() is executed.
   *
   * NOTE: This also shows how you can set *multiple* variables to the same value by
   *       "chaining" the '=' operator together.  This sets BOTH variables to the initial
   *       value.
   */
  darkest_light = brightest_light = analogRead(PHOTORESISTOR_PIN);
}

// The loop() function is called over and over when sketch is run.
void loop() {
  /*
   * Each time through our loop() we will read the current value of our photoresistor.  When
   * the voltage goes up from more light we flash the built-in LED faster (with shorter blinks).
   *
   * We will use the reading from the PHOTORESISTOR_PIN and modify how long we delay using it.
   * But we want a SHORTER delay as the value goes UP.  So we will subtrack the reading from
   * the maximum analog value and use that number for the delay, giving us a faster blink as
   * read value goes up.
   */
  uint16_t light_value = analogRead(PHOTORESISTOR_PIN);
  /*
   * Our HERO board doesn't have a text display, so the Arduino IDE has provided us a way to
   * for the HERO to send messages that are displayed in a window in the Arduino IDE.  To open
   * the Serial Monitor on the Arduino IDE you can select Tools/Serial Monitor from the Arduino
   * IDE menu, use the shortcut keys listed in the menu or click the "magnifying glass" icon in
   * the upper right of the IDE window.
   *
   * We initialized the Serial functions in setup and now we will use Serial.print() and
   * Serial.println() to send messages to the Arduino IDE Serial Monitor.  Both functions
   * take a single value which can be either a constant or a variable.  The only difference
   * between the two functions is that Serial.print() leaves the cursor at the end of the
   * current line.  Any additional output will be appended to the current line.  Serial.println()
   * prints the value and THEN adds a "newline", so that any following messages will appear
   * on the following line.
   */
  Serial.print("Light value: ");  // Display label string to serial monitor
  Serial.print(light_value);      // display the value read from our photoresistor
  /*
   * Now that we have a light value let's update our darkest and brightest values
   * if the current value is darker (less than) our previous darkest or brighter
   * (greater than) our previous brightest value.
   */
  if (light_value < darkest_light) {  // If value is LESS THAN ('<') the darkest...
    darkest_light = light_value;      // ...then save current value as our new darkest value
  }
  if (light_value > brightest_light) {  // If value is GREATER THAN ('>') the brightest...
    brightest_light = light_value;      // ...then save current value as our new brightest value
  }

  /*
   * Now we have an interesting problem.  As our voltage reading goes up, we want the LED to
   * blink faster (and thus with a smaller delay).  In addition, we need to adjust the blink
   * rate in a noticeable way.  So, we have one range of numbers (darkest to brightest values)
   * from our light sensor that we wish to convert to a different range that goes from MAX_DELAY
   * down to MIN_DELAY.
   *
   * The Arduino language provides a neat function named map() that was created just for this
   * situation.  It takes a value from one range and *maps* it into a desired range.  It properly
   * handles the situation where the second range goes DOWN when the first range goes UP.
   *
   * We introduce it's used here to map our light_value (which goes from darkest_light to
   * brightest_light) and return a value from MAX_DELAY *down* to MIN_DELAY.  Perfect!
   */
  uint16_t delay_value = map(light_value, darkest_light, brightest_light, MAX_DELAY, MIN_DELAY);
  Serial.print(", Delay value: ");  // display label after light_value
  Serial.println(delay_value);      // display delay_value returned by map() function with newline

  // now blink our built in LED using our delay_value.
  digitalWrite(LED_BUILTIN, HIGH);  // Turn on LED
  delay(delay_value);               // Leave on delay_value microseconds
  digitalWrite(LED_BUILTIN, LOW);   // Turn off LED
  delay(delay_value);               // Leave off delay_value microseconds
}