/*
|--------------------------------------------------------------------------
| Project 04 - Color Mixing Lamp
|--------------------------------------------------------------------------
|
| Use a tri-color LED, three photoresistors and the technique called Pulse 
| Width Modulation (PWM) to create a lamp that smoothly changes colors 
| depending on the external lighting conditions.
|
*/

// Constants (pins)
const int   greenLEDPin     = 9;    // Output pin to control the green color
const int   redLEDPin       = 11;   // Output pin to control the red color
const int   blueLEDPin      = 10;   // Output pin to control the blue color

const int   redSensorPin    = A0;   // Input pin to read the analog value of the color red.
const int   greenSensorPin  = A1;   // Input pin to read the analog value of the color green.
const int   blueSensorPin    = A2;   // Input pin to read the analog value of the color blue.

int redValue          = 0;
int greenValue        = 0;
int blueValue         = 0;

int redSensorValue    = 0;
int greenSensorValue  = 0;
int blueSensorValue   = 0;


// Setup code, run once
void setup() {

  // Setup reading speed of the serial port
  Serial.begin(9600);

  pinMode(greenLEDPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);
  pinMode(blueLEDPin, OUTPUT);

}

// Main code, run repeatedly
void loop() {
  redSensorValue    = analogRead(redSensorPin);
  delay(5);
  greenSensorValue  = analogRead(greenSensorPin);
  delay(5);
  blueSensorValue   = analogRead(blueSensorPin);

  Serial.print("Raw Sensor Values \t Red: ");
  Serial.print(redSensorValue);
  Serial.print("\t Green: ");
  Serial.print(greenSensorValue);
  Serial.print("\t Blue: ");
  Serial.println(blueSensorValue);

  redValue    = redSensorValue/4;
  greenValue  = greenSensorValue/4;
  blueValue   = blueSensorValue/4;

  Serial.print("Mapped Sensor Values \t Red: ");
  Serial.print(redValue);
  Serial.print("\t Green: ");
  Serial.print(greenValue);
  Serial.print("\t Blue: ");
  Serial.println(blueValue);

  analogWrite(redLEDPin, redValue);
  analogWrite(greenLEDPin, greenValue);
  analogWrite(blueLEDPin, blueValue);

}


