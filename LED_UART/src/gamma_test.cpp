#include <iostream>
#include <time.h>
#include "../lib/LED_strip.h"
#include "../lib/gamma_correction.h"
using namespace std;

vector<uint16_t> nLeds{100};
vector< vector<char> > buf;
LED_Strip strips(nLeds);

void breathe_test(float gg, float gr, float gb, int max, int min,float g, float r, float b, Color_regulator* regulator, int fps=30){
    //pervious 1.19 1.2 1.1
    int decay = -1;
    int level = max;

    clock_t init;
    init = clock();

    Color_regulator reg_g = regulator[0];
    Color_regulator reg_r = regulator[1];
    Color_regulator reg_b = regulator[2];

    cout << "before while(1)\n";

    while(1){
	init = clock();
    	while( (1000 * (clock() - init)) / CLOCKS_PER_SEC < 1000/fps);
      cout << "after clk\n";
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
          // if(i==0&&j==0)
          // cout<<"g: "<<level*0.8<<" "<<(int)buf[0][0]<<"  r: "<<level<<" "<<(int)buf[0][1]<<'\n';

	    }
	}
        
	cout << "buf set up success\n";

	strips.sendToStrip(buf);
	if(level <= min || level >= max)
	    decay -= (decay + decay);
	level -= decay;
    }
}

int main() {

    Color_regulator *regulator = new Color_regulator[3];

    cout << "Usage : \n>> <gammaR> <gammaG> <gammaB> \n" ;
    for (int i=0;i<3;i++){
	float temp;
	cin >> temp;
        regulator[i] = Color_regulator(temp);
    }
    cout << "set up success\n" ;
//    Color_regulator reg_g(1.8);
//    Color_regulator reg_r(1.6);
//    Color_regulator reg_b(1.66);
    // float gg, gr, gb;
    // int ma, mi;
    // float rg, rr, rb;
    // cin >> gg >> gr >> gb >> ma >> mi >> rg >> rr >> rb;
    // breathe_test(gg, gr, gb, ma, mi, rg, rr, rb);
    breathe_test(1.8, 1.6, 1.66, 200, 0, 0.7, 0.2, 0.1, regulator);
}
