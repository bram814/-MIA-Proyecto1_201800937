//
// Created by abraham on 28/08/21.
//

#include "../../Header//Reporte/Reporte.h"
//Reporte* Reporte::instance=0;
//
//Reporte* Reporte::getInstanceRep() {
//    if(instance==0){
//        instance = new Reporte();
//    }
//    return instance;
//}


void Reporte::execute_rep(Nodo *root) {
    list<Nodo>:: iterator nodo;
    nodo = root->hijo.begin()->hijo.begin();
    int i = 0;
    string _id, _path, _name;
    bool flag_id = false, flag_path = false, flag_name = false;
    while(i<root->hijo.begin()->contador){
        if(nodo->tipo == "ID" && !flag_id){
            _id = nodo->valor;
            flag_id = true;
        }else if(nodo->tipo == "PATH" && !flag_path){
            _path = nodo->valor;
            flag_path = true;
        }else if(nodo->tipo == "NAME" && !flag_name){
            _name = nodo->valor;
            flag_name = true;
        }else{
            return Controlador::getInstance()->print("ERROR!!!  PARAMETRO INCORRECTO.");
        }
        i++;
        nodo++;
    }


    if(toLower(_name) == "mbr"){
        generate_mbr(Controlador::getInstance()->getPathMount(_id), _path);
    }else if(toLower(_name) == "disk"){
        generate_disk(Controlador::getInstance()->getPathMount(_id), _path);
    }

}
void Reporte::generate_mbr(string _disk_path, string _graph_path) {
    FILE *file;
    file = fopen(_disk_path.c_str(), "rb+");

    string nombre_disco = disk_name(_disk_path);

    Controlador::MBR mbr{};
    fseek(file,0,SEEK_SET);
    fread(&mbr, sizeof(Controlador::MBR), 1, file);

    string contenido = "digraph {\n"
                     "    \n"
                     " node[ shape = plaintext, fontname = \"Times New Roman\" ];\n"
                     " \n"
                     "    labelloc = \"t\"; \n"
                     "    label = \"Reporte\"; \n"
                     "    fontsize  = 25; \n"
                     "    fontcolor = \"#a12411\"; \n"
                     " \n"
                     " subgraph cluster_0 {\n"
                     "     \n"
                     "    tbl [\n"
                     "    label = < \n"
                     "      <table cellspacing='0' CELLPADDING=\"5\">\n"
                     "          <tr><td bgcolor = \"#c9fa47\"> Nombre </td><td bgcolor = \"#c9fa47\">Valor</td></tr>\n"
                     "          <tr><td> mbr_tamaño </td><td> "          + to_string(mbr.mbr_tam)                   + " </td></tr>\n"
                     "          <tr><td> mbr_fecha_creación </td><td> "  + asctime(gmtime(&mbr.mbr_fecha_creacion)) + " </td></tr>\n"
                     "          <tr><td> mbr_disk_asignature </td><td> " + to_string(mbr.mbr_disk_asignature)       + " \t</td></tr>\n"
                     "          <tr><td> Disk_fit </td><td> "            + mbr.mbr_disk_fit                         + " </td></tr>\n"
                     "          \n";


    int aux_i = -1;
    for (int i = 0; i < 4; i++) {
        if(mbr.mbr_particion[i].part_status != '0'){
            contenido += ""
            "        <tr><td> part_status_" + to_string(i+1) + " </td><td> " + mbr.mbr_particion[i].part_status           + " </td></tr>\n"
            "        <tr><td> part_type_"   + to_string(i+1) + " </td><td> " + mbr.mbr_particion[i].part_type             + " </td></tr>\n"
            "        <tr><td> part_fit_"    + to_string(i+1) + " </td><td> " + mbr.mbr_particion[i].part_fit              + " </td></tr>\n"
            "        <tr><td> part_start_"  + to_string(i+1) + " </td><td> " + to_string(mbr.mbr_particion[i].part_start) + " </td></tr>\n"
            "        <tr><td> part_size_"   + to_string(i+1) + " </td><td> " + to_string(mbr.mbr_particion[i].part_size)  + " </td></tr>\n"
            "        <tr><td> part_name_"   + to_string(i+1) + " </td><td> " + mbr.mbr_particion[i].part_name             + " </td></tr>\n"
            "        \n";
        }
        if(mbr.mbr_particion[i].part_type == 'e'){
            aux_i = i;
        }
    }

    contenido += "      </table>\n"
               "        \n"
               "    >];\n"
               "    labelloc=\"t\";\n"
               "    label=\"MBR " + nombre_disco + " \";\n"
               "    fontsize  = 22;\n"
               "};\n"
               "\n";

    if(aux_i != -1){
        Controlador::EBR ebr{};
        fseek(file, mbr.mbr_particion[aux_i].part_start, SEEK_SET);
        fread(&ebr, sizeof(Controlador::EBR), 1, file);
        int cont = 1;
        while (ebr.part_next != -1) {
            if (ebr.part_status != '0') {
                contenido += "subgraph cluster_" + to_string(cont) + " {\n"
                           "    \n"
                           "  tbl" + to_string(cont) + " [\n"
                           "    label= < \n"
                           "      <table cellspacing='0' CELLPADDING=\"5\">\n"
                           "        <tr><td bgcolor=\"#c9fa47\"  >Nombre</td><td bgcolor=\"#c9fa47\">Valor</td></tr>\n"
                           "        <tr><td> part_status_" + to_string(cont) + " </td><td> " + ebr.part_status           + " </td></tr>\n"
                           "        <tr><td> part_fit_"    + to_string(cont) + " </td><td> " + ebr.part_fit              + " </td></tr>\n"
                           "        <tr><td> part_start_"  + to_string(cont) + " </td><td> " + to_string(ebr.part_start) + " </td></tr>\n"
                           "        <tr><td> part_size_"   + to_string(cont) + " </td><td> " + to_string(ebr.part_size)  + " </td></tr>\n"
                           "        <tr><td> part_next_"   + to_string(cont) + " </td><td> " + to_string(ebr.part_next)  + " </td></tr>\n"
                           "        <tr><td> part_name_"   + to_string(cont) + " </td><td> " + ebr.part_name             + " </td></tr>\n"
                           "        \n"
                           "      </table>\n"
                           "        \n"
                           "    >];\n"
                           "    labelloc=\"t\";\n"
                           "    label=\"EBR_" + to_string(cont) + "  \";\n"
                           "    fontsize  = 22;\n"
                           "}\n";

            }
            cont++;
            fseek(file, ebr.part_next, SEEK_SET);
            fread(&ebr, sizeof(Controlador::EBR), 1, file);
        }
        if (ebr.part_status != '0') {
            contenido +=  " subgraph cluster_" + to_string(cont) + " {\n"
                        " \n"
                        " \n"
                        " \n"
                        " tbl" + to_string(cont) + " [\n"
                        "       label= < \n"
                        "      <table cellspacing='0' CELLPADDING=\"5\">\n"
                        "        <tr><td bgcolor=\"#c9fa47\"  >Nombre</td><td bgcolor=\"#c9fa47\">Valor</td></tr>\n"
                        "        \n"
                        "        <tr><td> part_status_" + to_string(cont) + "</td><td>" + ebr.part_status           + " </td></tr>\n"
                        "        <tr><td> part_fit_"    + to_string(cont) + "</td><td>" + ebr.part_fit              + " </td></tr>\n"
                        "        <tr><td> part_start_"  + to_string(cont) + "</td><td>" + to_string(ebr.part_start) + " </td></tr>\n"
                        "        <tr><td> part_size_"   + to_string(cont) + "</td><td>" + to_string(ebr.part_size)  + " </td></tr>\n"
                        "        <tr><td> part_next_"   + to_string(cont) + "</td><td>" + to_string(ebr.part_next)  + " </td></tr>\n"
                        "        <tr><td> part_name_"   + to_string(cont) + "</td><td>" + ebr.part_name             + " </td></tr>\n"
                        "        \n"
                        "      </table>\n"
                        "        \n"
                        "    >];\n"
                        "    labelloc=\"t\";\n"
                        "    label=\"EBR_" + to_string(cont) + "\";\n" + "fontsize  = 22;\n"
                        "    }\n";

        }
    }
    fclose(file);
    contenido +=       "}";
    RepDot("Reporte_mbr.txt", _graph_path, contenido);

}

