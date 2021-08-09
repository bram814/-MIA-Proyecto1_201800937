# -MIA-Proyecto1_201800937

LABORATORIO MANEJO E IMPLEMENTACION DE ARCHIVOS Sección A-

###Comandos para instalar FLex y Bison 
1. sudo apt-get install flex

2. sudo apt-get install bison

###Comandos para generar el Analizador Léxico y Sintáctico 

Primero deben irse a la carpeta del proyecto donde tienen el archivo (.l) y (.y) de los Analizadores, abren una terminal desde esa ubicacion y utilizan los siguientes comandos para generar los analizadores.

####Analizador léxico
1. flex --header-file=scanner.h -o scanner.cpp lexico.l
####Analizador sintáctico
2. bison -o parser.cpp --defines=parser.h parser.y