
# Day 2 code walkthrough

## ChatGPT prompt used to modify existing script

Here are five numbered lists of paragraphs for a code walkthrough.  Please edit the language to be suitable for an audience as young as 5th or 6th grade and then convert each list into a GitHub Markdown formatted table.  Each table should have three columns labeled "Paragraph", "Script" and "Notes".  Place the list number in column 1, the text into column 2 and leave column 3 blank.

[original script paragraphs]

ChatGPT: Sure, here are the edited paragraphs for a younger audience and converted into GitHub Markdown formatted tables:

## Section 1

| Paragraph | Script | Notes |
|-----------|--------|-------|
| 1 | Today, we're diving deeper into the fascinating world of coding with our HERO board. | Show sketch with line 1 at the top.|
| 2 | We are going to explore a new sketch, which is a bit like the Blink sketch we saw on Day 1. This time, we've made it even cooler by controlling an external light, and we've added notes to help you understand the Arduino C++ language better. | |
| 3 | Let's begin with something basic but important in our program, the "comments". These are like little notes that help explain what the different parts of the code do. | |
| 4 | Comments can be just one line or many lines long. We'll start by looking at the longer comments at the start of our Day 2 sketch. | |
| 5 | To start a long comment, we use special symbols: a slash and an asterisk right next to each other. You will see this at the start of our sketch. | Highlight /* on first line.|
| 6 | The computer ignores everything from the start symbol until it finds the end symbol, which is an asterisk followed by a slash. This can be found anywhere in our sketch, even many lines away from the start symbol. | Highlight ending */ sequence. |
| 7 | It's a good idea to put these start and end symbols on lines by themselves, even though the computer can find them even if they are in the middle of a line. | |
| 8 | To make it easy to read, each line of our comments starts with an asterisk. This just makes it look nice and is not necessary. | Highlight column of asterisks between start and end symbols.|
| 9 | Our first block of long comments introduces the sketch. We will do this in all of our lessons to make it easy to find things. | |
| 10 | To make reading easier, the Arduino IDE lets you hide long comments after you read them. You'll see a special "down pointer" where the long comment starts, which lets you hide the comment with a click. | Show how to collapse comment block by clicking after line number. |
| 11 | When you hide a comment, it shows three periods at the end of the line that is still shown to tell you there is hidden text. To see the hidden text again, just click in the same spot. Isn't that cool? | Highlight "..." at end of remaining line then re-expand.|
| 12 | Let's hide the first comment as we move to the next block of comments in this sketch. | Collapse first comment. |
| 13 | The next section has lots of important information about what we'll learn in this sketch. You can come back to these comments anytime. For now, we'll hide this section to move forward. | Collapse second comment.|

## Section 2

| Paragraph | Script | Notes |
|-----------|--------|-------|
| 1 | Now, here's a coding secret - programmers don't usually write all their code from the start. Instead, we use pieces of code created by other programmers and add them to our sketches using special lines called compiler directives. These lines start with a hashtag (#).  Here we use #include to bring in some code from other files without having to copy and paste everything into our own sketches. | Highlight #include |
| 2 | It's important to note that the Arduino IDE automatically includes the "Arduino.h" file for us. Including this file ourselves not only makes it work with other IDEs but also reminds us of this important step, so it's a good idea to do it in all your sketches. | |
| 3 | Using included files is more than just bringing pieces together, it also automatically updates the files, making sure your sketch always uses the newest version without you having to do anything. | |
| 4 | It also lets you include specific versions based on what board you have selected.  This allows us to use the same code for different boards, even if different boards have different settings. | |
| 5 | Remember the "LED_BUILTIN" from the first Blink sketch? Different boards use different pin numbers for the built in LED. This smart feature comes from choosing the right "Arduino.h" file, making sure it works with all boards. | |

## Section 3

| Paragraph | Script | Notes |
|-----------|--------|-------|
| 1 | After we hide the last comment, we find the biggest comment section in this sketch. | |
| 2 | Just like the "LED_BUILTIN" feature, the Arduino IDE lets us give names to constants, which are values that don't change while the sketch is running. | |
| 3 | Using constants is very handy, as explained in this big comment section. To sum it up, it makes coding simpler and avoids mistakes. There are two main ways to declare constants: using #define directive or the "const" variable declaration. | |
| 4 | Even though many people use #define, choosing the const declaration can avoid problems and makes fixing errors easier. | |
| 5 | Both methods let us use both upper and lower case letters for names, but usually, we use UPPER CASE for constants so we can tell them apart from variable names which might change while the program runs. | |
| 6 | In this sketch, we name a constant that controls the cabin lights connected to our HERO board. Since it's outside the board, we'll choose pin 12 for this, giving it the name "CABIN_LIGHTS_PIN" with a value of 12. | Highlight CABIN_LIGHTS_PIN constant declaration|
| 7 | Using the "const" keyword lets us choose the kind of data our constant represents. "uint8_t" is a type of data that is good for small values like 12. This choice saves memory space because it only uses a small amount of memory. | Highlight uint8_t|
| 8 | The next sections will explain more about constants, helping you understand this important part of programming better. | |

## Section 4

| Paragraph | Script | Notes |
|-----------|--------|-------|
| 1 | As we get ready to run our first advanced sketch, it's important to know about the first steps or "setup" that every Arduino sketch needs. The `setup()` function, like its name suggests, prepares everything we need to run our sketch successfully. | |
| 2 | Inside the `setup()` function, we find the `pinMode` function, a helpful tool that lets us decide what each pin on the Arduino does. Today, we'll use it to make the `CABIN_LIGHTS_PIN` an OUTPUT. | |
| 3 | Understanding `pinMode` is a key step to working with real objects connected to the Arduino, like lights, motors, and sensors. | |
| 4 | Next, we find the `digitalWrite` function, used here to turn the cabin lights off at the start of the sketch. | |
| 5 | This prepares us for the next part of our sketch, where the real fun begins. Before we move on, think about how these functions set the stage for the exciting actions we are about to code. | |

## Section 5

| Paragraph | Script | Notes |
|-----------|--------|-------|
| 1 | Now that we've set everything up, it's time to dive into the `loop()` function, where all the exciting actions are coded in our Arduino sketch. | |
| 2 | The `loop()` function has codes that keep running over and over, letting us continuously interact with the things connected to it. | |
| 3 | The first line inside the `loop()` function uses the `digitalWrite` function to turn the cabin lights on, showing how one function can do different things in a sketch. | |
| 4 | Then, we use the `delay` function to pause for a certain amount of time, creating a visible pause before the next code line runs, giving a little break between turning the light on and off. | |
| 5 | After the pause, we use the `digitalWrite` function again to turn the cabin lights off, showing a simple but cool example of automation. | |
| 6 | We add another pause before the loop starts again, making the cabin lights flash in a rhythmic pattern. | |
| 7 | This cycle shows the magic of automation, demonstrating how a few lines of code can control real objects, making our HERO board light up in a dancing pattern of lights. | |
| 8 | As we end today's lesson, try changing the delay values to see how it changes the rhythm of the lights, helping you learn how code changes affect the real world. | |
| 9 | We hope you try different things and make this sketch your own. Remember, learning to be a great programmer is all about experimenting and learning from what happens. | |
