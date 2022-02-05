#include "dpll.h"
#include "cnf.h"
#include "mask.h"
#include "setcnf.h"
#include "pointercontainer.h"
#include "exception.h"

DPLL::DPLL(const Cnf &cnf) : cnf(cnf), arr_size(cnf.arr_size){
    pointer_container = new PointerContainer<Mask>(cnf.variable_num);
}

DPLL::~DPLL(){
    delete pointer_container;
    pointer_container = nullptr;
}

sshort DPLL::getUnitPropagation(const Mask &mask){
    int start_pos = 0, end_pos, i;
    sshort unitLiteral;
    bool unit;

    while(start_pos < arr_size){
        end_pos = cnf.getClauseEndPosition(start_pos);
        unitLiteral = 0;
        unit = false;

        for(i = 0; i <= end_pos - start_pos; i++){
            if(mask.mask_arr[start_pos + i] == 0 && !unit){
                unitLiteral = cnf.cnf_arr[start_pos + i];
                unit = true;
                continue;
            } 
            
            if(mask.mask_arr[start_pos + i] == 0 && unit){
                unit = false;
                break;
            }
        }

        if(unit){
            return unitLiteral;
        }

        start_pos = end_pos + 2;
    }

    return 0;
}

sshort DPLL::getPureLiteralElimination(const Mask &mask){
    SetCnf set_cnf(cnf.variable_num);

    for(int i = 0; i < arr_size; i++){
        if(mask.mask_arr[i] == 0 && cnf.cnf_arr[i] != 0){
            set_cnf.addElement(cnf.cnf_arr[i]);
        }
    }

    return set_cnf.getElement();
}

bool DPLL::checkEmptyClause(const Mask &mask){
    bool empty_clause;
    int start_pos = 0, end_pos;

    while(start_pos < arr_size){
        end_pos = cnf.getClauseEndPosition(start_pos);
        empty_clause = true;
        for(int i = 0; i <= end_pos - start_pos; i++){
            if(mask.mask_arr[start_pos + i] != 1){
                empty_clause = false;
                break;
            }
        }

        if(empty_clause){
            return true;
        }
        start_pos = end_pos + 2;
    }

    return false;
}

bool DPLL::checkEmptyCnf(Mask &mask){
    for(int i = 0; i < cnf.arr_size; i++){
        if(mask.mask_arr[i] != 2 && cnf.cnf_arr[i] != 0){
            return false;
        }
    }

    return true;
}

sshort DPLL::getAvailableLiteral(const Mask &mask){
    for(int i = 0; i < arr_size; i++){
        if(mask.mask_arr[i] == 0 && cnf.cnf_arr[i] != 0){
            return cnf.cnf_arr[i];
        }
    }

    return 0;
}

Mask& DPLL::createMask(sshort assignment, Mask *parent){
    char *mask_arr = new char[arr_size];
    if(parent != nullptr){
        memcpy(mask_arr, parent->getMask(), arr_size);
        int start_pos = 0, end_pos;
        while(start_pos < arr_size){
            end_pos = cnf.getClauseEndPosition(start_pos);
            for(int i = 0; i <= end_pos - start_pos; i++){
                if(cnf.cnf_arr[start_pos + i] == assignment){
                    for(int j = 0; j < end_pos - start_pos + 1; j++){
                        mask_arr[start_pos + j] = 2;
                    }
                } else if(cnf.cnf_arr[start_pos + i] == assignment * (-1)
                            && mask_arr[start_pos + i] == 0){
                    mask_arr[start_pos + i] = 1;
                }
            }
            start_pos = end_pos + 2;
        }
    }

    Mask *newmask = new Mask(mask_arr, assignment, parent);
    try{
        pointer_container->addPointer(newmask);
    } catch(const CustomException &e){
        cerr << e.getMessage() << endl;
    }

    return *newmask;
}

Mask& DPLL::algorithm(Mask &mask){
    if(checkEmptyClause(mask)){
        cout << "found empty clause" << endl;
        mask.isEmptyCnf = false;
        return mask;
    } 
    
    if(checkEmptyCnf(mask)){
        cout << "found empty cnf" << endl;
        mask.isEmptyCnf = true;
        return mask;
    }

    sshort result;
    result = getUnitPropagation(mask);
    if(result != 0){
        cout << "unit propagation, assignment: " << result << endl;
        return algorithm(createMask(result, &mask));
    } else {
        result = getPureLiteralElimination(mask);
        if(result != 0){
            cout << "pure literal elimination, assignment: " << result << endl;
            return algorithm(createMask(result, &mask));
        } else {
            result = getAvailableLiteral(mask);
            cout << "left branch, assignment: " << result << endl;
            Mask &left_branch = algorithm(createMask(result, &mask));
            if(left_branch.isEmptyCnf){
                return left_branch;
            } else {
                deleteAllChild(left_branch, mask);
            }

            cout << "right branch, assignment: " << result * (-1) << endl;
            Mask &right_branch = algorithm(createMask(result * (-1), &mask));
            if(right_branch.isEmptyCnf){
                return right_branch;
            } else {
                deleteAllChild(right_branch, mask);
            }

            mask.isEmptyCnf = false;

            return mask;
        }
    }
}

Mask& DPLL::startAlgorithm(){
    return algorithm(createMask(0, nullptr));
}

void DPLL::deleteAllMask(){
    pointer_container->deleteAllPointer();
}

sshort* DPLL::getInterpretation(Mask &mask){
    sshort *ret = new sshort[cnf.variable_num];
    int ret_top = -1;
    Mask *inner_mask = &mask;
    while(inner_mask->parent != nullptr){
        ret[++ret_top] = inner_mask->getAssignment();
        inner_mask = inner_mask->parent;
    }

    int ret_length = ret_top + 1;

    int half_num = ret_length % 2 == 0 ?
                     ret_length / 2 :
                     floor(ret_length / 2);
    sshort switch_var;

    for(int i = 0; i < half_num; i++){
        switch_var = ret[i];
        ret[i] = ret[ret_top - i];
        ret[ret_top - i] = switch_var;
    }

    return ret;
}

void DPLL::deleteAllChild(Mask &node_mask, Mask &branch_mask){
    Mask *parent_pointer = node_mask.parent;
    Mask *current_pointer = &node_mask;

    while(current_pointer != &branch_mask){
        try{
            pointer_container->deletePointer(current_pointer);
        } catch(const CustomException &e){
            cerr << e.getMessage() << endl;
        }
        delete current_pointer;
        current_pointer = parent_pointer;
        parent_pointer = parent_pointer->parent;
    }
}

void DPLL::printMask(Mask &mask){
    for(int i = 0; i < arr_size; i++){
        cout << +mask.mask_arr[i];
    }
    cout << endl;
}
