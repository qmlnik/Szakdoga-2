#pragma once

#include "helper.h"

#include "cnf.h"
#include "mask.h"
#include "pointercontainer.h"

class DPLL{
private:
    const Cnf &cnf; //const?
    int arr_size;
    PointerContainer<Mask> *pointer_container;
    

public:
    DPLL(const Cnf &cnf);
    ~DPLL();
    sshort getUnitPropagation(const Mask&);
    sshort getPureLiteralElimination(const Mask&);
    bool checkEmptyClause(const Mask&);
    bool checkEmptyCnf(Mask&);
    sshort getAvailableLiteral(const Mask&);
    Mask& algorithm(Mask&);
    Mask& createMask(sshort, Mask*);
    Mask& startAlgorithm();
    void deleteAllMask();
    sshort* getInterpretation(Mask&);
    void deleteAllChild(Mask&, Mask&);
    void printMask(Mask&);
};
