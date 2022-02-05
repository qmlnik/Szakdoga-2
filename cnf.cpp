#include "cnf.h"

using namespace std;

Cnf::Cnf(ifstream &input){
    arr_size = 0;
    string value;
    int start_position;

    while(getline(input, value)){
        if(value[0] == 'p'){
            if(value.substr(2, 3) != "cnf"){
                throw "Invalid input format";
            }
            string data_str = value.substr(6, value.length() - 6);
            size_t pos = data_str.find_first_of(" ");
            variable_num = stoi(data_str.substr(0, pos));
            pure_literal_arr = new sshort[variable_num];
            clause_num = stoi(data_str.substr(pos + 1, value.length() - pos + 1));
            start_position = input.tellg();
            break;
        }
    }

    while(getline(input, value, ' ')){
        if(value[0] == '0'){
            arr_size = arr_size + 2;
        } else {
            arr_size++;
        }
    }

    arr_size--;

    cnf_arr = new sshort[arr_size];

    input.clear();
    input.seekg(start_position, ios::beg);

    int i = 0;
    while(getline(input, value, ' ')){
        if(value[0] == '0'){
            cnf_arr[i] = 0;
            if(value.length() > 2){
                i++;
                cnf_arr[i] = stoi(value.substr(2, value.length() - 6));
            }
        } else {
            cnf_arr[i] = stoi(value);
        }
        i++;
    }
}

Cnf::~Cnf(){
    delete[] cnf_arr;
    cnf_arr = nullptr;
    delete[] pure_literal_arr;
    pure_literal_arr = nullptr;
}

void Cnf::printCnf(){
    for(int i = 0; i < arr_size; i++){
        cout << cnf_arr[i];
        if(cnf_arr[i] == 0){
            cout << endl;
        } else {
            cout << ", ";
        }
    }
}

int Cnf::getClauseEndPosition(int start_pos) const{
    int end_pos = 0;

    while(cnf_arr[start_pos + end_pos + 1] != 0){
        end_pos++;
    }

    return start_pos + end_pos;
}


