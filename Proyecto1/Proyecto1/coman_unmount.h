#ifndef COMAN_UNMOUNT_H
#define COMAN_UNMOUNT_H
#include <QObject>
#include <stdio.h>
#include <QtCore>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <QObject>
#include "nodo_arbol.h"
#include "estructuras.h"
#include "list_particiones.h"
#include "n_particiones.h"
using namespace std;

class coman_unmount
{
public:
    coman_unmount();
    List_particiones *lista;
    void recorrido_unmount(Nodo_arbol *raiz);
    void correr_unmount(QString id);
};

#endif // COMAN_UNMOUNT_H
