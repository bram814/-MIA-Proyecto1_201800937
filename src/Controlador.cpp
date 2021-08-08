//
// Created by abraham on 8/08/21.
//
#include "../Header/Controlador.h"

void Controlador::execute() {
    string input;
    while(true){
        cout << "Ingrese un COMANDO: " << endl;
        cout << "~$ ";
        getline(cin, input);
        if(input == "exit"){
            break;
        }else if(input == "clear"){
            this->clear();
        }
        cout << input.c_str() << endl;
        YY_BUFFER_STATE buffer = yy_scan_string(input.c_str());
        if(yyparse()==0){
            execute_command(root);
        }
        yy_delete_buffer(buffer);


    }
}

void Controlador::execute_command(Nodo *root) {
    if(root->tipo == "MKDISK"){
        cout << "entro" << endl;
    }
}


void Controlador::clear() {
    string command = "clear";
    system(command.c_str());
}