//
// Created by abraham on 8/08/21.
//

#ifndef PROYECTO_NODO_H
#define PROYECTO_NODO_H

#include <iostream>
#include <list>
#include <stdio.h>
#include <cstdlib>
#include <fstream>
/*
    CLASE LIST :: #include <list>
    *******************************************
    push_back() -> Agrega.
    pop_back() -> Elimina.
    begin() -> Inidio de la lista.
    end() -> Final de la lista.
    size() -> Tamaño de la lista.
    empty() -> Verifica si esta vacia la lista.
    *******************************************
    iterator -> Es un puntero de la lista.

 */
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
