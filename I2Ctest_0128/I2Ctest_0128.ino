// combine from master_writer.ino and ReadASCIIString.ino
#include <Wire.h>
#define ADDRESS 63


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin(); // join i2c bus (address optional for master)
}

byte data[2];
void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available() > 0) {
    data[0] = Serial.parseInt();//data[0]<<=1;
    // -------address----- RW-
    // A6 A5 A4 A3 A2 A1 A0 0
    data[1] = Serial.parseInt();

/*
    Wire.beginTransmission(ADDRESS); // transmit to device #8
    Wire.write(data[0]);        // sends five bytes
    Wire.write(data[1]);              // sends one byte
    Wire.endTransmission();    // stop transmitting
    Serial.print("address=");
    Serial.println(data[0]>>1,HEX);
    Serial.print("reg=");
    Serial.println(data[0],HEX);
    Serial.print("data=");
    Serial.println(data[1],HEX);
    Serial.read();
    Serial.read();
    Serial.read();
*/
  Wire.beginTransmission(ADDRESS); // transmit to device #8
  Wire.write(64);        // sends five bytes
  Wire.write(255);              // sends one byte
  Wire.endTransmission();    // stop transmitting  
  delay(30);
  while(1){
    for(byte i=10;i<34;++i){
      Wire.beginTransmission(ADDRESS); // transmit to device #8
      Wire.write(i);        // sends five bytes
      Wire.write(255);              // sends one byte
      Wire.endTransmission();    // stop transmitting  
      delay(30);
      Wire.beginTransmission(ADDRESS); // transmit to device #8
      Wire.write(i);        // sends five bytes
      Wire.write(0);              // sends one byte
      Wire.endTransmission();    // stop transmitting  
      delay(30);
    }
  }
  }
}
