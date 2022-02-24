#include <Wire.h> // Library for I2C communication
#include <FastLED.h>
#include "gamma_correction.h"

#define DATA_PIN 11
const byte interruptPin = 2;

int num_leds = 30;
// the grb that the user input
int ig = 0, ir = 0, ib = 0;
int ia = 0;
int iRefg = 0, iRefr = 0, iRefb = 0;
// false means color picker off
bool mode = false;
CRGB leds[35];

void change() {
  mode = true;
}
void setup() {
  // initialize leds
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, num_leds);
  for(int i=0;i<num_leds;i++){
    leds[i] = CRGB::Black;
   }
  FastLED.show();
  // initialize serial
  Serial.begin(9600);
  // initialize knobs
  pinMode(A1,INPUT); // a
  pinMode(A2,INPUT); // g
  pinMode(A4,INPUT); // r
  pinMode(A5,INPUT); // b
}

void loop() {
  // change grb to the actual grba we should feed into the leds
  // 調色模式on
  if(mode) {
    
  }
  // 調色模式off
  else {
    
  }

  
}
