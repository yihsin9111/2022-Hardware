/**
 * @file pca9685_LED.h
 *
 */
/* Copyright (C) 2022 by NTUEE, Taiwan
 *
 */

#ifndef PCA9956_LED_H
#define PCA9956_LED_H

#define LED_ADDR_MAX 7
#define LED_ADDR_MIN 0

#include "pca9956.h"

struct LED{
    int PWM_R = 0;
    int PWM_G = 0;
    int PWM_B = 0;
    int IREF_R = 0;
    int IREF_G = 0;
    int IREF_B = 0;
};

class PCA9956_LED {
    public:
        PCA9956_LED(PCA9956 pca);
        ~PCA9956_LED() {};

        int SetLED(int LED_ADDR, LED LED_data); // ADDR can only 0 ~ 7

    private:
        PCA9956 pca9956;

};

#endif /*PCA9956_LED_H*/

