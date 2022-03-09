#ifndef LIST_PARTICIONES_H
#define LIST_PARTICIONES_H

#include <QObject>
#include <iostream>
#include "n_particiones.h"
using namespace std;

class List_particiones
{
public:
    List_particiones();
    n_particiones *primero;
    int buscarLetra(QString path, QString name);
    int buscarNumero(QString path, QString name);
    void mostrarLista();
    void insertarNodo(n_particiones*);
    int eliminarNodo(QString id);
    bool buscarNodo(QString path, QString name);
    QString getDireccion(QString id);
    n_particiones getParticionMontada(QString id);
    bool estaVacio();
};

#endif // LIST_PARTICIONES_H
