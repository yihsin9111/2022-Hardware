#include "pca9956_LED.h"
#include <iostream>

using namespace std;

PCA9956_LED::PCA9956_LED(PCA9956 pca):pca9956(pca) {

};

int PCA9956_LED::SetLED(int LED_ADDR, LED LED_data){
    if(LED_ADDR < LED_ADDR_MIN) return -1;
    if(LED_ADDR > LED_ADDR_MAX) return -1;
    
  //  cout << "LED_ADDR : " << LED_ADDR << ", LED data : R ->" << LED_data.IREF_R << "," << LED_data.PWM_R << ", G ->" << LED_data.IREF_G << "," << LED_data.PWM_G << ", B ->" << LED_data.IREF_B << "," << LED_data.PWM_B << endl;

    pca9956.SetIREF(CHANNEL(LED_ADDR*3), VALUE(LED_data.IREF_R));
    pca9956.SetIREF(CHANNEL(LED_ADDR*3+1), VALUE(LED_data.IREF_G));
    pca9956.SetIREF(CHANNEL(LED_ADDR*3+2), VALUE(LED_data.IREF_B));

    pca9956.SetPWM(CHANNEL(LED_ADDR*3), VALUE(LED_data.PWM_R));
    pca9956.SetPWM(CHANNEL(LED_ADDR*3+1), VALUE(LED_data.PWM_G));
    pca9956.SetPWM(CHANNEL(LED_ADDR*3+2), VALUE(LED_data.PWM_B));

    return 0;
};
