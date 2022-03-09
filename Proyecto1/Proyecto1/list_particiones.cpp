#include "list_particiones.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

List_particiones::List_particiones()
{
    primero = nullptr;
}

void List_particiones::insertarNodo(n_particiones *nuevo){
    n_particiones *aux = primero;
    if(primero == nullptr){
        primero = nuevo;
    }else{
        while(aux->siguiente != nullptr){
            aux = aux->siguiente;
        }
        aux->siguiente = nuevo;
    }
}

int List_particiones::eliminarNodo(QString id){
    n_particiones *aux = primero;
    QString tempId = "89";
    tempId += QString::number(aux->num)+aux->letra;
    if(id == tempId){
        primero = aux->siguiente;
        free(aux);
        return 1;
    }else{
        n_particiones *aux2 = nullptr;
        while(aux != nullptr){
            tempId = "89";
            tempId += QString::number(aux->num)+aux->letra;
            if(id == tempId){
                aux2->siguiente = aux->siguiente;
                return 1;
            }
            aux2 = aux;
            aux = aux->siguiente;
        }
    }
    return 0;
}

int List_particiones::buscarLetra(QString path, QString name){
    n_particiones *aux = primero;
    int retorno = 'a';
    while(aux != NULL){
        cout<<path.toStdString()<<endl;
        cout<<name.toStdString()<<endl;
        cout<<"HOLIS"<<endl;
        cout<<aux->path.toStdString().c_str()<<endl;
        cout<<aux->name.toStdString().c_str()<<endl;
        if((path == aux->path) && (name == aux->name)){
            return -1;
        }else{
            if(path == aux->path){
                return aux->letra;
            }else if(retorno <= aux->letra){
                retorno++;
            }
        }
        aux = aux->siguiente;
    }
    return retorno;
}

int List_particiones::buscarNumero(QString path, QString name){
    int retorno = 1;
    n_particiones *aux = primero;
    while(aux != nullptr){
        if((path == aux->path) && (retorno == aux->num)){
            retorno++;
        }
        aux = aux->siguiente;
    }
    return retorno;
}

QString List_particiones::getDireccion(QString id){
    n_particiones *aux = primero;
    while(aux != nullptr){
        QString tempId = "89";
        tempId += QString::number(aux->num)+aux->letra;
        if(id == tempId){
            return aux->path;
        }
        aux = aux->siguiente;
    }
    return "null";
}

bool List_particiones::buscarNodo(QString path, QString name){
    n_particiones *aux = primero;
    while(aux != nullptr){
        if((aux->path == path) && (aux->name == name)){
            return true;
        }
        aux = aux->siguiente;
    }
    return false;
}

void List_particiones::mostrarLista(){
    cout<<"---------------------------"<<endl;
    cout<<"|   Lista de particiones  |"<<endl;
    cout<<"---------------------------"<<endl;
    cout<<"|    Nombre    |    Id    |"<<endl;
    cout<<"---------------------------"<<endl;
    n_particiones *aux = primero;
    while(aux != nullptr){
        cout<<"   "<<aux->name.toStdString()<<"   "<<"89"<<aux->num<<aux->letra<<endl;
        cout<<"---------------------------"<<endl;
        aux = aux->siguiente;
    }
}

n_particiones List_particiones::getParticionMontada(QString id){
    n_particiones *aux = primero;
    while(aux != nullptr){
        QString tempId = "89";
        tempId.append(QString::number(aux->num));
        tempId.append(aux->letra);
        if(tempId == id){
            return *aux;
        }
        aux = aux->siguiente;
    }
    n_particiones *temp = new n_particiones();
    return *temp;
}

bool List_particiones::estaVacio(){
    if(primero == nullptr){
        return true;
    }
    return false;
}
