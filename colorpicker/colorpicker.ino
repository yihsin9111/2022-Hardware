#include <Wire.h> // Library for I2C communication
#include <FastLED.h>
#include "gamma_correction.h"

#define DATA_PIN 11
int num_leds = 30;
// the grb that the user input
int ig = 0;
int ir = 0;
int ib = 0;
int ia = 0;
CRGB leds[35];

Color_regulator reg_g(1.8);
Color_regulator reg_r(1.6);
Color_regulator reg_b(1.66);

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, num_leds);
  for(int i=0;i<num_leds;i++){
    leds[i] = CRGB::Black;
   }
  FastLED.show();
  Serial.begin(9600);
}

void loop() {
  // change grb to the actual grba we should feed into the leds
//  int g = reg_g.gamma_correction(ig);
//  int r = reg_r.gamma_correction(ir);
//  int b = reg_b.gamma_correction(ib);
  

  
}
