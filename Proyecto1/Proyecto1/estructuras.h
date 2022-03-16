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
    MOUNT = 17,
    UNMOUNT = 18,
    ID = 19,
    MKFS = 20,
    FS = 21,
    REP = 22,
    MBR = 23,
    DISK =24
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

typedef struct{
    int s_filesystem_type;
    int s_inodes_count;
    int s_blocks_count;
    int s_free_blocks_count;
    int s_free_inodes_count;
    time_t s_mtime;
    time_t s_umtime;
    int s_mnt_count;
    int s_magic;
    int s_inode_size;
    int s_block_size;
    int s_firts_ino;
    int s_first_blo;
    int s_bm_inode_start;
    int s_bm_block_start;
    int s_inode_start;
    int s_block_start;
}superbloque;

typedef struct{
    int i_uid;
    int i_gid;
    int i_size;
    time_t i_atime;
    time_t i_ctime;
    time_t i_mtime;
    int i_block;
    char i_type;
    int i_perm;
}inodos;

//BLOQUES CARPETAS
typedef struct{
    char b_name [12];
    int b_inodo;
}bcontent;

typedef struct{
    bcontent b_content [4];
}bcarpeta;

//BLOQUE ARCHIVOS
typedef struct{
    char b_content[64];
}barchivo;

//BLOQUE APUNTADOR
typedef struct{
    int b_pointers[16];
}bapuntador;

typedef struct{
    char operacion[16];
    int next;
    char usuario[16];
    char tipo;
    char nombre[150];
    char content[230];
    time_t date;
}journal;

typedef struct{
    int last;
    int max;
}info_journal;

typedef struct{
    int bloque_padre;
    int posicion;
    int inodo;
}inodo_dato;

typedef struct{
    short lectura;
    short escritura;
    short ejecucion;
}permiso;

class estructuras
{
public:
    estructuras();
};

#endif // ESTRUCTURAS_H
