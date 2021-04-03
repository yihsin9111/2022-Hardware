#include <iostream>
#include <time.h>
#include "../include/pca9956.h"
#include "../include/pca9955.h"
#include "../include/gamma_correction.h"
using namespace std;

int main(int argc, char* argv[]){
    //number of slaves
    //slave addr sequentially
    int n=3;
    PCA9956 *pca9956 = new PCA9956[n];
    int temp[3]={63,43,86};
    for(int i=0;i<n;i++){
        int temp = 0;
        pca9956[i] = PCA9956(temp);
	if(pca9956[i].Getfd())cout << "Slave Init Success\n";
	else {
	    cout << "Slave Init Failed\n";
	    i--;
	}
    }

        //Reset
        int *IREF = new int [24];
        int *PWM = new int [24];

        for(int i=0;i<24;i++){
            IREF[i] = 0;
            PWM[i] = 0;
        }
        for(int i=0;i<n;i++){
            pca9956[i].SetIREFAI(0, IREF, 24);
            pca9956[i].SetPWMAI(0, PWM, 24);
        }

        //choose one mode
        cout << "Usage : \n >> <channel> <R duty> <G duty> <B duty> <R iref> <G iref> <B iref>\n";
        cout << "You may enter -1 to checkout all register values in PCAs\n";
        int channel = 0, Rduty = 0, Gduty = 0, Bduty = 0, Riref = 0, Giref = 0, Biref = 0;
        while(1){
            
            cin >> channel;
            if(channel == -1){  
                for(int i=0;i<n;i++){
                    pca9956[i].GetAll();
                }
            }else{
                cin >> Rduty >> Gduty >> Bduty >> Riref >> Giref >> Biref ;
                cout << pca9956[channel/8].SetRGB(channel%8, Rduty, Gduty, Bduty, Riref, Giref, Biref) << endl;
                }
            }
}