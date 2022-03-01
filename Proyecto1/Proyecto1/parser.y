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


%token <TEXT> tk_size
%token <TEXT> tk_fit
%token <TEXT> tk_unit
%token <TEXT> tk_path

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


/* No Terminales, que tambien podemos especificar su tipo */
%type <tipo_nodo> I
//%type <tipo_nodo> LCONTENIDO
%type <tipo_nodo> CONTENIDO
%type <tipo_nodo> LPARAMETROS PARAMETROS
%type <tipo_nodo> AJUSTE UNIDADES

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
        printf("Comando mkdisk correcto!!");
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

