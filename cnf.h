#pragma once

#include "helper.h"

class Cnf{
    sshort *cnf_arr;
    sshort *pure_literal_arr;
    int arr_size;
    sshort variable_num;
    int clause_num;
public:
    Cnf(ifstream&);
    ~Cnf();
    void printCnf();
private:
    int getClauseEndPosition(int) const;

    friend class DPLL;
};
