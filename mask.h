#pragma once

#include "helper.h"

class Mask{
private:
    char *mask_arr;
    sshort assignment;
    Mask *parent;
    bool isEmptyCnf;

public:
    Mask(char*, sshort, Mask*);
    ~Mask();
    void setChild(Mask*);
    Mask* getPointer();
    char* getMask();
    sshort getAssignment();
    bool getIsEmptyCnf();
    friend class DPLL;
};
