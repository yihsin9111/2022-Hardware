/****************************************************************************
  FileName     [ definition.h ]
  PackageName  [ clientApp ]
  Synopsis     [ definitions ]
  Author       [  ]
  Copyright    [ Copyleft(c) , NTUEE, Taiwan ]
****************************************************************************/

//----------------------------------------------------------------------
//    Global
//----------------------------------------------------------------------
#ifndef _DEF_H_
#define _DEF_H_

//PCA(OF) I2C address
#define PCA_ADDR_1 0x00
#define PCA_ADDR_2 0x20
#define PCA_ADDR_3 0x40
#define PCA_ADDR_4 0x60

//PCA(OF) types
#define PCA_TYPE_1 9956
#define PCA_TYPE_2 9956
#define PCA_TYPE_3 9955
#define PCA_TYPE_4 9955

//PCA tpye
#define _PCA9956  9956
#define _PCA9955B 9955

//numbers of pca data needed
#define NUM_AN_OF_NEED 6 //number of data need sent to an of
#define NUM_OF 26 //number of total OFs

const int pcaTypeAddr[4][2] = {
  {PCA_TYPE_1, PCA_ADDR_1}, 
  {PCA_TYPE_2, PCA_ADDR_2}, 
  {PCA_TYPE_3, PCA_ADDR_3}, 
  {PCA_TYPE_4, PCA_ADDR_4}
}

#endif /* _DEF_H_ */