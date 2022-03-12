#include "../include/pca9956.h"


// Derived PCA9956
bool PCA9956::CheckChannelLegal(int channel) {
    return channel < 0 ? false : channel > PCA9956_CHANNELS ? false
                                                            : true;
};
int PCA9956::GetChannelNum() {
    return PCA9956_CHANNELS;
};
