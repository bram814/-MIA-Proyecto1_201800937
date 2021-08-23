//
// Created by abraham on 8/08/21.
//
#include "Header/Controlador.h"


int main() {

    cout << ".__________________________________." << endl;
    cout << "|____________PROYECTO1_____________|" << endl;
    cout << "|__JOSE ABRAHAM SOLORZANO HERRERA__|" << endl;
    cout << "|____________201800937_____________|" << endl;
    cout << ".__________________________________." << endl;
    auto *instance = new Controlador();
    instance->execute();
    delete instance;
    return 0 ;
}