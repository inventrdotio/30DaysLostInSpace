// Code written by Alexander Eschenauer for the 30 Day Adventure Kit
// Learn more at https://inventr.io/adventure

#include <Keypad.h>

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

byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2}; 

Keypad customKeypad = Keypad(makeKeymap(buttons), rowPins, colPins, ROWS, COLS); 

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
          return -1;
       }
       Serial.print("*");
    }
    
    Serial.print("");
    Serial.println("Device Successfully Unlocked!");
    return 0;
}

void setup() {
  Serial.begin(9600); // Begin monitoring via the serial monitor
  Serial.println("Press * to set new password or # to access the system.");
}

void loop(){
  char customKey = customKeypad.getKey();

  if (customKey == '*'){ // button to change password
    int access = unlockMode();
    
    if(access < 0) {
      Serial.println("Access Denied. Cannot change password without the old or default.");
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
      }
      
      Serial.println("");
      Serial.println("Password Successfully Changed!");
    }
  }

  if (customKey == '#') { // button to access system
    int access = unlockMode();
    if(access < 0) {
      Serial.println("Access Denied.");
    }
    else {
      Serial.println("Welcome, authorized user. You may now begin using the system.");
    }
  }
  
}