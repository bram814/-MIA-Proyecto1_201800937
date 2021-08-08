%option case-insensitive
%option yylineno

%{
#include <iostream>
#include "parser.h"
Nodo *root;
#include <string>
%}

%option noyywrap
%option nounput




/* EXPRESION_REGULAR */
t_entero ("-")?[0-9]+
t_letra1 ([a-zA-Z_])[a-zA-Z0-9_]*
t_letra2 ([a-zA-Z_]*)[a-zA-Z0-9_]*

t_identificador1 ("/"{t_letra1})+("/"{t_letra1}"."{t_letra1})
t_identificador2 ("/"{t_letra1})+("/"{t_letra1})

/*t_caracter "\'"("\\")?({t_letra1}|{t_entero})"\'"*/
t_cadena [\"][^\"\n]*[\"\n]


/*%x COM*/

%%

"." {return punto;}
"<" {return menorque;}
">" {return mayorque;}
"[" {return corchetea;}
"]" {return corchetec;}
";" {return puntocoma;}
"^" {return potencia;}
"," {return coma;}
"(" {return parentesisa;}
")" {return parentesisc;}
"{" {return llavea;}
"}" {return llavec;}
"+" {return mas;}
"-" {return menos;}
"*" {return por;}
"=" {return igual;}
"$" {return dolar;}
":" {return dospuntos;}

"size" {return size;}
"mkdisk" {return mkdisk;}


{t_entero}         {strcpy(yylval.TEXT, yytext); return t_entero;}
{t_letra1}         {strcpy(yylval.TEXT, yytext); return t_letra1;}
{t_letra2}         {strcpy(yylval.TEXT, yytext); return t_letra2;}
{t_identificador1} {strcpy(yylval.TEXT, yytext); return t_identificador1;}
{t_identificador2} {strcpy(yylval.TEXT, yytext); return t_identificador2;}
{t_cadena}         {strcpy(yylval.TEXT, yytext); return t_cadena;}
(\s|\r|\t|\n)+     {}

[[:blank:]]     {}
.               {
                    if(yytext != "\r"){
                        std::cout << "Error : " << yytext << std::endl;
                    }
                }
%%