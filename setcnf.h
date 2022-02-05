#pragma once

#include "helper.h"

class SetCnf{
private:
    sshort *set_arr;
    sshort set_top_pos;
    sshort *close_arr;
    sshort close_top_pos;

    void removeSetArr(sshort);
    bool inSetArr(sshort);
    bool inCloseArr(sshort);

public:
    SetCnf(sshort);
    ~SetCnf();
    void addElement(sshort);
    sshort getElement();
};
