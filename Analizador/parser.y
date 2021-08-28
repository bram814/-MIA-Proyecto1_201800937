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
%token <TEXT> t_root1
%token <TEXT> t_root2
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


// ----------------
%token<TEXT> mkdisk 		// COMANDO mkdisk
%token<TEXT> exec		// COMANDO exec
%token<TEXT> rmdisk		// COMANDO rmdisk
%token<TEXT> fdisk		// COMANDO fdisk
%token<TEXT> t_pause		// COMANDO pause
%token<TEXT> mount		// COMANDO mount
// ----------------
%token<TEXT> size		// PARAMETRO -size
%token<TEXT> path		// PARAMETRO -path
// ----------------
%token<TEXT> u			// PARAMETRO -u
%token<TEXT> k
%token<TEXT> m
%token<TEXT> b
// ----------------
%token<TEXT> f			// PARAMETRO -f
%token<TEXT> bf
%token<TEXT> ff
%token<TEXT> wf
// ----------------
%token<TEXT> type		// PARAMETRO -type
%token<TEXT> p
%token<TEXT> e
%token<TEXT> l
// ----------------
%token<TEXT> t_delete            // PARAMETRO -delete
%token<TEXT> fast
%token<TEXT> full
// ----------------
%token<TEXT> add               // PARAMETRO -add
// ----------------
%token<TEXT> t_name               // PARAMETRO -name



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
	: mkdisk COMANDOMKDISKS 	{ $$ = new Nodo("MKDISK", ""); $$->add(*$2); }
	| exec COMANDOMKDISKS		{ $$ = new Nodo("EXEC", ""); $$->add(*$2); }
	| rmdisk COMANDOMKDISKS		{ $$ = new Nodo("RMDISK", ""); $$->add(*$2); }
	| fdisk COMANDOMKDISKS		{ $$ = new Nodo("FDISK", ""); $$->add(*$2); }
	| mount COMANDOMKDISKS		{ $$ = new Nodo("MOUNT", ""); $$->add(*$2); }
	| t_pause				{ $$ = new Nodo("PAUSE", "");}
	;
// ADMINISTRACION DE DISCOS.
COMANDOMKDISKS
	: COMANDOMKDISKS COMANDOMKDISK	{ $$ = $1; $$->add(*$2); }
	| COMANDOMKDISK			{ $$ = new Nodo("PARAMETROS-MKDISK",""); $$->add(*$1);}
	;
COMANDOMKDISK
	: menos size igual t_entero 	{ $$ = new Nodo("SIZE", $4); 	}
	| menos path igual t_root1	{ $$ = new Nodo("PATH", $4); 	}
	| menos u igual k		{ $$ = new Nodo("U", "k"); 	}
	| menos u igual m		{ $$ = new Nodo("U", "m"); 	}
	| menos u igual b		{ $$ = new Nodo("U", "b"); 	}
	| menos f igual bf		{ $$ = new Nodo("F", "bf"); 	}
	| menos f igual ff		{ $$ = new Nodo("F", "ff"); 	}
	| menos f igual wf		{ $$ = new Nodo("F", "wf"); 	}
	| type igual p			{ $$ = new Nodo("TYPE", "p"); 	}
	| type igual e			{ $$ = new Nodo("TYPE", "e"); 	}
	| type igual l			{ $$ = new Nodo("TYPE", "l"); 	}
	| t_name igual t_cadena		{ $$ = new Nodo("NAME", $3);	}
	| t_name igual t_letra1		{ $$ = new Nodo("NAME", $3);	}
	| t_delete igual fast		{ $$ = new Nodo("DELETE", "fast");	}
	| t_delete igual full		{ $$ = new Nodo("DELETE", "full");	}
	| add igual t_entero		{ $$ = new Nodo("ADD", $3);	}
	;

