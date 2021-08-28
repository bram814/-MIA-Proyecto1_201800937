//
// Created by abraham on 16/08/21.
//

#include "../../../Header/Administracion/Discos/Fdisk.h"

void Fdisk::execute_fdisk(Nodo *root){
    list<Nodo> :: iterator nodo_actual;
    nodo_actual = root->hijo.begin()->hijo.begin();
    int i=0;
    FDISK fdisk{};
    bool flag_size = false , flag_path = false, flag_name = false; // OBLIGATORIO.
    bool flag_u = false, flag_type = false, flag_f = false, flag_delete = false, flag_add = false; // OPCIONAL
    while(i<root->hijo.begin()->contador){
        if(nodo_actual->tipo == "SIZE" && !flag_size){
            fdisk.part_size = stoi(nodo_actual->valor); flag_size = true;
        }else if(nodo_actual->tipo == "PATH" && !flag_path){
            fdisk.part_path = nodo_actual->valor; flag_path = true;
        }else if(nodo_actual->tipo == "NAME" && !flag_name){
            fdisk.part_name = nodo_actual->valor; flag_name = true;
        }else{
            if(nodo_actual->tipo == "U" && !flag_u){
                if(nodo_actual->valor == "b"){      fdisk.part_u = 'b'; }
                else if(nodo_actual->valor == "k"){ fdisk.part_u = 'k'; }
                else if(nodo_actual->valor == "m"){ fdisk.part_u = 'm'; }
                else{ return Controlador::print("Error de -u (" + nodo_actual->valor + ") -u = [b,k,m]"); }
                flag_u = true;
            }else if(nodo_actual->tipo == "TYPE" && !flag_type){
                if(nodo_actual->valor == "p"){       fdisk.part_type = 'p'; }
                else if(nodo_actual->valor == "e") { fdisk.part_type = 'e'; }
                else if(nodo_actual->valor == "l") { fdisk.part_type = 'l'; }
                else{ return Controlador::print("Error de -type (" + nodo_actual->valor + ") -type = [p,e,l]"); }
                flag_type = true;
            }else if(nodo_actual->tipo == "F" && !flag_f){
                if(nodo_actual->valor == "bf"){       fdisk.part_f = 'b'; }
                else if(nodo_actual->valor == "ff") { fdisk.part_f = 'f'; }
                else if(nodo_actual->valor == "wf") { fdisk.part_f = 'w'; }
                else{ return Controlador::print("Error de -f (" + nodo_actual->valor + ") -f = [bf,ff,wf]"); }
                flag_f = true;
            }else if(nodo_actual->tipo == "DELETE" && !flag_delete){
                if(nodo_actual->valor == "fast"){ fdisk.part_delete = "fast"; }
                else if(nodo_actual->valor == "full"){ fdisk.part_delete = "full"; }
                else{ return Controlador::print("Error de delete (" + nodo_actual->valor + ") delete = [fast,full]"); }
                flag_delete = true;
            }else if(nodo_actual->tipo == "ADD" && !flag_add){
                fdisk.part_add = stoi(nodo_actual->valor);
                flag_add = true;
            }else{
                return Controlador::print("Error de parametro (" + nodo_actual->tipo + ")");
            }
        }
        i++;
        nodo_actual++;
    }

    if(flag_size && flag_path && flag_name){
        if (!flag_delete && flag_add || (flag_delete && !flag_add) || (!flag_delete && !flag_add)){
            if(!Controlador::getFile(fdisk.part_path)){
                return Controlador::print("NO EXISTE EL DISCO!");
            }

            if(fdisk.part_u == 'm'){ fdisk.part_size = fdisk.part_size*1024*1024; }         // convierte a MEGABYTES.
            else if(fdisk.part_u == 'k'){ fdisk.part_size = fdisk.part_size*1024; }         // convierte a KILOBYTES.
            else if(fdisk.part_u == 'b'){ fdisk.part_size = fdisk.part_size; }              // convierte a BYTES.
            else{ return Controlador::print("Error de parametro -u"); }

            if(fdisk.part_type == 'p'){             // PRIMARIA
                primary(&fdisk);
            }else if(fdisk.part_type == 'e'){       // EXTENDIDA
                extend(&fdisk);
            }else if(fdisk.part_type == 'l'){       // LOGICA
                logic(&fdisk);
            }

        }else{
            return Controlador::print("ERROR, NO PUEDEN VENIR JUNTOS (DELETE Y ADD)!!!");
        }
    }else{
        if(flag_path && flag_name){
            if(flag_delete && !flag_add){
                part_delete(&fdisk);
            }else{
                return Controlador::print("ERROR, NO PUEDEN VENIR JUNTOS ADD Y DELETE.");
            }
        }else{
            return Controlador::print("ERROR, FALTA PARAMETRO [SIZE,PATH,NAME]!!");
        }
    }
}

