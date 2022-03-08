#include <time.h>

#include <iostream>

#include "../lib/LED_strip.h"
#include "../lib/gamma_correction.h"
#define fps 30
using namespace std;

// the number of leds of every strip
// maximum 16 numbers in the vector ( maximum 16 led strips )
// declaration
vector<uint16_t> nLeds;
// rgb data of every single led
vector<vector<char> > buf;

// initialization
LED_Strip strips;
Color_regulator reg_g(1.8);
Color_regulator reg_r(1.6);
Color_regulator reg_b(1.66);
void test_color() {
    int channel = 0;
    char mode = '\0';
    uint32_t color;
    float alpha = 0, r = 0, g = 0, b = 0;
    bool channel_state = true;
    while (channel_state) {
        cout << "please enter the target channel (dec): ";
        cin >> channel;
        if (channel < 0 || channel >= nLeds.size()) {
        } else {
            channel_state = false;
        }
    }

    cout << "\nplease choose your testing mode.A for rgba;B for rgb: ";
    cin >> mode;
    if (mode == 'a' || mode == 'A') {
        float* temp = new float[3];
        cout << "\nplease enter the color(HEX) in the order of R G B & alpha (ex:0xfffabf 8): ";
        cin >> hex >> color >> alpha;
        r = color / 65536;
        color -= r * 65536;
        g = color / 256;
        color -= g * 256;
        b = color;
        cout << r << " " << g << " " << b << " " << alpha << endl;
        temp = rgba_to_rgb(r, g, b, alpha);
        cout << temp[0] << " " << temp[1] << " " << temp[2] << endl;
        for (int i = 0; i < nLeds.size(); ++i) {
            for (int j = 0; j < nLeds[i]; ++j) {
                if (i == channel) {
                    buf[i][3 * j] = reg_g.gamma_correction(temp[1]);      // g
                    buf[i][3 * j + 1] = reg_r.gamma_correction(temp[0]);  // r
                    buf[i][3 * j + 2] = reg_b.gamma_correction(temp[2]);  // b
                } else {
                    buf[i][3 * j] = 0;      // g
                    buf[i][3 * j + 1] = 0;  // r
                    buf[i][3 * j + 2] = 0;  // b
                }
            }
        }
        strips.sendToStrip(buf);
    } else if (mode == 'b' || mode == 'B') {
        cout << "\nplease enter the color(HEX) in the order of R G B (ex:0xff12a3): ";
        cin >> hex >> color;
        cout << hex << color << endl;
        r = (int)(color / 65536);
        color -= r * 65536;
        g = (int)color / 256;
        color -= g * 256;
        b = (int)color;
        cout << hex << r << " " << hex << g << " " << hex << b << " ";
        for (int i = 0; i < nLeds.size(); ++i) {
            for (int j = 0; j < nLeds[i]; ++j) {
                if (i == channel) {
                    buf[i][3 * j] = (int)g;      // g
                    buf[i][3 * j + 1] = (int)r;  // r
                    buf[i][3 * j + 2] = (int)b;  // b
                } else {
                    buf[i][3 * j] = 0;      // g
                    buf[i][3 * j + 1] = 0;  // r
                    buf[i][3 * j + 2] = 0;  // b
                }
            }
        }
        strips.sendToStrip(buf);
    }
}
int main() {
    // resize buf to a (number of strips)*(number of leds of the strip)*3 vector
    nLeds = {10, 10, 10, 10, 10, 10, 10, 10};  // change the numbers of lights here
    strips.initialize(nLeds);
    buf.resize(nLeds.size());
    for (int i = 0; i < nLeds.size(); ++i) {
        buf[i].resize(nLeds[i] * 3, (char)0);
    }
    test_color();
}