#include <iostream>
#include <time.h>
#include "../lib/LED_strip.h"
#include "../lib/gamma_correction.h"

using namespace std;
double wait = 0.005;
// vector<uint16_t> nLeds{18, 69, 3, 8, 0, 0, 0, 0, 19, 11, 8, 9}; // no longer than 16
vector<uint16_t> nLeds{100, 30, 30, 35, 35, 26, 26, 47, 47};
// vector<uint16_t> nLeds{50};

vector< vector<char> > buf;

const uint8_t rainbow[360] = {
  0,   0,   0,   0,   0,   1,   1,   2,
  2,   3,   4,   5,   6,   7,   8,   9,
 11,  12,  13,  15,  17,  18,  20,  22,
 24,  26,  28,  30,  32,  35,  37,  39,
 42,  44,  47,  49,  52,  55,  58,  60,
 63,  66,  69,  72,  75,  78,  81,  85,
 88,  91,  94,  97, 101, 104, 107, 111,
114, 117, 121, 124, 127, 131, 134, 137,
141, 144, 147, 150, 154, 157, 160, 163,
167, 170, 173, 176, 179, 182, 185, 188,
191, 194, 197, 200, 202, 205, 208, 210,
213, 215, 217, 220, 222, 224, 226, 229,
231, 232, 234, 236, 238, 239, 241, 242,
244, 245, 246, 248, 249, 250, 251, 251,
252, 253, 253, 254, 254, 255, 255, 255,
255, 255, 255, 255, 254, 254, 253, 253,
252, 251, 251, 250, 249, 248, 246, 245,
244, 242, 241, 239, 238, 236, 234, 232,
231, 229, 226, 224, 222, 220, 217, 215,
213, 210, 208, 205, 202, 200, 197, 194,
191, 188, 185, 182, 179, 176, 173, 170,
167, 163, 160, 157, 154, 150, 147, 144,
141, 137, 134, 131, 127, 124, 121, 117,
114, 111, 107, 104, 101,  97,  94,  91,
 88,  85,  81,  78,  75,  72,  69,  66,
 63,  60,  58,  55,  52,  49,  47,  44,
 42,  39,  37,  35,  32,  30,  28,  26,
 24,  22,  20,  18,  17,  15,  13,  12,
 11,   9,   8,   7,   6,   5,   4,   3,
  2,   2,   1,   1,   0,   0,   0,   0,
  0,   0,   0,   0,   0,   0,   0,   0,
  0,   0,   0,   0,   0,   0,   0,   0,
  0,   0,   0,   0,   0,   0,   0,   0,
  0,   0,   0,   0,   0,   0,   0,   0,
  0,   0,   0,   0,   0,   0,   0,   0,
  0,   0,   0,   0,   0,   0,   0,   0,
  0,   0,   0,   0,   0,   0,   0,   0,
  0,   0,   0,   0,   0,   0,   0,   0,
  0,   0,   0,   0,   0,   0,   0,   0,
  0,   0,   0,   0,   0,   0,   0,   0,
  0,   0,   0,   0,   0,   0,   0,   0,
  0,   0,   0,   0,   0,   0,   0,   0,
  0,   0,   0,   0,   0,   0,   0,   0,
  0,   0,   0,   0,   0,   0,   0,   0,
  0,   0,   0,   0,   0,   0,   0,   0
};

LED_Strip strips(nLeds);
//pervious 1.19 1.2 1.1
Color_regulator reg_g(1.8);
Color_regulator reg_r(1.6);
Color_regulator reg_b(1.65);

void breathe(int max, int min) {
    int decay = -1;
    int level = max;
    while(true){
	for (int i = 0; i < nLeds.size(); ++i) {
	    for (int j = 0; j < nLeds[i]; ++j){
        buf[i][3*j  ] = reg_r.gamma_correction(level * 0.8); // g 
        buf[i][3*j+1] = reg_g.gamma_correction(level); // r
        buf[i][3*j+2] = 0; // b 
	    }
	}
	strips.sendToStrip(buf);
	usleep(300 * 1000);
    	if(level <= min || level >= max) {
      	    decay -= (decay + decay);
    	}
	level -= decay;
    }
}

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
          if(buf[i][3*j]==0||buf[i][3*j+1]==0||buf[i][3*j+2]==0){
            buf[i][3*j]=0;
            buf[i][3*j+1]=0;
            buf[i][3*j+2]=0;
          }
          if(i==0&&j==0)
          cout<<"g: "<<level*0.8<<" "<<(int)buf[0][0]<<"  r: "<<level<<" "<<(int)buf[0][1]<<'\n';

	    }
	}
	strips.sendToStrip(buf);
	if(level <= min || level >= max)
	    decay -= (decay + decay);
	level -= decay;
    }
}

