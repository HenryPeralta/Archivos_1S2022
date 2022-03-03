%option case-insensitive
%option yylineno

%{
#include <cstdlib>
#include "parser.h"
#include <QString>
#include <stdio.h>
#include <iostream>
#include "qlist.h"

Nodo_arbol *raiz;

int yylex();
void yyerror(const char *s);
int linea=0; // Para contar lineas
int columna = 1; // para las columnas
int anterior = 0;
%}
%option noyywrap
%option nounput

DIGITOS "-"?[0-9]
NUMERO {DIGITOS}+


LETRAS [a-zA-Z]

IDENTIFICADOR {LETRAS}({LETRAS}|{DIGITOS}|"_")*


RUTA  "/"[^("\n"|"\t"|"\r"|"\f"|" "|"%"|"&")]*
ARCHIVO ({IDENTIFICADOR}"."{IDENTIFICADOR})

%%

INITIAL
{
["\""][^"\""]*["\""]     {strcpy(yylval.TEXT, yytext); return tk_cadena;}
["#"][^"\n"]*    { }
"bf" 	{   columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return tk_bf; }
"ff" 	{   columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return tk_ff; }
"wf" 	{   columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return tk_wf; }
"k" 	{   columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return tk_kilo; }
"m" 	{   columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return tk_mega; }

"mkdisk" 	{   columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return tk_mkdisk; }
"rmdisk" 	{   columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return tk_rmdisk; }

"-size" 	{   columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return tk_size; }
"-fit"      {   columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return tk_fit; }
"-unit" 	{   columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return tk_unit; }
"-path" 	{   columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return tk_path; }

"=" 	{   columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return tk_igual; }

{ARCHIVO} {   columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return tk_archivo; }
{RUTA}      {strcpy(yylval.TEXT, yytext); return tk_ruta;}
{NUMERO}    {   columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return tk_numero; }
{IDENTIFICADOR} {   columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return tk_identificador; }


[[:blank:]]     { columna++; }
"\n"            {linea++; columna = 0; anterior = 0;}
[\t\r\f] {}

.         {
             columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);
             std::cout <<yytext<<" Error Lexico en la linea "<< linea << " Columna:"<< columna<<  std::endl;
          }
}
%%

