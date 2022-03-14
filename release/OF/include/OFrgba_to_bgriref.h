/****************************************************************************
  FileName     [ OFrgba_to_rgbiref.h ]
  PackageName  [ clientApp ]
  Synopsis     [  ]
  Author       [  ]
  Copyright    [ Copyleft(c) , NTUEE, Taiwan ]
****************************************************************************/

//----------------------------------------------------------------------
//    Global
//----------------------------------------------------------------------
#ifndef _OFRGBA_TO_RGBIREF_H
#define _OFRGBA_TO_RGBIREF_H
#include <math.h>
#define gamma_r 1.6
#define gamma_g 1.8
#define gamma_b 1.66

char *OFrgba_to_bgriref(int R, int G, int B, float a) {
    a = a > 12 ? 1 : a / 12;
    // a will be 0-10,15 from software
    // however, OF is too dark if we need to handle a = 15, OF won't be bright enough
    // So we need to resize a to be 0-10, 12
    // In Addition, gamma correction need a to be smaller than 1, So we need a to be divided by 12

    char *color = new char[3];

    color[0] = char(pow(a / 3, gamma_b) * 255);
    color[1] = char(pow(a / 3, gamma_g) * 255);
    color[2] = char(pow(a / 3, gamma_r) * 255);
    color[3] = B;
    color[4] = G;
    color[5] = R;

    return color;
};
#endif /* _OFRGBA_TO_RGBIREF_H */