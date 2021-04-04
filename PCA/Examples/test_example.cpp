#include "../include/pca2022.h"
#include "../include/rgba_to_rgb.h"
#include <time.h>
#include <iostream>
using namespace std;

int OFs[156] = {
    0, 0, 0, 0, 0, 0, //PWM_RED PWM_GREEN PWM_BLUE IREF_RED IREF_GREEN IREF_BLUE of OF0 
    0, 0, 0, 0, 0, 0, //PWM_RED PWM_GREEN PWM_BLUE IREF_RED IREF_GREEN IREF_BLUE of OF1
    0, 0, 0, 0, 0, 0, //PWM_RED PWM_GREEN PWM_BLUE IREF_RED IREF_GREEN IREF_BLUE of OF2
    0, 0, 0, 0, 0, 0, //PWM_RED PWM_GREEN PWM_BLUE IREF_RED IREF_GREEN IREF_BLUE of OF3
    0, 0, 0, 0, 0, 0, //...
    0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, // 26 OFs in total
};

int main(int argc, char* argv[]){

    int *channelOrder = new int [26];
    for(int i=0;i<26;i++)channelOrder[i] = i;
    
    int **pcaTypeAddr = new int* [4];
    
    pcaTypeAddr[0] = new int[2];
    pcaTypeAddr[0][0] = 9955;
    pcaTypeAddr[0][1] = 0x3f;
    pcaTypeAddr[1] = new int[2];
    pcaTypeAddr[1][0] = 9955;
    pcaTypeAddr[1][1] = 0x2b;
    pcaTypeAddr[2] = new int[2];
    pcaTypeAddr[2][0] = 9956;
    pcaTypeAddr[2][1] = 0x56;
    pcaTypeAddr[3] = new int[2];
    pcaTypeAddr[3][0] = 9956;
    pcaTypeAddr[3][1] = 0x32;

    PCA pca(channelOrder, pcaTypeAddr); // PCA init

    while(1){
        
        //choose one mode
        char Mode;
        cout << "Plz enter the OF mode you want:\n";
        cout << "(A)RGBA (B)RGB_PWM_IREF (Q)Quit\n";
        cin >> Mode;

        if(Mode == 'A' || Mode == 'a'){
            cout << "Choose one led between 0 and 25" << endl;
            cout << "Usage : \n >> <channel> <R> <G> <B> <A>\n";
            cout << "You may enter -1 to quit the current mode\n";
            int channel = 0, R = 0, G = 0, B = 0, A = 0;
            while(1){

                int newChannel = 0;
                cin >> newChannel;

                for(int i = 0; i < 6; i++)
                    OFs[channel*6+i] = 0;
                channel = newChannel;
                if(channel == -1){
                    break;
                }else{
                    cin >> R >> G >> B >> A;
                    float *color = OFrgba_to_rgb(A);
                    OFs[channel*6] = int(color[0]);
                    OFs[channel*6+1] = int(color[1]);
                    OFs[channel*6+2] = int(color[2]);
                    OFs[channel*6+3] = R;
                    OFs[channel*6+4] = G;
                    OFs[channel*6+5] = B;
                    pca.Write(OFs);
		        }

            }

        }else if(Mode == 'B' || Mode == 'b'){
            cout << "Choose one led between 0 and 25" << endl;
            cout << "Usage : \n >> <channel> <R duty> <G duty> <B duty> <R iref> <G iref> <B iref>\n";
            cout << "You may enter -1 to quit the current mode\n";
            int channel = 0, Rduty = 0, Gduty = 0, Bduty = 0, Riref = 0, Giref = 0, Biref = 0;
            while(1){

                int newChannel = 0;
                cin >> newChannel;

                for(int i = 0; i < 6; i++)
                    OFs[channel*6+i] = 0;
                channel = newChannel;
                if(channel == -1){
                    break;
                }else if(channel == -2){
		    
		    break;
		}else{
                    cin >> Rduty >> Gduty >> Bduty >> Riref >> Giref >> Biref ;
                    OFs[channel*6] = Rduty;
                    OFs[channel*6+1] = Gduty;
                    OFs[channel*6+2] = Bduty;
                    OFs[channel*6+3] = Riref;
                    OFs[channel*6+4] = Giref;
                    OFs[channel*6+5] = Biref;
                    pca.Write(OFs);
		        }

            }
        }else if(Mode == 'Q' || Mode == 'q'){
            break;
        }
    }

}
