#include "../include/pca2022.h"
#include "../include/pca9955.h"
#include "../include/pca9956.h"

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

int PCA::SetAll(int *data){
    
    return (pca9955[0].SetPWMIREFAI(data) && pca9955[1].SetPWMIREFAI(&data[30]) && pca9956[0].SetPWMIREFAI(&data[60]) && pca9956[1].SetPWMIREFAI(&data[108]));

};