#include "pointercontainer.h"
#include "exception.h"

template<typename T>
PointerContainer<T>::PointerContainer(int size) : arr_size(size + 1){
    free_space_arr = new bool[arr_size]; 
    pointer_arr = new T *[arr_size];
    for (int i = 0; i < arr_size; i++){
        free_space_arr[i] = true;
    }
}

template<typename T>
PointerContainer<T>::~PointerContainer(){
    delete[] free_space_arr;
    free_space_arr = nullptr;
    delete[] pointer_arr;
    pointer_arr = nullptr;
}

template<typename T>
void PointerContainer<T>::addPointer(T *pointer){
    for (int i = 0; i < arr_size; i++){
        if (free_space_arr[i]){
            pointer_arr[i] = pointer;
            free_space_arr[i] = false;
            return;
        }
    }

    throw CustomException("No more free space!");
}

template<typename T>
void PointerContainer<T>::deletePointer(T *pointer){
    for (int i = 0; i < arr_size; i++){
        if (pointer_arr[i] == pointer){
            pointer_arr[i] = nullptr;
            free_space_arr[i] = true;
            return;
        }
    }

    throw CustomException("Pointer not found, cant delete!");
}

template<typename T>
void PointerContainer<T>::deleteAllPointer(){
    for (int i = 0; i < arr_size; i++){
        delete pointer_arr[i];
    }
}