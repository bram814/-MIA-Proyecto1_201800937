//
// Created by abraham on 28/08/21.
//

#ifndef PROYECTO_REPORTE_H
#define PROYECTO_REPORTE_H
#include "../Controlador.h"
#include <cmath>
class Reporte{
private:
//    static Reporte *instance;
public:
//    static Reporte *getInstanceRep();
    static void execute_rep(Nodo *root);
//  ------------------------------- REPORTE -------------------------------
    static void generate_mbr(string _disk_path, string _graph_path);
    static void generate_disk(string _disk_path, string _graph_path);
//  -----------------------------------------------------------------------
    static string toLower(string _cadena);
    static string disk_name(string _path);
    static void RepDot(string _name, string _path, string _contenido);
    static string extension_path(string _path);

};

#endif //PROYECTO_REPORTE_H
