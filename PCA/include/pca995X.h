/****************************************************************************
  FileName     [ pca995X.h ]
  PackageName  [ clientApp ]
  Synopsis     [  ]
  Author       [ Ken Chung ]
  Copyright    [ Copyleft(c) , NTUEE, Taiwan ]
****************************************************************************/

//----------------------------------------------------------------------
//    Global
//----------------------------------------------------------------------

#ifndef PCA995X_H
#define PCA995X_H

#include <cstdint>

#define PCA995X_I2C_ADDRESS_DEFAULT 0x00
#define PCA995X_IREF_DEFAULT 255
#define PCA995X_PWM_DEFAULT 0

#define ADDRESS(x) (static_cast<int>(x))
#define VALUE(x) (static_cast<int>(x))
#define CHANNEL(x) (static_cast<int>(x))

#define PCA995X_IREF0_ADDR 0x22
#define PCA995X_PWM0_ADDR 0x0a

#define IREF_MAX 255
#define IREF_MIN 0
#define PWM_MAX 255
#define PWM_MIN 0

#define AUTO_INCREMENT 128

// PCA9956 definitions
#define PCA9956_CHANNELS 24

// PCA9955 definitions
#define PCA9955_CHANNELS 15

class PCA995X {
   public:
    PCA995X() {}
    ~PCA995X() {}
    PCA995X(int Address);

    int SetPWMAI(int channel, int *PWM, int size);
    int SetIREFAI(int channel, int *IREF, int size);
    int SetPWMIREFAI(int *data);

    int SetRGB(int led_address, int Rduty, int Gduty, int Bduty, int Riref, int Giref, int Biref);

    void GetAll();

    int Getfd() { return fd; };

   protected:
    virtual bool CheckChannelLegal(int channel){};
    virtual int GetChannelNum(){};

    int SetPWM(int channel, int PWM);
    int GetPWM(int channel);

    int SetIREF(int channel, int IREF);
    int GetIREF(int channel);

    int I2CWriteReg(int reg, int value);
    int I2CReadReg(int reg);

    int PCA995X_Address;
    int fd;
};

class PCA9955 : public PCA995X {
   public:
    PCA9955(){};
    ~PCA9955(){};
    PCA9955(int Address) : PCA995X(Address){};

   protected:
    bool CheckChannelLegal(int channel);
    int GetChannelNum();
};

class PCA9956 : public PCA995X {
   public:
    PCA9956(){};
    ~PCA9956(){};
    PCA9956(int Address) : PCA995X(Address){};

   protected:
    bool CheckChannelLegal(int channel);
    int GetChannelNum();
};

#endif /* PCA995X_H */
