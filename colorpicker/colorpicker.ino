#include <Wire.h> // Library for I2C communication
#include <FastLED.h>
#include <LiquidCrystal_I2C.h> // Library for LCD
#include "gamma_correction.h"
#include "rgba_to_rgb.h"

#define LED_DATA_PIN 11

#define LED_ALPHA A1
#define LED_GREEN A2
#define LED_RED   A4
#define LED_BLUE  A5

#define OF_ALPHA  A6
#define OF_RED    A7
#define OF_GREEN  A8
#define OF_BLUE   A9

const byte interruptPin = 2;

int num_leds = 30;
// the grb that the user input
int ledSigR = 0, ledSigG = 0, ledSigB = 0, ledSigA = 0;
int ofSigR = 0, ofSigG = 0, ofSigB = 0, ofSigA = 0;
// false means color picker off
bool mode = true;
CRGB leds[35];

void change() {
  mode = !mode;
}

void Align(LiquidCrystal_I2C b, char type, int n) {
  if(n >= 100) {
    b.print(type);
    b.print(n, DEC);
    b.print(" ");
  }
  else if(n >= 10) {
    b.print(type);
    b.print(" ");
    b.print(n, DEC);
    b.print(" ");    
  }
  else {
    b.print(type);
    b.print("  ");
    b.print(n, DEC); 
    b.print(" ");     
  }
}

float Round(float a) {
  a *= 10;
  a = round(a);
  a /= 10;
}

void LCD_Show(int ledR, int ledG, int ledB, float ledA, int ofR, int ofG, int ofB, float ofA) {
  sLCD.setCursor(0, 0);
  sLCD.print("LED ");
  Align(sLCD, 'R', ledR);
  Align(sLCD, 'G', ledG);
  Align(sLCD, 'B', ledB);
  sLCD.setCursor(4, 1);
  ledA = Round(ledA);
  sLCD.print("A");
  sLCD.print(ledA, DEC);
  
  sLCD.setCursor(0, 2);
  sLCD.print("OF  ");
  Align(sLCD, 'R', ofR);
  Align(sLCD, 'G', ofG);
  Align(sLCD, 'B', ofB);
  sLCD.setCursor(4, 1);
  ofA = Round(ofA);
  sLCD.print("A");
  sLCD.print(ofA);
}


void setup() {
  LiquidCrystal_I2C sLCD = LiquidCrystal_I2C(0x27, 20, 4); // Change to (0x27,20,4) for 20x4 LCD.
  LiquidCrystal_I2C hLCD = LiquidCrystal_I2C(0x26, 20, 4); // Change to (0x27,20,4) for 20x4 LCD.
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
  FastLED.addLeds<NEOPIXEL, LED_DATA_PIN>(leds, num_leds);
  for (int i = 0; i < num_leds; i++)
  {
    leds[i] = CRGB::Black;
   }
  FastLED.show();
  // initialize serial
  Serial.begin(9600);
  // initialize knobs
  pinMode(LED_ALPHA,INPUT); // led a
  pinMode(LED_GREEN,INPUT); // led g
  pinMode(LED_RED,INPUT); // led r
  pinMode(LED_BLUE,INPUT); // led b
  
  pinMode(OF_ALPHA, INPUT); //
  
  // Interrupt--Change Mode
  attachInterrupt(digitalPinToInterrupt(interruptPin), change, CHANGE);
}

void loop() {
  // change grb to the actual grba we should feed into the leds
  // 調色模式on
  if (mode)
  {
    float *color;
    ledSigA = analogRead(A1) / 4;
    ledSigG = analogRead(A2) / 4;
    ledSigR = analogRead(A4) / 4;
    ledSigB = analogRead(A5) / 4;
    total = ledSigG + ledSigR + ledSigB;

    ledSigG = ledSigG * 255 / total;
    ledSigR = ledSigR * 255 / total;
    ledSigB = ledSigB * 255 / total;
    // color[0]:g color[1]:r color[2]:b
    color = rgba_to_rgb(ledSigG, ledSigR, ledSigB, ledSigA, 200);

    for (int i = 0; i < NUM_LEDS; i++)
    {
      leds[i] = CRGB((int)color[0], (int)color[1], (int)color[2]);
      FastLED.show();
    }
  }
  // 調色模式off
  else {
    // read RGB and light them 
    ledSigR = analogRead(A2)/4;
    ledSigG = analogRead(A4)/4;
    ledSigB = analogRead(A5)/4;
    for(int i=0;i<NUM_LEDS;i++){
      leds[i] = CRGB(ledSigR, ledSigG, ledSigB);
      FastLED.show();
    }
    // show 
  }
  
}
