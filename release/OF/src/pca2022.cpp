#include "../include/pca2022.h"
#include "../include/pca9955.h"
#include "../include/pca9956.h"

#include <iostream>
using namespace std;

#define PCA9956_ADDR_01 0x01 // GND GND GND
#define PCA9956_ADDR_02 0x7d // VDD VDD VDD

#define PCA9955_ADDR_01 0X20 
#define PCA9955_ADDR_02 0x40


PCA::PCA(){
    pca9956 = new PCA9956[2];
    pca9955 = new PCA9955[2];
    
    pca9956[0] = PCA9956(PCA9956_ADDR_01); //GND GND GND
    pca9956[1] = PCA9956(PCA9956_ADDR_02); //VDD VDD VDD
    pca9955[0] = PCA9955(PCA9955_ADDR_01);
    pca9955[1] = PCA9955(PCA9955_ADDR_02);
};

int PCA::Write(int *data){
    
    int pcaData[156] = {0};

    //transform the data structure
    for(int i=0;i<5;i++){
        pcaData[i*3] = data[i*6];
        pcaData[i*3+1] = data[i*6+1];
        pcaData[i*3+2] = data[i*6+2];
        pcaData[i*3+15] = data[i*6+3];
        pcaData[i*3+1+15] = data[i*6+4];
        pcaData[i*3+2+15] = data[i*6+5];
    }
    for(int i=5;i<10;i++){
        pcaData[(i-5)*3+30] = data[i*6];
        pcaData[(i-5)*3+1+30] = data[i*6+1];
        pcaData[(i-5)*3+2+30] = data[i*6+2];
        pcaData[(i-5)*3+45] = data[i*6+3];
        pcaData[(i-5)*3+1+45] = data[i*6+4];
        pcaData[(i-5)*3+2+45] = data[i*6+5];
    }
    for(int i=10;i<18;i++){
        pcaData[(i-10)*3+60] = data[i*6];
        pcaData[(i-10)*3+1+60] = data[i*6+1];
        pcaData[(i-10)*3+2+60] = data[i*6+2];
        pcaData[(i-10)*3+84] = data[i*6+3];
        pcaData[(i-10)*3+1+84] = data[i*6+4];
        pcaData[(i-10)*3+2+84] = data[i*6+5];
    }
    for(int i=18;i<26;i++){
        pcaData[(i-18)*3+108] = data[i*6];
        pcaData[(i-18)*3+1+108] = data[i*6+1];
        pcaData[(i-18)*3+2+108] = data[i*6+2];
        pcaData[(i-18)*3+132] = data[i*6+3];
        pcaData[(i-18)*3+1+132] = data[i*6+4];
        pcaData[(i-18)*3+2+132] = data[i*6+5];
    }
    
    pca9955[0].SetPWMIREFAI(pcaData);
    pca9955[1].SetPWMIREFAI(&pcaData[30]);
    pca9956[0].SetPWMIREFAI(&pcaData[60]);
    pca9956[1].SetPWMIREFAI(&pcaData[108]);

    return 0;

};
