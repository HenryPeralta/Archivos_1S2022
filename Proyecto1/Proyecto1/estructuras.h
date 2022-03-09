#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H
#include <sys/stat.h>//obtiene la fecha del sistema
#include <QString>
#include <QObject>
#include <string>

using namespace std;

enum comandos{
    MKDISK = 1,
    PATH = 2,
    FIT = 3,
    UNIT = 4,
    SIZE = 5,
    PARAMETRO = 6,
    AJUSTE = 7,
    UNIDAD = 8,
    RMDISK = 9,
    EXEC = 10,
    FDISK = 11,
    NAME = 12,
    TIPO = 13,
    TYPE = 14,
    DELETE = 15,
    ADD = 16,
    MOUNT = 17

    //RMDISK = 2,
    //FDISK = 3,
    //MOUNT = 4,
    //UNMOUNT = 5,
    //REP = 6,
    //EXEC = 7,
    //PARAMETRO = 8,

    //PATH = 9,
    //ID = 10,
    //NAME = 11,
    //TIPO = 12,
    //FIT = 13,
    //UNIT = 14,
    //SIZE = 15,
    //TYPE = 16,
    //DELETE = 17,
    //ADD = 18,
    //AJUSTE = 19,
    //UNIDAD = 20,

    //MKFS = 21,
    //LOGIN = 22,
    //LOGOUT= 23,
    //MKGRP = 24,
    //RMGRP = 25,
    //MKUSR = 26,
    //RMUSR = 27,
    //CHMOD = 28,
    //MKFILE = 29,
    //CAT = 30,
    //REM =31,
    //EDIT = 32,
    //REN = 33,
    //MKDIR = 34,
    //CP = 35,
    //MV = 36,
    //FIND = 37,
    //CHOWN = 38,
    //CHGRP = 39,
    //PAUSE = 40,

    //RUTA=41,
    //USR=42,
    //PWD=43,
    //GRP=44,

    //UGO=45,
    //R=46,
    //P=47,
    //CONT=48,
    //PFILE=49
};

typedef struct {
    char part_status;
    char part_type;
    char part_fit;
    int part_start;
    int part_size;
    char part_name[16];
} particion;

typedef struct{
    int mbr_tamano;
    time_t mbr_fecha_creacion;
    int mbr_dsk_signature;
    char dsk_fit;
    particion mbr_partition[4];
}mbr;

typedef struct{
    char part_status;
    char part_fit;
    int part_start;
    int part_size;
    int part_next;
    char part_name[16];
}ebr;


class estructuras
{
public:
    estructuras();
};

#endif // ESTRUCTURAS_H
