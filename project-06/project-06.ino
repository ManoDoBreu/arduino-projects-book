/*
|--------------------------------------------------------------------------
| Project 06 - Light theremin
|--------------------------------------------------------------------------
|
| Create a light-based theremin using a photoresistor and a piezo element. 
| Using the tone() function and the external lighting value, generate a
| characteristic sound.
|
*/


// Constants (pins)
const int buttonPin     = 13;     // Input pin of the button used to trigger the calibration process.
const int sensorPin     = A0;     // Input pin to read the analog value of the photoresistor.
const int piezoPin      = 8;      // Output pin to control the piezo.

// Variable initialization
long sensorValue        = 0L;     // Stores the readed value from the piezo (long var to store values over 32767).
int sensorMin           = 1023;   // The initial minimum value of the sensor is the maximum possible value.
int sensorMax           = 0;      // The initial maximum value of the sensor is the minimum possible value.
int duration            = 20;     // Duration of the sound;
int pitchMin            = 50;     // Minimum pitch value of the piezo;
long pitchMax           = 40000L; // Maximum pitch value (long var because the value is over 32767)

// This function reads the sensor value
int readSensor() {
  
  // read the analog value (range 0 - 1023)
  sensorValue = analogRead(sensorPin);

  // print raw values
  Serial.print("Raw Sensor Value: ");
  Serial.print(sensorValue);
  
  // re-map the readed value to the corresponding min-max ranges.
  sensorValue = map(sensorValue, sensorMin, sensorMax, pitchMin, pitchMax);
  
  // store and constrain the output in case the sensor value is outside the range seen during calibration.
  sensorValue = constrain(sensorValue, pitchMin, pitchMax);

  // print re-mapped values
  Serial.print(" Mapped Sensor Value: ");
  Serial.println(sensorValue);
  
  return sensorValue;
}

// Calibrate the sensors
void calibrate() {

  Serial.print("Calibrating: ");
  
  // read the sensor
  sensorValue = analogRead(sensorPin);
  
  // record the maximum sensor value
  if (sensorValue > sensorMax) {
    sensorMax = sensorValue;
  }
  
  // record the minimum sensor value
  if (sensorValue < sensorMin) {
    sensorMin = sensorValue;
  }

  Serial.print(sensorMin);
  Serial.print(",");
  Serial.println(sensorMax);
  
}

// Setup code, run once
void setup() {
  
  // Setup reading speed of the serial port
  Serial.begin(9600);

  // Pin configuration
  pinMode(buttonPin, INPUT);

}

// Main code, run repeatedly
void loop() {

  // while the button is pressed, take calibration readings
  while (digitalRead(buttonPin) == HIGH) {
    calibrate();
  }

  // get the sensor value
  int pitch = readSensor();

  // generate the sound
  tone(piezoPin, pitch, duration);

  // delay the loop before next iteration
  delay(10);

}
