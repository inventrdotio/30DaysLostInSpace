// Code written by Alexander Eschenauer for the 30 Day Adventure Kit
// Learn more at https://inventr.io/adventure

#include <Keypad.h>

int buzzer = 8;
int redPin = 11;
int greenPin = 10;
int bluePin = 9;
const byte ROWS = 4; 
const byte COLS = 4;
const byte PassLength = 4;
char password[PassLength] = {'0','0','0','0'};

char buttons[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {13, 12, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2}; 

Keypad customKeypad = Keypad(makeKeymap(buttons), rowPins, colPins, ROWS, COLS); 

void playSuccess() {
  tone(buzzer, 370, 1000);
  RGB_color(0, 125, 0);
  delay(50);
  noTone(buzzer);
}

void playError() {
  tone(buzzer, 147, 500);
  RGB_color(125, 0, 0);
  delay(50);
  noTone(buzzer);
}

void playInput() {
  tone(buzzer, 880, 250);
  RGB_color(0, 0, 125);
  delay(50);
  noTone(buzzer);
}

void RGB_color(int red_value, int green_value, int blue_value)
{
  analogWrite(redPin, red_value);
  analogWrite(greenPin, green_value);
  analogWrite(bluePin, blue_value);
}

int unlockMode(){
    char customKey = customKeypad.getKey();
    Serial.println("Unlock Mode: Type Password to continue");
    delay(500);
    
    for(int i = 0; i < PassLength; i++) {
       while(!(customKey = customKeypad.getKey())) {
         // wait infinitley for input
       }
       if(password[i] != customKey){
          Serial.println("WRONG PASSWORD");
          Serial.println(customKey);
          playError();
          return -1;
       }
       Serial.print("*");
       playInput();
    }
    
    Serial.print("");
    Serial.println("Device Successfully Unlocked!");
    playSuccess();
    return 0;
}

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  RGB_color(125, 125, 125);
  
  Serial.begin(9600); // Begin monitoring via the serial monitor
  Serial.println("Press * to set new password or # to access the system.");
}

void loop(){
  char customKey = customKeypad.getKey();
  
  if (customKey == '*'){ // button to change passwords
    int access = unlockMode();
    
    if(access < 0) {
      Serial.println("Access Denied. Cannot change password without the old or default.");
      RGB_color(125, 0, 0);
    }
    else {
      Serial.println("Welcome, authorized user. Please Enter a new password: ");
      delay(500);
    
      for(int i = 0; i < PassLength; i++) {
        while(!(customKey = customKeypad.getKey())) {
        // wait infinitley for input
        }
   
        password[i] = customKey;
        Serial.print("*");
        playInput();  
      }
      
      Serial.println("");
      Serial.println("Password Successfully Changed!");
      playSuccess();
    }
  }

  if (customKey == '#') { // button to access system
    int access = unlockMode();
    if(access < 0) {
      Serial.println("Access Denied.");
    }
    else {
      Serial.println("Welcome, authorized user. You may now begin using the system.");
      playSuccess();
    }
  }
  
}