void Reporte::generate_disk(string _disk_path, string _graph_path) {
    FILE *file;
    file = fopen(_disk_path.c_str(), "rb+");
    Controlador::MBR mbr{};
    fseek(file,0,SEEK_SET);
    fread(&mbr, sizeof(Controlador::MBR), 1, file);

    string contenido = "digraph structs {\n"
                     "    rankdir=LR\n"
                     "    node [shape=plaintext]\n"
                     "    \n"
                     
                     "    Bar [label=<\n"
                     "    <table border=\"2\" cellborder=\"1\" cellspacing=\"5\" cellpadding=\"5\">\n"
                     "      <tr>\n"
                     "          <td rowspan=\"3\" width=\"10\">MBR</td>\n"
                     "  \n";                                                                                                                                                                                                                                                                                                                       "        \n";

    int aux_i = -1;
    for (int i = 0; i < 4; i++) {
        if(mbr.mbr_particion[i].part_status != '0'){
            if(mbr.mbr_particion[i].part_type != 'e'){
                double porcentaje= 0;
                porcentaje = mbr.mbr_particion[i].part_size*100/mbr.mbr_tam;
                contenido += "    <td rowspan=\"3\" width=\"10\">Primaria " + to_string(trunc(porcentaje)) + "%</td>\n";
            }
        }
        if(mbr.mbr_particion[i].part_type == 'e'){
            contenido += "    <td colspan=\"20\" width=\"10\"> Extendida </td>\n";
            aux_i = i;
        }
    }

    contenido += "      </tr>\n";

    int contador = 1;
    if(aux_i != -1){
        Controlador::EBR ebr;
        double porcentaje = 0;
        fseek(file, mbr.mbr_particion[aux_i].part_start, SEEK_SET);
        fread(&ebr, sizeof(Controlador::EBR), 1, file);
        contenido += "  \n"
                   "  <tr>\n";
        while(ebr.part_next != -1){
            porcentaje = ebr.part_size*100/mbr.mbr_tam;
            contenido += "    <td > EBR| Lógica " + to_string(porcentaje) + "%</td>\n"
                                                                          "  \n";
            contador++;
            fseek(file, ebr.part_next, SEEK_SET);
            fread(&ebr, sizeof(Controlador::EBR), 1, file);
        }

        porcentaje = ebr.part_size*100/mbr.mbr_tam;
        contenido += "    <td> EBR| Lógica " + to_string(porcentaje) + "%</td>\n"
                   "  </tr>\n"
                   "  \n";

    }
    contenido += "\n"
               "</table>>];\n"
               "}";
    fclose(file);
    RepDot("Reporte_disk.txt", _graph_path, contenido);
}


