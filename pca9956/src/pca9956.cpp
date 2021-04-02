#include "../include/pca9956.h"
#include "../../../WiringPi/wiringPi/wiringPiI2C.h"
#include "../../../WiringPi/wiringPi/wiringPi.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <asm/ioctl.h>

enum PCA9956Reg{
    PCA9956_REG_PWMALL = 0x3f,
    PCA9956_REF_IREFALL = 0x40,
};

union i2c_smbus_data {
    uint8_t byte;
    uint16_t word;
    uint8_t block [34];
};

struct i2c_smbus_ioctl_data{
    char rw;
    uint8_t cmd;
    int size;
    union i2c_smbus_data *data;
};

PCA9956::PCA9956(int Address):PCA9956_Address(ADDRESS(Address)){
    fd = wiringPiI2CSetup(PCA9956_Address);
};

int PCA9956::SetPWMAI(int *PWM, int size){

    union i2c_smbus_data regData;

    regData.block[0] = size;
    for(int i=0;i<size;i++){
    	regData.block[i]=PWM[i];
    }

    struct i2c_smbus_ioctl_data args;
    args.rw = 0;
    args.cmd = PCA9956_PWM0_ADDR+128;
    args.size = 5;
    args.data = &regData;

    return ioctl(fd, 0x0720, &args);
};

int PCA9956::SetRGB(int channel, int Rduty, int Gduty, int Bduty, int Riref, int Giref, int Biref){
    return 0;	
}

int PCA9956::SetPWM(int channel, int PWM){
    PWM = PWM < PWM_MIN ? PWM_MIN : PWM > PWM_MAX ? PWM_MAX : PWM ;
    return I2CWriteReg(channel+PCA9956_PWM0_ADDR, PWM);
};
int PCA9956::GetPWM(int channel){
    return I2CReadReg(channel+PCA9956_PWM0_ADDR);
};
int PCA9956::SetIREF(int channel, int IREF){
    IREF = IREF < IREF_MIN ? IREF_MIN : IREF > IREF_MAX ? IREF_MAX : IREF ;
    return I2CWriteReg(channel+PCA9956_IREF0_ADDR, IREF);
};
int PCA9956::GetIREF(int channel){
    return I2CReadReg(channel+PCA9956_IREF0_ADDR);
};


int PCA9956::I2CWriteReg(int reg, int value){
    return wiringPiI2CWriteReg8(fd, reg, value);
};

int PCA9956::I2CReadReg(int reg){
    return wiringPiI2CReadReg8(fd, reg);
}

