#include <iostream>
#include <time.h>
#include "../include/pca9956.h"
#include "../include/pca9955.h"

using namespace std;

int main(int argc, char* argv[]){

    //number of slaves
    int n = 0, m = 0;
    cout << "Usage :\nPlz enter the number of your PCA9956 slaves and that of your PCA9955 slaves respectively:\n";
    cin >> n >> m;

    //slave addr sequentially
    PCA9956 *pca9956 = new PCA9956[n];
    PCA9955 *pca9955 = new PCA9955[m];
    if(n>0)cout << "Plz enter the addresses of your PCA9956 slaves in decimal sequentially :\n" ;
    for(int i=0;i<n;i++){
        int temp = 0;
        cin >> temp;
        pca9956[i] = PCA9956(temp);
    }
    if(m>0)cout << "Plz enter the addresses of your PCA9955 slaves in decimal sequentially :\n" ;
    for(int i=0;i<m;i++){
        int temp = 0;
        cin >> temp;
        pca9955[i] = PCA9955(temp);
    }

    while(1){

        //Reset
        int *IREF = new int [24];
        int *PWM = new int [24];

        for(int i=0;i<24;i++){
            IREF[i] = 0;
            PWM[i] = 0;
        }
        for(int i=0;i<n;i++){
            pca9956[i].SetIREFAI(0, IREF, 24);
            pca9956[i].SetPWMAI(0, PWM, 24);
            pca9956[i].GetAll();
        }
        for(int i=0;i<m;i++){
            pca9955[i].SetIREFAI(0, IREF, 24);
            pca9955[i].SetPWMAI(0, PWM, 24);
        }

        //choose one mode
        char Mode;
        cout << "Plz enter the OF mode you want :\n";
        cout << "(B)Breath (C)ChooseOne (Q)Quit :\n";
        cin >> Mode;

        if(Mode == 'B' || Mode == 'b'){
            clock_t init, clk;
            bool increase = true;
            init = clock();
            int bright = 0;
            int *IREF = new int [24];
            int *PWM = new int [24];

            while(1){
                clk = clock();
                if((clk-init)%(1000/30) == 0){
                    if(increase == true){
                        bright+=1;
                        if(bright == 30){
                            increase = false;
                        }
                    }
                    else if(increase == false){
                        bright-=1;
                        if(bright == 0){
                            increase = true;
                        }
                    }

                    for(int i=0;i<24;i++){
                        IREF[i] = 255*bright/30;
                        PWM[i] = 50;
                    }
                    for(int i=0;i<n;i++){
                        pca9956[i].SetIREFAI(0, IREF, 24);
                        pca9956[i].SetPWMAI(0, PWM, 24);
                    }
                    for(int i=0;i<m;i++){
                        pca9955[i].SetIREFAI(0, IREF, 24);
                        pca9955[i].SetPWMAI(0, PWM, 24);
                    }

                }
            }
        }else if(Mode == 'C' || Mode == 'c'){
            cout << "Choose one led between 0 and " << (n+m)*8-1 << endl;
            cout << "Usage : \n >> <channel> <R duty> <G duty> <B duty> <R iref> <G iref> <B iref>\n";
            cout << "You may enter -1 to checkout all register values in PCAs";
            int channel = 0, Rduty = 0, Gduty = 0, Bduty = 0, Riref = 0, Giref = 0, Biref = 0;
            while(1){
                
                cin >> channel;
                if(channel == -1){
                    for(int i=0;i<n;i++){
                        pca9956[i].GetAll();
                    }
                    for(int i=0;i<m;i++){
                        pca9955[i].GetAll();
                    }
                }
                cin >> Rduty >> Gduty >> Bduty >> Riref >> Giref >> Biref ;
                if(channel >= n*8){
                    channel -= n*8;
                    pca9955[channel/8].SetRGB(channel%8, Rduty, Gduty, Bduty, Riref, Giref, Biref);
                }else{
                    pca9956[channel/8].SetRGB(channel%8, Rduty, Gduty, Bduty, Riref, Giref, Biref);
                }

            }

            break;
        }else if(Mode == 'Q' || Mode == 'q'){
            break;
        }
    }

}
