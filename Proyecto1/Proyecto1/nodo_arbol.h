#ifndef NODO_ARBOL_H
#define NODO_ARBOL_H

#include <QObject>
#include <QString>
#include <QList>
using namespace std;

class Nodo_arbol
{
public:
    //constructor
    Nodo_arbol(QString ptipo, QString pvalor);
    //VARIABLES
    //el tipo que va ser el nodo
    QString tipo;
    //el valor o lexema que se obtiene
    QString valor;
    //linea
    int line;
    //columna
    int columna;
    //para saber el tipo, en numero
    int tipo_num;
    //este va a ser la variable global que concatena el AST para saber como manejar nuestro arbol
    QString cadenaDot;
    //los hijos de cada nodo
    QList<Nodo_arbol> hijos;

    //METODOS
    void add(Nodo_arbol n); //agrega los nuevos hijos a la lista de hijos
    int getTipo(); //devuelve el tipo en int

};

#endif // NODO_ARBOL_H
