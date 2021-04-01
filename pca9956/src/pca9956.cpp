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

PCA9956::PCA9956(int Address):PCA9956_Address(ADDRESS(Address)){
    fd = wiringPiI2CSetup(PCA9956_Address);
};

int PCA9956::SetPWMAI(int channel, int *PWM, int size){

   return wiringPiI2CWriteAI(fd, channel, PWM, size);
};
