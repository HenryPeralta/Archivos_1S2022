#ifndef COMAN_FDISK_H
#define COMAN_FDISK_H
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

class coman_fdisk
{
public:
    coman_fdisk();
    void recibe_lista(List_particiones *lista);
    List_particiones *lista;
    //Recorrido del arbol
    void recorrido_fdisk(Nodo_arbol*);
    bool existe_archivo(QString path);
    void crear_particiones(string ptype, QString ppath, QString pname, int psize, string pfit, string punit);
    void crearParticionPrimaria(QString path, QString nombre, int size, string fit, string unit, QString archivo);
    void crearParticionExtendida(QString path, QString nombre, int size, string fit, string unit, QString archivo);
    void crearParticionLogica(QString path, QString name, int size, string fit, string unit, QString archivo);
    void eliminarParticion(QString path, QString name, string tipo_delete, QString archivo);
    void comando_add(QString path, QString name, int add, string unit, QString archivo);

    bool existeParticion(string path, string name);
    int buscarParticion_L(QString path, QString name);
};

#endif // COMAN_FDISK_H
