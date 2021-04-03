#include "../lib/LED_strip.h"
#include <vector>
#include <time.h>

using namespace std;

vector<uint16_t> nLeds{100, 30, 30};
vector< vector<char> > buf;

LED_Strip strips(nLeds);

int main(void){
	buf.resize(nLeds.size());
	for(int i = 0; i < nLeds.size(); ++i)
		buf[i].resize(nLeds[i] * 3, (char)0);

	clock_t init = clock();
	uint16_t rgbCount = 0; // just for example use
	while(1){
		// 30 fps
		while( (1000 * (clock() - init)) / CLOCKS_PER_SEC < 1000/30);
		init = clock();
		for(int i = 0; i < nLeds.size(); ++i){
			for(int j = 0; j < nLeds[i]; ++j){
				buf[i][3*j  ] = rgbCount % 3 == 0 ? 50 : 0;
				buf[i][3*j+1] = rgbCount % 3 == 1 ? 50 : 0;
				buf[i][3*j+2] = rgbCount % 3 == 2 ? 50 : 0;
			}
		}
		strips.sendToStrip(buf);
		++rgbCount;
		rgbCount %= 3;
	}
}
