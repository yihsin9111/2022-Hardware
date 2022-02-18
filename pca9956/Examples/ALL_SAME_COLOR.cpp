#include <iostream>
#include "../pca9956.h"
#include "../pca9956_LED.h"

using namespace std;

void Set_All_Same_Color(PCA9956_LED pca, LED data);

int main(int argc, char *argv[]){

    PCA9956 pca9956(0x0D);

    pca9956.SetAllIREF(134);

    PCA9956_LED pca9956_led(pca9956);

    cout << "Usage: Plz enter \nR as RED /G as GREEN /B as BLUE /\nY as YELLOW /C as CYAN /M as MAGENTA /W as WHITE\n 0 as reset\n>> <Color>\n" ;

    char color = 0;

    while(cin >> color){
        switch (color){
	        case '0':
                LED reset;
                reset.IREF_R = 134;
                reset.IREF_G = 134;
                reset.IREF_B = 134;
                reset.PWM_R = 0;
                reset.PWM_G = 0;
                reset.PWM_B = 0;
            case 'R':
                LED red;
                red.IREF_R = 134;
                red.IREF_G = 134;
                red.IREF_B = 134;
                red.PWM_R = 255;
                red.PWM_G = 0;
		        red.PWM_B = 0;
                Set_All_Same_Color(pca9956_led, red);
                break;
            case 'G':
                LED green;
		        green.IREF_R = 134;
                green.IREF_G = 134;
		        green.IREF_B = 134;
		        green.PWM_R = 0;
                green.PWM_G = 255;
		        green.PWM_B = 0;
                Set_All_Same_Color(pca9956_led, green);
                break;
            case 'B':
                LED blue;
                blue.IREF_R = 134;
                blue.IREF_G = 134;
                blue.IREF_B = 134;
                blue.PWM_R = 0;
                blue.PWM_G = 0;
                blue.PWM_B = 255;
                Set_All_Same_Color(pca9956_led, blue);
                break;
            case 'Y':
                LED yellow;
                yellow.IREF_R = 134;
                yellow.PWM_R = 255;
                yellow.IREF_G = 134;
                yellow.PWM_G = 255;
                yellow.IREF_B = 134;
                yellow.PWM_B = 0;
                Set_All_Same_Color(pca9956_led, yellow);
                break;
            case 'C':
                LED cyan;
                cyan.IREF_R = 134;
                cyan.PWM_R = 0;
                cyan.IREF_B = 134;
                cyan.PWM_B = 255;
                cyan.IREF_G = 134;
                cyan.PWM_G = 255;
                Set_All_Same_Color(pca9956_led, cyan);
                break;
            case 'M':
                LED magenta;
                magenta.IREF_B = 134;
                magenta.PWM_B = 255;
                magenta.IREF_G = 134;
                magenta.PWM_G = 0;
                magenta.IREF_R = 134;
                magenta.PWM_R = 255;
                Set_All_Same_Color(pca9956_led, magenta);
                break;
            default:
                LED white;
                white.IREF_R = 134;
                white.PWM_R = 255;
                white.IREF_G = 134;
                white.PWM_G = 255;
                white.IREF_B = 134;
                white.PWM_B = 255;
                Set_All_Same_Color(pca9956_led, white);
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