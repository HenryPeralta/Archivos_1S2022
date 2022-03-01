#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H
#include <sys/stat.h>//obtiene la fecha del sistema
#include <QString>
#include <QObject>
#include <string>

using namespace std;

enum comandos{
    MKDISK = 1,
    RMDISK = 2,
    FDISK = 3,
    MOUNT = 4,
    UNMOUNT = 5,
    REP = 6,
    EXEC = 7,
    PARAMETRO = 8,

    PATH = 9,
    ID = 10,
    NAME = 11,
    TIPO = 12,
    FIT = 13,
    UNIT = 14,
    SIZE = 15,
    TYPE = 16,
    DELETE = 17,
    ADD = 18,
    AJUSTE = 19,
    UNIDAD = 20,

    MKFS = 21,
    LOGIN = 22,
    LOGOUT= 23,
    MKGRP = 24,
    RMGRP = 25,
    MKUSR = 26,
    RMUSR = 27,
    CHMOD = 28,
    MKFILE = 29,
    CAT = 30,
    REM =31,
    EDIT = 32,
    REN = 33,
    MKDIR = 34,
    CP = 35,
    MV = 36,
    FIND = 37,
    CHOWN = 38,
    CHGRP = 39,
    PAUSE = 40,

    RUTA=41,
    USR=42,
    PWD=43,
    GRP=44,

    UGO=45,
    R=46,
    P=47,
    CONT=48,
    PFILE=49
};

class estructuras
{
public:
    estructuras();
};

#endif // ESTRUCTURAS_H
