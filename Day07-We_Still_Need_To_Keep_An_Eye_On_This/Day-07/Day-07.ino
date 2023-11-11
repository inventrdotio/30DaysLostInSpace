/*
 * 30 Days - Lost in Space
 * Day 7 - We still need to keep an eye on this
 *
 * Learn more at https://inventr.io/adventure
 *
 * Now we will use the circuit from Day 6 and use the value read from the photoresistor
 * to simulate charging our lander's battery.  Our battery is currently drained
 * (current level is 0) and we will stop charging once the battery is full.
 *
 * Alex Eschenauer
 * David Schmidt
 */

/*
 * Arduino concepts introduced/documented in this lesson.
 * - "+=" operator.
 * - defining our own functions.
 *
 * Parts and electronics concepts introduced in this lesson.
 * - No new parts as this sketch uses the same circuit as Day 6
 */

// Explicitly include Arduino.h
#include "Arduino.h"

// Our photoresistor will give us a reading of the current light level on this analog pin
const byte PHOTORESISTOR_PIN = A0;  // Photoresistor analog pin

// Use an unsigned, 16 bit value (0 - 65535) for maximum battery capacity
const unsigned int BATTERY_CAPACITY = 50000;  // Maximum battery capacity

void setup() {
  pinMode(PHOTORESISTOR_PIN, INPUT);  // Input current light level from photoresistor

  Serial.begin(9600);  // Initialize Serial Monitor to 9600 baud
}

// Use global here because this variable is accessed by both loop() and our custom
// function.  (In later lessons we will show how to avoid globals.)
unsigned int battery_level = 0;  // Current battery charge level (set to 0 first time)

/*
 * Each time through our loop() we read the current light level from the photoresistor
 * and add that to our current battery level to simulate charging our battery.
 *
 * We then display current charge level on the Serial Monitor.
 */
void loop() {

  // Display battery information on the Serial Monitor
  if (battery_level < BATTERY_CAPACITY) {  // If battery is not fully charged..
    /*
     * Here we introduce a new arithmetic operator, "+=".
     * When you wish to add a value to an existing variable you *could* write it like
     * "value = value + additional;".  But the Arduino C++ language allows you to avoid
     * the duplication.  The += operator allows us to add to an existing variable value.
     *
     * In the following statement we will add our current light level to our existing
     * battery level.
     */
    battery_level += analogRead(PHOTORESISTOR_PIN);  // read light level and add to battery level
    if (battery_level > BATTERY_CAPACITY) {          // If this would make charge over 100%...
      battery_level = BATTERY_CAPACITY;              // ...set current level to maximum capacity.
    }
  }

  /*
   * Previously we have only used functions included in the Arduino C++ Language.  Here
   * we demonstrate how we can use our own functions.  This keeps our main code cleaner
   * and easier to understand.  All you need to know here is that this new function prints
   * the current charge level on the Serial Monitor.
   *
   * If you need to know the details you can examine the full function declaration following
   * our loop() code.
   */
  printBatteryChargeLevel();  // Display current charge percentage on Serial Monitor

  delay(100);
}

/*
 * This is where our own function is defined to display the current battery charge
 * level on the Serial Monitor.
 *
 * This function takes no parameters and returns no values (indicated by the "void" preceeding the name).
 *
 * If the battery is not fully charged yet we then print the current battery percentage
 * to the Serial Monitor.
 *
 * If the battery is fully charged we display that to the serial monitor.
 */
void printBatteryChargeLevel() {
  if (battery_level < BATTERY_CAPACITY) {  // if not fully charged
    // Percentage of charge is current level divided by capacity, multiplied by 100 to get a percentage.
    Serial.print(((double)battery_level / (double)BATTERY_CAPACITY) * 100);  // display charge % to Serial Monitor
    Serial.println("%");
  } else {
    Serial.println("FULLY CHARGED");  // ...indicate fully charged on Serial Monitor
  }
}
