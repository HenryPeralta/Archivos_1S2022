#ifndef GRAFICAR_H
#define GRAFICAR_H
#include <QObject>
#include "nodo_arbol.h"

class graficar
{
public:
    //constructor
    graficar(Nodo_arbol *raiz);
    //atributos
    Nodo_arbol *raiz;
    QString dot;
    int cont;
    //metodos y funciones
    QString generarCodigoGraphviz();
    QString limpiarString(QString str);
    void recorrerAST(QString padre, Nodo_arbol *hijo);
    void generarImagen();
};

#endif // GRAFICAR_H
