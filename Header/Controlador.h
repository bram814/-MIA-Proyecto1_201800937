//
// Created by abraham on 8/08/21.
//

#ifndef PROYECTO_CONTROLADOR_H
#define PROYECTO_CONTROLADOR_H
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "Nodo.h"
#include "../Analizador/parser.h"
#include "../Analizador/scanner.h"
extern Nodo *root;
using namespace std;

class Controlador{
public:
    void execute();
    void clear();
    void execute_command(Nodo *root);
    void search_hijos(Nodo *root);
};

#endif //PROYECTO_CONTROLADOR_H
