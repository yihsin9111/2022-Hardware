/****************************************************************************
  FileName     [ pca9956.h ]
  PackageName  [ clientApp ]
  Synopsis     [  ]
  Author       [ Ken Chung ]
  Copyright    [ Copyleft(c) , NTUEE, Taiwan ]
****************************************************************************/

//----------------------------------------------------------------------
//    Global
//----------------------------------------------------------------------

#ifndef PCA9956_H
#define PCA9956_H

#include "pca995X.h"

class PCA9956 : public PCA995X {
   public:
    PCA9956(){};
    ~PCA9956(){};
    PCA9956(int Address) : PCA995X(Address){};

   protected:
    bool CheckChannelLegal(int channel);
    int GetChannelNum();
};

#endif /* PCA9956_H */
