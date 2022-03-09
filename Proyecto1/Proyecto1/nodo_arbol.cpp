#include "nodo_arbol.h"
#include<stdlib.h>
#include<iostream>
using namespace std;

Nodo_arbol::Nodo_arbol(QString ptipo, QString pvalor)
{
    tipo = ptipo;
    valor = pvalor;
    tipo_num = getTipo();
    hijos = QList<Nodo_arbol>();
}

//aqui permitimos saber que es cada nodo del arbol
int Nodo_arbol::getTipo(){
    if(this->tipo == "MKDISK"){
        return 1;
    }
    if(this->tipo == "path"){
        return 2;
    }
    if(this->tipo == "fit"){
        return 3;
    }
    if(this->tipo == "unit"){
        return 4;
    }
    if(this->tipo == "size"){
        return 5;
    }
    if(this->tipo == "PARAMETRO"){
        return 6;
    }
    if(this->tipo == "ajuste"){
        return 7;
    }
    if(this->tipo == "unidad"){
        return 8;
    }
    if(this->tipo == "RMDISK"){
        return 9;
    }
    if(this->tipo == "EXEC"){
        return 10;
    }
    if(this->tipo == "FDISK"){
        return 11;
    }
    if(this->tipo == "name"){
        return 12;
    }
    if(this->tipo == "tipo"){
        return 13;
    }
    if(this->tipo == "type"){
        return 14;
    }
    if(this->tipo == "delete"){
        return 15;
    }
    if(this->tipo == "add"){
        return 16;
    }
    if(this->tipo == "MOUNT"){
        return 17;
    }
    return 0;
}

void Nodo_arbol::add(Nodo_arbol n){
    hijos.append(n);
}

