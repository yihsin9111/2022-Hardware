#include "../include/pca2022.h"
#include <time.h>
#include <iostream>
using namespace std;

int OFs[156] = {
    255, 255, 255, 80, 120, 55, //PWM_RED PWM_GREEN PWM_BLUE IREF_RED IREF_GREEN IREF_BLUE of OF0 
    255, 255, 255, 80, 120, 55, //PWM_RED PWM_GREEN PWM_BLUE IREF_RED IREF_GREEN IREF_BLUE of OF1
    255, 255, 255, 100, 100, 55, //PWM_RED PWM_GREEN PWM_BLUE IREF_RED IREF_GREEN IREF_BLUE of OF2
    255, 255, 255, 100, 100, 55, //PWM_RED PWM_GREEN PWM_BLUE IREF_RED IREF_GREEN IREF_BLUE of OF3
    255, 255, 255, 150, 55, 50, //...
    255, 255, 255, 150, 55, 50, 
    255, 255, 255, 50, 55, 150, 
    255, 255, 255, 50, 55, 150, 
    255, 255, 255, 55, 50, 150, 
    255, 255, 255, 55, 50, 150, 
    255, 255, 255, 150, 50, 55, 
    255, 255, 255, 150, 50, 55, 
    255, 255, 255, 120, 85, 50, 
    255, 255, 255, 120, 85, 50, 
    255, 255, 255, 85, 120, 50, 
    255, 255, 255, 85, 120, 50, 
    255, 255, 255, 120, 50, 85,
    255, 255, 255, 120, 50, 85, 
    255, 255, 255, 85, 50, 120,
    255, 255, 255, 85, 50, 120,
    255, 255, 255, 50, 120, 85,
    255, 255, 255, 50, 120, 85,
    255, 255, 255, 50, 85, 120,
    255, 255, 255, 50, 85, 120,
    255, 255, 255, 85, 85, 85, 
    255, 255, 255, 85, 85, 85, // 26 OFs in total
};

int main(int argc, char* argv[]){

    int *channelOrder = new int [26];
    for(int i=0;i<26;i++)channelOrder[i] = i+1;
    
    int **pcaTypeAddr = new int* [4];
    
    pcaTypeAddr[0] = new int[2];
    pcaTypeAddr[0][0] = 9955;
    pcaTypeAddr[0][1] = 0x3f;
    pcaTypeAddr[1] = new int[2];
    pcaTypeAddr[1][0] = 9955;
    pcaTypeAddr[1][1] = 0x2b;
    pcaTypeAddr[2] = new int[2];
    pcaTypeAddr[2][0] = 9956;
    pcaTypeAddr[2][1] = 0x56;
    pcaTypeAddr[3] = new int[2];
    pcaTypeAddr[3][0] = 9956;
    pcaTypeAddr[3][1] = 0x32;

    PCA pca(channelOrder, pcaTypeAddr); // PCA init

    clock_t init, clk;
    int level = 200, decay = 1;
    init = clock();

    while(1){
        clk = clock();
	if((clk - init)%(1000/30) == 0){

            for(int i=0;i<26;i++){
                OFs[i*6]   = level;
                OFs[i*6+1] = level;
                OFs[i*6+2] = level;
            }
 
            pca.Write(OFs); // PCA Write
  
            if(level <= 0 || level >= 255) {
                decay -= (decay + decay);
            }
            level -= decay;
	}

    }

}
