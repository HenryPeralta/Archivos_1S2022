#include "coman_mkfs.h"

coman_mkfs::coman_mkfs()
{

}

void coman_mkfs::recorrer_mkfs(QList<Nodo_arbol> *hijos){
    bool bandera_id = false;
    QString valor_id = "";
    QString valor_tipoD = "full";
    QString valor_fs = "2fs";

    for(int c = 0; c < hijos->length(); c++){
        if(hijos->at(c).tipo.toStdString().compare("id") == 0){
            bandera_id = true;
            valor_id = hijos->at(c).valor;
            valor_id.replace(QString("\""), QString(""));
        }else if(hijos->at(c).tipo.toStdString().compare("type") == 0){
            valor_tipoD = hijos->at(c).valor;
        }else if(hijos->at(c).tipo.toStdString().compare("fs") == 0){
            valor_fs = hijos->at(c).valor;
        }
    }

    if(bandera_id == false){
        cout<<"Error: el parametro -id es obligatorio"<<endl;
    }else{
        ejecutar_mkfs(valor_id, valor_tipoD, valor_fs);
    }
}

void coman_mkfs::ejecutar_mkfs(QString id, QString type, QString fs){
    //cout<<id.toStdString()<<endl;
    //cout<<type.toStdString()<<endl;
    //cout<<fs.toStdString()<<endl;
    n_particiones encontrado = lista->getParticionMontada(id);
    if(encontrado.path.size() > 0){
        FILE *Archivo = fopen(encontrado.path.toStdString().c_str(), "rb+");
        if(Archivo != NULL){
            if(encontrado.part_type == 'P'){
                valores::formatearParticion(Archivo, encontrado.particiones, type.toStdString(), fs.toStdString());
                int inicioByte = encontrado.particiones.part_start;
                valores archivo(Archivo, &encontrado, inicioByte);
                archivo.userInformacion("root", 1, "root", 1);
                QStringList contenido;
                contenido.append("1, G, root\n1, U, root, root, 123\n");
                QStringList file_name;
                file_name.append("user.txt");
                inodos actual = valores::getInodo(Archivo, archivo.super.s_inode_start, 0);
                archivo.crearArchivo_(actual, contenido, file_name, 0, false);
                archivo.actualizarSuperBloque();
                cout<<"EDD creados exitosamente"<<endl;
            }else if(encontrado.part_type == 'l'){
                valores::formatearPart_logica(Archivo, encontrado.particion_logica, type.toStdString(), fs.toStdString());
                int inicioByte = encontrado.particion_logica.part_start + sizeof(ebr);
                valores archivo(Archivo, &encontrado, inicioByte);
                archivo.userInformacion("root", 1,"root",1);
                QStringList contenido;
                contenido.append("1, G,root\n1, U, root, root, 123");
                QStringList file_name;
                file_name.append("user.txt");
                inodos actual = valores::getInodo(Archivo, archivo.super.s_inode_start, 0);
                archivo.crearArchivo_(actual, contenido, file_name, 0, false);
                archivo.actualizarSuperBloque();
                cout<<"EDD creados exitosamente"<<endl;
            }else{
                cout<<"Particion no existe"<<endl;
            }
            fclose(Archivo);
        }
    }else{
        cout<<"No se encontro la particion"<<endl;
    }
}





