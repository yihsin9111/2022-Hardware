#include "../include/OFrgba_to_rgb.h"
#include "../include/pca2022.h"

using namespace std;
// 26(channel) * 6(PWM&iref)
// 備用channel 6個值都填上0
int OFs[156] = {
    255, 255, 255, 80, 70, 55,  // PWM_RED PWM_GREEN PWM_BLUE IREF_RED IREF_GREEN IREF_BLUE of OF0
    255, 255, 255, 80, 70, 55,  // PWM_RED PWM_GREEN PWM_BLUE IREF_RED IREF_GREEN IREF_BLUE of OF1
    255, 255, 255, 70, 70, 55,  // PWM_RED PWM_GREEN PWM_BLUE IREF_RED IREF_GREEN IREF_BLUE of OF2
    255, 255, 255, 70, 70, 55,  // PWM_RED PWM_GREEN PWM_BLUE IREF_RED IREF_GREEN IREF_BLUE of OF3
    255, 255, 255, 70, 55, 50,  //...
    255, 255, 255, 70, 55, 50,
    255, 255, 255, 50, 55, 70,
    255, 255, 255, 50, 55, 70,
    255, 255, 255, 55, 50, 70,
    255, 255, 255, 55, 50, 70,
    255, 255, 255, 70, 50, 55,
    255, 255, 255, 70, 50, 55,
    255, 255, 255, 70, 85, 50,
    255, 255, 255, 70, 85, 50,
    255, 255, 255, 85, 70, 50,
    255, 255, 255, 85, 70, 50,
    255, 255, 255, 70, 50, 85,
    255, 255, 255, 70, 50, 85,
    255, 255, 255, 85, 50, 70,
    255, 255, 255, 85, 50, 70,
    255, 255, 255, 50, 70, 85,
    255, 255, 255, 50, 70, 85,
    255, 255, 255, 50, 85, 70,
    255, 255, 255, 50, 85, 70,
    255, 255, 255, 85, 85, 85,
    255, 255, 255, 85, 85, 85,  // 26 OFs in total
};

int main(int argc, char* argv[]) {
    int* channelOrder = new int[26];
    for (int i = 0; i < 26; i++) channelOrder[i] = i;
    // index 對應 OFs(上面的陣列) 第幾行
    //存的值表示編號多少的光纖(channel)要吃data

    int** pcaTypeAddr = new int*[4];

    pcaTypeAddr[0] = new int[2];
    pcaTypeAddr[0][0] = 9956;
    pcaTypeAddr[0][1] = 0x3f;
    pcaTypeAddr[1] = new int[2];
    pcaTypeAddr[1][0] = 9956;
    pcaTypeAddr[1][1] = 0x2b;
    pcaTypeAddr[2] = new int[2];
    pcaTypeAddr[2][0] = 9956;
    pcaTypeAddr[2][1] = 0x56;
    pcaTypeAddr[3] = new int[2];
    pcaTypeAddr[3][0] = 9956;
    pcaTypeAddr[3][1] = 0x32;

    PCA pca(channelOrder, pcaTypeAddr);  // PCA init

    pca.Write(OFs);  // PCA Write
}