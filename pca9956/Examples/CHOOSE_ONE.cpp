#include <iostream>
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

    cout << "Usage: \n Plz enter led address and RGB\n>> <channel><R><G><B>" ;
    
    while(1){
	int channel=0;
    	while(cin>>channel){
	    int R=0, G=0, B=0;
	    cin >> R >> G >> B;

	    if(channel>23){
	    	channel -= 24;
		pca9956_4.SetPWM(channel*3, R);
		pca9956_4.SetPWM(channel*3+1, G);
		pca9956_4.SetPWM(channel*3+2, B);
	    }else if(channel>15){
	    	channel -= 16;
		pca9956_3.SetPWM(channel*3, R);
		pca9956_3.SetPWM(channel*3+1, G);
		pca9956_3.SetPWM(channel*3+2, B);
	    }else if(channel>7){
	    	channel -= 8;
		pca9956_2.SetPWM(channel*3, R);
		pca9956_2.SetPWM(channel*3+1, G);
		pca9956_2.SetPWM(channel*3+2, B);
	    }else{
	    	pca9956_1.SetPWM(channel*3, R);
		pca9956_2.SetPWM(channel*3+1, G);
		pca9956_3.SetPWM(channel*3+2, B);
	    }
	}
    }

    return 0;
}
