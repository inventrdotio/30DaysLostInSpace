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
 * - Serial Console: Allows the HERO to display text in an Arduino IDE window.
 * - Serial.begin(): Used to initialize the serial console.
 * - Serial.println(): Display some text in the Arduino IDE serial console window.
 * - analogRead(): Read a value from an analog pin that is based on how much voltage is on the pin (0-5v)
 *
 * Parts and electronics concepts introduced in this lesson.
 * - Analog pins: Pins on the HERO that can read many different values instead of just HIGH/LOW.
 * - Photo Resistor: Changes it's resistance depending on how much light it senses.
 */

/* We start by including this line of code, which helps our HERO work properly with the Arduino program. */
#include "Arduino.h"

const uint8_t PHOTORESISTOR_PIN = A0;  // we pick an analog pin (defined in Arduino.h)

const uint16_t MAX_DELAY = 500; // 500 ms longest blink delay
const uint16_t MIN_DELAY = 50; // 50 ms shortest blink delay

uint16_t darkest_light;
uint16_t brightest_light;

// One time setup
void setup() {
  // We will blink our build in LED based on amount of light received from our photoresistor
  pinMode(LED_BUILTIN, OUTPUT);   // output since we will control the built in LED
  pinMode(PHOTORESISTOR_PIN, INPUT);  // input value from analog pin connected to photoresistor

  /*
   * To show you the exact value being read on the analog pin we will print the exact number
   * using our Arduino IDE's "Serial Console".  This is a window displayed under the sketch that
   * can display text sent to it from the HERO.
   *
   * The speed that this data is sent/received must match between the Arduino IDE and HERO.  We
   * configure this speed for the HERO to send data using the Serial.begin() function.  Throughout
   * this course we will use a typical value of 9600 "baud", which is 9,600 bit of information per
   * second.
   */
  Serial.begin(9600);   // set output serial console speed to 9600 baud

  darkest_light = analogRead(PHOTORESISTOR_PIN);
  brightest_light = darkest_light;
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
  Serial.print(light_value);   // Display on Serial Console

  // Adapt our min/max if our new value is outside our current min/max
  if (light_value > brightest_light) {
    brightest_light = light_value;
  }
  if (light_value < darkest_light) {
    darkest_light = light_value;
  }
  uint16_t delay_value = map(light_value, darkest_light, brightest_light, MAX_DELAY, MIN_DELAY);
  Serial.print(" -> ");
  Serial.println(delay_value);

  // now blink our built in LED using our delay_value.
  digitalWrite(LED_BUILTIN, HIGH);
  delay(delay_value);
  digitalWrite(LED_BUILTIN, LOW);
  delay(delay_value);
}