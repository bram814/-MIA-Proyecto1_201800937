//
// Created by abraham on 8/08/21.
//
#include "../Header/Controlador.h"
//#include <stdio.h>
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
        YY_BUFFER_STATE buffer = yy_scan_string(input.c_str());
        if(yyparse()==0){
            execute_command(root);
        }
        yy_delete_buffer(buffer);


    }
}

void Controlador::execute_command(Nodo *root) {
    if(root->tipo == "MKDISK"){
        this->search_hijos(root);
    }
}


void Controlador::clear() {
    string command = "clear";
    system(command.c_str());
}

void Controlador::search_hijos(Nodo *root) {
    list<Nodo>:: iterator pos;
    pos = root->hijo.begin()->hijo.begin();
//    cout << "Tipo: " << root->hijo.begin()->tipo << endl;
//    cout << "Valor: " << root->hijo.begin()->valor << endl;
//    cout << "Contador: " << root->hijo.begin()->contador << endl;
    int i = 0, sizeDK;
    string dirDK;
    while(i<root->hijo.begin()->contador){
        if(pos->tipo == "SIZE"){
            cout << pos->tipo << ": " << pos->valor << endl;
            sizeDK = atoi(pos->valor.c_str());
        }else if(pos->tipo == "PATH"){
            cout << pos->tipo << ": " << pos->valor << endl;
            dirDK = pos->valor;
        }
        pos++;
        i++;
    }

    FILE *ptr_file;
    ptr_file = fopen(dirDK.c_str(), "ab");
    if(ptr_file==NULL){
        exit(1);
    }
    char buffer[1024];

    int x = 1000;
    fwrite(&x, sizeof(int), 1, ptr_file);
    cout << "SE HA CREADO EL ARCHIVO" << endl;
    fclose(ptr_file);
}