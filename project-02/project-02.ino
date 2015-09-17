/*
|--------------------------------------------------------------------------
| Project 02 - Spaceship interface
|--------------------------------------------------------------------------
|
| A green LED will be on, until you press a button. When the Arduino gets 
| a signal from the buttom, the green light will turn off and 2 other 
| red lights will start blinking.
|
*/

// Constants (pins)
const int button   = 2;
const int greenLed = 3;
const int redLed1  = 4;
const int redLed2  = 5;


// Setup code, run once
void setup() {
  
  // Digital outputs
  pinMode(greenLed, OUTPUT);
  pinMode(redLed1, OUTPUT);
  pinMode(redLed2, OUTPUT);

  // Digital inputs
  pinMode(button, INPUT);

}


// Main code, run repeatedly
void loop() {

  //check button state
  int switchState = digitalRead(button);

  // if the button is not pressed
  // turn on Green LED
  // turn off Red LEDs
  if (switchState == LOW) {
    
    digitalWrite(greenLed, HIGH);
    digitalWrite(redLed1, LOW);
    digitalWrite(redLed2, LOW);
    
  }

  // if the button is pressed
  // turn off Green LED
  // blink red LEDs (delay 250ms each state)
  else {
    
    digitalWrite(greenLed, LOW);
    
    digitalWrite(redLed1, LOW);
    digitalWrite(redLed2, HIGH);
    delay(250);
    
    digitalWrite(redLed1, HIGH);
    digitalWrite(redLed2, LOW);
    delay(250);
    
  }
  
} // loop
