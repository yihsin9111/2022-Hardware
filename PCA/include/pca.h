/****************************************************************************
  FileName     [ pca.h ]
  PackageName  [ clientApp ]
  Synopsis     [  ]
  Author       [ Ken Chung ]
  Copyright    [ Copyleft(c) , NTUEE, Taiwan ]
****************************************************************************/

//----------------------------------------------------------------------
//    Global
//----------------------------------------------------------------------
#ifndef PCA_H
#define PCA_H

#include <vector>

#include "pca995X.h"

// Initialize function : PCA() , which is the default constructor
// There're two different function to write data to a PCA, WriteAll(vector<vector<unsigned char>>) and WriteChannel(vector<vector<unsigned char>>)
// WriteAll can be used to update all OFs' datas
// WriteChannel is used to updata only one OF datas, which can be used to Debug
class PCA {
   public:
    PCA();

    int WriteAll(std::vector<std::vector<char> > &data);
    int WriteChannel(std::vector<char> &data, int channel);
    void Read();

   private:
    std::vector<PCA995X> PCAs;
};

#endif /* PCA */
