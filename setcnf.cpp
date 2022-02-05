#include "setcnf.h"

/*A set implementation that was specifically made for pure literals.*/
SetCnf::SetCnf(sshort arr_size){
    set_arr = new sshort[arr_size];
    close_arr = new sshort[arr_size];
    set_top_pos = 0;
    close_top_pos = 0;
}

SetCnf::~SetCnf(){
    delete[] set_arr;
    set_arr = nullptr;
    delete[] close_arr;
    close_arr = nullptr;
}

void SetCnf::addElement(sshort element){
    if(!this->inCloseArr(element)){
        if(this->inSetArr(element * (-1))){
            this->removeSetArr(element * (-1));
            close_arr[close_top_pos++] = element;
        } else {
            for(int i = 0; i < set_top_pos; i++){
                if(set_arr[i] == element){
                    return;
                }
            }
            set_arr[set_top_pos++] = element;
        }
    }
}

sshort SetCnf::getElement(){
    if(set_top_pos == 0){
        return 0;
    }
    return set_arr[set_top_pos - 1];
}

void SetCnf::removeSetArr(sshort element){
    bool found = false;
    for(int i = 0; i < set_top_pos; i++){
        if(found){
            set_arr[i - 1] = set_arr[i];
        }

        if(set_arr[i] == element){
            found = true;
        }
    }

    if(found){
        set_top_pos--;
    }
}

bool SetCnf::inSetArr(sshort element){
    for(int i = 0; i < set_top_pos; i++){
        if(set_arr[i] == element){
            return true;
        }
    }

    return false;
}

bool SetCnf::inCloseArr(sshort element){
    for(int i = 0; i < close_top_pos; i++){
        if(close_arr[i] == element || close_arr[i] == element * (-1)){
            return true;
        }
    }

    return false;
}
