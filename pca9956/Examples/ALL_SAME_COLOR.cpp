#include <iostream>
#include "../pca9956.h"
#include "../pca9956_LED.h"

using namespace std;

void Set_All_Same_Color(PCA9956_LED pca, LED data);

int main(int argc, char *argv[]){

    PCA9956 pca9956(0x2b);
    PCA9956 pca9956_2(0x3f);
    PCA9956 pca9956_3(0x56);
    //PCA9956 pca9956_4(0x32);

    pca9956.SetAllIREF(100);
    pca9956_2.SetAllIREF(100);
    pca9956_3.SetAllIREF(100);
//     pca9956_4.SetAllIREF(100);

    PCA9956_LED pca9956_led(pca9956);
    PCA9956_LED pca9956_led_2(pca9956_2);
    PCA9956_LED pca9956_led_3(pca9956_3);
    //PCA9956_LED pca9956_led_4(pca9956_4);

    cout << "Usage: Plz enter \nR as RED /G as GREEN /B as BLUE /\nY as YELLOW /C as CYAN /M as MAGENTA /W as WHITE\n 0 as reset\n>> <Color>\n" ;

    char color = 0;

    while(cin >> color){
        switch (color){
	    case '0':
		LED reset;
		reset.IREF_R = 100;
		reset.IREF_G = 100;
		reset.IREF_B = 100;
		reset.PWM_R = 0;
		reset.PWM_G = 0;
		reset.PWM_B = 0;
		Set_All_Same_Color(pca9956_led, reset);
		Set_All_Same_Color(pca9956_led_2, reset);
		Set_All_Same_Color(pca9956_led_3, reset);
		//Set_All_Same_Color(pca9956_led_4, reset);
		break;
            case 'R':
                ;LED red;
                red.IREF_R = 100;
		red.IREF_G = 100;
		red.IREF_B = 100;
		red.PWM_R = 255;
                red.PWM_G = 0;
		red.PWM_B = 0;
                Set_All_Same_Color(pca9956_led, red);
		Set_All_Same_Color(pca9956_led_2, red);
		Set_All_Same_Color(pca9956_led_3, red);
		//Set_All_Same_Color(pca9956_led_4, red);
                break;
            case 'G':
                LED green;
		green.IREF_R = 100;
                green.IREF_G = 100;
		green.IREF_B = 100;
		green.PWM_R = 0;
                green.PWM_G = 255;
		green.PWM_B = 0;
                Set_All_Same_Color(pca9956_led, green);
		Set_All_Same_Color(pca9956_led_2, green);
		Set_All_Same_Color(pca9956_led_3, green);
		//Set_All_Same_Color(pca9956_led_4, green);
                break;
            case 'B':
                LED blue;
		blue.IREF_R = 100;
		blue.IREF_G = 100;
                blue.IREF_B = 100;
		blue.PWM_R = 0;
		blue.PWM_G = 0;
                blue.PWM_B = 255;
                Set_All_Same_Color(pca9956_led, blue);
		Set_All_Same_Color(pca9956_led_2, blue);
		Set_All_Same_Color(pca9956_led_3, blue);
		//Set_All_Same_Color(pca9956_led_4, blue);
                break;
            case 'Y':
                LED yellow;
                yellow.IREF_R = 100;
                yellow.PWM_R = 255;
                yellow.IREF_G = 100;
                yellow.PWM_G = 255;
		yellow.IREF_B = 100;
		yellow.PWM_B = 0;
                Set_All_Same_Color(pca9956_led, yellow);
		Set_All_Same_Color(pca9956_led_2, yellow);
		Set_All_Same_Color(pca9956_led_3, yellow);
		//Set_All_Same_Color(pca9956_led_4, yellow);
                break;
            case 'C':
                LED cyan;
		cyan.IREF_R = 100;
		cyan.PWM_R = 0;
                cyan.IREF_B = 100;
                cyan.PWM_B = 255;
                cyan.IREF_G = 100;
                cyan.PWM_G = 255;
                Set_All_Same_Color(pca9956_led, cyan);
                break;
            case 'M':
                LED magenta;
                magenta.IREF_B = 100;
                magenta.PWM_B = 255;
		magenta.IREF_G = 100;
		magenta.PWM_G = 0;
                magenta.IREF_R = 100;
                magenta.PWM_R = 255;
                Set_All_Same_Color(pca9956_led, magenta);
                break;
	    case '!':
		for(int i=0;i<24;i++){
		    cout << "pca1:" << i << ", PWM:" << pca9956.GetPWM(i) << ", IREF:" << pca9956.GetIREF(i) << endl;
		}
		for(int i=0;i<24;i++){
		    cout << "pca2:" << i << ", PWM:" << pca9956_2.GetPWM(i) << ", IREF" << pca9956_2.GetIREF(i) << endl;
		}
		for(int i=0;i<24;i++){
		    cout << "pca3:" << i << ", PWM:" << pca9956_3.GetPWM(i) << ", IREF" << pca9956_3.GetIREF(i) << endl;
		}
		/*for(int i=0;i<24;i++){
		    cout << "pca4:" << i << ", PWM:" << pca9956_4.GetPWM(i) << ", IREF" << pca9956_4.GetIREF(i) << endl;
		}*/
		break;
            default:
                LED white;
                white.IREF_R = 100;
                white.PWM_R = 255;
                white.IREF_G = 100;
                white.PWM_G = 255;
                white.IREF_B = 100;
                white.PWM_B = 255;
                Set_All_Same_Color(pca9956_led, white);
		Set_All_Same_Color(pca9956_led_2, white);
		Set_All_Same_Color(pca9956_led_3, white);
		//Set_All_Same_Color(pca9956_led_4, white);
                break;
        }
    }

    return 0;
}

void Set_All_Same_Color(PCA9956_LED pca, LED data){
    for(int i = LED_ADDR_MIN ; i <= LED_ADDR_MAX ; i++){
        pca.SetLED(ADDRESS(i), data);
    }
}
