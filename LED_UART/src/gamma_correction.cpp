#include <math.h>
#include <iostream>
#include "../lib/gamma_correction.h"
#define MAX_BRIGHTNESS 200
using namespace std;

Color_regulator::Color_regulator(float g){
  gamma=g;
}
int Color_regulator:: gamma_correction(float c)
{
  float temp_c = (c) / 255;
  float c_out = pow(temp_c, gamma) * 255;
  return int(c_out + 0.5);

}
void rgba_to_rgb(float &r, float &g, float &b, float &a)
{
  a=a/15;
  r=r/(r+g+b);
  g=g/(r+g+b);
  b=b/(r+g+b);
  r=r*a*MAX_BRIGHTNESS;
  g=g*a*MAX_BRIGHTNESS;
  b=b*a*MAX_BRIGHTNESS;
}
// int main(int argc, char *argv[])
// {
//   return 0;
// }