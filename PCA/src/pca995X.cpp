#include "../include/pca995X.h"

#include <asm/ioctl.h>
#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>

#include <iostream>

#include "../../../WiringPi/wiringPi/wiringPi.h"
#include "../../../WiringPi/wiringPi/wiringPiI2C.h"

#define I2C_SMBUS_BLOCK_DATA 5  // SMBus-level access
#define I2C_SMBUS 0x0720

using namespace std;

union i2c_smbus_data {
    uint8_t byte;
    uint16_t word;
    uint8_t block[34];
};
struct i2c_smbus_ioctl_data {
    char rw;
    uint8_t cmd;
    int size;
    union i2c_smbus_data *data;
};
PCA995X::PCA995X(int Address, int pca_type) : PCA995X_Address(Address), type(pca_type) {
    fd = wiringPiI2CSetup(PCA995X_Address);
};
int PCA995X::SetPWMAI(int channel, int *PWM, int size) {
    if (!CheckChannelLegal(channel)) return false;

    union i2c_smbus_data regData;

    regData.block[0] = size - 1;
    for (int i = 1; i < size; i++) {
        regData.block[i] = PWM[i];
    }

    struct i2c_smbus_ioctl_data args;
    args.rw = 0;
    args.cmd = channel + PCA995X_PWM0_ADDR + AUTO_INCREMENT;
    args.size = I2C_SMBUS_BLOCK_DATA;
    args.data = &regData;

    return ioctl(fd, I2C_SMBUS, &args) && SetPWM(channel, PWM[0]);
};
int PCA995X::SetIREFAI(int channel, int *IREF, int size) {
    if (!CheckChannelLegal(channel)) return false;

    union i2c_smbus_data regData;

    regData.block[0] = size - 1;
    for (int i = 1; i < size; i++) {
        regData.block[i] = IREF[i];
    }

    struct i2c_smbus_ioctl_data args;
    args.rw = 0;
    args.cmd = channel + PCA995X_IREF0_ADDR + AUTO_INCREMENT;
    args.size = I2C_SMBUS_BLOCK_DATA;
    args.data = &regData;

    return ioctl(fd, I2C_SMBUS, &args) && SetIREF(channel, IREF[0]);
};
int PCA995X::SetPWMIREFAI(int *data) {
    SetPWMAI(0, data, GetChannelNum());
    SetIREFAI(0, &data[GetChannelNum()], GetChannelNum());

    return 0;
};
int PCA995X::SetRGB(int led_address, int Rduty, int Gduty, int Bduty, int Riref, int Giref, int Biref) {
    int *PWM, *IREF;
    PWM = new int[3];
    IREF = new int[3];
    PWM[0] = Rduty;
    PWM[1] = Gduty;
    PWM[2] = Bduty;
    IREF[0] = Riref;
    IREF[1] = Giref;
    IREF[2] = Biref;
    int temp01 = SetPWMAI(led_address * 3 + PCA995X_PWM0_ADDR, PWM, 3);
    int temp02 = SetIREFAI(led_address * 3 + PCA995X_IREF0_ADDR, IREF, 3);
    return temp01 && temp02;
};
void PCA995X::GetAll() {
    for (int i = 0; i < GetChannelNum(); i++) {
        cout << "addr : " << i << ", IREF : " << GetIREF(i) << ", PWM : " << GetPWM(i) << endl;
    }
};
int PCA995X::SetPWM(int channel, int PWM) {
    if (!CheckChannelLegal(channel)) return false;
    PWM = PWM < PWM_MIN ? PWM_MIN : PWM > PWM_MAX ? PWM_MAX
                                                  : PWM;
    return I2CWriteReg(channel + PCA995X_PWM0_ADDR, PWM);
};
int PCA995X::GetPWM(int channel) {
    if (!CheckChannelLegal(channel)) return false;
    return I2CReadReg(channel + PCA995X_PWM0_ADDR);
};
int PCA995X::SetIREF(int channel, int IREF) {
    if (!CheckChannelLegal(channel)) return false;
    IREF = IREF < IREF_MIN ? IREF_MIN : IREF > IREF_MAX ? IREF_MAX
                                                        : IREF;
    return I2CWriteReg(channel + PCA995X_IREF0_ADDR, IREF);
};
int PCA995X::GetIREF(int channel) {
    if (!CheckChannelLegal(channel)) return false;
    return I2CReadReg(channel + PCA995X_IREF0_ADDR);
};
int PCA995X::I2CWriteReg(int reg, int value) {
    return wiringPiI2CWriteReg8(fd, reg, value);
};
int PCA995X::I2CReadReg(int reg) {
    return wiringPiI2CReadReg8(fd, reg);
};
bool PCA995X::CheckChannelLegal(int channel) {
    if (type == 9955) {
        return channel < 0 ? false : channel > PCA9955_CHANNELS ? false
                                                                : true;
    }
    return channel < 0 ? false : channel > PCA9956_CHANNELS ? false
                                                            : true;
};
int PCA995X::GetChannelNum() {
    if (type == 9955) return PCA9955_CHANNELS;
    return PCA9956_CHANNELS;
};
