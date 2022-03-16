#ifndef COMAN_REP_H
#define COMAN_REP_H
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


class coman_rep
{
public:
    coman_rep();
    List_particiones *lista;
    void recorrer_rep(Nodo_arbol *raiz);
    void eleccion_repo(QString path, QString name, QString id);
    QString obtener_extension(QString path);
    QString obtener_path(QString path);
    void graficarMBR(QString path, QString destino, QString extension);
    void graficarDisk(QString path, QString destino, QString extension);
};

#endif // COMAN_REP_H