void test(int a) {
  while(true) {
    if ( a < 0 ) {
      a = 1;
    }
    else if ( a > 255) {
      a = 255;
    }
    for (int i = 0; i < nLeds.size(); ++i) {
      for (int j = 0; j < nLeds[i]; ++j) {
        if (i % 7 == 0) {
          buf[i][3*j  ] = a; // g
          buf[i][3*j+1] = 0; // r
          buf[i][3*j+2] = 0; // b          
        }
        else if (i % 7 == 1) {
          buf[i][3*j  ] = 0; // g
          buf[i][3*j+1] = a; // r
          buf[i][3*j+2] = 0; // b               
        }
        else if (i % 7 == 2) {
          buf[i][3*j  ] = 0; // g
          buf[i][3*j+1] = 0; // r
          buf[i][3*j+2] = a; // b               
        }
        else if (i % 7 == 3) {
          buf[i][3*j  ] = a/2; // g
          buf[i][3*j+1] = a/2; // r
          buf[i][3*j+2] = 0; // b               
        }    
        else if (i % 7 == 4) {
          buf[i][3*j  ] = 0; // g
          buf[i][3*j+1] = a/2; // r
          buf[i][3*j+2] = a/2; // b               
        }    
        else if (i % 7 == 5) {
          buf[i][3*j  ] = a/2; // g
          buf[i][3*j+1] = 0; // r
          buf[i][3*j+2] = a/2; // b               
        }
        else if (i % 7 == 6) {
          buf[i][3*j  ] = a/3; // g
          buf[i][3*j+1] = a/3; // r
          buf[i][3*j+2] = a/3; // b           
        }
      }
    }
    strips.sendToStrip(buf);
		usleep(27 * 1000);
  }
}

void rainbow_shine() {
    int angle = 0;
    while(1){
	for (int i = 0; i < nLeds.size(); ++i) { 
	    for (int j = 0; j < nLeds[i]; ++j){
		    buf[i][3*j  ] = rainbow[(angle + 18*i + j      ) % 360]; // g
		    buf[i][3*j+1] = rainbow[(angle + 18*i + j + 120) % 360]; // r
		    buf[i][3*j+2] = rainbow[(angle + 18*i + j + 240) % 360]; // b
	    }
	}
	++angle;
	angle = angle % 360;
	strips.sendToStrip(buf);
	usleep(30 * 1000);
    }
}

void rainbow_shine_beta(int fps = 30) {
    int angle = 0;
    clock_t init = clock();

    while(1){
	while( (1000 * (clock() - init)) / CLOCKS_PER_SEC < 1000/fps);
	init = clock();

	for (int i = 0; i < nLeds.size(); ++i) { 
	    for (int j = 0; j < nLeds[i]; ++j){
		    buf[i][3*j  ] = rainbow[(angle + 18*i + j      ) % 360]; // g
		    buf[i][3*j+1] = rainbow[(angle + 18*i + j + 120) % 360]; // r
		    buf[i][3*j+2] = rainbow[(angle + 18*i + j + 240) % 360]; // b
	    }
	}
	++angle;
	angle = angle % 360;
	strips.sendToStrip(buf);
    }
}

int main(){
	buf.resize(nLeds.size());
	for(int i = 0; i < nLeds.size(); ++i){
		buf[i].resize(nLeds[i] * 3, (char)0);
	}

  // while(true) {
  //   for (int i = 0; i < nLeds.size(); ++i) { 
	// 		for (int j = 0; j < nLeds[i]; ++j){
  //       if(j > 50) {
  //         buf[i][3*j  ] = 12;
  //         buf[i][3*j+1] = 0;
  //         buf[i][3*j+2] = 0;
  //       }
  //       else {
  //         buf[i][3*j  ] = 100;
  //         buf[i][3*j+1] = 0;
  //         buf[i][3*j+2] = 0;
  //       }
	// 		}
	// 	}
	// 	strips.sendToStrip(buf);
	// 	usleep(300 * 1000);

  // breath, brightness maximum and minimum(0-255) ,g,r,b(0-1)
  breathe_beta(200,0,0.7,0.4,0.3);
  // each strip has its own color, set the brightness(0-255)
  // test(12);
  //rainbow_shine_beta(30); // max 40

}

