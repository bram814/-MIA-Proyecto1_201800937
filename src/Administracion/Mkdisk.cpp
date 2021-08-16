//
// Created by abraham on 8/08/21.
//

#include "../../Header/Administracion/Mkdisk.h"

void Mkdisk::create_mkdisk(Nodo *root) {

    list<Nodo>:: iterator pos;
    pos = root->hijo.begin()->hijo.begin();
    int i = 0, sizeDK;
    string dirDK;
    char uDK='k', fDK='f';
    //    print("CONTADOR: "+);
    cout << "contador: " << root->hijo.begin()->contador << endl;
    while(i<root->hijo.begin()->contador){
        if(pos->tipo == "SIZE"){
            cout << pos->tipo << ": " << pos->valor << endl;
            sizeDK = stoi(pos->valor);
            if(sizeDK<=0){
                return Controlador::print("Es menor a 0 -size.");
            }
        }else if(pos->tipo == "PATH"){
            cout << pos->tipo << ": " << pos->valor << endl;
            dirDK = pos->valor;
        }else if(pos->tipo == "U"){
            Controlador::print(pos->tipo);
            Controlador::print(pos->valor);
            if(pos->valor == "m"){
                uDK = 'm';
            }else if(pos->valor == "k"){
                uDK = 'k';
            }else{
                return Controlador::print("Dimension incorrecta: "+pos->valor);
            }
        } else if(pos->tipo == "F"){
            if(pos->valor == "bf"){
                fDK = 'b';
            }else if(pos->valor == "ff"){
                fDK = 'f';
            }else if(pos->valor == "wf"){
                fDK = 'w';
            }else{
                return Controlador::print("Parametro incorrecto, solo puede ser -f = (BF, FF, WF).");
            }
        }
        pos++;
        i++;
    }

    if(Controlador::getFile(dirDK)){
        return;
    }

    // --------------------------
    // CREANDO EL FICHERO BINARIO
    // --------------------------

    if(uDK == 'm') sizeDK = sizeDK*1024*1024; // convierte a MEGABYTES
    if(uDK == 'k') sizeDK = sizeDK*1024;      // convierte a KILOBYTES

    Controlador::MBR mbr;
    mbr.mbr_tam = sizeDK;
    mbr.mbr_fecha_creacion = time(0);
    mbr.mbr_disk_asignature = rand()%100;
    mbr.mbr_disk_fit = fDK;

    Controlador::Particion part;
    part.part_status = '0'; // 0 incactiva, 1 activa.
    part.part_type = '-';
    part.part_fit = '-';
    part.part_start = -1;
    part.part_name[0] = '0';
    for(int i=0; i<4; i++){
        mbr.mbr_particion[i] = part;
    }
    Controlador::create_directorio(dirDK);

    FILE *file;
    char buffer[1];
    file = fopen(dirDK.c_str(), "wb");
    for(int i=0; i < sizeDK; i++){
        fwrite(&buffer, sizeof (buffer), 1, file);
    }

    fseek(file, 0, SEEK_SET);
    fwrite(&mbr, sizeof (Controlador::MBR), 1, file);
    fclose(file);

}