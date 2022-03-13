/****************************************************************************
  FileName     [ pcaDefinition.h ]
  PackageName  [ clientApp ]
  Synopsis     [ definitions ]
  Author       [ Ken Chung ]
  Copyright    [ Copyleft(c) , NTUEE, Taiwan ]
****************************************************************************/

//----------------------------------------------------------------------
//    Global
//----------------------------------------------------------------------
#ifndef _DEF_H_
#define _DEF_H_

// PCA type
#define _PCA9956 9956
#define _PCA9955B 9955

// numbers of pca data needed
#define NUM_PCA 4                                                       // number of PCA used
#define NUM_OF 26                                                       // number of total OFs
#define NUM_AN_OF_NEED_IREF 3                                           // number of IREF data need sent to an of
#define NUM_AN_OF_NEED_PWM 3                                            // number of PWM data need sent to an of
#define NUM_AN_OF_NEED_DATA (NUM_AN_OF_NEED_IREF + NUM_AN_OF_NEED_PWM)  // number of data need sent to an of
#define NUM_CHANNEL_FROM_PCA9955B 5                                     // number of OFs provided from a pca9955B
#define NUM_CHANNEL_FROM_PCA9956 8                                      // number of OFs provided from a pca9956
#define NUM_DATA_TO_PCA(x, y) (x * y)                                   // number of data sent to a pca

#endif /* _DEF_H_ */
