//
// Created by abraham on 19/08/21.
//

#include "../../Header/Script/Pause.h"

void Pause::pause(){
    Controlador::print("Presione Enter para Continuar...");
    cin.get();
}