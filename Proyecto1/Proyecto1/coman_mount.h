#ifndef COMAN_MOUNT_H
#define COMAN_MOUNT_H
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


class coman_mount
{
public:
    coman_mount();
    List_particiones *lista;
    void recorrer_mount(QList<Nodo_arbol> *hijos);
    void crear_mount(QString path, QString name);
    int buscarParticion_P_E(QString path, QString name);
    int buscarParticion_L(QString path, QString name);

};

#endif // COMAN_MOUNT_H
