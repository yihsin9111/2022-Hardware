#include <FastLED.h>
#include <Wire.h>
#include <LiquidCrystal.h> 

#define LED_PIN     4
#define NUM_LEDS    18

CRGB leds[NUM_LEDS];
LiquidCrystal lcd(7,8,9,10,11,12);

int sigR = 0, sigG = 0, sigB = 0;
String str;

void setup() {
  Wire.begin();
  lcd.begin(16,2);
//  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Hello World!");
  
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  
  pinMode(A2,INPUT);
  pinMode(A4,INPUT);
  pinMode(A5,INPUT);
  Serial.begin(9600);
}
void loop() {
    sigR = analogRead(A2)/4;
    sigG = analogRead(A4)/4;
    sigB = analogRead(A5)/4;
//    Serial.println(sigR);
//    Serial.println(sigG);
//    Serial.println(sigB);
    for(int i=0;i<NUM_LEDS;i++){
      leds[i] = CRGB(sigR, sigG, sigB);
      FastLED.show();
    }
    //16*2 LCD
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
    delay(50);
    if(Serial.available()){
      str = Serial.readStringUntil('\n');
      if(str == "LED"){
        Serial.print("R : "+String(sigR)+", G : "+String(sigG)+", B : "+String(sigB));
      }
    }
}
