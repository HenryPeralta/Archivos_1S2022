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
    if(this->tipo == "UNMOUNT"){
        return 18;
    }
    if(this->tipo == "id"){
        return 19;
    }
    if(this->tipo == "MKFS"){
        return 20;
    }
    if(this->tipo == "fs"){
        return 21;
    }
    if(this->tipo == "REP"){
        return 22;
    }
    if(this->tipo == "mbr"){
        return 23;
    }
    if(this->tipo == "disk"){
        return 24;
    }
    if(this->tipo == "LOGIN"){
        return 25;
    }
    if(this->tipo == "usuario"){
        return 26;
    }
    if(this->tipo == "password"){
        return 27;
    }
    if(this->tipo == "LOGOUT"){
        return 28;
    }
    return 0;
}

void Nodo_arbol::add(Nodo_arbol n){
    hijos.append(n);
}

