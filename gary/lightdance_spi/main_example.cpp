#include <iostream>
#include <time.h>
#include "LED_strip.h"
using namespace std;

double wait = 0.005;
const uint8_t nStrips = 3;
uint16_t *nLeds=new uint16_t[3];

vector<int>* buf;
LED_Strip strips(nStrips, nLeds);
int main(){
	nLeds[0]=1;
	nLeds[1]=1;
	nLeds[2]=5;
	printf("in main");
	int num = 0;
	buf = new vector<int> [nStrips];
	for(int i = 0; i < nStrips; i++){
		buf[i].resize(nLeds[i]*3);
		for(int j = 0; j < nLeds[i] * 3; j++){
			buf[i][j] = 0;
		}
		strips.sendToStrip(i, buf[i]);
	}
	while (1) {
	sleep(1);
	for (int i = 0; i < nStrips; ++i) { for (int j = 0; j < nLeds[i] * 3; ++j) buf[i][j] = 255; strips.sendToStrip(i, buf[i]);}
	sleep(1);
	for (int i = 0; i < nStrips; ++i) { for (int j = 0; j < nLeds[i] * 3; ++j) buf[i][j] = 0; strips.sendToStrip(i, buf[i]);}
	}

}