void Reporte::RepDot(string _name, string _path, string _contenido){
    string directory;

    const size_t last_slash = _path.rfind('/');
    if(string::npos != last_slash){
        directory = _path.substr(0, last_slash) + "/";
    }

    string cmd = "sudo mkdir -p '" + directory + "'";
    system(cmd.c_str());
    cmd = "sudo chmod -R 777 '" + directory + "'";
    system(cmd.c_str());

    _name = directory + "/" + _name;

    ofstream file;
    file.open(_name, ios_base::out | ios_base::trunc);
    if(file.is_open()){
        file << _contenido;
        file.close();
    }

    cmd = "dot " + extension_path(_path) + " " + _name + " -o " + _path;
    system(cmd.c_str());
    cout << "\n REPORTE MBR GENERADO! \n" << endl;
}

string Reporte::toLower(string _cadena) {
    for (int i = 0; i < _cadena.length(); i++) _cadena[i] = tolower(_cadena[i]);
    return _cadena;
}

string Reporte::disk_name(string _path) {
    string nombre_disco;
    const size_t last_slash = _path.rfind('/');
    if(string::npos != last_slash){
        nombre_disco = _path.substr(last_slash+1,_path.length()-1);
    }
    return nombre_disco;
}

string Reporte::extension_path(string _path) {
    string extension_path = _path.substr(_path.find(".")+1, _path.size());
    if(extension_path == "pdf"){
        return "-Tpdf";
    }else if(extension_path == "jpg"){
        return "-Tjpg";
    }else if(extension_path == "png"){
        return "-Tpng";
    }
    return "-Tpng";
}