#include <iostream>
#define DEPTH 5

using namespace std;

class Node{
private:
    Node *parent;
    Node *child;
    int value;
    bool pass = true;
    int id;

public:
    Node(Node *parent, Node *child, int value, int id) : parent(parent), child(child), value(value), id(id) {}

    ~Node(){
        cout << "deleting: " << value << endl;
    }

    int getValue(){
        return value;
    }

    Node *getParent(){
        return parent;
    }

    Node *getChild(){
        return child;
    }

    bool getPass(){
        return pass;
    }

    int getId(){
        return id;
    }

    void setParent(Node *parent){
        this->parent = parent;
    }

    void setPass(bool pass){
        this->pass = pass;
    }

    void setChild(Node *child){
        this->child = child;
    }

    void incValue(){
        this->value++;
    }
};

class Container{
private:
    bool *free_space_arr = new bool[DEPTH];
    Node **pointer_arr = new Node *[DEPTH];

public:
    Container(){
        for (int i = 0; i < DEPTH; i++){
            free_space_arr[i] = true;
        }
    }

    ~Container(){
        delete[] free_space_arr;
        free_space_arr = nullptr;
        delete[] pointer_arr;
        pointer_arr = nullptr;
    }

    void addElement(Node *node){
        for (int i = 0; i < DEPTH; i++){
            if (free_space_arr[i]){
                pointer_arr[i] = node;
                free_space_arr[i] = false;
                return;
            }
        }

        throw "no space in Container";
    }

    void deleteElement(Node *node){
        for (int i = 0; i < DEPTH; i++){
            if (pointer_arr[i] == node){
                pointer_arr[i] = nullptr;
                free_space_arr[i] = true;
                return;
            }
        }

        throw "no element found";
    }

    void deleteAllElement(){
        for (int i = 0; i < DEPTH; i++){
            delete pointer_arr[i];
        }
    }

    void printAllElement(){
        cout << "pointer arr:" << endl;
        for (int i = 0; i < DEPTH; i++){
            if (pointer_arr[i] == nullptr){
                cout << "0" << endl;
            } else {
                cout << pointer_arr[i]->getValue() << endl;
            }
        }
    }
};

Node &algorithm(Node &node, int depth, Container &cont){
    //cont.printAllElement();
    //cout << "depth: " << depth << endl;
    //cout << "id: " << node.getId() << endl;
    if (depth == 5){
        return node;
    }

    if (depth == 2){
        Node *newNode = new Node(&node, nullptr, node.getValue(), node.getId() + 1);
        node.setChild(newNode);
        cont.addElement(newNode);

        Node &result = algorithm(*newNode, ++depth, cont);

        while (!result.getPass()){
            
            Node *parent_pointer = result.getParent();

            for (int i = 0; i < 2; i++){
                parent_pointer = parent_pointer->getParent();
                cont.deleteElement(parent_pointer->getChild());
                delete parent_pointer->getChild();
            }

            result.setParent(parent_pointer);
            parent_pointer->setChild(&result);

            Node *newNode = new Node(&result, nullptr, result.getValue(), result.getId() + 1);
            result.setChild(newNode);
            cont.addElement(newNode);

            result = algorithm(*newNode, 3, cont);
        }

        return result;
    }

    if (depth == 4){
        node.incValue();
        if (node.getValue() < 4){
            node.setPass(false);
            return node;
        } else {
            node.setPass(true);
        }
    }

    Node *newNode = new Node(&node, nullptr, node.getValue(), node.getId() + 1);
    node.setChild(newNode);
    cont.addElement(newNode);

    return algorithm(*newNode, ++depth, cont);
}

int main(){
    Container *cont = new Container();
    Node *node = new Node(nullptr, nullptr, 1, 1);
    cont->addElement(node);
    Node &result = algorithm(*node, 1, *cont);
    cont->printAllElement();
    //cout << "result value: " << result.getValue() << endl;

    cont->deleteAllElement();
    delete cont;
    return 0;
}