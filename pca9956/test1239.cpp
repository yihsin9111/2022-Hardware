#include <iostream>
#include <wiringPiI2C.h>

using namespace std;

void LED_RESET(int slave){
    for(int i=0;i<24;i++)
	    wiringPiI2CWriteReg8(slave, i+10, 0);
}
void LED_FULLON(int slave){
    for(int i=0;i<24;i++)
	    wiringPiI2CWriteReg8(slave, i+10, 255);
}
void LED_FULL_RED(int slave){
     for(int i=0;i<24;i+=3){
 	    wiringPiI2CWriteReg8(slave, i+10, 255);
 	    wiringPiI2CWriteReg8(slave, i+1+10, 0);
 	    wiringPiI2CWriteReg8(slave, i+2+10, 0);
     }
}
void LED_FULL_GREEN(int slave){
     for(int i=0;i<24;i+=3){
      	    wiringPiI2CWriteReg8(slave, i+10, 0);
 	    wiringPiI2CWriteReg8(slave, i+1+10, 255);
 	    wiringPiI2CWriteReg8(slave, i+2+10, 0);
     }
}
void LED_FULL_BLUE(int slave){
     for(int i=0;i<24;i+=3){
             wiringPiI2CWriteReg8(slave, i+10, 0);
 	    wiringPiI2CWriteReg8(slave, i+1+10, 0);
 	    wiringPiI2CWriteReg8(slave, i+2+10, 255);
     }
}
void setIREF(int Iref, int slave){
    wiringPiI2CWriteReg8(slave, 0x40, Iref);
}

int main(){
    int fd = wiringPiI2CSetup(0x3f);
    cout << "led setup result : " << fd << endl;
    int fd01 = wiringPiI2CSetup(0x58);
    cout << "led setup result : " << fd01 << endl;
    int fd02 = wiringPiI2CSetup(0x40);
    // wiringPiI2CWriteReg8(fd, 0x40, 134);
   setIREF(134, fd);
   setIREF(134, fd01);
   setIREF(134, fd02);


	LED_RESET(fd);
	LED_RESET(fd01);
	LED_RESET(fd02);
	int pin = 0;
	while(1){
		if(cin >> pin){
//		for(int i=0;i<24;i++)
//		wiringPiI2CWriteReg8(fd,i,0);
//		for(int i=0;i<24;i++){
//		int result0 = wiringPiI2CWriteReg8(fd, 0, 100);
			if(pin == -1){
			    LED_FULLON(fd);
			    LED_FULLON(fd01);
			    LED_FULLON(fd02);
			}		
			 else if(pin == -2){
			     LED_RESET(fd);
			     LED_RESET(fd01);
			     LED_RESET(fd02);
			}else if(pin == -3){
			     LED_FULL_RED(fd);
			     LED_FULL_RED(fd01);
			     LED_FULL_RED(fd02);
			}else if(pin == -4){
			     LED_FULL_GREEN(fd);
			     LED_FULL_GREEN(fd01);
			     LED_FULL_GREEN(fd02);
			}else if(pin == -5){
			     LED_FULL_BLUE(fd);
			     LED_FULL_BLUE(fd01);
			     LED_FULL_BLUE(fd02);
			}else if(pin == -6){
			     LED_FULL_BLUE(fd);
			}else if(pin == -7){
			     LED_FULL_BLUE(fd01);
			}else if(pin == -8){
			     LED_FULL_BLUE(fd02);
			}else if(pin == -9){
			     int red = 0;
			     int green = 0;
			     int blue = 0;
			     int pinp = 0;
			     cin >> red >> green >> blue >> pinp;
			     if(pinp<8){
			     	wiringPiI2CWriteReg8(fd, pinp*3+10, red);
				wiringPiI2CWriteReg8(fd, pinp*3+1+10, green);
				wiringPiI2CWriteReg8(fd, pinp*3+2+10, blue);
			     }else if(pinp<16){
				pinp -= 8;
			        wiringPiI2CWriteReg8(fd01, pinp*3+10, red);
				wiringPiI2CWriteReg8(fd01, pinp*3+1+10, green);
				wiringPiI2CWriteReg8(fd01, pinp*3+2+10, blue);
			     }else{
				pinp -= 16;
			        wiringPiI2CWriteReg8(fd02, pinp*3+10, red);
				wiringPiI2CWriteReg8(fd02, pinp*3+1+10, green);
				wiringPiI2CWriteReg8(fd02, pinp*3+2+10, blue);
			     }
			     
			}
			
			
			else{
    				wiringPiI2CWriteReg8(fd, pin+10, 100);
			}
		}
//		int result1 = wiringPiI2CWriteReg16(fd, 1, 100);
//		cout << "result0 : " << result0 << endl;
//		cout << "result1 : " << result1 << endl;
		//}
//		wiringPiI2CWriteReg8(fd, 0x02, 0x5f);
//		wiringPiI2CWrite(fd,200);
	}

}
