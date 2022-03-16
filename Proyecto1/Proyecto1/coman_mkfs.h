#ifndef COMAN_MKFS_H
#define COMAN_MKFS_H
#include <stdio.h>
#include <QtCore>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <QObject>
#include <QList>
#include "nodo_arbol.h"
#include "estructuras.h"
#include "list_particiones.h"
#include "valores.h"
using namespace std;

class coman_mkfs
{
public:
    coman_mkfs();
    List_particiones *lista;
    void recorrer_mkfs(QList<Nodo_arbol> *hijos);
    void ejecutar_mkfs(QString id, QString type, QString fs);
};

#endif // COMAN_MKFS_H
