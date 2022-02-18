/*
	UART communication on Raspberry Pi using C (WiringPi Library)
	http://www.electronicwings.com
*/

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <iostream>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <time.h>
#include <unistd.h>

using namespace std;

int main ()
{
  std::cout << "in"<<std::endl;
  int serial_port ;
  char dat;
  if ((serial_port = serialOpen ("/dev/ttyS0", 9600)) < 0)	/* open serial port */
  {
    fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
    return 1 ;
  }

  if (wiringPiSetup () == -1)					/* initializes wiringPi setup */
  {
    fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno)) ;
    return 1 ;
  }

  while(1){
		dat = 'a';		/* receive character serially*/	
		cout <<dat<<endl;
    char data[5]={1,2,3,4,5};
		serialPuts(serial_port, data);		/* transmit character serially on port */

  sleep(1);
	}

}

//save

		
		if(runcount>nLeds[0]){
			runcount=0;
			cout<<"a"<<endl;
		}
			
		cout<< runcount <<endl;
		usleep(10*1000);
		for (int i = 0; i < nStrips; ++i) { 
			for (int j = 0; j < nLeds[i] * 3; ++j){
				if(j/3==runcount){
					buf[i][j]=255;
				}
				else
					buf[i][j]=0;
			}
		strips.sendToStrip(i, buf[i]);
		}
		runcount++;