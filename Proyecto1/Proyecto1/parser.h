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
    tk_igual = 258,
    tk_mkdisk = 259,
    tk_rmdisk = 260,
    tk_exec = 261,
    tk_fdisk = 262,
    tk_mount = 263,
    tk_unmount = 264,
    tk_mkfs = 265,
    tk_rep = 266,
    tk_size = 267,
    tk_fit = 268,
    tk_unit = 269,
    tk_path = 270,
    tk_type = 271,
    tk_delete = 272,
    tk_name = 273,
    tk_add = 274,
    tk_id = 275,
    tk_fs = 276,
    tk_ruta = 277,
    tk_numero = 278,
    tk_identificador = 279,
    tk_cadena = 280,
    tk_clave = 281,
    tk_kilo = 282,
    tk_mega = 283,
    tk_bf = 284,
    tk_ff = 285,
    tk_wf = 286,
    tk_archivo = 287,
    tk_byte = 288,
    tk_primaria = 289,
    tk_extendida = 290,
    tk_logica = 291,
    tk_fast = 292,
    tk_full = 293,
    tk_2fs = 294,
    tk_3fs = 295,
    tk_mbr = 296,
    tk_disk = 297
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 44 "parser.y"


  char TEXT [256];
  class Nodo_arbol *tipo_nodo;


#line 107 "parser.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
