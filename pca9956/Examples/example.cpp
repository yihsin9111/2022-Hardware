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
    PCA9956 *pca9956 = new PCA9956[m];
    PCA9955 *pca9955 = new PCA9955[m];
    cout << "Plz enter the addresses of your PCA9956 slaves in decimal sequentially :\n" ;
    for(int i=0;i<n;i++){
        int temp = 0;
        cin >> temp;
        pca9956 = PCA9956(temp);
    }
    for(int i=0;i<m;i++){
        int temp = 0;
        cin >> temp;
        pca9955 = PCA9955(temp);
    }

    while(1){

        //choose one mode
        char Mode;
        cout << "Plz enter the OF mode you want :\n";
        cout << "(A)AutoIcrement (B)Breath (C)ChooseOne (Q)Quit :\n";
        cin >> Mode;

        if(Mode == 'A' || Mode == 'a'){
            clock_t init, clk;
            bool increase = true;
            init = clock();
            int bright = 0;
            int *IREF = new int [24*(n+m)];

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
                    }
                    for(int i=0;i<n;i++){
                        pca9956
                    }


                    for(int i=0 ; i<(n+m)*8 ; i++){
                        
                        
                        if(i>23){
                        }else if(i>15){
                        pca9956_3.SetPWM((i-16)*3, 255*bright/30);
                        pca9956_3.SetPWM((i-16)*3+1, 255*bright/30);
                        pca9956_3.SetPWM((i-16)*3+2, 255*bright/30);
                        }else if(i>8){
                        pca9956_2.SetPWM((i-8)*3, 255*bright/30);
                        pca9956_2.SetPWM((i-8)*3+1, 255*bright/30);
                        pca9956_2.SetPWM((i-8)*3+2, 255*bright/30);
                        }else{
                        pca9956_1.SetPWM(i*3, 255*bright/30);
                        pca9956_1.SetPWM(i*3+1, 255*bright/30);
                        pca9956_1.SetPWM(i*3+2, 255*bright/30);
                        }
                    }
                }
            }
            
        }else if(Mode == 'B' || Mode == 'b'){

        }else if(Mode == 'C' || Mode == 'c'){

        }else if(Mode == 'Q' || Mode == 'q'){
            break;
        }
    }

}