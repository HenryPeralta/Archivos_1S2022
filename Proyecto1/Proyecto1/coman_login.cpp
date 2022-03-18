#include "coman_login.h"

coman_login::coman_login()
{

}

coman_login::coman_login(List_particiones *lista, int *id_usuario, QString *usuario, QString *id_mount, QString *grupo, int *id_grupo, n_particiones *part_global){
    this->lista = lista;
    this->id_usuario = id_usuario;
    this->usuario = usuario;
    this->id_mount = id_mount;
    this->grupo = grupo;
    this->id_grupo = id_grupo;
    this->part_global = part_global;
}

void coman_login::recorrer_login(Nodo_arbol *raiz){
    bool bandera_error = false;
    bool bandera_usuario = false;
    bool bandera_password = false;
    bool bandera_id = false;
    QString valor_usuario = "";
    QString valor_password = "";
    QString valor_id = "";

    for(int i = 0; i < raiz->hijos.count(); i++){
        Nodo_arbol temp = raiz->hijos.at(i);
        if(temp.tipo_num == USUARIO){
            bandera_usuario = true;
            valor_usuario = temp.valor;
            valor_usuario.replace(QString("\""), QString(""));
        }else if(temp.tipo_num == PASSWORD){
            bandera_password = true;
            valor_password = temp.valor;
            valor_password.replace(QString("\""), QString(""));
        }else if(temp.tipo_num == ID){
            bandera_id = true;
            valor_id = temp.valor;
            valor_id.replace(QString("\""), QString(""));
        }
    }

    if(bandera_usuario == false){
        bandera_error = true;
        std::cout<<"Error: El parametro -usuario es obligatorio \n";
    }
    if(bandera_password == false){
        bandera_error = true;
        std::cout<<"Error: El parametro -password es obligatorio \n";
    }
    if(bandera_id == false){
        bandera_error = true;
        std::cout<<"Error: El parametro -id es obligatorio \n";
    }
    if(bandera_error == false){
        crearUsuarios(valor_usuario, valor_password, valor_id);
    }
}

void coman_login::crearUsuarios(QString usuario, QString password, QString id){
    //cout<<usuario.toStdString()<<endl;
    //cout<<password.toStdString()<<endl;
    //cout<<id.toStdString()<<endl;
    if(*id_usuario == -1){
        n_particiones encontrado = lista->getParticionMontada(id);
        if(encontrado.path.size() > 0){
            *part_global = encontrado;
            FILE* Archivo = fopen(part_global->path.toStdString().c_str(), "rb+");
            if(Archivo != NULL){
                int inicioByte = 0;
                if(part_global->part_type == 'P'){
                    inicioByte = part_global->particiones.part_start;
                    valores archivo(Archivo, part_global, inicioByte);
                    int id_user = archivo.iniciarSesion(usuario, password);
                    if(id_user > 0){
                        *this->id_usuario = id_user;
                        *this->usuario = usuario;
                        *this->id_mount = id.toStdString().c_str();
                        *this->grupo = archivo.group;
                        *this->id_grupo = archivo.group_id;
                        cout<<"Bienvenido!!"<<endl;
                        cout<<"Se ha iniciado sesion con el Usuario: "<<this->usuario->toStdString()<<" Id: "<<*id_usuario<<" Id_Grupo: "<< *id_grupo<<endl<<endl;
                    }else{
                        part_global->path = "";
                        cout<<"Error: el usuario o password no existen"<<endl;
                    }
                }
                else if(part_global->part_type == 'l'){
                    inicioByte = part_global->particion_logica.part_start + sizeof(ebr);
                    valores archivo(Archivo, part_global, inicioByte);
                    int id_user = archivo.iniciarSesion(usuario, password);
                    if(id_user > 0){
                        *this->id_usuario = id_user;
                        *this->usuario = usuario;
                        *this->id_mount = id.toStdString().c_str();
                        *this->grupo = archivo.group;
                        *this->id_grupo = archivo.group_id;
                        cout<<"Bienvenido!!"<<endl;
                        cout<<"Se ha iniciado sesion con el Usuario: "<<this->usuario->toStdString()<<" Id: "<<*id_usuario<<" Id_Grupo: "<< *id_grupo<<endl<<endl;
                    }else{
                        part_global->path = "";
                        cout<<"Error: el usuario o password no existen"<<endl;
                    }
                }else{
                    cout<<"Error: la particion no existe"<<endl;
                }
                fclose(Archivo);
            }else{
                cout<<"Error: disco no encontrado"<<endl;
            }
        }else{
            cout<<"Error: el id ingresado no existe"<<endl;
        }
    }else{
        cout<<"Error: ya hay una sesion iniciada, para iniciar otra cierre esta sesion con el comando logout"<<endl;
    }
}
