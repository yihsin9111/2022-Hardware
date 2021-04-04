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
int* rgba_to_rgb(float r, float g, float b, float a)
{
  int* color;
  a=a/15;
  r=r/(r+g+b);
  g=g/(r+g+b);
  b=b/(r+g+b);
  color[0]=(int)r*a*MAX_BRIGHTNESS;
  color[1]=(int)g*a*MAX_BRIGHTNESS;
  color[2]=(int)b*a*MAX_BRIGHTNESS;
  return color;
}
// int main(int argc, char *argv[])
// {
//   return 0;
// }