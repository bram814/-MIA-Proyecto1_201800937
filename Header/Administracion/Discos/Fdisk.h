//
// Created by abraham on 16/08/21.
//

#ifndef PROYECTO_FDISK_H
#define PROYECTO_FDISK_H
#include "../../Controlador.h"
class Fdisk{
public:

    struct FDISK{
        int part_size       = 0;
        string part_path    = "-";
        string part_name    = "-";
        char part_u         = 'k';
        char part_type      = 'p';
        char part_f         = 'w';
        string part_delete  = "-";
        int part_add        = 0;

    };
    static void execute_fdisk(Nodo *root);
    static void primary(FDISK *fdisk);
    static void extend(FDISK *fdisk);
    static void logic(FDISK *fdisk);
    static void part_delete(FDISK *fdisk);




};
#endif //PROYECTO_FDISK_H
