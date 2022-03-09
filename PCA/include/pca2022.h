/**
 * @file 2022pca.h
 *
 */
/* Copyright (C) 2022 by NTUEE, Taiwan
 *
 */

#ifndef PCA2022_H
#define PCA2022_H

#include <vector>

#include "./pca9955.h"
#include "./pca9956.h"

class LinkedList;
class PCAnode;
class LinkedList {
   public:
    LinkedList() : first(nullptr){};

    void Add(int PCA_ADDR, bool IsPCA9956);

    PCAnode *first;
};
class PCAnode {
   public:
    PCAnode();
    PCAnode(int PCA_ADDR, bool IsPCA9956);

    PCA9956 *pca9956;
    PCA9955 *pca9955;
    PCAnode *nxt;

    friend class LinkedList;
};
class PCA {
   public:
    PCA();

    void Debug();
    int Write(std::vector<std::vector<char> > &);
    void Read();

   private:
    LinkedList PCAs;
};

#endif /* PCA2022_H */