void Fdisk::primary(FDISK *fdisk){
    FILE *file;
    file = fopen(fdisk->part_path.c_str(), "rb+");
    Controlador::MBR mbr{};
    fseek(file,0,SEEK_SET);
    fread(&mbr, sizeof(Controlador::MBR), 1, file);

    int part_tam_ocupado = 0, part_cant = 0;
    for(int i = 0; i < 4; i++){
        if(strcmp(mbr.mbr_particion[i].part_name,fdisk->part_name.c_str()) == 0){ // strcmp, compara dos cadenas char, si son iguales retorna 0.
            return Controlador::print("ERROR, YA EXISTE ESE NOMBRE!!!");
        }else if(mbr.mbr_particion[i].part_status == '1'){
            part_cant += 1;
            part_tam_ocupado += mbr.mbr_particion[i].part_size;
        }
    }

    if((mbr.mbr_tam - part_tam_ocupado) < fdisk->part_size){
        return Controlador::print("SE EXCEDIO DEL TAMAÑO EL DISCO!!");
    }
    if(part_cant == 4){ return Controlador::print("INSUFICIENTE ESPACIO, NO SE PUEDE EXCEDER MAS DE 4 PARTICIONES."); }

    for(int i=0; i<4; i++){
        if(mbr.mbr_particion[i].part_status == '0'){
            mbr.mbr_particion[i].part_status = '1';
            mbr.mbr_particion[i].part_type = fdisk->part_type;
            mbr.mbr_particion[i].part_fit = fdisk->part_f;
            mbr.mbr_particion[i].part_size = fdisk->part_size;
            if(i==0){
                mbr.mbr_particion[i].part_start = sizeof(Controlador::MBR);
            }else{
                mbr.mbr_particion[i].part_start = mbr.mbr_particion[i-1].part_start + mbr.mbr_particion[i-1].part_size;
            }
            strcpy(mbr.mbr_particion[i].part_name, fdisk->part_name.c_str());
            fseek(file, 0, SEEK_SET);
            fwrite(&mbr,sizeof(Controlador::MBR), 1, file);
            char buffer = '1';
            fseek(file, mbr.mbr_particion[i].part_start, SEEK_SET);
            for (int j = 0; j < mbr.mbr_particion[i].part_size; j++) {
                fwrite(&buffer, 1, 1, file);
            }

            break;
        }

    }
    Controlador::print("PARTICION PRIMARIA CREADA!!!");
    fclose(file);
}

