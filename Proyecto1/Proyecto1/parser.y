%{
/********************
  Declaraciones en C
**********************/
    #include "scanner.h"
    #include <stdio.h>
    #include <stdlib.h>
    #include <QString>
    #include <iostream>
    #include <string>
    #include <string.h>
    #include <cstring>
    #include <vector>
    //#include "lista_simple.h"
    #include "estructuras.h"
    #include "nodo_arbol.h"

    extern int yylineno; //linea actual donde se encuentra el parser (analisis lexico) lo maneja BISON
    extern int columna; //columna actual donde se encuentra el parser (analisis lexico) lo maneja BISON
    extern char *yytext; //lexema actual donde esta el parser (analisis lexico) lo maneja BISON

    extern Nodo_arbol *raiz; // Raiz del arbol

    //extern Lista_Simple *lista = new Lista_Simple(); // Raiz del arbol
    //extern int yylex(void);
    //extern char *yytext;
    //extern int linea;
    //extern FILE *yyin;
    //string expresion;
    //string cadena;
    using namespace std;

    void yyerror(char *s);
%}

/************************
  Declaraciones de Bison
*************************/

/*  Especifica la coleccion completa de tipos de datos para poder usar
   varios tipos de datos en los terminales y no terminales*/

%union
{

  char TEXT [256];
  class Nodo_arbol *tipo_nodo;

}
/* Indica la produccion con la que inicia nuestra gramatica*/
%start I

/* Especificacion de termines, podemos especificar tambien su tipo  */
%token <TEXT> tk_igual
%token <TEXT> tk_mkdisk
%token <TEXT> tk_rmdisk
%token <TEXT> tk_exec
%token <TEXT> tk_fdisk

%token <TEXT> tk_size
%token <TEXT> tk_fit
%token <TEXT> tk_unit
%token <TEXT> tk_path
%token <TEXT> tk_type
%token <TEXT> tk_delete
%token <TEXT> tk_name
%token <TEXT> tk_add


%token <TEXT> tk_ruta
%token <TEXT> tk_numero
%token <TEXT> tk_identificador
%token <TEXT> tk_cadena

%token <TEXT> tk_kilo
%token <TEXT> tk_mega
%token <TEXT> tk_bf
%token <TEXT> tk_ff
%token <TEXT> tk_wf
%token <TEXT> tk_archivo
%token <TEXT> tk_byte
%token <TEXT> tk_primaria
%token <TEXT> tk_extendida
%token <TEXT> tk_logica
%token <TEXT> tk_fast
%token <TEXT> tk_full

/* No Terminales, que tambien podemos especificar su tipo */
%type <tipo_nodo> I
//%type <tipo_nodo> LCONTENIDO
%type <tipo_nodo> CONTENIDO
%type <tipo_nodo> LPARAMETROS PARAMETROS
%type <tipo_nodo> AJUSTE UNIDADES
%type <tipo_nodo> LPARAMETROS_FDISK OPARAMETROS_FDISK
%type <tipo_nodo> UNIDADES_FDISK
%type <tipo_nodo> TIPO_PARTICION
%type <tipo_nodo> VDELETE
%%

/**********************
  Reglas Gramaticales
***********************/


I: CONTENIDO{
        raiz = $$;
  }
  ;

CONTENIDO: tk_mkdisk LPARAMETROS{
        $$= new Nodo_arbol("MKDISK","");
        $$->add(*$2);
    }
    | tk_rmdisk tk_path tk_igual tk_ruta{
        $$= new Nodo_arbol("RMDISK","");
        $$->add(*(new Nodo_arbol("path",$4)));
    }
    | tk_rmdisk tk_path tk_igual tk_cadena{
        $$= new Nodo_arbol("RMDISK","");
        $$->add(*(new Nodo_arbol("path",$4)));
    }
    | tk_exec tk_path tk_igual tk_ruta{
        $$= new Nodo_arbol("EXEC","");
        $$->add(*(new Nodo_arbol("path",$4)));
        printf("Comando Exec correcto!!");
    }
    | tk_exec tk_path tk_igual tk_cadena{
        $$= new Nodo_arbol("EXEC","");
        $$->add(*(new Nodo_arbol("path",$4)));
        printf("Comando Exec correcto!!");
    }
    | tk_fdisk LPARAMETROS_FDISK{
        $$= new Nodo_arbol("FDISK","");
        $$->add(*$2);
        printf("Comando Fdisk correcto!!");
    }
  ;

