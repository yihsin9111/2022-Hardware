#include "../include/pca2022.h"
#include "../include/pcaDefinition.h"
#include <time.h>
#include <iostream>
#include <vector>
using namespace std;

vector< vector<unsigned char> > OFs;
vector< unsigned char > OF;

int main(int argc, char* argv[]){
    PCA pca; // PCA init
    clock_t init, clk;
    int level = 200, decay = 1;
    init = clock();
    while(1){
        clk = clock();
	if((clk - init)%(1000/15) == 0){
	    OF.resize(NUM_AN_OF_NEED_DATA);
	    OF[0] = level;
	    OF[1] = 200 - level;
	    OF[2] = level;
	    OF[3] = 100;
	    OF[4] = 80;
	    OF[5] = 90;
	    pca.WriteChannel(OF, 9);
//	    OFs.resize(NUM_OF);
//            for(int i=0;i<NUM_OF;i++){
//		OFs[i].resize(NUM_AN_OF_NEED_DATA);
//                OFs[i][0] = level;
//                OFs[i][1] = 200-level;
//                OFs[i][2] = level;
//                OFs[i][3] = 90;
//                OFs[i][4] = 80;
//                OFs[i][5] = 100;
//            }
// 
//            pca.WriteAll(OFs); // PCA Write
  
            if(level <= 0 || level >= 255) {
                decay -= (decay + decay);
            }
            level -= decay;
	}

    }

}
