#include <Wire.h> // Library for I2C communication
#include <FastLED.h>
#include "gamma_correction.h"
#include "rgba_to_rgb.h"
#define DATA_PIN 11
const byte interruptPin = 2;

int num_leds = 30;
// the grb that the user input
int sigR = 0, sigG = 0, sigB = 0;
int sigA = 0;
int iRefg = 0, iRefr = 0, iRefb = 0;
// false means color picker off
bool mode = false;
CRGB leds[35];

void change()
{
  mode = true;
}
void setup()
{
  // initialize leds
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, num_leds);
  for (int i = 0; i < num_leds; i++)
  {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
  // initialize serial
  Serial.begin(9600);
  // initialize knobs
  pinMode(A1, INPUT); // a
  pinMode(A2, INPUT); // g
  pinMode(A4, INPUT); // r
  pinMode(A5, INPUT); // b
}

void loop()
{
  // change grb to the actual grba we should feed into the leds
  // 調色模式on
  if (mode)
  {
    float R_out = 0f, G_out = 0f, B_out = 0f;
    float *color;
    sigA = analogRead(A1) / 4;
    sigG = analogRead(A2) / 4;
    sigR = analogRead(A4) / 4;
    sigB = analogRead(A5) / 4;
    total = sigG + sigR + sigB;

    sigG = sigG * 255 / total;
    sigR = sigR * 255 / total;
    sigB = sigB * 255 / total;
    // color[0]:g color[1]:r color[2]:b
    color = rgba_to_rgb(sigG, sigR, sigB, sigA, 200);

    for (int i = 0; i < NUM_LEDS; i++)
    {
      leds[i] = CRGB((int)color[0], (int)color[1], (int)color[2]);
      FastLED.show();
    }
  }
  // 調色模式off
  else
  {
  }
}