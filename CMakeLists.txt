cmake_minimum_required(VERSION 3.20)
project(PROYECTO)

set(CMAKE_CXX_STANDARD 14)

add_executable(PROYECTO
        Analizador/lexico.l
        Analizador/parser.cpp
        Analizador/parser.h
        Analizador/parser.y
        Analizador/scanner.cpp
        Analizador/scanner.h
        main.cpp src/Nodo.cpp Header/Nodo.h Header/Controlador.h src/Controlador.cpp Header/Administracion/Mkdisk.h src/Administracion/Mkdisk.cpp)
