/*
|--------------------------------------------------------------------------
| Project 03 - Love-o-Meter
|--------------------------------------------------------------------------
|
| Use Arduino's built-in Analog-to-Digital Converter (ADC) to read your 
| skin temperature. Analog pins A0-A5 can report back values between  
| 0-1023, which maps to a range from 0 volts to 5 volts.
|
*/

// Constants (pins)
const int   sensorPin     = A0;   // Pin where the temperature sensor is attached
const int   firstLEDPin   = 2;    // First Digital pin used for the LED thermometer
const int   numOfLEDs     = 5;    // Total number of LEDs used to build the thermometer
                                  // In the book there are only 3 LEDs, I use 5 as example
                                  // The digital pins used must be consecutive 2,3,4,5,6...
const float minTempValue  = 22.0; // Minimum threshold temperature of the LED thermometer
const float maxTempValue  = 30.0; // Maximum threshold temperature of the LED thermometer
const int   checkInterval = 750;  // Time interval (in miliseconds) between readings


/*
 * Setup the LED pins as OUTPUTs and set their value to LOW.
 * The first pin is 2 and the las is 2+numOfLEDs
 */
void setupLEDs(){
  for(int pinNumber = 2; pinNumber < numOfLEDs+2; pinNumber++){
    pinMode(pinNumber, OUTPUT);
    digitalWrite(pinNumber, LOW);
  }
}


/*
 * Enable or disable LEDs according to the current temperature.
 * Using the current temperature, we will turn the LEDs on or off
 */
void writeLEDs(float temperature) {

  // Find the range of temperature to display
  int tempDifference = maxTempValue - minTempValue;

  // Find threshold increment
  float tempInterval = tempDifference / (float) numOfLEDs;

  Serial.print("|");
  
  // For each LED
  for(int nLED = 1; nLED <= numOfLEDs; nLED++){

    // Find min threshold temperature
    float minTempLED= minTempValue + (tempInterval * (float) nLED);
    
    // The LED pin is the number of the LED in the loop + 1
    int nLEDPin = nLED+1;

    Serial.print(minTempLED);
    
    // If we are over the threshold temperature
    if(temperature >= minTempLED) {
      
      // Light up the LED
      digitalWrite(nLEDPin, HIGH);
      Serial.print("-X-");
    
    } else {
    
      // Turn off the LED
      digitalWrite(nLEDPin, LOW);
      Serial.print("---");
    
    }

    Serial.print("|");
    
  }

  Serial.println();
  
}



// Setup code, run once
void setup() {
  
  // Setup reading speed of the serial port
  Serial.begin(9600);

  // Prepare the pins
  setupLEDs();
  
}


// Main code, run repeatedly
void loop() {

  // Get the analog reading from the sensor (TMP36)
  // The value is an integer, between 0 and 1023,
  int sensorVal = analogRead(sensorPin);

  Serial.print("Sensor Value: ");
  Serial.print(sensorVal);

  // Convert the value to Volts which is based 
  // off the reference voltage (5.0V)
  float voltage = (sensorVal/1024.0) * 5.0;
  
  Serial.print(", Volts: ");
  Serial.print(voltage);
  Serial.print("v");

  // Find out the real temperature in celsius
  // The resolution is 10 mV / degree centigrade with
  // a 500 mV offset to allow for negative temperatures
  // Converting from 10 mV per degree wit 500 mV offset
  // to degrees ((volatge - 500mV) times 100)
  float temperature = (voltage - 0.5) * 100;
  
  Serial.print(", degrees: ");
  Serial.print(temperature);
  Serial.println("c");
  
  // Light up the LEDs according to the real temperature
  writeLEDs(temperature);  

  //delay the reading
  delay(checkInterval);
  
}


