
#include <time.h>

#include <iostream>
#include "OFrgba_to_bgriref.h"
#include "../include/pca.h"
#include "../include/pcaDefinition.h"
using namespace std;

vector<vector<char> > OFs;
vector<char> OF;

int main(int argc, char* argv[]) {
    PCA pca;  // PCA init

    OFs.resize(NUM_OF);
    for(int i = 0; i < NUM_OF; i++){
        OFs[i].resize(NUM_AN_OF_NEED_DATA);
        for(int j = 0; j < NUM_AN_OF_NEED_DATA; j++)
            OFs[i][j] = 0;
    }
    pca.WriteAll(OFs);

    while (1) {
        // choose one mode
        char Mode;
        cout << "Plz enter the OF mode you want:\n";
        cout << "(A)RGBA (B)RGB_PWM_IREF (Q)Quit\n";
        cin >> Mode;

        if (Mode == 'A' || Mode == 'a') {
            cout << "Choose one led between 0 and 25" << endl;
            cout << "Usage : \n >> <channel> <R> <G> <B> <A>\n";
            cout << "You may enter -1 to quit the current mode\n";
            cout << "Also, You may enter -2 to check all register in all PCAs\n";
            int channel = 0, R = 0, G = 0, B = 0, newChannel = 0;
            float A = 0;
            while (1) {
                cin >> newChannel;
                
                // first set last channel off
                for (int i = 0; i < 6; i++)
                    OFs[channel][i] = 0;
                
                channel = newChannel;
                if (channel == -1) {
                    break;
                } else if (channel == -2) {
                    pca.Read();
                } else {
                    cin >> R >> G >> B >> A;
                    char* color = OFrgba_to_bgriref(R, G, B, A);
                    
                    OFs[channel][0] = color[0];
                    OFs[channel][1] = color[1];
                    OFs[channel][2] = color[2];
                    OFs[channel][3] = color[3];
                    OFs[channel][4] = color[4];
                    OFs[channel][5] = color[5];
                    pca.WriteAll(OFs);
                }
            }

        } else if (Mode == 'B' || Mode == 'b') {
            cout << "Choose one led between 0 and 25" << endl;
            cout << "Usage : \n >> <channel> <R duty> <G duty> <B duty> <R iref> <G iref> <B iref>\n";
            cout << "You may enter -1 to quit the current mode\n";
	    cout << "You may enter -2 to read all registers in your pcas\n";
            int channel = 0, Rduty = 0, Gduty = 0, Bduty = 0, Riref = 0, Giref = 0, Biref = 0;
	    int newChannel = 0;
            while (1) {
                cin >> newChannel;

                for (int i = 0; i < 6; i++)
                    OFs[channel][i] = 0;
                
                channel = newChannel;
                if (channel == -1) {
                    break;
                } else if (channel == -2) {
                    pca.Read();
                } else {
                    cin >> Rduty >> Gduty >> Bduty >> Riref >> Giref >> Biref;
                    OFs[channel][0] = Bduty;
                    OFs[channel][1] = Gduty;
                    OFs[channel][2] = Rduty;
                    OFs[channel][3] = Biref;
                    OFs[channel][4] = Giref;
                    OFs[channel][5] = Riref;
                    pca.WriteAll(OFs);
                }
            }
        } else if (Mode == 'Q' || Mode == 'q') {
            break;
        }
    }
}
