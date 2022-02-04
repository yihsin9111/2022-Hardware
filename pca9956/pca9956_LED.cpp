#include "pca9956_LED.h"

PCA9956_LED::PCA9956_LED(PCA9956 pca):pca9956(pca) {

};

int PCA9956_LED::SetLED(int LED_ADDR, LED LED_data){
    LED_ADDR < LED_ADDR_MIN ? return -1 : LED_ADDR > LED_ADDR_MAX ? return -1 : ;

    pca9956.SetIREF(CHANNEL(LED_ADDR*3), VALUE(LED_data.IREF_R));
    pca9956.SetIREF(CHANNEL(LED_ADDR*3+1), VALUE(LED_data.IREF_G));
    pca9956.SetIREF(CHANNEL(LED_ADDR*3+2), VALUE(LED_data.IREF_B));

    pca9956.SetPWM(CHANNEL(LED_ADDR*3), VALUE(LED_data.PWM_R));
    pca9956.SetPWM(CHANNEL(LED_ADDR*3+1), VALUE(LED_data.PWM_G));
    pca9956.SetPWM(CHANNEL(LED_ADDR*3+2), VALUE(LED_data.PWM_B));

    return 0;
}