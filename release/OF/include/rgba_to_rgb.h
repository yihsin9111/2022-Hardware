#include <math.h>
#define gamma_r 1.6
#define gamma_g 1.8
#define gamma_b 1.66

float *OFrgba_to_rgb(float a)
{
  float *color = new float[3];
  //color[0] = 1/3 * a ;
  //color[1] = 1/3 * a ;
  //color[2] = 1/3 * a ;

  color[0] = pow(a/3, gamma_r) * 255;
  color[1] = pow(a/3, gamma_g) * 255;
  color[2] = pow(a/3, gamma_b) * 255;

  return color;
};
