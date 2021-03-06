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
    tk_login = 267,
    tk_logout = 268,
    tk_size = 269,
    tk_fit = 270,
    tk_unit = 271,
    tk_path = 272,
    tk_type = 273,
    tk_delete = 274,
    tk_name = 275,
    tk_add = 276,
    tk_id = 277,
    tk_fs = 278,
    tk_usuario = 279,
    tk_password = 280,
    tk_ruta = 281,
    tk_numero = 282,
    tk_identificador = 283,
    tk_cadena = 284,
    tk_clave = 285,
    tk_kilo = 286,
    tk_mega = 287,
    tk_bf = 288,
    tk_ff = 289,
    tk_wf = 290,
    tk_archivo = 291,
    tk_byte = 292,
    tk_primaria = 293,
    tk_extendida = 294,
    tk_logica = 295,
    tk_fast = 296,
    tk_full = 297,
    tk_2fs = 298,
    tk_3fs = 299,
    tk_mbr = 300,
    tk_disk = 301
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 44 "parser.y"


  char TEXT [256];
  class Nodo_arbol *tipo_nodo;


#line 111 "parser.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
