#include "../include/OFrgba_to_rgbiref.h"
#include "../include/pca.h"
#include "../include/pcaDefinition.h"
#include <time.h>
#include <iostream>
#include <vector>
using namespace std;

vector<vector<char> > OFs;

int main(int argc, char* argv[]){

    PCA pca; // PCA init
    
    OFs.resize(NUM_OF);
    for(int i = 0; i < NUM_OF; i++){
        OFs[i].resize(NUM_AN_OF_NEED_DATA);
        for(int j = 0; j < 3; j++)
            OFs[i][j] = 0;
	for(int j = 3; j < 6; j++)
	    OFs[i][j] = 0;
    }

    pca.WriteAll(OFs);
    

}
