// Simulate heat headband with heating wire and led strip to make you "sweat/flush".
// uses several libraries such as OneWire, DallasTemperature, and Adafruit_NeoPixel to control a temperature sensor, a heating element, and a strip of LED lights.

#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_NeoPixel.h>
#include <Wire.h>

//defining constants such as the LED pin, the number of LED lights, and the delay time. 
//It also sets the initial temperature to 0, the upper and lower temperature thresholds, and initializes the oneWire and DallasTemperature libraries to read the temperature from the DS18B20 sensor.

#define LED_PIN    6
#define LED_COUNT 37
//#define DELAYVAL 500

float temperature = 0; // temperature in Celsius
int Temp_map=0;
int old_temp_map=0;
//int fadeAmount = 5; 

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

#define SENSOR_PIN  2   // Arduino pin connected to DS18B20 sensor's DQ pin
#define fadePin 9  // Arduino pin connected to relay which connected to heating element


const int TEMP_THRESHOLD_UPPER = 40; // upper threshold of temperature, change to your desire value -> hier brauchen wir die genauen Daten des Heißdrahtes, max. temp.
const int TEMP_THRESHOLD_LOWER = 25; // lower threshold of temperature, change to your desire value -> hier die Ausgangstemperatur 

OneWire oneWire(SENSOR_PIN);         // setup a oneWire instance
DallasTemperature sensors(&oneWire); // pass oneWire to DallasTemperature library

//initial brightness and other variables for controlling the LED lights. It also initializes the strip object and sets the brightness to 150.
int brightness = 0;
int TOTAL_LEDS = 37;
float MaximumBrightness = 255;
float SpeedFactor = 0.03; // I don't actually know what would look good
float StepDelay = 10; // ms for a step delay on the lights

void setup() {
  Serial.begin(9600); // initialize serial
  sensors.begin();    // initialize the sensor
  pinMode(fadePin, OUTPUT); // initialize digital pin as an output
  /***** LED STRIP *****/
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(150); // Set BRIGHTNESS to about 1/5 (max = 255) 
}

//In the loop function, the code requests the temperature from the sensor and checks if it is above the upper threshold or below the lower threshold. 
//If it is above the threshold, the heating element is turned off by setting the output of the fadePin to 0. 
//If it is below the threshold, the heating element is turned on by setting the output of the fadePin to 250.

void loop() {

  Serial.println("funktioniert3");
  sensors.requestTemperatures();             // send the command to get temperatures
  temperature = sensors.getTempCByIndex(0);  // read temperature in Celsius
  Serial.print(sensors.getTempCByIndex(0));

  if(temperature > TEMP_THRESHOLD_UPPER) {
    Serial.println("The heating element is turned off");
    analogWrite(fadePin, 0); // turn off

  } else if(temperature < TEMP_THRESHOLD_LOWER){
    Serial.println("The heating element is turned on");
    analogWrite(fadePin, 250); // turn on
  }

//After controlling the heating element, the code loops through a sequence of changing the brightness and color of the LED lights. 
//The intensity of the lights changes in a "breathing" manner using a sine function. The color of the LED lights is set to red for all the LED lights. 
//The code also shows the changes in the serial monitor and delays for a set amount of time before repeating the loop.

  for (int i = 0; i < 199; i++) {
    Serial.println(i);
// Intensity will go from 10 - MaximumBrightness in a "breathing" manner
//float intensity = MaximumBrightness /2.0 * (1.0 + sin(SpeedFactor * i));
  float intensity = i;
  
Serial.println("LED1");
  strip.setBrightness(intensity);
// Now set every LED to that color
  for (int ledNumber=0; ledNumber<TOTAL_LEDS; ledNumber++) {
  strip.setPixelColor(ledNumber, 255, 0, 0);
}

Serial.println("LE3D");
strip.show();
//Wait a bit before continuing to breathe
delay(StepDelay);
Serial.println("Ende");

}
}