LPARAMETROS: LPARAMETROS PARAMETROS{
        $$=$1;
        $$->add(*$2);
  }
  | PARAMETROS{
        $$ = new Nodo_arbol("PARAMETRO","");
        $$->add(*$1);
  }
  ;

PARAMETROS: tk_fit tk_igual AJUSTE {
        $$= new Nodo_arbol("fit","");
        $$->add(*$3);
  }
  | tk_unit tk_igual UNIDADES {
        $$= new Nodo_arbol("unit","");
        $$->add(*$3);
  }
  | tk_size tk_igual tk_numero {
        $$= new Nodo_arbol("size",$3);
  }
  | tk_path tk_igual tk_ruta {
        $$= new Nodo_arbol("path",$3);
  }
  | tk_path tk_igual tk_cadena {
        $$= new Nodo_arbol("path",$3);
  }
  ;

AJUSTE: tk_bf {
        $$=new Nodo_arbol("ajuste","bf");
  }
  | tk_ff {
        $$=new Nodo_arbol("ajuste","ff");
  }
  | tk_wf {
        $$=new Nodo_arbol("ajuste","wf");
  }
  ;

UNIDADES: tk_kilo {
        $$=new Nodo_arbol("unidad","k");
  }
  | tk_mega {
        $$=new Nodo_arbol("unidad","m");
  }
  ;

LPARAMETROS_FDISK: LPARAMETROS_FDISK OPARAMETROS_FDISK {
        $$=$1;
        $$->add(*$2);
  }
  | OPARAMETROS_FDISK {
        $$= new Nodo_arbol("PARAMETRO","");
        $$->add(*$1);
  }
  ;

OPARAMETROS_FDISK: tk_size tk_igual tk_numero {
        $$= new Nodo_arbol("size",$3);
  }
  | tk_unit tk_igual UNIDADES_FDISK {
        $$= new Nodo_arbol("unit","");
        $$->add(*$3);
  }
  | tk_path tk_igual tk_ruta {
        $$= new Nodo_arbol("path", $3);
  }
  | tk_path tk_igual tk_cadena {
        $$= new Nodo_arbol("path", $3);
  }
  | tk_type tk_igual TIPO_PARTICION {
        $$= new Nodo_arbol("type","");
        $$->add(*$3);
  }
  | tk_fit tk_igual AJUSTE {
        $$= new Nodo_arbol("fit","");
        $$->add(*$3);
  }
  | tk_delete tk_igual VDELETE {
        $$= new Nodo_arbol("delete","");
        $$->add(*$3);
  }
  | tk_name tk_igual tk_identificador {
        $$= new Nodo_arbol("name", $3);
  }
  | tk_name tk_igual tk_cadena {
        $$= new Nodo_arbol("name", $3);
  }
  | tk_add tk_igual tk_numero {
        $$= new Nodo_arbol("add", $3);
  }
  ;

UNIDADES_FDISK: tk_byte {
        $$=new Nodo_arbol("unidad","b");
  }
  | tk_kilo {
        $$=new Nodo_arbol("unidad","k");
  }
  | tk_mega {
        $$=new Nodo_arbol("unidad","m");
  }
  ;

TIPO_PARTICION: tk_primaria {
        $$=new Nodo_arbol("tipo","primaria");
  }
  | tk_extendida {
        $$=new Nodo_arbol("tipo","extendida");
  }
  | tk_logica {
        $$=new Nodo_arbol("tipo","logica");
  }
  ;

VDELETE: tk_fast {
        $$=new Nodo_arbol("tipo","fast");
  }
  | tk_full {
        $$=new Nodo_arbol("tipo","full");
  }
  ;

%%
/********************
  Codigo C o C++ Adicional
**********************/
void yyerror(char *s)
{
  printf("Error sintactico %s",s);
  cout<<" token no reconocido: ";
  cout<<yytext<<" En la Linea: "<<yylineno<<endl;;

  //expresion="Error Sintactico";
}

