/**
 * @file pca9685_LED.h
 *
 */
/* Copyright (C) 2022 by Ken Chung
 *
 */

#ifndef PCA9956_LED_H
#define PCA9956_LED_H

#include "pca9956.h"

struct LED{
    int PWM_R;
    int PWM_G;
    int PWM_B;
    int IREF_R;
    int IREF_G;
    int IREF_B;
};

class PCA9956_LED {
    public:
        PCA9956_LED(PCA9956 pca);
        ~PCA9956_LED() {};

        void SetLED(int LED_ADDR, LED LED_data); // ADDR can only 0 ~ 7

    private:
        PCA9956 pca9956;

};

#endif /*PCA9956_LED_H*/

