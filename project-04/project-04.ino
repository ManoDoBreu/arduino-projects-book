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
const int   blueSensorPin   = A2;   // Input pin to read the analog value of the color blue.

const int   buttonPin       = 12;   // Input pin of the button used to trigger the calibration process.

// Variable initialization
int redValue          = 0;  // This variables will store the calculated output values 
int greenValue        = 0;  // of each color that we will send to the tri-color LED.
int blueValue         = 0;  // The value will be an integer between 0 and 255.

int sensorValue[]     = {0, 0, 0};          // This array will store the readed input values of the sensors (range 0 - 1023).
int sensorMin[]       = {1023, 1023, 1023}; // The initial minimum value of each sensor is the maximum value possible.
int sensorMax[]       = {0, 0, 0};          // The initial maximum value of each sensor is the minimum value possible.

// This function reads the sensor values
void readSensors() {
  
  // read the analog value (range 0 - 1023)
  sensorValue[0]    = analogRead(redSensorPin);
  sensorValue[1]    = analogRead(greenSensorPin);
  sensorValue[2]    = analogRead(blueSensorPin);

  // print raw values
  Serial.print("Raw Sensor Values ");
  logValues(sensorValue[0], sensorValue[1], sensorValue[2]);

  // re-map the readed values to the corresponding min-max ranges.
  for(int i=0; i<3; i++) {
    sensorValue[i]    = map(sensorValue[i], sensorMin[i], sensorMax[i], 0, 255);
  }

  // print re-mapped values
  Serial.print("Mapped Sensor Values ");
  logValues(redValue, greenValue, blueValue);

  // store and constrain the output in case the sensor value is outside the range seen during calibration.
  redValue          = constrain(sensorValue[0], 0, 255);
  greenValue        = constrain(sensorValue[1], 0, 255);
  blueValue         = constrain(sensorValue[2], 0, 255);
}

// Print the color values
void logValues(int red, int green, int blue){
  Serial.print("\t Red: ");
  Serial.print(red);
  Serial.print("\t Green: ");
  Serial.print(green);
  Serial.print("\t Blue: ");
  Serial.println(blue);
}

// Calibrate the sensors
void calibrate() {

  Serial.println("Calibrating");
  
  // read the sensors
  sensorValue[0]    = analogRead(redSensorPin);
  sensorValue[1]    = analogRead(greenSensorPin);
  sensorValue[2]    = analogRead(blueSensorPin);

  // record the maximum sensor values
  for(int i=0; i<3; i++) {
    if (sensorValue[i] > sensorMax[i]) {
      sensorMax[i] = sensorValue[i];
    }  
  }
  
  // record the minimum sensor values
  for(int i=0; i<3; i++) {
    if (sensorValue[i] < sensorMin[i]) {
      sensorMin[i] = sensorValue[i];
    }
  }
  
}

// Setup code, run once
void setup() {

  // Setup reading speed of the serial port
  Serial.begin(9600);

  // Pin configuration
  pinMode(greenLEDPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);
  pinMode(blueLEDPin, OUTPUT);
  pinMode(buttonPin, INPUT);

}

// Main code, run repeatedly
void loop() {

  // while the button is pressed, take calibration readings
  while (digitalRead(buttonPin) == HIGH) {
    calibrate();
  }

  // read the sensor values
  readSensors();

  // write values to the tri-color LED
  analogWrite(redLEDPin, redValue);
  analogWrite(greenLEDPin, greenValue);
  analogWrite(blueLEDPin, blueValue);

  delay(500);
}


