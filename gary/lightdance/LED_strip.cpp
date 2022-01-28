/****************************************************************************
  FileName     [ LED_strip.cpp ]
  PackageName  [ clientApp ]
  Synopsis     [ LED strip control ]
  Author       [  ]
  Copyright    [ Copyleft(c) , NTUEE, Taiwan ]
****************************************************************************/
#include "LED_strip.h"
#include <time.h>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <errno.h>
//#include "definition.h"

/*from definition.h*/
#define LED_BRIGHTNESS_SCALE 0.8
#define LEDS_0 10
#define LEDS_1 96
#define LEDS_2 42
#define LEDS {LEDS_0, LEDS_1, LEDS_2}
/**/
using namespace std;
/*
  @brief constructor of LED strip, initialize SPI communication.
  @param nStrips number of LED strips
  @param nLEDs number of LEDs in each strip
*/
LED_Strip::LED_Strip(const uint8_t &nStrips, const uint16_t *nLEDs) : _nStrips(nStrips)
{
	// uart
	if ((serial_port = serialOpen ("/dev/ttyS0", 1000000)) < 0)	/* open serial port */
  {
    fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
		exit(-1);
	}
  if (wiringPiSetup () == -1)					/* initializes wiringPi setup */
  {
    fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno)) ;
		exit(-1);
  }

	_nLEDs = new uint16_t[nStrips];
	uint16_t m=0;
	for (uint8_t i = 0; i < nStrips; ++i){
		_nLEDs[i] = nLEDs[i];
		if (nLEDs[i]*3>m){
			m=nLEDs[i]*3;
			cout<<m<<endl;
		}
		MAX=m;
	}
}

LED_Strip::~LED_Strip()
{
  delete _nLEDs;
}

/*!
  @brief Send pixel secquence to LED strip via SPI.
  @param id Destination strip ID
  @param color pixel secquence to send

  @note strip ID from 0 to nStrips - 1
*/
void LED_Strip::send (const uint8_t &id, std::vector<char>& color){
	char buf[MAX] = {0};
	getSeq(buf,color);
	serialPutchar(serial_port,(char)255);
	serialPutchar(serial_port,(char)id);
	for(int i=0;i<MAX;i++)serialPutchar(serial_port,(char)buf[i]);
	for (int a = 0; a < color.size(); a++) std::cout << (unsigned short)buf[a] << " ";
		std::cout << std::endl;
}

void LED_Strip::sendToStrip(const uint8_t &id, std::vector<char>& color)
{
	send(id,color);
}


/*!
  @brief 	   Convert pixel secquence to special dataframe for SPI communication.
  @param id    Destination strip ID
  @param len   Data length of pixel secquence
  @param seq   Pixel secquence to send
  @param color Output dataframe
*/
void LED_Strip::getSeq(char *seq, std:: vector<char>& color)
{
	for (int i = 0 ; i < color.size(); ++i)
	{
		seq[i + DATA_OFFSET] = color[i]*LED_BRIGHTNESS_SCALE ;
	}

}
