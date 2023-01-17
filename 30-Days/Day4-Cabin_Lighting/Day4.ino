// Code written by Alexander Eschenauer for the 30 Day Adventure Kit
// Learn more at https://inventr.io/adventure

int SWITCH1 = 4;
int SWITCH2 = 3;
int SWITCH3 = 2;
int Light1 = 10;
int Light2 = 11;
int Light3 = 12;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(Light1, OUTPUT);
  pinMode(Light2, OUTPUT);
  pinMode(Light3, OUTPUT);
  pinMode(SWITCH1, INPUT);
  pinMode(SWITCH2, INPUT);
  pinMode(SWITCH3, INPUT);
}
// the loop function runs over and over again forever
void loop() {
  // SWITCH/LED 1
  if (digitalRead(SWITCH1) == 1){
        digitalWrite(Light1, HIGH);   // turn the LED on (HIGH is the voltage level)
  } else {
        digitalWrite(Light1, LOW);
  }

  // SWITCH/LED2
  if (digitalRead(SWITCH2) == 1){
        digitalWrite(Light2, HIGH);   // turn the LED on (HIGH is the voltage level)
  } else {
        digitalWrite(Light2, LOW);
  }

  // SWITCH/LED3
  if (digitalRead(SWITCH3) != 0){
        digitalWrite(Light3, HIGH);   // turn the LED on (HIGH is the voltage level)
  } else {
        digitalWrite(Light3, LOW);
  }
}