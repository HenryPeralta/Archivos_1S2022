#include "coman_unmount.h"

coman_unmount::coman_unmount()
{

}

void coman_unmount::recorrido_unmount(Nodo_arbol *raiz){
    cout<<raiz->valor.toStdString()<<endl;
    correr_unmount(raiz->valor);
}

void coman_unmount::correr_unmount(QString id){
    if(lista->primero != nullptr){
        int eliminarP = lista->eliminarNodo(id);
        if(eliminarP == 1){
            cout<<"Particion desmontada con exito"<<endl;
        }else{
            cout<<"Error: La particion "<<id.toStdString()<<" no esta montada"<<endl;
        }
    }else{
        cout<<"No hay particiones montadas"<<endl;
    }
}
