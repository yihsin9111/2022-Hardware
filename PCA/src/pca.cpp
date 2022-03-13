#include "pca.h"

#include <iostream>
#include <vector>

#include "pcaDefinition.h"

// PCA(OF) I2C address
#define PCA_ADDR_1 0x20
#define PCA_ADDR_2 0x22
#define PCA_ADDR_3 0x3f
#define PCA_ADDR_4 0x23

using namespace std;

enum {
    CHANNEL_SIZE_ERROR = 1,  // if the length of data sent to PCA::WriteAll is not equal to 26, return this error
    DATA_SIZE_ERROR = 2,     // if the length of data for an OF channel is not equal to 6, return this error
};

// pca type and addr for pca initialize in pca.cpp
// an (NUM_PCA * 2) 2D array of int type
// each row of the array refer to one pca
// On each row, the first element means the type of pca,
// where value equals to 9955 refering to PCA9955B and that of 9956 refering to PCA9956
// the second element means the I2C address of pca, which will be value between 0 ~ 127
const int pcaTypeAddr[NUM_PCA][2] = {
    {_PCA9955B, PCA_ADDR_1},
    {_PCA9956, PCA_ADDR_2},
    {_PCA9955B, PCA_ADDR_3},
    {_PCA9956, PCA_ADDR_4}};

PCA::PCA() {
    PCAs.resize(NUM_PCA);

    for (int i = 0; i < NUM_PCA; i++)
        PCAs[i] = PCA995X(pcaTypeAddr[i][1], pcaTypeAddr[i][0]);
};

int PCA::WriteAll(std::vector<std::vector<char>> &data) {
    // check for length of data, it needs NUM_OF(26, in pcaDefinition.h) channels for OFs
    if (data.size() != NUM_OF)
        return CHANNEL_SIZE_ERROR;

    int leds = 0;

    // use while loop to go through all PCAs
    for (int i = 0; i < PCAs.size(); i++) {
        int pcaData[PCAs[i].GetLedChannelNum() * NUM_AN_OF_NEED_DATA] = {0};
        for (int j = 0; j < PCAs[i].GetLedChannelNum(); j++) {
            // check for length of each channel data, it needs NUM_AN_OF_NEED_DATA(6, in pcaDefinition.h) datas for an OF
            if (data[j + leds].size() != NUM_AN_OF_NEED_DATA)
                return DATA_SIZE_ERROR;
            // data from software would be 26 channels * 6 datas per channel
            // however, data form need to send to an PCA would be :
            // NUM_CHANNEL_FROM_PCA9955B(5, in pcaDefinition.h) * 3 pwm datas per channel
            // and followed by
            // NUM_CHANNEL_FROM_PCA9955B(5, in pcaDefinition.h) * 3 iref datas per channel
            // Therefore, we need to transform data form right here
            //
            // { {led01PwmR, led01PwmG, led01PwmB, led01IrefR, led01IrefG, led01IrefB},          {led01PwmR, led01PwmG, led01PwmB, led02PwmR, led02PwmG, led02PwmB,
            //   {led02PwmR, led02PwmG, led02PwmB, led02IrefR, led02IrefG, led02IrefB},       \   led03PwmR, led03PwmG, led03PwmB, led04PwmR, led04PwmG, led04PwmB,
            //   {led03PwmR, led03PwmG, led03PwmB, led03IrefR, led03IrefG, led03IrefB},    --- \  led05PwmR, led05PwmG, led05PwmB, led06PwmR, led06PwmG, led06PwmB, ...
            //   {led04PwmR, led04PwmG, led04PwmB, led04IrefR, led04IrefG, led04IrefB},    --- /  led01IrefR, led01IrefG, led01IrefB, led02IrefR, led02IrefG, led02IrefB,
            //   {led05PwmR, led05PwmG, led05PwmB, led05IrefR, led05IrefG, led05IrefB},       /   led03IrefR, led03IrefG, led03IrefB, led04IrefR, led04IrefG, led04IrefB,
            //   {led06PwmR, led06PwmG, led06PwmB, led06IrefR, led06IrefG, led06IrefB}, }         led05IrefR, led05IrefG, led05IrefB, led06IrefR, led06IrefG, led06IrefB, ... }
            for(int k = 0; k < NUM_AN_OF_NEED_PWM; k++ )
                pcaData[j * NUM_AN_OF_NEED_PWM] = data[(j + leds)][k];    
            for(int k = 0; k < NUM_AN_OF_NEED_IREF; k++)
                pcaData[j * NUM_AN_OF_NEED_IREF + PCAs[i].GetLedChannelNum() * NUM_AN_OF_NEED_PWM] = data[(j + leds)][k+NUM_AN_OF_NEED_PWM];
        }
        leds += PCAs[i].GetLedChannelNum();
        PCAs[i].SetPWMIREFAI(pcaData);
    }

    return 0;
};

int PCA::WriteChannel(std::vector<char> &data, int channel) {
    // check for length of each channel data, it needs NUM_AN_OF_NEED_DATA(6, in pcaDefinition.h) datas for an OF
    if (data.size() != NUM_AN_OF_NEED_DATA)
        return DATA_SIZE_ERROR;

    for (int i = 0; i < PCAs.size(); i++) {
        if (channel > PCAs[i].GetLedChannelNum())
            channel -= PCAs[i].GetLedChannelNum();
        else
            return PCAs[i].SetRGB(channel, data[0], data[1], data[2], data[3], data[4], data[5]);
    }
    return 0;
};

void PCA::Read() {
    for (int i = 0; i < PCAs.size(); i++) {
        PCAs[i].GetAll();
    }
};
