#include <iostream> 
#include <time.h> 
#include "../lib/LED_strip.h"
#include "../lib/gamma_correction.h"
using namespace std;

// the number of leds of every strip
// maximum 16 numbers in the vector ( maximum 16 led strips )
// declaration
vector<uint16_t> nLeds;
// rgb data of every single led
vector< vector<char> > buf; 

// initialization
LED_Strip strips;
Color_regulator reg_g(1.8);
Color_regulator reg_r(1.6);
Color_regulator reg_b(1.66);
void breathe_beta(int max, int min,float g,float r,float b, int fps = 30){
    int decay = -1;
    int level = max;
    clock_t init;
    init = clock();
    while(1){
    	while( (1000 * (clock() - init)) / CLOCKS_PER_SEC < 1000/fps);
	    init = clock();
      for(int i = 0; i < nLeds.size(); ++i) {
        for(int j = 0; j < nLeds[i]; ++j){
          if(reg_g.gamma_correction(level*g)<1&&reg_g.gamma_correction(level*g)>0)
            buf[i][3*j  ]=1;
          else
            buf[i][3*j  ] = reg_g.gamma_correction(level*g); // g
          if( reg_r.gamma_correction(level*r)<1&& reg_r.gamma_correction(level*r)>0)
            buf[i][3*j+1] = 1; // r
          else
            buf[i][3*j+1] =reg_r.gamma_correction(level*r);
          if(reg_b.gamma_correction(level*b)<1&&reg_b.gamma_correction(level*b)>0)
            buf[i][3*j+2] = 1; // b
          else
            buf[i][3*j+2]=reg_b.gamma_correction(level*b);
          //if(buf[i][3*j]==0||buf[i][3*j+1]==0||buf[i][3*j+2]==0) to pervent any color become 0
          // if(i==0&&j==0)
          // cout<<"g: "<<level*0.8<<" "<<(int)buf[0][0]<<"  r: "<<level<<" "<<(int)buf[0][1]<<'\n';
	    }
	}
	strips.sendToStrip(buf);
	if(level <= min || level >= max)
	  decay -= (decay + decay);
	  level -= decay;
  }
}
int main(){
    // resize buf to a (number of strips)*(number of leds of the strip)*3 vector
    nLeds={60, 60, 60, 60, 60,60};//change the numbers of lights here
    strips.initialize(nLeds);
	buf.resize(nLeds.size());
	for(int i = 0; i < nLeds.size(); ++i){
		buf[i].resize(nLeds[i] * 3, (char)0);
	}
  breathe_beta(100,0,0.7,0.7,0.7);
}