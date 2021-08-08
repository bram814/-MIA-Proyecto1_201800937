//
// Created by abraham on 8/08/21.
//

#ifndef PROYECTO_NODO_H
#define PROYECTO_NODO_H

#include <iostream>
#include <list>
using namespace std;

class Nodo{
public:
    Nodo(string tipo, char valor[]);
    void add(Nodo nodo_nuevo);
    string tipo;
    string valor;
    int contador;
    list<Nodo> hijo;

};
#endif //PROYECTO_NODO_H
