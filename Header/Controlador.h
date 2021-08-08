//
// Created by abraham on 8/08/21.
//

#ifndef PROYECTO_CONTROLADOR_H
#define PROYECTO_CONTROLADOR_H
#include <iostream>
#include "Nodo.h"
#include "../Analizador/parser.h"
#include "../Analizador/scanner.h"
extern Nodo *root;
using namespace std;

class Controlador{
public:
    void execute_command(Nodo *root);
    void execute();
    void clear();

};

#endif //PROYECTO_CONTROLADOR_H
