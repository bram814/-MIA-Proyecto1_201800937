//
// Created by abraham on 8/08/21.
//

#ifndef PROYECTO_CONTROLADOR_H
#define PROYECTO_CONTROLADOR_H
#include <iostream>
#include <cstdio>
#include <cstring>
#include <dirent.h>
#include "Nodo.h"
#include "../Analizador/parser.h"
#include "../Analizador/scanner.h"
#include "Administracion/Discos/Mkdisk.h"
#include "Administracion/Discos/Rmdisk.h"
#include "Administracion/Discos/Fdisk.h"
#include "Script/Exec.h"
#include "Script/Pause.h"
extern Nodo *root;
using namespace std;

class Controlador{
public:
    void execute();
    static void command(const string& input);
    static void execute_command(Nodo *root);
    static void clear();
    static bool getDir(string dir);
    static bool getFile(string dir);
    static void create_directorio(string dir);
    static void print(const string& msg);

    struct Particion{
        char part_status;
        char part_type;
        char part_fit;
        int part_start;
        int part_size;
        char part_name[16];
    };
    struct MBR{
        int mbr_tam;
        time_t mbr_fecha_creacion;
        int mbr_disk_asignature;
        char mbr_disk_fit;
        Particion mbr_particion[4];
    };
    struct EBR{
        char part_status;
        char part_fit;
        int part_start;
        int part_size;
        int part_next;
        char part_name[16];
    };
};



#endif //PROYECTO_CONTROLADOR_H
