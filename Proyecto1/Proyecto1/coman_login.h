#ifndef COMAN_LOGIN_H
#define COMAN_LOGIN_H
#include <QObject>
#include <stdio.h>
#include <QtCore>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <string.h>
#include "nodo_arbol.h"
#include "estructuras.h"
#include "list_particiones.h"
#include "valores.h"
using namespace std;


class coman_login
{
public:
    int *id_usuario;
    QString *usuario;
    QString *id_mount;
    QString *grupo;
    int *id_grupo;
    n_particiones *part_global;
    List_particiones *lista;

    coman_login();
    coman_login(List_particiones *lista, int *id_usuario, QString *usuario, QString *id_mount, QString *grupo, int *id_grupo, n_particiones *part_global);
    void recorrer_login(Nodo_arbol *raiz);
    void crearUsuarios(QString usuario, QString password, QString id);
};

#endif // COMAN_LOGIN_H
