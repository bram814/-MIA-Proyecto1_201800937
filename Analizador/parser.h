/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    t_entero = 258,
    t_letra1 = 259,
    t_letra2 = 260,
    t_root1 = 261,
    t_root2 = 262,
    t_cadena = 263,
    punto = 264,
    menorque = 265,
    mayorque = 266,
    corchetea = 267,
    corchetec = 268,
    puntocoma = 269,
    potencia = 270,
    coma = 271,
    parentesisa = 272,
    parentesisc = 273,
    llavea = 274,
    llavec = 275,
    mas = 276,
    menos = 277,
    por = 278,
    igual = 279,
    dolar = 280,
    dospuntos = 281,
    mkdisk = 282,
    exec = 283,
    rmdisk = 284,
    fdisk = 285,
    t_pause = 286,
    mount = 287,
    umount = 288,
    size = 289,
    path = 290,
    u = 291,
    k = 292,
    m = 293,
    b = 294,
    f = 295,
    bf = 296,
    ff = 297,
    wf = 298,
    type = 299,
    p = 300,
    e = 301,
    l = 302,
    t_delete = 303,
    fast = 304,
    full = 305,
    add = 306,
    t_name = 307,
    id = 308,
    suma = 309,
    multi = 310,
    division = 311
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 21 "parser.y"

char              TEXT[256];
class Nodo        *node;

#line 119 "parser.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
