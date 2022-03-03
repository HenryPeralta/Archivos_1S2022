#ifndef COMAN_MKDISK_H
#define COMAN_MKDISK_H
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

using namespace std;
class coman_mkdisk
{
public:
    coman_mkdisk();
    //recorrido de los arboles
    void recorrido_mkdisk(Nodo_arbol*);
    //ejecutar comandos
    void ejecutarDisco(int psize, string pfit, string punit, QString ppath);
    void creandoRuta(QString ppath);
    QString obtener_path(QString);
};

#endif // COMAN_MKDISK_H
