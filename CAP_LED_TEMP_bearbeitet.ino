#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_NeoPixel.h>
#include <Wire.h>

#define LED_PIN    6
#define LED_COUNT 6
#define DELAYVAL 50

float temperature = 0; // temperature in Celsius
int Temp_map=0;
int old_temp_map=0;
//int fadeAmount = 5; 

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

#define SENSOR_PIN  2   // Arduino pin connected to DS18B20 sensor's DQ pin
#define fadePin 9  // Arduino pin connected to relay which connected to heating element


const int TEMP_THRESHOLD_UPPER = 35; // upper threshold of temperature, change to your desire value -> hier brauchen wir die genauen Daten des Heißdrahtes, max. temp.
const int TEMP_THRESHOLD_LOWER = 25; // lower threshold of temperature, change to your desire value -> hier die Ausgangstemperatur 

OneWire oneWire(SENSOR_PIN);         // setup a oneWire instance
DallasTemperature sensors(&oneWire); // pass oneWire to DallasTemperature library

int brightness = 0;

void setup() {
  Serial.begin(9600); // initialize serial
  sensors.begin();    // initialize the sensor
  pinMode(fadePin, OUTPUT); // initialize digital pin as an output
  /***** LED STRIP *****/
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(100); // Set BRIGHTNESS to about 1/5 (max = 255) 
}

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

temperature = sensors.getTempCByIndex(0);

Temp_map = map(temperature, 25, 35, 0,255);

    strip.clear();
    strip.fill(strip.Color(Temp_map,0,0),0,6);
    strip.show(); 
}
/*
  temperature = sensors.getTempCByIndex(0);
  old_temp_map = Temp_map;
  Temp_map = map(temperature, 25, 35, 0, brightness);
  if (old_temp_map > Temp_map){
    while (old_temp_map > Temp_map) {
    strip.clear();
    
    strip.fill(strip.Color(255,0,0,0),0,old_temp_map-1);
    strip.show();
    old_temp_map--;
    delay(5);
  }
  }
  else if (old_temp_map < Temp_map){
    while (old_temp_map < Temp_map) {
    strip.clear();
    strip.fill(strip.Color(255,0,0,0),0,old_temp_map-1);
    strip.show();
    old_temp_map++;
    delay(5);
  }
  }
  else {
    strip.clear();
    strip.fill(strip.Color(255,0,0,0),0,old_temp_map-1);
    strip.show();
  }
}
*/
