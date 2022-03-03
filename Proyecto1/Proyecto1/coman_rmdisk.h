#ifndef COMAN_RMDISK_H
#define COMAN_RMDISK_H
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

class coman_rmdisk
{
public:
    coman_rmdisk();
    //recorrido de los arboles
    void recorrido_rmdisk(Nodo_arbol*);
};

#endif // COMAN_RMDISK_H