void  Fdisk::extend(FDISK *fdisk){
    FILE *file;
    file = fopen(fdisk->part_path.c_str(), "rb+");
    Controlador::MBR mbr{};
    fseek(file,0,SEEK_SET);
    fread(&mbr, sizeof(Controlador::MBR), 1, file);

    int part_tam_ocupado = 0, part_cant = 0;
    for(int i = 0; i < 4; i++){
        if(mbr.mbr_particion[i].part_type == 'e'){
            return Controlador::print("YA EXISTE UNA PARTICION EXTENDIDA!!");
        }
    }

    for(int i = 0; i < 4; i++){
        if(strcmp(mbr.mbr_particion[i].part_name,fdisk->part_name.c_str()) == 0){
            return Controlador::print("ERROR, YA EXISTE ESE NOMBRE!!!");
        }else if(mbr.mbr_particion[i].part_status == '1'){
            part_cant += 1;
            part_tam_ocupado += mbr.mbr_particion[i].part_size;
        }
    }

    if((mbr.mbr_tam - part_tam_ocupado) < fdisk->part_size){
        return Controlador::print("SE EXCEDIO DEL TAMAÑO EL DISCO!!");
    }
    if(part_cant == 4){ return Controlador::print("INSUFICIENTE ESPACIO, NO SE PUEDE EXCEDER MAS DE 4 PARTICIONES."); }
    for(int i=0; i<4; i++){
        if(mbr.mbr_particion[i].part_status == '0'){
            //SE CREA LA PARTICION EXTENDIDA
            mbr.mbr_particion[i].part_status = '1';
            mbr.mbr_particion[i].part_type = fdisk->part_type;
            mbr.mbr_particion[i].part_fit = fdisk->part_f;
            mbr.mbr_particion[i].part_size = fdisk->part_size;
            if(i==0){
                mbr.mbr_particion[i].part_start = sizeof(Controlador::MBR);
            }else{
                mbr.mbr_particion[i].part_start = mbr.mbr_particion[i-1].part_start + mbr.mbr_particion[i-1].part_size;
            }
            strcpy(mbr.mbr_particion[i].part_name, fdisk->part_name.c_str());

            // SE CREA ESPACIO PARA LAS PARTICIONES LOGICAS EBR.
            Controlador::EBR ebr{};
            ebr.part_status = '0';
            ebr.part_fit = fdisk->part_f;
            ebr.part_start = mbr.mbr_particion[i].part_start;
            ebr.part_size = 0;
            ebr.part_next = -1;
            strcpy(ebr.part_name, fdisk->part_name.c_str());

            fseek(file, 0, SEEK_SET);
            fwrite(&mbr,sizeof(Controlador::MBR), 1, file);

            fseek(file, ebr.part_start, SEEK_SET);
            fwrite(&ebr, sizeof(Controlador::EBR), 1, file);
            char buffer = '1';
            for (int j = 0; j < ebr.part_size - (int) sizeof(Controlador::EBR); j++) {
                fwrite(&buffer, 1, 1, file);
            }

            break;
        }

    }
    fclose(file);
    Controlador::print("PARTICION EXTENDIDA CREADA!!!");

}

void Fdisk::logic(FDISK *fdisk){
    FILE *file;
    file = fopen(fdisk->part_path.c_str(), "rb+");
    Controlador::MBR mbr{};
    fseek(file,0,SEEK_SET);
    fread(&mbr, sizeof(Controlador::MBR), 1, file);

    int i_extendida=4, aux_size = 0;
    for(int i = 0; i < 4; i++){
        if(strcmp(mbr.mbr_particion[i].part_name, fdisk->part_name.c_str())==0){
            return Controlador::print("YA EXISTE ESE NOMBRE EN LA PARTICION PRIMARIA Os EXTENDIDA!!");
        }
    }
    for(int i = 0; i < 4; i++){
        if(mbr.mbr_particion[i].part_type == 'e'){
            i_extendida = i;
            break;
        }
    }

    if(i_extendida == 4){
        return Controlador::print("ERROR, NO SE PUEDE CREAR UNA PARTICION LOGICA, NO EXISTE PARTICION EXTENDIDA!!!");
    }

    Controlador::EBR ebr{};
    fseek(file, mbr.mbr_particion[i_extendida].part_start, SEEK_SET);
    fread(&ebr, sizeof(Controlador::EBR), 1, file);

    while(ebr.part_next != -1){
        if(strcmp(ebr.part_name, fdisk->part_name.c_str())==0){
            return Controlador::print("YA EXISTE ESE NOMBRE EN LA PARTICION LOGICA!!");
        }
        aux_size += ebr.part_size;
        fseek(file, ebr.part_next, SEEK_SET);
        fread(&ebr, sizeof(Controlador::EBR), 1, file);
    }
    if(mbr.mbr_particion[i_extendida].part_size < (aux_size+fdisk->part_size)){
        return Controlador::print("Error, excede el tamaño de la particion logica con la extendida.");
    }
    int aux_part_next;
    if(ebr.part_next == -1){
        aux_part_next = ebr.part_start + ebr.part_size;
        ebr.part_next = aux_part_next;
        fseek(file, ebr.part_start, SEEK_SET);
        fwrite(&ebr, sizeof(Controlador::EBR), 1, file);
    }

    Controlador::EBR aux_ebr{};
    aux_ebr.part_status = '1';
    aux_ebr.part_fit = fdisk->part_f;
    aux_ebr.part_start = ebr.part_next;
    aux_ebr.part_size = fdisk->part_size;
    aux_ebr.part_next = -1;
    strcpy(aux_ebr.part_name, fdisk->part_name.c_str());

    fseek(file, aux_ebr.part_start, SEEK_SET);
    fwrite(&aux_ebr, sizeof(Controlador::EBR), 1, file);
    char buffer = '1';
    for (int i = 0; i < (aux_ebr.part_size - (int) sizeof(Controlador::EBR)); i++) {
        fwrite(&buffer, 1, 1, file);
    }
    Controlador::print("PARTICION LOGICA CREADA!!!");
    fclose(file);
}


