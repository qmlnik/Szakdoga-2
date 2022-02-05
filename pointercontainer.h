#pragma once

#include "helper.h"
#include "mask.h"

template <typename T>
class PointerContainer{
private:
    int arr_size;
    bool *free_space_arr;
    T **pointer_arr;

public:
    PointerContainer(int size);
    ~PointerContainer();
    void addPointer(T*);
    void deletePointer(T*);
    void deleteAllPointer();
    void printAllPointer();
};

template class PointerContainer<Mask>;