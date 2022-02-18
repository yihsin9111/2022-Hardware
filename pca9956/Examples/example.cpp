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

        //choose one mode
        char Mode;
        cout << "Plz enter the OF mode you want :\n";
        cout << "(A)AutoIcrement (B)Breath (C)ChooseOne (Q)Quit :\n";
        cin >> Mode;

        if(Mode == 'A' || Mode == 'a'){
            
            
            break;
        }else if(Mode == 'B' || Mode == 'b'){
            clock_t init, clk;
            bool increase = true;
            init = clock();
            int bright = 0;
            bool quit = false;
            int *IREF = new int [24];
            int *PWM = new int [24];

            while(!quit){
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
                if(cin >> quit){
                    if(quit) break;
                }
            }
        }else if(Mode == 'C' || Mode == 'c'){

            break;
        }else if(Mode == 'Q' || Mode == 'q'){
            break;
        }
    }

}
