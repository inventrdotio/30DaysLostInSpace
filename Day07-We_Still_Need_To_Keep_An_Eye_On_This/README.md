# Day 07 – “We still need to keep an eye on this”

<p align="center">
    <img src="30DaysDay07.png" height="300"><br>
    <i>You need to keep charging that battery and get better control</i>
</p>

## The Story So Far..
You have been doing a great job and are now successfully acquiring analog data with your Hero and responding to it with actions controlled by logic in your Hero. This is exactly where you need to be in order to control the recharging of your batteries and get your shuttle up and running. We are now going to build some more sophisticated logic and control. We want to monitor and respond to the state of charge of the batteries and report that back to us using the Serial Monitor.

[![video](../Art/VideoScreenshot.png)](https://www.youtube.com/watch?v=JO7xNes4FoY&list=PL-ykYLZSERMSZFH8_4zQx4BMWpt4aG1kr&index=8)

## Day 7 Activity
We used the same circuit set up as Day 6. We learned about different types of variables (signed and unsigned integers, float and doubles) At the start of the code, we declared 3 integer variables to show that we would be using the A0 pin, the onboardLED and a variable to contain the value of the light levels – setting it initially to zero. We also declared 4 unsigned integer variables that would hold large numbers – batteryCapacity, batteryLevel, ticks and wait.  Finally in this section, we declared a double variable called percentFull.
In the setup() function, we opened the serial communication line and determined the speed of this communication. We also used the pinMode command to set the onboardLED as an output. We created a new function, which we called PrintBatteryPercentage() and is called later in the loop() function. The PrintBatteryPercentage() function prints the value of the ticks variable to the serial monitor along with some text. To calculate the percentFull value, which is a double, we first converted the integer variables batteryLevel and batteryCapacity into doubles and then used them in the percentage calculation. The result was printed to the serial monitor, followed by the “%” symbol. In the main loop() function, we read the sensor value and added it to the battery level. We also added the value of wait that we defined at the start of the code to the variable ticks, which represented the time taken. Next, we applied a logical test to determine if the batteryLevel had reached the batteryCapacity and determined what action should be taken dependent on the result. We printed out the BatteryPercentage to the serial monitor if it was less than 100%, otherwise we printed out the message that it was fully charged, set the batteryLevel to the batteryCapacity and the ticks to zero, and caused the code to have a long pause to indicate the completion of the battery charging process. (After the long wait, the loop begins again.). We tried to compile the code but, since there was a deliberate mistake in the code, encountered an error message that was displayed at the bottom of the coding window. Once corrected, we compiled and uploaded the sketch to the HERO board. We started the serial monitor before our code began to run on the HERO. We ran the program and altered the light levels on the photoresistor by shining a torch on it.

## Wiring Diagram:
| HERO | Component |
| --- | --- |
| 5V | Photoresistor in |
| A0 | Photoresistor out |
| GND | Photoresistor out (220&Omega;) |

## Fritzing Diagram
<i>[(Click here for full size image)](../Day06-Time_To_Fix_The_Battery/Day6.png)</i>

<img src="../Day06-Time_To_Fix_The_Battery/Day6.png" height="300"><br>
*Note that this is the same circuit as Day 6*

## Code Used

<i>[Click here for Day7.ino sketch](Day7.ino) – (Note that this is not the completed version of the code)</i>

```

void PrintBatteryPercentage() {
  Serial.print(((double)batteryLevel / (double)batteryCapacity)*100);
  Serial.println("%");
}

```

## Installation
No libraries or includes required.

---
## <center><b>Key Learning for Day 7</b></center>
---
| Key learning introduced in Day 7 | Example of code / Further instructions|
| :--- | :--- |
| We learned how to monitor and respond to the state of our battery |  |
| We learned about various VARIABLES that can be used when programming the Arduino. Numbers are held and processed differently to make the best use of the binary digits available on the device. |  |
| [[bit]](https://www.arduino.cc/reference/en/language/functions/bits-and-bytes/bit/) is a binary digit. 3 binary digits can be used to produce 8 integer numbers (ie. 23) | e.g. 000 = 0, 001 = 1, 010 = 2, 011 = 3, 100 = 4, 101=5, 110 = 6, 111 = 7 |
| Integer [[int]](https://www.arduino.cc/reference/en/language/variables/data-types/int/) variables are whole numbers that can be negative (-) or positive (+) These are represented by several bits where each bit is a binary digit. | In the Arduino, 16 bits are used to hold and process short integer values. *(Long integers use 32 bits: 232 is 4,294,967,296, which is how big a long integer can be in the Arduino) This restriction on the number of bits assigned to processing smaller integers ensures that the code can run more efficiently)*. |
| Signed Integer : [[int]](https://www.arduino.cc/reference/en/language/variables/data-types/int/) If we want to have negative and positive numbers, one of the bits is used to identify whether it is positive or negative. *(1 means negative, 0 means positive)*. This leaves 15 bits for the rest of the integer. | *215 is 32,768. This is the biggest signed short integer we can use in our code, in other words, about + or - 32,000* |
| The measurement from the photoresistor is between 0-1023, which can be represented by 10 bits since 210 is 1024. This is why the sensorValue could be defined as an integer value. We set the starting value of this variable to be zero. | int sensorValue = 0 ; |
| Unsigned Integer: [[unsigned int]](https://www.arduino.cc/reference/en/language/variables/data-types/unsignedint/) Since the value of our batteryCapacity variable is set at 50,000, which is greater than the standard short integer maximum of 32,768, we will need to define it as an unsigned integer. | unsigned int batteryCapacity = 50000 ; <br> *216 is 65,536 (or about 64,000) This is the biggest integer a short integer can be if the integer is unsigned.* |
| [float variables](https://www.arduino.cc/reference/en/language/variables/constants/floatingpointconstants/) are used for a number with a decimal point that can be anywhere in that number. <br> A float variable in the Arduino can go up to 1038 | *Floating point numbers, which are single precision (see below,) use 32 bits, where the first bit is used for the sign), the next 7 are used for the exponent (eg. The 4 in 1 x 104) and the remaining 23 bits are for the main number. This gives a precision of 7, since 223 is 8388608 (i.e. 7 digits).*  |
| Precision is the number of digits in a number.  | e.g. 123.4567 has a precision of 7 |
| [[double]](https://www.arduino.cc/reference/en/language/variables/data-types/double/) variables are used for decimal values. Double is known as double precision. This could be represented by scientific notation, for example 30,000 = 3 x 104. A double variable is assigned 64 bits, *where the first bit stands for the sign, 11 bits for the exponent and 52 bits for the main number*. | A double variable in the Arduino has twice as many bits as the float and can hold a number up to 10308 - a very large number indeed! |
| We can set up our own functions | void PrintBatteryPercentage() { <br> &nbsp;&nbsp;// The code for this function goes in this section <br> } |
| In the loop() function, we read the sensor value and added it to the battery level. We also added the value of wait that we defined at the start of the code to the variable ticks, which represented the time taken. ‘+=’ adds the value on the right side of the operation to the variable on the left. | batteryLevel += sensorValue ; <br> ticks += wait ; |
| We applied a logical test to determine if the batteryLevel had reached the batteryCapacity and determined what action should be taken dependent on the result. | if(batteryLevel >= batteryCapacity) { <br> &nbsp;&nbsp;  // The code to determine what happens this condition is true goes here <br> } <br> else { <br> &nbsp;&nbsp;   // The alternative code goes here <br> } |
| We learned that if we try to compile the code by selecting the Verify button and there is a mistake, the line with an error will be highlighted and guidance regarding the error is displayed in the orange banner below the coding window. |  |
---