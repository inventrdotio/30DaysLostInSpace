# Day 01 - "Incoming Broadcast from InventrCorp"



<p align="center">
    <img src="..\Art\30DaysCadet.jpg" height="300"><br>
    <i>We are still waiting for the artwork for Day 01</i>
</p>

## The Story So Far..
You have crash landed on an unknown planet and now you need to activate and fly your ancient rescue craft to safety. Play the video below to discover how this is going to be possible and learn to take your first steps in this challenging mission. If you want an overview of what your will be doing today, you can read the "Day 1 Activity" section below this video.



[![video](..\Art\VideoScreenshot.png)](https://www.youtube.com/watch?v=faVBaH7iDV0&list=PL-ykYLZSERMSZFH8_4zQx4BMWpt4aG1kr&index=1&t=2s)



## Day 1 Activity
First, we download the Arduino IDE onto our computer and connect the HERO board (which is based on the Arduino Uno) to our computer using a Type B USB Cable. Then, we access the built in Sketch program called Blink and upload it to the HERO board. We learn about how the code is structured, with its setup() function and loop() function. We learn that the pinMode() function can be used to set up a digital pin on the HERO board as an OUTPUT, and that the digitalWrite() function can set the pin to be a HIGH or LOW voltage. The delay() function is used to get the program to wait for a specified number of milliseconds before it continues with the next command. We learn how to compile and upload the Sketch program to the HERO board in order to run it. Finally, we modify the code to change the amount of time that the LED is expected to be on and off.

## Hardware Required:

We attached our computer/laptop/MAC/chromebook or linux machine to the HERO board using a Type B USB Cable

<p align="center">
    <img src="30Days-Day01-HeroBoard.png" height="300">
</p>

<img src="DayXX_bb.png" width="350">


## Code Used

```

/* Blink

  Turns an LED on for one second, then off for one second, repeatedly. 

  Most Arduinos have an on-board LED you can control. 
  On the UNO, MEGA and ZERO it is attached to digital pin 13, on MKR1000 on pin 6. 
  LED_BUILTIN is set to the correct LED pin independent of which board is used.
*/

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);                      // wait for a second
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  delay(1000);                      // wait for a second
}

```
## Installation
No libraries or includes required.

---
## <center><b>Key Learning for Day 1</b></center>

---
| Key learning introduced in Day 1 | Example of code / Further instructions|
| :--- | :--- |
| How to download the Arduino IDE for your computer (IDE stands for Integrated Development Environment)	| You can download the Arduino IDE using this [link](https://www.arduino.cc/en/software)| 
|How to connect the <FONT COLOR="RED">Hero board</font> to the computer using a <FONT COLOR="RED">Type B USB Cable</font> and select the correct board and port in the IDE window 	Tools>Board>Arduino AVR Boards>Arduino Uno | Tools>Port>COM3 (Arduino Uno) |
| How to access the built-in <FONT COLOR="BLUE">Sketch program called Blink</font> available within the IDE. The Blink program causes the on-board light to link on and off | File>Examples>01.Basics>Blink |
| A [setup() function](https://www.arduino.cc/reference/en/language/structure/sketch/setup/) runs once when you press reset or power the board (the void datatype for the setup() function indicates that the function is not expected to return any information when it is run) | void setup() { <br>&nbsp;&nbsp;// put your setup code here, to run once:<br>} |
| [//](https://www.arduino.cc/reference/en/language/structure/further-syntax/singlelinecomment/) is used to write single line comments in the code. Any text to the right of these symbols is not executed as code. [/*  */](https://www.arduino.cc/reference/en/language/structure/further-syntax/blockcomment/) is used for a block of comments. | // These are used to comment out code, <br>/* These comment out a block of code */|
| A [loop() function](https://www.arduino.cc/reference/en/language/structure/sketch/loop/) runs repeatedly until you press reset or power down the board. (the void datatype for the loop() function indicates that the function is not expected to return any information when it is run) | void loop() { <br>&nbsp;&nbsp;// put your main code here, to run repeatedly: <br>} |
| [pinMode command](https://www.arduino.cc/reference/en/language/functions/digital-io/pinmode/) is a built-in function of the Hero and is used to initialize a <FONT COLOR="RED">digital pin</font> as an [OUTPUT](https://www.arduino.cc/reference/en/language/variables/constants/constants/), in this case, pin 13 which is also given the name [LED_BUILTIN](https://www.arduino.cc/reference/en/language/variables/constants/constants/). This is used within the setup() function | pinMode(LED_BUILTIN, OUTPUT); or pinMode(13, OUTPUT); (later we will learn about initializing a pin as an INPUT) 
| The [digitalWrite() function](https://www.arduino.cc/reference/en/language/functions/digital-io/digitalwrite/) tells a pin to do something. This is used within the loop() function. Find out more about [HIGH/LOW constant variables](https://www.arduino.cc/reference/en/language/variables/constants/constants/) | digitalWrite(LED_BUILTIN, HIGH); or digitalWrite(LED_BUILTIN, LOW); |
| The [delay() function](https://www.arduino.cc/reference/en/language/functions/time/delay/) gives the command to do nothing, or delay for specified period of time. This is used within the loop() function. | delay(1000); <br>(This causes a delay of 1 second, or 1000 ms) |
| Upload a <FONT COLOR="BLUE">Sketch program</font> to the Hero board and test out its correct function | Select the Upload arrow at the top of our coding window |
---