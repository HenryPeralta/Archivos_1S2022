#ifndef N_PARTICIONES_H
#define N_PARTICIONES_H

#include <QObject>
#include "estructuras.h"
using namespace std;

class n_particiones
{
public:
    n_particiones();
    n_particiones(QString path, QString name, char letra, int num, char part_type);
    QString path;
    QString name;
    char letra;
    int num;
    n_particiones *siguiente;
    char part_type;
    particion particiones;
    ebr particion_logica;
};

#endif // N_PARTICIONES_H
