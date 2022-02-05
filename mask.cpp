#include "mask.h"

/*We represent the current state of the cnf with masks.
Every mask has the same length as the cnf array.
Every literal's state is stored in the mask (mask_arr), on the same position.
States: 0 - unassigned, 1 - assigned to false, 2 - inside a clause that is already true.*/
Mask::Mask(char *mask, sshort assignment, Mask *parent) 
        : mask_arr(mask), assignment(assignment), parent(parent), isEmptyCnf(false){};

Mask::~Mask(){
    cout << "deleting mask: " << assignment << endl;
    delete[] mask_arr;
    mask_arr = nullptr;
    parent = nullptr;
}

char* Mask::getMask(){ return mask_arr; }
Mask* Mask::getPointer(){ return this; }

sshort Mask::getAssignment(){ return assignment; }

bool Mask::getIsEmptyCnf(){
    return isEmptyCnf;
}