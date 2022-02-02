/**
 * @file pca9685.h
 *
 */
/* Copyright (C) 2022 by Ken Chung
 *
 */

#ifndef PCA9956_H
#define PCA9956_H

#include <cstdint>

#define PCA9956_I2C_ADDRESS_DEFAULT 0X3f
#define PCA9956_IREF_DEFAULT 255
#define PCA9956_PWM_DEFAULT 0

#define ADDRESS(x)    (static_cast<int>(x))
#define CHANNEL(x)    (static_cast<int>(x))
#define REG(x)        (static_cast<int>(x))
#define VALUE(x)      (static_cast<int>(x))

#define PCA9956_IREF_ALL_REG 0x40
#define PCA9956_PWM_ALL_REG 0x3f

#define PCA9956_IREF0_ADDR 0x22
#define PCA9956_PWM0_ADDR 0x0a

#define PCA_PWM_CHANNELS 24

class PCA9956 {
    public:
        PCA9956(int Address = PCA9956_I2C_ADDRESS_DEFAULT);
        ~PCA9956() {};

        void SetAllIREF(int IREF);

        void SetIREF(int channel, int IREF); //channel can only 0 ~ 23
        int GetIREF(int channel);

        void SetPWM(int channel, int PWM); // channel can only 0 ~ 23
        int GetPWM(int channel);

        void SetFullOn();
        void SetFullOff();

    private:
        
        void I2CWriteReg(int reg, int value);
        int I2CReadReg(int reg);

    private:

        int PCA9956_Address;
        int fd;

};

#endif /* PCA9956_H */