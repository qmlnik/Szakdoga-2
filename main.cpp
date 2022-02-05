#include "helper.h"

#include "cnf.h"
#include "dpll.h"


int main(){
    ifstream cnf_file("3sat/test.cnf");
    Cnf cnf(cnf_file);
    cnf.printCnf();
    DPLL dpll(cnf);
    Mask &result = dpll.startAlgorithm();

    if(!result.getIsEmptyCnf()){
        cout << "unsatisfiable" << endl;
    } else {
        cout << "satisfiable" << endl;
        sshort *interpretation = dpll.getInterpretation(result);
        int i = 0;
        cout << "interpretation:" << endl;
        while(interpretation[i] != 0){
            cout << interpretation[i] << endl;
            i++;
        }

        delete[] interpretation;
    }
    dpll.deleteAllMask();
    cnf_file.close();
    return 0;
}
