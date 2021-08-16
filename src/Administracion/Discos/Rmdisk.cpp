//
// Created by abraham on 16/08/21.
//

#include "../../../Header/Administracion/Discos/Rmdisk.h"

void Rmdisk::execute_rmdisk(Nodo *root){
    list<Nodo> :: iterator nodo_actual;
    nodo_actual = root->hijo.begin()->hijo.begin();
    int i=0;
    string path;
    while(i<root->hijo.begin()->contador){
        if(nodo_actual->tipo == "PATH"){
            path = nodo_actual->valor;
        }else{ return Controlador::print("Error de Parametro("+nodo_actual->tipo+")"); }
        nodo_actual++;
        i++;
    }
    string input;
    char root_file[path.length()+1]; // se crea un array de char.
    strcpy(root_file, path.c_str()); // se convierte la ruta a char, por qué "remove" solo acepta char.
    if(Controlador::getFile(path)){
        Controlador::print("¿Quiere eliminar el Archivo? [s/n}");
        getline(cin, input);
        if(input == "s" || input == "S"){
            if(remove(root_file)!=0) return Controlador::print("ERROR PARA ELIMINAR EL DISCO!!");
            return Controlador::print("DISCO ELIMINADO!!");
        }else{
            return Controlador::print("NO SE ELIMINO EL DISCO!!");
        }
    }
    return Controlador::print("NO EXISTE EL ARCHIVO!!");
}