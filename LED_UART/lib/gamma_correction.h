#include <math.h>
#include <iostream>

class Color_regulator{
  public:
    Color_regulator(){};
    Color_regulator(float );
    int gamma_correction(float c);
    void rgba_to_rgb(float &r, float &g, float &b, float &a);
    void set_gamma(float &);
  private:
    float gamma;

};