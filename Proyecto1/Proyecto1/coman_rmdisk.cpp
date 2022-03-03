#include "coman_rmdisk.h"

coman_rmdisk::coman_rmdisk()
{

}

void coman_rmdisk :: recorrido_rmdisk(Nodo_arbol *raiz){
    QString path = raiz->valor;
    path.replace(QString("\""), QString(""));
    string rutax = path.toStdString();

    QString ruta = rutax.c_str();
    FILE *archivo;
    if((archivo=fopen(ruta.toStdString().c_str(),"r"))){
        string opcion = "";
        cout << "¿Esta seguro que desea eliminar el disco? S/N : ";
        getline(cin, opcion);
        if(opcion.compare("S") == 0 || opcion.compare("s") == 0){
            string comando = "rm \""+ruta.toStdString()+"\"";
            system(comando.c_str());
            cout<< "Disco eliminado con exito \n" <<  endl;
        }else if(opcion.compare("N") == 0 || opcion.compare("n") == 0){
            cout << "Operacion Cancelada" << endl;
        }else{
            cout << "Error: No existe la particion seleccionada" << endl;
        }
        fclose(archivo);
    }else{
        cout << "No Existe el disco que desea eliminar" << endl;
    }
}
