#include <Wire.h> // Library for I2C communication
#include <FastLED.h>
#include <LiquidCrystal_I2C.h> // Library for LCD
#include "gamma_correction.h"
#include "rgba_to_rgb.h"

#define LED_DATA_PIN 11
#define NUM_LEDS 30
#define LED_ALPHA A1
#define LED_GREEN A2
#define LED_RED   A4
#define LED_BLUE  A5

#define OF_ALPHA  A6
#define OF_RED    A7
#define OF_GREEN  A8
#define OF_BLUE   A9

#define ADDRESS 0x3f

const byte interruptPin = 2;

// the grb that the user input
double ledSigR = 0, ledSigG = 0, ledSigB = 0, ledSigA = 0;
double ofSigR = 0, ofSigG = 0, ofSigB = 0, ofSigA = 0;
// false means color picker off
bool mode = true;
CRGB leds[35];
// lcd
LiquidCrystal_I2C sLCD = LiquidCrystal_I2C(0x27, 20, 4); // Change to (0x27,20,4) for 20x4 LCD.
LiquidCrystal_I2C hLCD = LiquidCrystal_I2C(0x26, 20, 4); // Change to (0x27,20,4) for 20x4 LCD.

void change() {
  
  mode = !mode;
}

void Align(LiquidCrystal_I2C b, String type, int n) {
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

float Round_LED(float a) {
  a /= 170;
  a *= 1000;
  int a_show = int(round(a));
  return a_show;
}

float Round_OF(float a) {
  a /= 255;
  a *= 1000;
  int a_show = int(round(a));
  return a_show;
}

void sLCD_Show(int ledR, int ledG, int ledB, float ledA, int ofR, int ofG, int ofB, float ofA) {
  sLCD.setCursor(0, 0);
  sLCD.print("LED ");
  Align(sLCD, "R", ledR);
  Align(sLCD, "G", ledG);
  Align(sLCD, "B", ledB);
  sLCD.setCursor(4, 1);
  int ledA_show = Round_LED(ledA);
  ledA = ledA_show * 0.001;
  sLCD.print("A");
  sLCD.print(ledA, DEC);
  
  sLCD.setCursor(0, 2);
  sLCD.print("OF  ");
  Align(sLCD, "R", ofR);
  Align(sLCD, "G", ofG);
  Align(sLCD, "B", ofB);
  sLCD.setCursor(4, 3);
  int ofA_show = Round_OF(ofA);
  ofA = ofA_show * 0.001;
  sLCD.print("A");
  sLCD.print(ofA, DEC);
}

void hLCD_Show(int IR, int IG, int IB, int PR, int PG, int PB, int ledR, int ledG, int ledB) {
  hLCD.setCursor(0, 0);
  hLCD.print("LED ");
  Align(hLCD, "R", ledR);
  hLCD.setCursor(10, 0);
  Align(hLCD, "G", ledG);
  hLCD.setCursor(16, 0);
  Align(hLCD, "B", ledB);
  hLCD.setCursor(0, 1); 
  hLCD.print("OF ");   
  Align(hLCD, "IR", IR);
  Align(hLCD, "IG", IG);
  Align(hLCD, "IB", IB);
  hLCD.setCursor(3, 2); 
  Align(hLCD, "PR", PR);
  Align(hLCD, "PG", PG);
  Align(hLCD, "PB", PB);
}

void setup() {
  // Initialize the LCDs:
  sLCD.init();
  sLCD.backlight();
  sLCD.setCursor(2, 0); //Set the cursor on the third column and the second row (counting starts at 0!).
  sLCD.print("Mode: Color Picking");
  sLCD.setCursor(2, 1); //Set the cursor on the third column and the second row (counting starts at 0!).
  sLCD.print("for software team");  
  delay(1000);
  sLCD.clear();
  hLCD.init();
  hLCD.backlight();
  hLCD.setCursor(2, 0); //Set the cursor on the third column and the second row (counting starts at 0!).
  hLCD.print("Mode: Color Picking");
  hLCD.setCursor(2, 1); //Set the cursor on the third column and the second row (counting starts at 0!).
  hLCD.print("for hardware team");  
  delay(3000);
  hLCD.clear();
  // initialize leds
  FastLED.addLeds<NEOPIXEL, LED_DATA_PIN>(leds, NUM_LEDS);
  for (int i = 0; i < NUM_LEDS; i++)
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
  
  pinMode(OF_ALPHA, INPUT); // of a
  pinMode(OF_RED, INPUT);   //of r
  pinMode(OF_GREEN, INPUT); //of g
  pinMode(OF_BLUE, INPUT);  //of b
  
  //Wire
  Wire.begin();
  // Interrupt--Change Mode
  attachInterrupt(digitalPinToInterrupt(interruptPin), change, CHANGE);

}

void loop()
{
  Serial.print(digitalRead(interruptPin));
  // change grb to the actual grba we should feed into the leds
  // 調色模式on
  if (mode)
  {
    float *LEDcolor;
    int ledTotal;
    ledSigA = analogRead(LED_ALPHA) / 4;
    ledSigG = analogRead(LED_GREEN) / 4;
    ledSigR = analogRead(LED_RED) / 4;
    ledSigB = analogRead(LED_BLUE) / 4;
    ledTotal = ledSigG + ledSigR + ledSigB;

    ledSigG = ledSigG * 255 / ledTotal;
    ledSigR = ledSigR * 255 / ledTotal;
    ledSigB = ledSigB * 255 / ledTotal;
    // color[0]:r color[1]:g color[2]:b
//    Serial.print(int(ledSigR));
//    Serial.print(' ');
//    Serial.print(int(ledSigG));
//    Serial.print(' ');
//    Serial.println(int(ledSigB));
    LEDcolor = LEDrgba_to_rgb(ledSigR, ledSigG, ledSigB, ledSigA, 255);

    for (int i = 0; i < NUM_LEDS; i++)
    {
      leds[i] = CRGB((int)LEDcolor[0], (int)LEDcolor[1], (int)LEDcolor[2]);
      FastLED.show();
    }

    //OF data read
    ofSigA = analogRead(OF_ALPHA)/4;
    ofSigR = analogRead(OF_RED)/4;
    ofSigG = analogRead(OF_GREEN)/4;
    ofSigB = analogRead(OF_BLUE)/4;
    
    //OF data normalize
    int ofTotal = 0;
    ofTotal = ofSigR + ofSigG + ofSigB;
    
    ofSigR = ofSigR * 255/ofTotal;
    ofSigG = ofSigG * 255/ofTotal;
    ofSigB = ofSigB * 255/ofTotal;

    //handle alpha
    float *OFcolor = OFrgba_to_rgb(ofSigA);
    //Set IREF
    Wire.beginTransmission(ADDRESS); // transmit to device
    Wire.write(0x22);        // sends five bytes
    Wire.write(int(ofSigR));              // sends one byte
    Wire.endTransmission();    // stop transmitting
    Wire.beginTransmission(ADDRESS); // transmit to device
    Wire.write(0x23);        // sends five bytes
    Wire.write(int(ofSigG));              // sends one byte
    Wire.endTransmission();    // stop transmitting
    Wire.beginTransmission(ADDRESS); // transmit to device
    Wire.write(0x24);        // sends five bytes
    Wire.write(int(ofSigB));              // sends one byte
    Wire.endTransmission();    // stop transmitting
    Wire.beginTransmission(ADDRESS); // transmit to device
    Wire.write(0x0a);        // sends five bytes
    Wire.write(int(OFcolor[0]));              // sends one byte
    Wire.endTransmission();    // stop transmitting
    Wire.beginTransmission(ADDRESS); // transmit to device
    Wire.write(0x0b);        // sends five bytes
    Wire.write(int(OFcolor[1]));              // sends one byte
    Wire.endTransmission();    // stop transmitting
    Wire.beginTransmission(ADDRESS); // transmit to device
    Wire.write(0x0c);        // sends five bytes
    Wire.write(int(OFcolor[2]));              // sends one byte
    Wire.endTransmission();    // stop transmitting
    // show 
    hLCD_Show(ofSigR, ofSigG, ofSigB, int(OFcolor[0]), int(OFcolor[1]), int(OFcolor[2]), LEDcolor[0], LEDcolor[1], LEDcolor[0]);
//    Serial.print(int(ledSigR));
//    Serial.print(' ');
//    Serial.print(int(ledSigG));
//    Serial.print(' ');
//    Serial.println(int(ledSigB));
    sLCD_Show(int(ledSigR), int(ledSigG), int(ledSigB), ledSigA, ofSigR, ofSigG, ofSigB, ofSigA);
    delay(50);
  }
  // 調色模式off
  else {
    // read RGB and light them 
    ledSigR = analogRead(LED_RED)/4;
    ledSigG = analogRead(LED_GREEN)/4;
    ledSigB = analogRead(LED_BLUE)/4;
    for(int i=0;i<NUM_LEDS;i++){
      leds[i] = CRGB(ledSigR, ledSigG, ledSigB);
      FastLED.show();
    }

    //OF data read
    ofSigR = analogRead(OF_RED)/4;
    ofSigG = analogRead(OF_GREEN)/4;
    ofSigB = analogRead(OF_BLUE)/4;
    
    //OF data normalize
    int ofTotal = 0;
    ofTotal = ofSigR + ofSigG + ofSigB;
    
    ofSigR = ofSigR * 0.8;
    ofSigG = ofSigG * 0.8;
    ofSigB = ofSigB * 0.8;

    //Set IREF
    Wire.beginTransmission(ADDRESS); // transmit to device
    Wire.write(0x22);        // sends five bytes
    Wire.write(int(ofSigR));              // sends one byte
    Wire.endTransmission();    // stop transmitting
    Wire.beginTransmission(ADDRESS); // transmit to device
    Wire.write(0x23);        // sends five bytes
    Wire.write(int(ofSigG));              // sends one byte
    Wire.endTransmission();    // stop transmitting
    Wire.beginTransmission(ADDRESS); // transmit to device
    Wire.write(0x24);        // sends five bytes
    Wire.write(int(ofSigB));              // sends one byte
    Wire.endTransmission();    // stop transmitting
    Wire.beginTransmission(ADDRESS); // transmit to device
    Wire.write(0x0a);        // sends five bytes
    Wire.write(255);              // sends one byte
    Wire.endTransmission();    // stop transmitting
    Wire.beginTransmission(ADDRESS); // transmit to device
    Wire.write(0x0b);        // sends five bytes
    Wire.write(255);              // sends one byte
    Wire.endTransmission();    // stop transmitting
    Wire.beginTransmission(ADDRESS); // transmit to device
    Wire.write(0x0c);        // sends five bytes
    Wire.write(255);              // sends one byte
    Wire.endTransmission();    // stop transmitting

    // show 
    sLCD_Show(int(ledSigR), int(ledSigG), int(ledSigB), ledSigA, int(ofSigR), int(ofSigG), int(ofSigB), ofSigA);
  }
}
