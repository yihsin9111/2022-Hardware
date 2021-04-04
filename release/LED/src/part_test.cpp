#include <iostream> 
#include <time.h> 
#include "../lib/LED_strip.h"
#define fps 30
using namespace std;

// the number of leds of every strip
// maximum 16 numbers in the vector ( maximum 16 led strips )
// declaration
vector<uint16_t> nLeds;
// rgb data of every single led
vector< vector<char> > buf; 

// initialization
LED_Strip strips;

int main() {
    // resize buf to a (number of strips)*(number of leds of the strip)*3 vector
    nLeds={60,60,60,60,60,60,60,60,60,60,60,60};//change the numbers of lights here
    strips.initialize(nLeds);
	buf.resize(nLeds.size());
	for(int i = 0; i < nLeds.size(); ++i){
		buf[i].resize(nLeds[i] * 3, (char)0);
	}
  for (int c=0;c<nLeds.size();++c){
    cout<<c<<endl;
    for (int i = 0; i < nLeds.size(); ++i) { 
      for (int j = 0; j < nLeds[i]; ++j){
        if(i==c){
          buf[i][3*j  ] = 50; // g
          buf[i][3*j+1] = 50; // r
          buf[i][3*j+2] = 50; // b
        }
        else{
          buf[i][3*j  ] = 0; // g
          buf[i][3*j+1] = 0; // r
          buf[i][3*j+2] = 0; // b
        }
      }
	  }
    strips.sendToStrip(buf);
    usleep(1000*1000);
  }
}
