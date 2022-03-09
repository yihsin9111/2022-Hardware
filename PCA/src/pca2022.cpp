#include "../include/pca2022.h"
#include "../include/pca9955.h"
#include "../include/pca9956.h"

#include <iostream>
using namespace std;

PCA::PCA(int *channelOrder, int **pcaTypeAddr):channelOrder(channelOrder){

    for(int i = 0; i < 4; i++)
        if(pcaTypeAddr[i][0] == 9955)
            PCAs.Add(pcaTypeAddr[i][1], false);
        else PCAs.Add(pcaTypeAddr[i][1], true);

};

int PCA::Write(int *data){

    for(int i = 0; i < 26; i++){
        if(channelOrder[i] != i){
            data[channelOrder[i]*6] = data[i*6];
            data[channelOrder[i]*6+1] = data[i*6+1];
            data[channelOrder[i]*6+2] = data[i*6+2];
            data[channelOrder[i]*6+3] = data[i*6+3];
            data[channelOrder[i]*6+4] = data[i*6+4];
            data[channelOrder[i]*6+5] = data[i*6+5];
        }
    }

    int leds = 0;
    PCAnode *current = PCAs.first;
    while(current != nullptr){
        
        if(current->pca9955 != nullptr){
            int pcaData[30] = {0};
            for(int i=0;i<5;i++){
                pcaData[i*3] = data[(i+leds)*6];
                pcaData[i*3+1] = data[(i+leds)*6+1];
                pcaData[i*3+2] = data[(i+leds)*6+2];
                pcaData[i*3+15] = data[(i+leds)*6+3];
                pcaData[i*3+1+15] = data[(i+leds)*6+4];
                pcaData[i*3+2+15] = data[(i+leds)*6+5];
            }
            leds += 5;
            current->pca9955[0].SetPWMIREFAI(pcaData);
        }else{
            int pcaData[48] = {0};
            for(int i=0;i<8;i++){
                pcaData[i*3] = data[(i+leds)*6];
                pcaData[i*3+1] = data[(i+leds)*6+1];
                pcaData[i*3+2] = data[(i+leds)*6+2];
                pcaData[i*3+24] = data[(i+leds)*6+3];
                pcaData[i*3+1+24] = data[(i+leds)*6+4];
                pcaData[i*3+2+24] = data[(i+leds)*6+5];
            }
            leds += 8;
            current->pca9956[0].SetPWMIREFAI(pcaData);
        }
        current = current->nxt;
    }

    return 0;

};

void PCA::Read(){
    PCAnode *current = PCAs.first;
    while(current != nullptr){
        
        if(current->pca9955 != nullptr){
            current->pca9955[0].GetAll();
        }else{
            current->pca9956[0].GetAll();
        }
        current = current->nxt;
    }
};

void PCA::Debug(){
    PCAnode *current = PCAs.first;
    while(current != nullptr){
    	if(current->pca9955 != nullptr){
	   cout << "9955" << endl;
	}else{
	   cout << "9956" << endl;
	}
	current = current->nxt;
    }
};

PCAnode::PCAnode(){
    pca9956 = nullptr;
    pca9955 = nullptr;
    nxt = nullptr;
};

PCAnode::PCAnode(int PCA_ADDR, bool IsPCA9956){
    
    if(IsPCA9956 == true){
        pca9955 = nullptr;
        pca9956 = new PCA9956[1];
        pca9956[0] = PCA9956(PCA_ADDR);
    }else{
        pca9956 = nullptr;
        pca9955 = new PCA9955[1];
        pca9955[0] = PCA9955(PCA_ADDR);
    }
    
    nxt = nullptr;
};

void LinkedList::Add(int PCA_ADDR, bool IsPCA9956){

    PCAnode *newNode = new PCAnode(PCA_ADDR, IsPCA9956);

    if(first == nullptr){
        first = newNode;
        return;
    }

    PCAnode *current = first;
    while(current->nxt != nullptr){
        current = current->nxt;
    }
    current->nxt = newNode;

}
