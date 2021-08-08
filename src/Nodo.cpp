//
// Created by abraham on 8/08/21.
//

#include "../Header/Nodo.h"

Nodo::Nodo(string tipo, char valor[]) {
    this->tipo = tipo;
    this->valor = valor;
    if (this->valor[0] == '"') {
        string aux;
        for (int i = 0; i < this->valor.size(); i++) {
            if (this->valor[i] != '"') {
                aux += this->valor[i];
            }
        }
        this->valor = aux;
    }
    this->contador = 0;
}


void Nodo::add(Nodo nodo_nuevo) {
    this->hijo.push_back(nodo_nuevo);
    this->contador += 1;

}