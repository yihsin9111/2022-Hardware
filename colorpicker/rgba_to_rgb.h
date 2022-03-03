#include <math.h>
#define gamma_r 1.6
#define gamma_g 1.8
#define gamma_b 1.66

float *LEDrgba_to_rgb(float r, float g, float b, float a, int max_brightness)
{
  float *color = new float[3];
  a/=170;
  r = r / (r + g + b);
  g = g / (r + g + b);
  b = b / (r + g + b);
  color[0] = r * a * max_brightness;
  color[1] = g * a * max_brightness;
  color[2] = b * a * max_brightness;

  float temp = color[1] / 255;
  color[1] = pow(temp, gamma_g) * 255;
  temp = color[0] / 255;
  color[0] = pow(temp, gamma_r) * 255;
  temp = color[2] / 255;
  color[2] = pow(temp, gamma_b) * 255;

  return color;
};

float *OFrgba_to_rgb(float a)
{
  Serial.println(a);
  float *color = new float[3];
  a/=765;

  color[0] = pow(a, gamma_r) * 255;
  color[1] = pow(a, gamma_g) * 255;
  color[2] = pow(a, gamma_b) * 255;
  Serial.print(color[0]);
  Serial.print(' ');
  Serial.print(color[1]);
  Serial.print(' ');
  Serial.println(color[2]);  
  return color;
};
