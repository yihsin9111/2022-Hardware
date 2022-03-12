#include "../include/pca9955.h"

// Derived PCA9955
bool PCA9955::CheckChannelLegal(int channel) {
    return channel < 0 ? false : channel > PCA9955_CHANNELS ? false
                                                            : true;
};
int PCA9955::GetChannelNum() {
    return PCA9955_CHANNELS;
};
