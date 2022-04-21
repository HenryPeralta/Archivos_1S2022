#include "coman_mkdisk.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <time.h>
#include "string"
#include <QString>
using namespace std;

coman_mkdisk::coman_mkdisk()
{

}

void coman_mkdisk::recorrido_mkdisk(Nodo_arbol *raiz){
    bool bandera_size = false;
    bool bandera_path = false;
    bool bandera_error = false;
    int valor_size = 0;
    string valor_fit = "ff";
    string valor_unit = "m";
    QString valor_path = "";
    for(int c = 0; c < raiz->hijos.count();c++){
        Nodo_arbol temp = raiz->hijos.at(c);
        if(temp.tipo_num == SIZE){
            if(temp.valor.toUInt()>0){
                valor_size = temp.valor.toUInt();
                bandera_size = true;
            }else{
                bandera_error = true;
                std::cout<<"Los valores de size no pueden ser menores o iguales a cero \n";
            }
        }
        else if(temp.tipo_num == FIT){
            valor_fit = temp.hijos.at(0).valor.toStdString();
        }
        else if(temp.tipo_num == UNIT){
            valor_unit = temp.hijos.at(0).valor.toStdString();
        }
        if(temp.tipo_num == PATH){
            bandera_path = true;
            valor_path = temp.valor;
        }
    }
    if(bandera_size == false){
        bandera_error = true;
        std::cout<<"Error: El parametro -size es obligatorio \n";
    }
    if(bandera_path == false){
        bandera_error = true;
        std::cout<<"Error: El parametro -path es obligatorio \n";
    }
    if(bandera_error == false){
        ejecutarDisco(valor_size, valor_fit, valor_unit, valor_path);
    }
}

void coman_mkdisk::ejecutarDisco(int psize, string pfit, string punit, QString ppath){

    QString cambio_ruta = ppath;
    cambio_ruta.replace(QString("\""), QString(""));
    string rutax = cambio_ruta.toStdString();

    mbr prueba;
    creandoRuta(cambio_ruta);

    FILE *archivo;
    archivo = fopen(rutax.c_str(), "rb+");

    //Simulando un Kb
    char buffer[1024];

    //Si son Kb
    if(punit == "k" || punit == "K"){
        //Este if es para el tamaño
        prueba.mbr_tamano = psize*1024;

        for(int i = 0; i<1024 ; i++){
            buffer[i] = '\0';
        }

        for(int i = 0; i<(psize); i++){
            fwrite(&buffer, 1024, 1, archivo);
        }
        fclose(archivo);
    }

    //Si son megas
    else if(punit == "m" || punit == "M"){
        prueba.mbr_tamano = psize*1024*1024; //En bytes

        for(int i = 0; i<1024; i++){
            buffer[i] = '\0';
        }
        for(int i = 0; i<(psize*1024); i++){
            fwrite(&buffer, 1024, 1, archivo);
        }
        fclose(archivo);
    }

    prueba.mbr_fecha_creacion = time(nullptr);
    prueba.mbr_dsk_signature = (rand()% 100);//Numero random para la etiqueta del disco

    char auxfit = 0;
    if(pfit == "bf" || "BF"){
        auxfit = 'B';
    }else if(pfit == "ff" || pfit == "FF"){
        auxfit = 'F';
    }else if(pfit == "wf" || pfit == "WF"){
        auxfit = 'W';
    }

    prueba.dsk_fit = auxfit;

    for(int p = 0; p < 4; p++){
        prueba.mbr_partition[p].part_status = '0';
        prueba.mbr_partition[p].part_type = '0';
        prueba.mbr_partition[p].part_fit = '0';
        prueba.mbr_partition[p].part_size = 0;
        prueba.mbr_partition[p].part_start = -1;
        strcpy(prueba.mbr_partition[p].part_name,"");
    }

    archivo = fopen(rutax.c_str(), "rb+");
    fseek(archivo, 0, SEEK_SET);
    fwrite(&prueba, sizeof(mbr), 1, archivo);
    fclose(archivo);
    cout<<"Disco creado correctamente"<<endl;
    cout<<"Se agrego el mbr de manera correcta \n"<<endl;
}

void coman_mkdisk::creandoRuta(QString path){
    QString aux = obtener_path(path);
    string comando = "sudo mkdir -p \'"+aux.toStdString()+"\'";
    cout << comando << endl;
    system(comando.c_str());
    string comando2 = "sudo chmod -R 777 \'"+aux.toStdString()+"\'";
    system(comando2.c_str());
    string arch = path.toStdString();
    FILE *archivo = fopen(arch.c_str(),"wb");
    if((archivo = fopen(arch.c_str(),"wb")))
        fclose(archivo);
    else
        cout << "Error: Al crear el Disco" << endl;
}

QString coman_mkdisk::obtener_path(QString path){

    string aux = path.toStdString();
    string delimiter = "/";
    size_t pos = 0;
    string res = "";
    while((pos = aux.find(delimiter))!=string::npos){
        res += aux.substr(0,pos)+"/";
        aux.erase(0,pos + delimiter.length());
    }
    cout << res << endl;
    return QString::fromStdString(res);
}






