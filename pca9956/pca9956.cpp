#include "pca9956.h"
#include "wiringPiI2C.h"

PCA9956::PCA9956(int Address):PCA9956_Address(ADDRESS(Address)){
    fd = wiringPiI2CSetup(PCA9956_Address);
    I2CWriteReg(PCA9956_IREF_ALL_REG, PCA9956_IREF_DEFAULT);
    I2CWriteReg(PCA9956_PWM_ALL_REG, PCA9956_PWM_DEFAULT);
};

void PCA9956::SetAllIREF(int IREF){
    IREF = IREF < IREF_MIN ? IREF_MIN : IREF > IREF_MAX ? IREF_MAX : IREF ;
    I2CWriteReg(PCA9956_IREF_ALL_REG, VALUE(IREF));
};

void PCA9956::SetIREF(int channel, int IREF){
    IREF = IREF < IREF_MIN ? IREF_MIN : IREF > IREF_MAX ? IREF_MAX : IREF ;
    I2CWriteReg(REG(channel+PCA9956_IREF0_ADDR), VALUE(IREF));
};
int PCA9956::GetIREF(int channel){
    return I2CReadReg(REG(channel+PCA9956_IREF0_ADDR));
};

void PCA9956::SetPWM(int channel, int PWM){
    PWM = PWM < PWM_MIN ? PWM_MIN : PWM > PWM_MAX ? PWM_MAX : PWM ;
    I2CWriteReg(REG(channel+PCA9956_PWM0_ADDR), VALUE(PWM));
};
int PCA9956::GetPWM(int channel){
    return I2CReadReg(REG(channel+PCA9956_PWM0_ADDR));
};

void PCA9956::SetFullOn(){
    I2CWriteReg(PCA9956_PWM_ALL_REG, PWM_MAX);
};
void PCA9956::SetFullOff(){
    I2CWriteReg(PCA9956_PWM_ALL_REG, 0);
};

void PCA9956::I2CWriteReg(int reg, int value){
    wiringPiI2CWriteReg8(fd, reg, value);
};

int PCA9956::I2CReadReg(int reg){
    return wiringPiI2CReadReg8(fd, reg);
}
