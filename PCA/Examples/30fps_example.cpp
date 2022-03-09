#include "../include/pca2022.h"
#include <time.h>
#include <iostream>
#include <vector>
using namespace std;

vector< vector<unsigned char> > OFs;

int main(int argc, char* argv[]){

    PCA pca; // PCA init

    clock_t init, clk;
    int level = 200, decay = 1;
    init = clock();

    while(1){
        clk = clock();
	if((clk - init)%(1000/15) == 0){

            for(int i=0;i<26;i++){
                OFs[i][0] = level;
                OFs[i][1] = level;
                OFs[i][2] = level;
                OFs[i][3] = 0;
                OFs[i][4] = 0;
                OFs[i][5] = 100;
            }
 
            pca.Write(OFs); // PCA Write
  
            if(level <= 0 || level >= 255) {
                decay -= (decay + decay);
            }
            level -= decay;
	}

    }

}
