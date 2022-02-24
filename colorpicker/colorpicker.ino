#include <Wire.h> // Library for I2C communication
#include <FastLED.h>
#include <LiquidCrystal_I2C.h> // Library for LCD
#include "gamma_correction.h"

#define DATA_PIN 11
const byte interruptPin = 2;

int num_leds = 30;
// the grb that the user input
int sigR = 0, sigG = 0, sigB = 0;
int sigA = 0;
// false means color picker off
bool mode = true;
CRGB leds[35];

void change() {
  mode = false;
}

void LCD_Show(int R, int sigG, int sigB, int sigA, int ) {

}

void setup() {
  LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x26, 16, 2); // Change to (0x27,20,4) for 20x4 LCD.
  lcd.init();
  lcd.backlight();
  // Check LCD
  lcd.setCursor(2, 0); // Set the cursor on the third column and first row.
  lcd.print("ColorPicker"); // Print the string "Hello World!"
  lcd.setCursor(2, 1); //Set the cursor on the third column and the second row (counting starts at 0!).
  lcd.print("For Software");
  delay(1000);
  lcd.clear();
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
  // Interrupt--Change Mode
  attachInterrupt(digitalPinToInterrupt(interruptPin), change, CHANGE);
}

void loop() {
  // change grb to the actual grba we should feed into the leds
  // 調色模式on
  if(mode) {
    
  }
  // 調色模式off
  else {
    // read RGB and light them 
    sigR = analogRead(A2)/4;
    sigG = analogRead(A4)/4;
    sigB = analogRead(A5)/4;
    for(int i=0;i<NUM_LEDS;i++){
      leds[i] = CRGB(sigR, sigG, sigB);
      FastLED.show();
    }
    // show 
    

  
}
