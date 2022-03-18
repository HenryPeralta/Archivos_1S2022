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
#include "list_particiones.h"

//COMANDOS
#include "coman_mkdisk.h"
#include "coman_rmdisk.h"
#include "coman_exec.h"
#include "coman_fdisk.h"
#include "coman_mount.h"
#include "coman_unmount.h"
#include "coman_mkfs.h"
#include "coman_rep.h"
#include "coman_login.h"

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
List_particiones *lista = new List_particiones();
void logout();

int id_usuario=-1;
QString usuario = "";
QString id_mount = "";
QString grupo = "";
int id_grupo = -1;
n_particiones part_global;


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
    }case MOUNT:{
        QList<Nodo_arbol> temp = raiz->hijos;
        coman_mount *mount = new coman_mount();
        mount->lista = lista;
        mount->recorrer_mount(&temp);
        lista->mostrarLista();
        break;
    }case UNMOUNT:{
        Nodo_arbol temp = raiz->hijos.at(0);
        coman_unmount *unmount = new coman_unmount();
        unmount->lista = lista;
        unmount->recorrido_unmount(&temp);
        lista->mostrarLista();
        break;
    }case MKFS:{
        QList<Nodo_arbol> temp = raiz->hijos;
        coman_mkfs *mkfs = new coman_mkfs();
        mkfs->lista=lista;
        mkfs->recorrer_mkfs(&temp);
        break;
    }case REP:{
        Nodo_arbol temp = raiz->hijos.at(0);
        coman_rep *rep = new coman_rep();
        rep->lista=lista;
        rep->recorrer_rep(&temp);
        break;
    }case LOGIN:{
        Nodo_arbol temp = raiz->hijos.at(0);
        coman_login *login = new coman_login(lista, &id_usuario, &usuario, &id_mount, &grupo, &id_grupo, &part_global);
        login->recorrer_login(&temp);
        break;
    }case LOGOUT:{
        logout();
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

void logout(){
    if(id_usuario == -1){
        cout<<"No hay ninguna sesion iniciada"<<endl;
    }else{
        part_global.path = "";
        id_usuario = -1;
        usuario = "";
        id_mount = "";
        cout<<"Se cerro la sesion con exito!!"<<endl;
    }
}



