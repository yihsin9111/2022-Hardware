#include "../include/pca2022.h"
#include <time.h>

int OFs[156] = {
    255, 255, 255, 80, 120, 55, //PWM_RED PWM_GREEN PWM_BLUE IREF_RED IREF_GREEN IREF_BLUE of OF0 
    255, 255, 255, 80, 120, 55, //PWM_RED PWM_GREEN PWM_BLUE IREF_RED IREF_GREEN IREF_BLUE of OF1
    255, 255, 255, 100, 100, 55, //PWM_RED PWM_GREEN PWM_BLUE IREF_RED IREF_GREEN IREF_BLUE of OF2
    255, 255, 255, 100, 100, 55, //PWM_RED PWM_GREEN PWM_BLUE IREF_RED IREF_GREEN IREF_BLUE of OF3
    255, 255, 255, 200, 55, 0, //...
    255, 255, 255, 200, 55, 0, 
    255, 255, 255, 0, 55, 200, 
    255, 255, 255, 0, 55, 200, 
    255, 255, 255, 55, 0, 200, 
    255, 255, 255, 55, 0, 200, 
    255, 255, 255, 200, 0, 55, 
    255, 255, 255, 200, 0, 55, 
    255, 255, 255, 170, 85, 0, 
    255, 255, 255, 170, 85, 0, 
    255, 255, 255, 85, 170, 0, 
    255, 255, 255, 85, 170, 0, 
    255, 255, 255, 170, 0, 85,
    255, 255, 255, 170, 0, 85, 
    255, 255, 255, 85, 0, 170,
    255, 255, 255, 85, 0, 170,
    255, 255, 255, 0, 170, 85,
    255, 255, 255, 0, 170, 85,
    255, 255, 255, 0, 85, 170,
    255, 255, 255, 0, 85, 170,
    255, 255, 255, 85, 85, 85, 
    255, 255, 255, 85, 85, 85, // 26 OFs in total
};

int main(int argc, char* argv[]){
    
    PCA pca; // PCA init

    clock_t init, clk;
    int level = 255, decay = 1;
	init = clock();

    while(1){
        while((1000 * (clock() - init)) / CLOCKS_PER_SEC < 1000/30);
        init = clock();
        
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