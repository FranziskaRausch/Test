#include <OneWire.h>
#include <DallasTemperature.h>
#include <FastLED.h>

#define SENSOR_PIN  2   // Arduino pin connected to DS18B20 sensor's DQ pin
#define fadePin 9  // Arduino pin connected to relay which connected to heating element

#define NUM_LEDS 6 // Anzahl der LEDs auf dem Strip die angesteuert werden sollen
#define LED_PIN 6
#define BRIGHTNESS  0
CRGB leds[NUM_LEDS];

int sensorwert;

const int TEMP_THRESHOLD_UPPER = 27; // upper threshold of temperature, change to your desire value -> hier brauchen wir die genauen Daten des Heißdrahtes, max. temp.
const int TEMP_THRESHOLD_LOWER = 25; // lower threshold of temperature, change to your desire value -> hier die Ausgangstemperatur 

OneWire oneWire(SENSOR_PIN);         // setup a oneWire instance
DallasTemperature sensors(&oneWire); // pass oneWire to DallasTemperature library

float temperature;    // temperature in Celsius

void setup() {
  Serial.begin(9600); // initialize serial
  sensors.begin();    // initialize the sensor
  pinMode(fadePin, OUTPUT); // initialize digital pin as an output
  /***** LED STRIP *****/
  FastLED.addLeds<WS2811, LED_PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
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

  sensorwert=analogRead(SENSOR_PIN); //Auslesen des Sensorwertes. 
  if(temperature < 24) {
    Serial.println("LED off");
    analogWrite(LED_PIN, 0);
  } 
  else (BRIGHTNESS = map(temperature() 25, 35, 0, 255){
  analogWrite(LED_PIN, BRIGHTNESS);
  }
  delay(500);
}
/*
  void FadeIn(byte red, byte green, byte blue){
    float r, g, b;
    // Temperaturanstieg   
    for(int k = 0; k < 256; k=k+1) {
      r = (k/256.0)*red;
      g = (k/256.0)*green;
      b = (k/256.0)*blue;
      setAll(r,g,b);
      showStrip();
    }
  }



  void FadeOut(byte red, byte green, byte blue){
    float r, g, b;
 
    // Temperaturfall 
    for(int k = 255; k >= 0; k=k-2) {
      r = (k/256.0)*red;
      g = (k/256.0)*green;
      b = (k/256.0)*blue;
      setAll(r,g,b);
      showStrip();
    }
  }

void showStrip() {
 #ifdef ADAFRUIT_NEOPIXEL_H
   strip.show();
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
   FastLED.show();
   FastLED.delay(10);
 #endif
}

void setPixel(int Pixel, byte red, byte green, byte blue) {
 #ifdef ADAFRUIT_NEOPIXEL_H
   strip.setPixelColor(Pixel, strip.Color(red, green, blue));
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
   leds[Pixel].r = red;
   leds[Pixel].g = green;
   leds[Pixel].b = blue;
 #endif
}

void setAll(byte red, byte green, byte blue) {
  for(int i = 0; i < NUM_LEDS; i++ ) {
    setPixel(i, red, green, blue);
  }
  showStrip();
}
*/
