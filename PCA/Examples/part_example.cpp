#include "../include/OFrgba_to_rgbiref.h"
#include "../include/pca.h"
#include "../include/pcaDefinition.h"
#include <time.h>
#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;

vector<vector<char> > OFs;

int main(int argc, char* argv[]){

    PCA pca; // PCA init

    int channel = 0, newChannel = 0;

    OFs.resize(NUM_OF);
    for(int i = 0; i < NUM_OF; i++){
        OFs[i].resize(NUM_AN_OF_NEED_DATA);
        for(int j = 0; j < NUM_AN_OF_NEED_DATA; j++)
            OFs[i][j] = 0;
    }
    OFs[0][0] = 100;
    OFs[0][1] = 100;
    OFs[0][2] = 100;
    OFs[0][3] = 100;
    OFs[0][4] = 100;
    OFs[0][5] = 100;

    char input;
    while(cin >> input){
        
        newChannel = channel-1;
        if(newChannel < 0)newChannel += NUM_OF;
        for(int i = 0; i < NUM_AN_OF_NEED_DATA; i++){
            OFs[newChannel][i] = OFs[channel][i];
            OFs[channel][i] = 0;
        }
        channel = newChannel;
        
        pca.WriteAll(OFs);
    }

}
