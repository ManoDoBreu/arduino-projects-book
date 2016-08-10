/*
|--------------------------------------------------------------------------
| Project 05 - Mood Cue
|--------------------------------------------------------------------------
|
| Use a servo motor to make a mechanical gauge to point out what sort 
| of mood you'are in that day. Also, use LEDs to represent the position
| of the potentiometer.
|
*/


#include <Servo.h>

// Constants (pins)
const int   potPin      = A0;   // The input pin of the potentiometer
const int   servoPin    = 9;    // Output pin where the servo motor is attached.

const int   firstLEDPin = 2;    // First Digital pin used for the LED thermometer
const int   numOfLEDs   = 3;    // Total number of LEDs used to build the thermometer
const int   potMin      = 0;    // Min range value of the potentiometer
const int   potMax      = 1023; // Max range value of the potentiometer
const int   angleMin    = 0;    // Min angle value of the servo motor
const int   angleMax    = 179;  // Max angle value of the servo motor

// Variable initialization
Servo       motor;              // The object variable for the servo motor
int         potVal;             // Used to store the readed value of the "pot"
int         angle;              // Used to store the calculated angle value


/*
 * Setup the LED pins as OUTPUTs and set their value to LOW.
 * The first pin is firstLEDPin and the last is firstLEDPin+numOfLEDs
 */
void setupLEDs(){
  for(int pinNumber = firstLEDPin; pinNumber < firstLEDPin+numOfLEDs; pinNumber++){
    pinMode(pinNumber, OUTPUT);
    digitalWrite(pinNumber, LOW);
  }
}

/*
 * Enable or disable LEDs according to the current angle position.
 * Using the current angle, we will turn the LEDs on or off
 */
void switchLEDs(int angle){

  // Find the range of operation in case it is not zero-based (servo = 0-179)
  int angleDiff = angleMax - angleMin;

  // Find increment. What is the working range of each LED
  float angleInc = angleDiff / (float) numOfLEDs;
  
  Serial.print("angleInc: ");
  Serial.print(angleInc);
  
  Serial.print(", threshold: ");
  Serial.print(angleMin);
  
  // For each LED
  for(int nLED = 0; nLED < numOfLEDs; nLED++){

    // Find min working threshold position
    float minLED = angleMin + (angleInc * (float) nLED);
    
    // Find max working threshold position
    float maxLED = minLED + angleInc;
    
    Serial.print("<");
    Serial.print(maxLED);
    
    int nLEDPin = nLED+firstLEDPin;
    
    // If we are in between the thresholds
    if(minLED <= angle && angle < maxLED) {
      
      // Light up the LED
      digitalWrite(nLEDPin, HIGH);
      
    } else {
      
      // Turn off the LED
      digitalWrite(nLEDPin, LOW);
      
    }
    
  }
    
}

/*
 * Prints out the current readed value from the potentiometer 
 * and the converted angle value.
 */
void logValues(int potVal, int angle){
  
  Serial.print("potVal: ");
  Serial.print(potVal);
  Serial.print(", angle: ");
  Serial.print(angle);
  Serial.print(", ");
  
}

// Setup code, run once
void setup() {
  
  // Setup reading speed of the serial port
  Serial.begin(9600);

  // Define where the servo is connected
  motor.attach(servoPin);

  // Prepare the LED pins
  setupLEDs();
  
}

// Main code, run repeatedly
void loop() {
  
  // Read the pot value (range 0-1023)
  potVal = analogRead(potPin); 

  // Convert the pot value to angle (angle = 0-179)
  angle = map(potVal, potMin, potMax, angleMin, angleMax);    

  // Print value on serial port
  logValues(potVal, angle);

  // Send angle value to servo motor
  motor.write(angle);

  // Light up the LEDs
  switchLEDs(angle);

  // Break the line in the serial monitor
  Serial.println();

  // Delay 15ms before a new read.
  delay(15);                              

}
