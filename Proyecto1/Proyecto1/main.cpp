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

//COMANDOS
#include "coman_mkdisk.h"
#include "coman_rmdisk.h"
#include "coman_exec.h"
#include "coman_fdisk.h"

using namespace std;

//COMPILADOR
extern int yyparse();
extern FILE *yyin;
extern Nodo_arbol *raiz; // Raiz del arbol
extern int columna;

void Comando(char*);
void recorrer_ast(Nodo_arbol*);
void varios_exec(QList<Nodo_arbol> *hijos);
bool existe_archivo(QString path);


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
    }case EXEC:{
        QList<Nodo_arbol> temp = raiz->hijos;
        varios_exec(&temp);
        break;
    }case FDISK:{
        Nodo_arbol temp = raiz->hijos.at(0);
        coman_fdisk *fdisk = new coman_fdisk();
        fdisk->recorrido_fdisk(&temp);
        break;
    }
    default:{
        cout<<"Error: comando no reconocido"<<endl;
        break;
    }
    }
}

void varios_exec(QList<Nodo_arbol> *hijos){
    QString path = hijos->at(0).valor;
    path.replace(QString("\""), QString(""));
    string rutax = path.toStdString();
    QString ruta = rutax.c_str();
    if(existe_archivo(ruta)){
        cout<<"Archivo encontrado con exito"<<endl;
        ifstream entrada(ruta.toStdString());
        string linea;
        QString aux_linea;
        int contador = 0;
        columna = 0;

        while(getline(entrada, linea)){
            contador++;
            if(linea.length()>1){
                aux_linea = linea.c_str();
                QByteArray nuevo = aux_linea.toLocal8Bit();
                char *caracter = nuevo.data();
                if(caracter[0] == '#'){

                }else{
                    cout<<"--- Ejecutando Script ---"<<endl;
                    cout<<"Linea: "<<contador<<" Comando: "<<linea<<endl;
                    Comando(caracter);
                }
            }
        }
    }else{
        cout<<"Error: El archivo no se encontro"<<endl;
    }
}

bool existe_archivo(QString path){
    QFileInfo check_file(path);
    if (check_file.exists() && check_file.isFile()) {
        return true;
    } else {
        return false;
    }
}



