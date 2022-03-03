#include <QCoreApplication>
#include <stdio.h>
#include <QtCore>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <string.h>
//LINEA POR LINEA
#include <sstream>
#include <string>
#include <fstream>
#include <QFileInfo>
#include <QObject>

//COMPILADOR
#include "scanner.h"
#include "parser.h"
#include "estructuras.h"
#include "graficar.h"

//COMANDO MKDISK
#include "coman_mkdisk.h"
//COMANDO RMDISK
#include "coman_rmdisk.h"

using namespace std;

//COMPILADOR
extern int yyparse();
extern FILE *yyin;
extern Nodo_arbol *raiz; // Raiz del arbol
extern int columna;

void Comando(char*);
void recorrer_ast(Nodo_arbol*);


int main()
{
    char entrada[500];
    string entradat;
    string salida;
    do{
        cout<<" -------------------------------"<<endl;
        cout<<"|      Ingrese un Comando       |"<<endl;
        cout<<" -------------------------------"<<endl;
        fgets(entrada,sizeof (entrada),stdin);
        entradat = entrada;
        entradat = entradat.substr(0, entradat.size()-1);
        if(entradat.length()==0){

        }
        else if(entradat!="salir"){
            Comando(entrada);
        }
    }while(entradat != "salir");

    return 0;
}

void Comando(char comando[400]){
    if(comando[0] != '#'){
        YY_BUFFER_STATE buffer = yy_scan_string(comando);
        if(yyparse() == 0){
            if(raiz!=nullptr){
                //graficar_ast *g = new graficar_ast(raiz);
                //g->generarImagen();
                recorrer_ast(raiz);
            }
        }else{
            cout<<"Error: Comando no Reconocido"<<endl;
        }
    }
}

void recorrer_ast(Nodo_arbol *raiz){
    switch (raiz->tipo_num){
    case MKDISK:{
        Nodo_arbol temp = raiz->hijos.at(0);
        coman_mkdisk *mkdisk = new coman_mkdisk();
        mkdisk->recorrido_mkdisk(&temp);
        break;
    }
    case RMDISK:{
        Nodo_arbol temp = raiz->hijos.at(0);
        coman_rmdisk *rmdisk = new coman_rmdisk();
        rmdisk->recorrido_rmdisk(&temp);
        break;
    }
    default:{
        cout<<"Error: comando no reconocido"<<endl;
        break;
    }
    }
}
