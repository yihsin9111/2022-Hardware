#include <iostream>
#include <time.h>
#include "../include/pca9956.h"
#include "../include/pca9955.h"
#include "../include/gamma_correction.h"
using namespace std;

int main(int argc, char* argv[]){
    
    PCA9956 pca9956 = PCA9956(0x56);
	if(pca9956.Getfd())cout << "Slave Init Success\n";
	else {
	    cout << "Slave Init Failed\n";
        return 0;
	}
    

    //Reset
    int *IREF = new int [24];
    int *PWM = new int [24];

    for(int i=0;i<24;i++){
        IREF[i] = 0;
        PWM[i] = 0;
    }
    pca9956.SetIREFAI(0, IREF, 24);
    pca9956.SetPWMAI(0, PWM, 24);
    
    int decay = -1, max = 255, min = 0;
    int level = max;
//    clock_t init, clk;
//    init = clock();

    while(1){

        float gammaR = 0, gammaG = 0, gammaB = 0, ratioR = 0, ratioG = 0, ratioB = 0;
        int frameRate = 0;
        cout << "Usage : \n>> <gamma R> <gamma G> <gamma B> <ratio R> <ratio G> <ratio B> <frame rate(fps)> \n";
        cin >> gammaR >> gammaG >> gammaB >> ratioR >> ratioG >> ratioB >> frameRate;

        Color_regulator regR(gammaR);
        Color_regulator regG(gammaG);
        Color_regulator regB(gammaB);

        int Rduty = 0, Gduty = 0, Bduty = 0;
	
	clock_t init, clk;
	init = clock();

        while(1){
    	     while((1000 * (clock() - init)) / CLOCKS_PER_SEC < 1000/frameRate){
	    //      // cout << (1000 * (clock() - init)) / CLOCKS_PER_SEC << " " << 1000/30 << endl;
	     };
	    // cout << "p" ;
    	     init = clock();
//	        clk = clock();
//    	    if(((clk-init)/CLOCKS_PER_SEC)%(1000/frameRate) == 0){
	
//	        init = clk;	
//              int Rduty = 0, Gduty = 0, Bduty = 0;
                Rduty = regR.gamma_correction(level);
                Gduty = regG.gamma_correction(level);
                Bduty = regB.gamma_correction(level);
 
                pca9956.SetRGB(0, Rduty, Gduty, Bduty, VALUE(255*ratioR), VALUE(255*ratioG), VALUE(255*ratioB));

                if(level <= min || level >= max) {
                    decay -= (decay + decay);
                }
                level -= decay;
//                clk = clock();
//                cout << clk - init << endl;
//            }
	    }
    }
}
