#include <iostream>
#include "../include/pca9956.h"

using namespace std;

int main(){

   PCA9956 pca9956(0x3f);

   int* PWM;

   PWM = new int [24];

   for(int i=0;i<24;i++)
	   PWM[i] = 255;

   int* IREF;

   IREF = new int [24];

   for(int i=0;i<24;i++)
	   IREF[i] = 134;

   pca9956.SetPWMAI(10, PWM, 24);
   pca9956.SetPWMAI(34, IREF, 24);

}
