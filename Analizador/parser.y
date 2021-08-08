%{
#include <stdio.h>
#include <string>
#include "scanner.h"       // Aca se esta importando el header del Análisis Sintáctico.
#include "../Header/Nodo.h"


extern int yylineno;       // Linea    actual donde encuentra el parse (Análisis Léxico) ESTO LO MANEJA BISON.
extern int columna;        // Columna  actual donde encuentra el parse (Análisis Léxico) ESTO LO MANEJA BISON. 
extern char *yytext;       // Lexema   actual donde encuentra el parse (Análisis Léxico) ESTO LO MANEJA BISON.
extern Nodo *root;

int yyerror(const char* menssage){
   std::cout<< "Error: " << menssage << " " << yytext << std::endl;
   return 0;
}
%}

%define parse.error verbose

%union {
char              TEXT[256];
class Nodo        *node;
}


//TERMINALES DE TIPO TEXT, SON STRINGS

%token <TEXT> t_entero
%token <TEXT> t_letra1
%token <TEXT> t_letra2
%token <TEXT> t_identificador1
%token <TEXT> t_identificador2
%token <TEXT> t_cadena


%token<TEXT> punto
%token<TEXT> menorque
%token<TEXT> mayorque
%token<TEXT> corchetea
%token<TEXT> corchetec
%token<TEXT> puntocoma
%token<TEXT> potencia
%token<TEXT> coma
%token<TEXT> parentesisa
%token<TEXT> parentesisc
%token<TEXT> llavea
%token<TEXT> llavec
%token<TEXT> mas
%token<TEXT> menos
%token<TEXT> por
%token<TEXT> igual
%token<TEXT> dolar
%token<TEXT> dospuntos

%token<TEXT> size
%token<TEXT> mkdisk

// ACA SERAN TODOS LOS NO TERMINALES
%type<node> Start 		// INICIA
%type<node> COMANDO
%type<node> COMANDOMKDISKS 	// lista de instrucciones para PARAMETROS
%type<node> COMANDOMKDISK

%left suma menos
%left multi division
%left potencia


%start Start
%%

Start
	: COMANDO { root = $$; }
     	;

COMANDO
	:  mkdisk COMANDOMKDISKS 	{ $$ = new Nodo("MKDISK", ""); $$->add(*$2); }
	;

COMANDOMKDISKS
	: COMANDOMKDISKS COMANDOMKDISK	{ $$ = $1; $$->add(*$2); }
	| COMANDOMKDISK			{ $$ = new Nodo("PARAMETROS-MKDISK",""); $$->add(*$1);}
	;
COMANDOMKDISK
	: menos size igual t_entero 	{ $$ = new Nodo("SIZE", $4); }
	;

