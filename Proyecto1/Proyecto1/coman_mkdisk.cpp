#include "coman_mkdisk.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <time.h>
#include "string"
#include <QString>
using namespace std;

coman_mkdisk::coman_mkdisk()
{

}

void coman_mkdisk::recorrido_mkdisk(Nodo_arbol *raiz){
    for(int c = 0; c < raiz->hijos.count();c++){
        Nodo_arbol temp = raiz->hijos.at(c);
        cout<<temp.valor.toUInt()<<endl;
    }
}
