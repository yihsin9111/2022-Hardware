#include <iostream>
#include "../include/pca9956.h"

using namespace std;

int main(){

   PCA9956 pca9956(0x3f);

   int* PWM;

   PWM = new int [15];

   for(int i=0;i<15;i++)
	   PWM[i] = 12;

   cout <<   pca9956.SetPWMAI(PWM, 15) << endl;

   for(int i=0;i<24;i++){
   cout << "i=0, " << pca9956.GetPWM(i) << endl;
   }
   
}
