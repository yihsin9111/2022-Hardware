/****************************************************************************
  FileName     [ pca9955.h ]
  PackageName  [ clientApp ]
  Synopsis     [  ]
  Author       [ Ken Chung ]
  Copyright    [ Copyleft(c) , NTUEE, Taiwan ]
****************************************************************************/

//----------------------------------------------------------------------
//    Global
//----------------------------------------------------------------------

#ifndef PCA9955_H
#define PCA9955_H

#include "pca995X.h"

class PCA9955 : public PCA995X {
   public:
    PCA9955(){};
    ~PCA9955(){};
    PCA9955(int Address) : PCA995X(Address){};

   protected:
    bool CheckChannelLegal(int channel);
    int GetChannelNum();
};

#endif /* PCA9955_H */
