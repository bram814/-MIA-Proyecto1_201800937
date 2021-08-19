//
// Created by abraham on 8/08/21.
//
#include "../Header/Controlador.h"

//#include <stdio.h>
void Controlador::execute() { // Obtiene el comando en cadena.
    string input;
    while(true){
        cout << "Ingrese un Comando: " << endl;
        cout << ">> ";
        getline(cin, input);
        if(input == "exit"){
            break;
        }else if(input == "clear"){
            clear();
        }else{
            if(input.length()>1 && input[0]!='#'){
                command(input);
            }
        }
    }
}

void Controlador::command(const string& input) { // Ejecuta el analizador BISON.
    YY_BUFFER_STATE buffer = yy_scan_string(input.c_str());
    if(yyparse()==0){
        execute_command(root);
    }
    yy_delete_buffer(buffer);

}

void Controlador::execute_command(Nodo *root) { // Verifica el comando y lo ejecuta.
    string tipo = root->tipo;
    if(root->tipo == "MKDISK"){
        Mkdisk::create_mkdisk(root);
        return;
    }else if(root->tipo == "EXEC"){
        Exec::execute_exec(root);
        return;
    }else if(root->tipo == "RMDISK"){
        Rmdisk::execute_rmdisk(root);
        return;
    }else if(root->tipo == "FDISK"){
        Fdisk::execute_fdisk(root);
    }else if(root->tipo == "PAUSE"){
        Pause::pause();
    }

}

void Controlador::clear() { // Limpia la consola.
    string command = "clear";
    system(command.c_str());
}

bool Controlador::getDir(string dir){ // Verifica que un directorio exista.
    DIR *directorio = opendir(dir.c_str());
    if(directorio){
        closedir((directorio));
        print("EXISTE EL ARCHIVO!!");
        return true;
    }
    return false;
}

bool Controlador::getFile(string dir){ // Verifica que el archivo exista.
    FILE *archivo = fopen(dir.c_str(), "r");
        if(archivo){
            fclose(archivo);
            print("EXISTE EL ARCHIVO!!");
            return true;
        }
    return false;
}

void Controlador::create_directorio(string dir) { // Crea carpetas, si el directorio no Existe.
    string pathDirectorio;
    const size_t last_slash = dir.rfind('/'); // Obtained la ruta y si no existe crea las carpetas.
    if(string::npos != last_slash){
        pathDirectorio = dir.substr(0, last_slash) + "/";
    }
    string consola = "sudo mkdir -p '" + pathDirectorio + "'"; // Crea la Carpeta que no exista.
    system(consola.c_str());
    consola = "sudo chmod -R 777 '" + pathDirectorio + "'"; // Accede a los permisos del usuario.
    system(consola.c_str());
}

void Controlador::print(const string& msg){ cout << msg << endl; }