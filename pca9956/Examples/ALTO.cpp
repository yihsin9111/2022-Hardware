#include <iostream>
#include <unistd.h>
#include "bcm2835.h"
#include "../pca9956.h"
#include "../pca9956_LED.h"

using namespace std;

int main(int argc, char *argv[]){
    PCA9956 pca9956_1(0x3f);
    PCA9956 pca9956_2(0x2b);
    PCA9956 pca9956_3(0x56);
    PCA9956 pca9956_4(0x32);

    pca9956_1.SetAllIREF(100);
    pca9956_2.SetAllIREF(100);
    pca9956_3.SetAllIREF(100);
    pca9956_4.SetAllIREF(100);
    pca9956_1.SetFullOff();
    pca9956_2.SetFullOff();
    pca9956_3.SetFullOff();
    pca9956_4.SetFullOff();

    while(1){
	    pca9956_1.SetFullOff();
	    pca9956_2.SetFullOff();
	    pca9956_3.SetFullOff();
	    pca9956_4.SetFullOff();
	for(int i=0;i<32;i++){
	    if(i>23){
	    	pca9956_4.SetPWM((i-24)*3, 150);
		pca9956_4.SetPWM((i-24)*3+1, 150);
		pca9956_4.SetPWM((i-24)*3+2, 150);
	    }else if(i>15){
		pca9956_3.SetPWM((i-16)*3, 150);
		pca9956_3.SetPWM((i-16)*3+1, 150);
		pca9956_3.SetPWM((i-16)*3+2, 150);
	    }else if(i>8){
		pca9956_2.SetPWM((i-8)*3, 150);
		pca9956_2.SetPWM((i-8)*3+1, 150);
		pca9956_2.SetPWM((i-8)*3+2, 150);
	    }else{
		pca9956_1.SetPWM(i*3, 150);
		pca9956_1.SetPWM(i*3+1, 150);
		pca9956_1.SetPWM(i*3+2, 150);
	    }
	    sleep(0.033);
	}
    }
}
