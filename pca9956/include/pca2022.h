/**
 * @file 2022pca.h
 *
 */
/* Copyright (C) 2022 by NTUEE, Taiwan
 *
 */

#ifndef PCA2022_H
#define PCA2022_H

#include "./pca9956.h"
#include "./pca9955.h"

class PCA{
    public:
        PCA();

        int Write(int *data);
    private:
        PCA9956 *pca9956;
        PCA9955 *pca9955;
};

#endif /* PCA2022_H */
