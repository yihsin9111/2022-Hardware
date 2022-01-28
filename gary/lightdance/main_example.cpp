#include <iostream>
#include <time.h>
#include "LED_strip.h"
#define NSTRIPS 13
using namespace std;

double wait = 0.005;
const uint8_t nStrips = NSTRIPS;
uint16_t nLeds[NSTRIPS]={87,87,87,87,87,87,87,87,87,87,87,87,87};

vector<char>* buf;


LED_Strip strips(nStrips, nLeds);
int main(){
	
	printf("in main");
	int num = 0;
	buf = new vector<char> [nStrips];
	for(int i = 0; i < nStrips; i++){
		buf[i].resize(nLeds[i]*3);
		for(int j = 0; j < nLeds[i] * 3; j++){
			buf[i][j] = (char)0;
		}
	}
	// int runcount[6]={0};
	// while (1) {
	// 	if(runcount[0]>nLeds[0]){
	// 			runcount[0]=0;
	// 			cout<<"a"<<endl;
	// 	}
	// 	if(runcount[1]>nLeds[1]){
	// 		runcount[1]=0;
	// 		cout<<"b"<<endl;
	// 	}
				
	// 	if(runcount[2]>nLeds[2]){
	// 		runcount[2]=0;
	// 		cout<<"c"<<endl;
	// 	}
	// 	if(runcount[3]>nLeds[3]){
	// 		runcount[3]=0;
	// 		cout<<"d"<<endl;
	// 	}
	// 	if(runcount[4]>nLeds[4]){
	// 		runcount[4]=0;
	// 		cout<<"e"<<endl;
	// 	}
	// 	if(runcount[5]>nLeds[5]){
	// 		runcount[5]=0;
	// 		cout<<"f"<<endl;
	// 	}

	// 	usleep(40*1000);
	// 	for (int i = 0; i < nStrips; ++i) { 
	// 		for (int j = 0; j < nLeds[i] * 3; ++j){
	// 			if(j/3==runcount[i]){
	// 				buf[i][j]=255;
	// 			}
	// 			else
	// 				buf[i][j]=0;
	// 		}
	// 		strips.sendToStrip(i, buf[i]);
	// 		usleep(10*1000);
	// 	}

	// 	for (int i=0;i<6;i++){
	// 		runcount[i]++;
	// 	}
	// }
	while(1){
		for (int i = 0; i < nStrips; ++i) { 
			for (int j = 0; j < nLeds[i] * 3; ++j)
					buf[i][j]=(char)100;
			strips.sendToStrip(i, buf[i]);
			usleep(10*1000);
		}
		usleep(50*1000);
		for (int i = 0; i < nStrips; ++i) { 
			for (int j = 0; j < nLeds[i] * 3; ++j)
					buf[i][j]=(char)0;
			strips.sendToStrip(i, buf[i]);
			usleep(10*1000);
		}
		usleep(50*1000);
	}
	
}
