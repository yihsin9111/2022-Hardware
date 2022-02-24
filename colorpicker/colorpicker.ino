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

void LCD_Show(int sigR, int sigG, int sigB, int sigA) {
  lcd.setCursor(0,0);
  lcd.print("R : ");
  lcd.setCursor(4,0);
  lcd.print(sigR, DEC);
  if(sigR<10){
    lcd.setCursor(5,0);
    lcd.print("  ");
  }
  else if(sigR<100){
    lcd.setCursor(6,0);
    lcd.print(" ");
  }
  lcd.setCursor(7,0);
  lcd.print(", G : ");
  lcd.setCursor(13,0);
  lcd.print(sigG, DEC);
  if(sigG<10){
    lcd.setCursor(14,0);
    lcd.print("  ");
  }
  else if(sigG<100){
    lcd.setCursor(15,0);
    lcd.print(" ");
  }
  lcd.setCursor(0,1);
  lcd.print("B : ");
  lcd.setCursor(4,1);
  lcd.print(sigB, DEC);
  if(sigB<10){
    lcd.setCursor(5,1);
    lcd.print("  ");
  }
  else if(sigB<100){
    lcd.setCursor(6,1);
    lcd.print(" ");
  }
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
    // color[0]:g color[1]:r color[2]:b
    LEDcolor = LEDrgba_to_rgb(ledSigG, ledSigR, ledSigB, ledSigA, 200);

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
    Wire.write(ofSigR);              // sends one byte
    Wire.endTransmission();    // stop transmitting
    Wire.beginTransmission(ADDRESS); // transmit to device
    Wire.write(0x23);        // sends five bytes
    Wire.write(ofSigG);              // sends one byte
    Wire.endTransmission();    // stop transmitting
    Wire.beginTransmission(ADDRESS); // transmit to device
    Wire.write(0x24);        // sends five bytes
    Wire.write(ofSigB);              // sends one byte
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

    //OF data read
    ofSigR = analogRead(OF_RED)/4;
    ofSigG = analogRead(OF_GREEN)/4;
    ofSigB = analogRead(OF_BLUE)/4;
    
    //OF data normalize
    int ofTotal = 0;
    ofTotal = ofSigR + ofSigG + ofSigB;
    
    ofSigR = ofSigR * 255/ofTotal;
    ofSigG = ofSigG * 255/ofTotal;
    ofSigB = ofSigB * 255/ofTotal;

    //Set IREF
    Wire.beginTransmission(ADDRESS); // transmit to device
    Wire.write(0x22);        // sends five bytes
    Wire.write(ofSigR);              // sends one byte
    Wire.endTransmission();    // stop transmitting
    Wire.beginTransmission(ADDRESS); // transmit to device
    Wire.write(0x23);        // sends five bytes
    Wire.write(ofSigG);              // sends one byte
    Wire.endTransmission();    // stop transmitting
    Wire.beginTransmission(ADDRESS); // transmit to device
    Wire.write(0x24);        // sends five bytes
    Wire.write(ofSigB);              // sends one byte
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
  }
  
}
