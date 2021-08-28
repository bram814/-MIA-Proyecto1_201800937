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
private:
    Controlador();
    static Controlador* instance;
public:
    static Controlador* getInstance();
    void execute();
    int id_disco;
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
//    ------------------------------------------------------------------------------------------
//                                          MOUNT
    void execute_mount(Nodo *root);
    void add(string _identificador, string _path, string _name);
    int verificar_id(string _path);
    char verificar_abecedario(string _path);
    bool verificar_mount(string _name);
    void mostrar();
    struct MOUNT{
        string identificador;
        string path;
        string name;
        int id_disco;

    };
    list<MOUNT> list_mount;
    char abecedario[26] = {
            'a','b','c','d','e','f','g','h','i','j','k','l','m',
            'n','o','p','q','r','s','t','u','v','w','x','y','z'
    };

//                                          UMOUNT
    void execute_umount(Nodo *root);
    void delete_umount(string _identificador);

//    ------------------------------------------------------------------------------------------
};



#endif //PROYECTO_CONTROLADOR_H
