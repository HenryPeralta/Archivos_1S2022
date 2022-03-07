#ifndef COMAN_EXEC_H
#define COMAN_EXEC_H
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


class coman_exec
{
public:
    coman_exec();
    void recorre_exec(QList<Nodo_arbol> *hijos);
};

#endif // COMAN_EXEC_H
