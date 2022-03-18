#ifndef VALORES_H
#define VALORES_H
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


class valores
{
public:
    valores();
    int user_id = -1;
    int user_grp_id = -1;
    QString user_grp = "";
    QString user_name = "";
    FILE *Archivo;
    QByteArray bitmap_block;
    QList<journal> journaling;
    journal journal_last;
    info_journal journal_info;
    QByteArray bitmap_inodo;
    int inicio_byte;
    QString group;
    int group_id;

    superbloque super;

    valores(FILE*disco, n_particiones *particion, int iniciobyte);
    void userInformacion(QString user_name, int user_id, QString user_grp,int user_grp_id);
    static const int SIZE_BLOCKS = 64;
    static void formatearParticion(FILE *Archivo, particion particiones, string type, string fs);
    static void formatearPart_logica(FILE *Archivo, ebr particion, string type, string fs);
    static inodos getInodo(FILE *Archivo, int inode_start, int posicion);
    int crearArchivo(inodos inodo_current, QStringList contenido, QStringList &path, int pos_actual, bool p);
    permiso getPermisoInodo(int permiso, char categoria);
    permiso verificarPermiso(inodos inodo);
    int removerCarpeta_Archivo(inodos inodo_current, QString name_file_direc);
    static bapuntador getBloqueApuntador(FILE *disco, int block_start, int posicion);
    int removerCarpeta_Archivo2(QString name_file_direc, int b_apuntador,int nivel_puntero_indirecto);
    static bcarpeta getBloqueCarpeta(FILE *disco, int block_start, int posicion);
    int removeInodoHijos(inodos inodo);
    int removeCarpetaHijos(int espacio, int nivel);
    void removeFileHijos(int espacio, int nivel);
    void liberarBitmapBlock(int posBlock);
    int escribirArchivo_(int puntero_actual, QString nombre_archivo, QStringList contenido,int nivel_puntero_indirecto);
    static QString getPathString(QStringList path);
    static QString getcontentString(QStringList content);
    void agregarJournal(QString comando, QString nombre, QString contenido, char tipo);
    int crearArchivo_(inodos inodo_current, QStringList contenido, QStringList &path, int pos_actual, bool p);
    void liberarBitmapInodo(int posInodo);
    int escribirArchivo(QStringList contenido);
    int crearBloquesArchivo(QListIterator<QString> &content, bapuntador& b_apuntador);
    int escribirContenidos(QListIterator<QString> &content, int espacio_actual, int nivel);
    void actualizarSuperBloque();
    void actualizarSB();
    void actualizarBitmaps();
    void actualizarJournal();
    static void getSuperBlock(FILE*disco, n_particiones part_montada, superbloque &superBlock);
    journal getJournal(int posicion);
    int iniciarSesion(QString user, QString psw);
    QListIterator<QString> getDatosUsers();
    QString getFileContent_(int espacio_apuntador, int nivel);
    QString getFileContent(inodos inodo);

private:
    static int calNoStructs(int size_particion, char part_type, string fs);
    static void escribirBloque(FILE *disco, bcarpeta block, int block_start, int posicion);
    static void escribirBloque(FILE *disco, bapuntador block, int block_start, int posicion);
    static void escribirBloque(FILE *disco, barchivo block, int block_start, int posicion);
    int existInodobyName(inodos inodo_current, QString name_file_direc);
    int getPositionInodobyName(QString name_file_direc, bapuntador b_apuntador, int nivel_puntero_indirecto);
    int crearCarpeta_(inodos inodo_current, QStringList &path, int pos_actual, bool p);
    int escribirCarpeta_(int puntero_actual, QString nombre_carpeta, int nivel_puntero_indirecto);
    int getFreeIndexBitmapBlock();
    int escribirCarpeta();
    int getFreeIndexBitmapInodo();
    static void escribirInodo(FILE *disco, inodos inodo, int inode_start, int posicion);
    void getSuperBlock(n_particiones *part_montada);
    void getBitmaps();
    void getJournal();
    static void crearCarpetaRaiz(FILE *disco, superbloque &s_block, int inicio_byte);
    static barchivo getBloqueArchivo(FILE *disco, int block_start, int posicion);
};

#endif // VALORES_H
