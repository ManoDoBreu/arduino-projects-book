/*
|--------------------------------------------------------------------------
| Project 05 - Mood Cue
|--------------------------------------------------------------------------
|
| Use a servo motor to make a mechanical gauge to point out what sort 
| of mood you'are in that day. 
|
*/


#include <Servo.h>

// Constants (pins)
const int   potPin      = A0;   // The input pin of the potentiometer
const int   servoPin    = 9;    // Output pin where the servo motor is attached.

// Variable initialization
Servo       motor;              // The object variable of the servo motor
int         potVal;             // Used to store the readed value of the "pot"
int         angle;              // Used to store the calculated angle value

void logValues(int potVal, int angle){
  Serial.print("potVal: ");
  Serial.print(potVal);
  Serial.print(", angle: ");
  Serial.println(angle);
}

// Setup code, run once
void setup() {
  
  // Setup reading speed of the serial port
  Serial.begin(9600);

  // Pin configuration
  motor.attach(servoPin);

}

// Main code, run repeatedly
void loop() {
  
  potVal = analogRead(potPin);            // Read the pot value (range 0-1023)
  angle = map(potVal, 0, 1023, 0, 179);   // Convert the pot value to angle (angle = 0-179)

  logValues(potVal, angle);               // Print value on serial port
  
  motor.write(angle);                     // Send angle value to servo motor
  
  delay(15);                              // Delay 15ms before a new read.

}
