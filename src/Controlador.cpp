//
// Created by abraham on 8/08/21.
//
#include "../Header/Controlador.h"

Controlador* Controlador::instance = 0;

Controlador *Controlador::getInstance() {
    if(instance == 0){
        instance = new Controlador();
    }
    return instance;
}

Controlador::Controlador(){
    this->id_disco = 0;
}

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
        return;
    }else if(root->tipo == "PAUSE"){
        Pause::pause();
        return;
    }else if(root->tipo == "MOUNT"){
        getInstance()->execute_mount(root);
        return;
    }else if(root->tipo == "UMOUNT"){
        getInstance()->execute_umount(root);
        return;
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

//                                            MOUNT
void Controlador::execute_mount(Nodo *root) {
    list<Nodo>:: iterator nodo_actual;
    nodo_actual = root->hijo.begin()->hijo.begin();
    int i=0;
    string _path, _name; bool flag_path = false, flag_name = false;
    while(i<root->hijo.begin()->contador){
        if(nodo_actual->tipo == "PATH" && !flag_path){
            _path = nodo_actual->valor;
            flag_path = true;
        }else if(nodo_actual->tipo == "NAME" && !flag_name){
            _name = nodo_actual->valor;
            flag_name = true;
        }else{
            Controlador::print("ERROR! PARAMETRO INCORRECTO. [-path|-name]");
        }
        i++;
        nodo_actual++;
    }
    if(verificar_mount(_name)){ return print("ERROR, YA EXISTE ESA PARTICIÓN MONTADA!!"); }
    FILE *file;
    file = fopen(_path.c_str(), "rb+");
    MBR mbr{};
    fseek(file, 0, SEEK_SET);
    fread(&mbr, sizeof(MBR), 1, file);
    int aux_i = -1;
    for(int i = 0; i < 4; i++){
        if(strcmp(mbr.mbr_particion[i].part_name,_name.c_str()) == 0 && (mbr.mbr_particion[i].part_status == '1')) { // strcmp, compara dos cadenas char, si son iguales retorna 0.
            return add("", _path, _name);
        }
        if(mbr.mbr_particion[i].part_type == 'e' && (mbr.mbr_particion[i].part_status == '1')){
            aux_i = i;
        }
    }

    if(aux_i != -1){
        EBR ebr{};
        fseek(file, mbr.mbr_particion[aux_i].part_start, SEEK_SET);
        fread(&ebr, sizeof(EBR), 1, file);
        while(ebr.part_next != -1){
            if(strcmp(ebr.part_name, _name.c_str())== 0 && ebr.part_status == '1'){
                return add("", _path, _name);
            }
            fseek(file, ebr.part_next, SEEK_SET);
            fread(&ebr, sizeof(EBR), 1, file);
        }
    }
}

void Controlador::add(string _identificador, string _path, string _name){
    if(!Controlador::getFile(_path)){
        return Controlador::print("NO EXISTE EL ARCHIVO!!");
    }
    int aux_id_disco = verificar_id(_path); // Aca Obtiene el contador o lo incrementa.
    _identificador = "37" + to_string(aux_id_disco) + verificar_abecedario(_path); // Aca concatena el carnet + contador + letra.

    MOUNT mount{};
    mount.identificador = _identificador;
    mount.path = _path;
    mount.name = _name;
    mount.id_disco = aux_id_disco;
    Controlador::list_mount.push_back(mount);
    mostrar();
}

int Controlador::verificar_id(string _path){
    list<MOUNT>:: iterator aux;
    for(aux = Controlador::list_mount.begin(); aux != Controlador::list_mount.end(); aux++){
        if(aux->path == _path) {
            return aux->id_disco;
        }
    }
    id_disco++;
    return id_disco;
}

char Controlador::verificar_abecedario(string _path) {
    list<MOUNT>:: iterator nodo;
    string temp_identificador;
    bool flag = false;
    int pos_letra;
    for(nodo = Controlador::list_mount.begin(); nodo != Controlador::list_mount.end(); nodo++){
        if(nodo->path == _path) {
            pos_letra = nodo->identificador.length() - 1;
            temp_identificador = nodo->identificador;
            flag = true;
        }
    }
    if(flag) {
        int i = 0;
        while (i < 26) {
            if (abecedario[i] == temp_identificador[pos_letra] && (i + 1) != 26) {
                return abecedario[i + 1];
            }
            i++;
        }
    }
    return abecedario[0];
}
bool Controlador::verificar_mount(string _name){
    list<MOUNT>:: iterator aux;
    for(aux = Controlador::list_mount.begin(); aux != Controlador::list_mount.end(); aux++){
        if(strcmp(aux->name.c_str(),_name.c_str())==0){
            return true;
        }
    }
    return false;
}

void Controlador::mostrar(){
    Controlador::print("------------------------ Particiones Montadas ------------------------");
    Controlador::print("Size: " + to_string(Controlador::list_mount.size()));
    list<MOUNT>:: iterator aux;
    for(aux = Controlador::list_mount.begin(); aux != Controlador::list_mount.end(); aux++){
        cout << aux->path << "|" << aux->name << "|" << aux->identificador << endl;
    }
    Controlador::print("----------------------------------------------------------------------");
}


void Controlador::execute_umount(Nodo *root){
    list<Nodo>:: iterator nodo;
    nodo = root->hijo.begin()->hijo.begin();
    int i = 0; bool flag_id = false; string _identificador;
    while(i<root->hijo.begin()->contador){
        if(nodo->tipo == "ID" && !flag_id){
            _identificador = nodo->valor;
            flag_id = true;
        }else {
            return print("ERROR DE PARAMETRO!!! SOLO ACEPTA [-id].");
        }
        nodo++;
        i++;
    }
    getInstance()->delete_umount(_identificador);
}

void Controlador::delete_umount(string _identificador){
    list<MOUNT>:: iterator aux;
    for(aux = Controlador::list_mount.begin(); aux != Controlador::list_mount.end(); aux++){
        if(aux->identificador == _identificador){
            Controlador::list_mount.erase(aux);
            print("Partición Desmontada...");
            break;
        }
    }

    mostrar();
}