void Fdisk::part_delete(FDISK *fdisk){
    string input;
    while(true){
        Controlador::print("¿Desea eliminar la Particion? [S/N]");
        getline(cin,input);
        if(input == "s" || input == "S"){
            break;
        }else{
            return Controlador::print("No se Elimino la Particion.");
        }
    }
    FILE *file;
    file = fopen(fdisk->part_path.c_str(), "rb+");
    Controlador::MBR mbr{};
    fseek(file,0,SEEK_SET);
    fread(&mbr, sizeof(Controlador::MBR), 1, file);
    int temp_extendida = -1;
    for(int i=0; i<4; i++){

        if(strcmp(mbr.mbr_particion[i].part_name, fdisk->part_name.c_str())==0){
            mbr.mbr_particion[i].part_status = '0';

            fseek(file, 0, SEEK_SET);
            fwrite(&mbr, sizeof(Controlador::MBR), 1, file);

            if(fdisk->part_delete == "full"){
                char buffer = '\0';
                fseek(file, mbr.mbr_particion[i].part_start, SEEK_SET);
                for(int j=0; j<mbr.mbr_particion[i].part_size; j++){
                    fwrite(&buffer, 1, 1, file);
                    fseek(file, mbr.mbr_particion[i].part_start + j, SEEK_SET);
                }
            }

            if(mbr.mbr_particion[i].part_type == 'e'){ //Si es una particion Extendida, se empieza eliminar cada particion logica.
                temp_extendida = i;
                Controlador::EBR ebr{};
                fseek(file, mbr.mbr_particion[i].part_start, SEEK_SET);
                fread(&ebr, sizeof(Controlador::EBR), 1, file);

                while(ebr.part_next != -1){
                    ebr.part_status = '0';
                    fseek(file, ebr.part_start, SEEK_SET);
                    fwrite(&ebr, sizeof(Controlador::EBR), 1, file);

                    if(fdisk->part_delete == "full"){
                        char buffer = '\0';
                        for (int j = 0; j < ebr.part_size-(int) sizeof(Controlador::EBR); j++) {
                            fwrite(&buffer, 1,1, file);
                        }
                    }
                    fseek(file, ebr.part_next, SEEK_SET);
                    fread(&ebr, sizeof(Controlador::EBR), 1, file);

                }

                ebr.part_status = '0';
                fseek(file, ebr.part_start, SEEK_SET);
                fwrite(&ebr, sizeof(Controlador::EBR), 1, file);

                if(fdisk->part_delete == "full"){
                    char buffer = '\0';
                    for (int j = 0; j < ebr.part_size - (int) sizeof(Controlador::EBR); j++) {
                        fwrite(&buffer, 1, 1, file);
                    }
                }

            }

        break;

        }
    }

    // Si en dado caso no es una partición primaria ni extendida, debe de ser una lógica.
    if(temp_extendida != -1){
        Controlador::EBR ebr{};
        fseek(file, mbr.mbr_particion[temp_extendida].part_start, SEEK_SET);
        fread(&ebr, sizeof(Controlador::EBR), 1, file);
        while(ebr.part_next != -1){

            if(strcmp(ebr.part_name, fdisk->part_name.c_str()) == 0){
                ebr.part_status = '0';
                fseek(file, ebr.part_start, SEEK_SET);
                fwrite(&ebr, sizeof(Controlador::EBR), 1, file);

                if(fdisk->part_delete == "full"){
                    char buffer = '\0';
                    //fseek(file,auxEBR.part_start, SEEK_SET);
                    for (int j = 0; j < ebr.part_size-(int) sizeof(Controlador::EBR); j++) {
                        fwrite(&buffer, 1, 1, file);
                    }
                }
                break;
            }

            fseek(file, ebr.part_next, SEEK_SET);
            fread(&ebr, sizeof(Controlador::EBR), 1, file);
        }
    }
    Controlador::print("USO DE -delete CORRECTO.");
    fclose(file);

}