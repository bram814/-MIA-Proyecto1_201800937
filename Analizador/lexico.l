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

t_root1 ("/"{t_letra1})+("/"{t_letra1}"."{t_letra1})
t_root2 ("/"{t_letra1})+("/"{t_letra1})

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



"mkdisk"    {return mkdisk;}            /* COMANDO mkdisk   */
"exec"      {return exec;}              /* COMANDO exec     */
"rmdisk"    {return rmdisk;}            /* COMANDO rmdisk   */
"fdisk"     {return fdisk;}             /* COMANDO fdisk    */
"pause"     {return t_pause;}           /* COMANDO pause    */
"mount"     {return mount;}             /* COMANDO mount    */
"umount"    {return umount;}            /* COMANDO umount   */
"size"      {return size;}
"path"      {return path;}
"u"         {return u;}                 /* PARAMETRO -u     */
"k"         {return k;}
"m"         {return m;}
"b"         {return b;}
"f"         {return f;}                 /* PARAMETRO -f     */
"bf"        {return bf;}
"ff"        {return ff;}
"wf"        {return wf;}
"-type"     {return type;}              /* PARAMETRO -type  */
"p"         {return p;}
"e"         {return e;}
"l"         {return l;}
"-delete"   {return t_delete;}          /* PARAMETRO -delete */
"fast"      {return fast;}
"full"      {return full;}
"-add"      {return add;}               /* PARAMETRO -add */
"-name"     {return t_name;}            /* PARAMETRO name */
"-id"       {return id;}                /* PARAMETRO -id  */
"\n" {}


{t_entero}         {strcpy(yylval.TEXT, yytext); return t_entero;}
{t_letra1}         {strcpy(yylval.TEXT, yytext); return t_letra1;}
{t_letra2}         {strcpy(yylval.TEXT, yytext); return t_letra2;}
{t_root1}          {strcpy(yylval.TEXT, yytext); return t_root1;}
{t_root2}          {strcpy(yylval.TEXT, yytext); return t_root2;}
{t_cadena}         {strcpy(yylval.TEXT, yytext); return t_cadena;}
(\s|\r|\t|\n)+     {}


[[:blank:]]     {}
.               {
                    if(yytext != "\r"){
                        std::cout << "Error : " << yytext << std::endl;
                    }
                }
%%