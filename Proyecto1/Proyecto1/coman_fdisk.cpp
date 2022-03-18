#include "coman_fdisk.h"

coman_fdisk::coman_fdisk()
{

}

void coman_fdisk::recorrido_fdisk(Nodo_arbol *raiz){
    bool bandera_error = false;
    bool bandera_size = false;
    bool bandera_path = false;
    bool bandera_delete = false;
    bool bandera_name = false;
    bool bandera_add = false;
    bool bandera_type = false;
    bool bandera_fit = false;
    int valor_size = 0;
    QString valor_path = "";
    string valor_unit = "k";
    string valor_type = "primaria";
    string valor_fit = "wf";
    QString valor_delete = "";
    QString valor_name = "";
    int valor_add = 0;

    for(int c = 0; c < raiz->hijos.count(); c++){
        Nodo_arbol temp = raiz->hijos.at(c);
        if(temp.tipo_num == SIZE){
            if(temp.valor.toUInt()>0){
                valor_size = temp.valor.toUInt();
                bandera_size = true;
            }else{
                bandera_error = true;
                std::cout<<"Los valores de size no pueden ser menores o iguales a cero \n";
            }
        }else if(temp.tipo_num == UNIT){
            valor_unit = temp.hijos.at(0).valor.toStdString();
        }else if(temp.tipo_num == PATH){
            bandera_path = true;
            valor_path = temp.valor;
            valor_path.replace(QString("\""), QString(""));
            //std::cout<<valor_path.toStdString()<<"\n";
        }else if(temp.tipo_num == TYPE){
            bandera_type = true;
            valor_type = temp.hijos.at(0).valor.toStdString();
        }else if(temp.tipo_num == FIT){
            bandera_fit = true;
            valor_fit = temp.hijos.at(0).valor.toStdString();
        }else if(temp.tipo_num == DELETE){
            bandera_delete = true;
            valor_delete = temp.hijos.at(0).valor;
        }else if(temp.tipo_num == NAME){
            bandera_name = true;
            valor_name = temp.valor;
            valor_name.replace(QString("\""), QString(""));
            //std::cout<<valor_name.toStdString()<<"\n";
        }else if(temp.tipo_num == ADD){
            bandera_add = true;
            valor_add = temp.valor.toInt();
        }
    }

    if(bandera_path == false){
        bandera_error = true;
        std::cout<<"Error: El parametro -path es obligatorio \n";
    }

    if(bandera_name == false){
        bandera_error = true;
        std::cout<<"Error: El parametro -name es obligatorio \n";
    }

    if(bandera_error == false){
        if(bandera_size == true){
            if(bandera_delete == true || bandera_add == true){
                bandera_error = true;
                std::cout<<"Error: Se esta creando una particion, los Parametros -delete, -add no estan permitidos\n";
            }else{
                //std::cout<<"Todo Correcto para crear una particion!!! \n";
                crear_particiones(valor_type, valor_path, valor_name, valor_size, valor_fit, valor_unit);
            }
        }else if(bandera_add == true){
            if(bandera_delete == true || bandera_size == true || bandera_type == true){
                bandera_error = true;
                std::cout<<"Error: Se esta modificando el tamaño una particion, los Parametros -delete, -size y -type no estas permitidos \n";
            }else{
                std::cout<<"Todo Correcto para crear una ADD!!! \n";
                comando_add(valor_path, valor_name, valor_add, valor_unit, "principal");
            }
        }else if(bandera_delete == true){
            if(bandera_size == true || bandera_add == true || bandera_fit == true || bandera_type == true){
                std::cout<<"Error: Se esta eliminando una particion, los Parametros -size, -add, -fit, -type no estan permitidos \n";
            }else{
                //std::cout<<"Todo Correcto para crear una DELETE!!! \n";
                string eleccion = "";
                cout << "¿Esta seguro que desea eliminar el disco? S/N : ";
                getline(cin, eleccion);
                if(eleccion.compare("s") == 0 || eleccion.compare("S") == 0){
                    eliminarParticion(valor_path, valor_name, valor_delete.toStdString(), "principal");
                }else if(eleccion.compare("n") == 0 || eleccion.compare("N") == 0){
                    cout << "Eliminacion cancelada \n";
                }else{
                    cout << "Esa opcion no esta permitida \n";
                }
            }
        }
    }
}

void coman_fdisk::crear_particiones(string ptype, QString ppath, QString pname, int psize, string pfit, string punit){
    //std::cout<<"El valor de type es: "<<ptype<<"\n";
    //std::cout<<"El valor de path es: "<<ppath.toStdString()<<"\n";
    //std::cout<<"El valor de name es: "<<pname.toStdString()<<"\n";
    //std::cout<<"El valor de size es: "<<psize<<"\n";
    //std::cout<<"El valor de fit es: "<<pfit<<"\n";
    //std::cout<<"El valor de unit es: "<<punit<<"\n";
    if(ptype == "primaria" || ptype == "PRIMARIA"){
        if(existe_archivo(ppath)){
            crearParticionPrimaria(ppath, pname, psize, pfit, punit, "principal");
        }else{
            std::cout<<"Error: No se encontro el disco \n";
        }
    }else if(ptype == "extendida" || ptype == "EXTENDIDA"){
        if(existe_archivo(ppath)){
            crearParticionExtendida(ppath, pname, psize, pfit, punit, "principal");
        }else{
            std::cout<<"Error: No se encontro el disco \n";
        }
    }else if(ptype == "logica" || ptype == "LOGICA"){
        if(existe_archivo(ppath)){
            crearParticionLogica(ppath, pname, psize, pfit, punit, "principal");
        }
    }
}

void coman_fdisk::crearParticionPrimaria(QString path, QString nombre, int size, string fit, string unit, QString archivo){
    //std::cout<<"El valor de path en particion p es: "<<path.toStdString()<<"\n";
    //std::cout<<"El valor de name en particion p es: "<<nombre.toStdString()<<"\n";
    //std::cout<<"El valor de size en particion p es: "<<size<<"\n";
    //std::cout<<"El valor de fit en particion p es: "<<fit<<"\n";
    //std::cout<<"El valor de unit en particion p es: "<<unit<<"\n";

    char auxFit = 0;
    char auxUnit = 0;
    string auxPath = path.toStdString();
    int size_bytes = 1024;
    char buffer = '1';

    if(fit == "bf" || fit == "BF"){
        auxFit = 'B';
    }else if(fit == "ff" || fit == "FF"){
        auxFit = 'F';
    }else if(fit == "wf" || fit == "WF"){
        auxFit = 'W';
    }

    if(unit == "b" || unit == "B"){
        auxUnit = 'b';
        size_bytes = size;
    }else if(unit == "k" || unit == "K"){
        auxUnit = 'k';
        size_bytes = size * 1024;
    }else if(unit == "m" || unit == "M"){
        auxUnit = 'm';
        size_bytes = size * 1024 * 1024;
    }

    FILE *Archivo;
    mbr MBR;

    if((Archivo = fopen(auxPath.c_str(), "rb+"))){
        bool flagParticion = false;//Flag para ver si hay una particion disponible
        int numParticion = 0;//Que numero de particion es
        fseek(Archivo,0,SEEK_SET);
        fread(&MBR,sizeof(mbr),1,Archivo);
        //Verificar si existe una particion disponible
        for(int i = 0; i < 4; i++){
            if(MBR.mbr_partition[i].part_start == -1 || (MBR.mbr_partition[i].part_status == '1' && MBR.mbr_partition[i].part_size>=size_bytes)){
                flagParticion = true;
                numParticion = i;
                break;
            }
        }

        //cout << "Espacio Disponible Actual: " << (MBR.mbr_tamano) << " Bytes" << endl;

        if(flagParticion){
            //Verificar el espacio libre del disco
            int espacioUsado = 0;
            for(int i = 0; i < 4; i++){
                if(MBR.mbr_partition[i].part_status!='1'){
                    espacioUsado += MBR.mbr_partition[i].part_size;
                }
            }

            //cout << "Espacio Que se esta restando: " << (espacioUsado) << " Bytes" << endl;

            if(archivo == "principal"){
                cout << "Espacio Disponible: " << (MBR.mbr_tamano - espacioUsado) << " Bytes" << endl;
                cout << "Espacio Requerido:  " << size_bytes << " Bytes" << endl;
            }
            //Verificar que haya espacio suficiente para crear la particion
            if((MBR.mbr_tamano - espacioUsado) >= size_bytes){
                if(!existeParticion(path.toStdString(),nombre.toStdString())){
                    if(MBR.dsk_fit == 'F'){//FIRST FIT
                        MBR.mbr_partition[numParticion].part_type = 'P';
                        MBR.mbr_partition[numParticion].part_fit = auxFit;
                        //start
                        if(numParticion == 0){
                            MBR.mbr_partition[numParticion].part_start = sizeof(MBR);
                        }else{
                            MBR.mbr_partition[numParticion].part_start = MBR.mbr_partition[numParticion-1].part_start + MBR.mbr_partition[numParticion-1].part_size;
                        }
                        MBR.mbr_partition[numParticion].part_size = size_bytes;
                        MBR.mbr_partition[numParticion].part_status = '0';
                        strcpy(MBR.mbr_partition[numParticion].part_name,nombre.toStdString().c_str());
                        //Se guarda de nuevo el MBR
                        fseek(Archivo,0,SEEK_SET);
                        fwrite(&MBR,sizeof(mbr),1,Archivo);
                        //Se guardan los bytes de la particion
                        fseek(Archivo,MBR.mbr_partition[numParticion].part_start,SEEK_SET);
                        for(int i = 0; i < size_bytes; i++){
                            fwrite(&buffer,1,1,Archivo);
                        }
                        if(archivo == "principal") cout << "Particion primaria creada con exito" <<  endl;
                    }else if(MBR.dsk_fit == 'B'){//BEST FIT
                        int bestIndex = numParticion;
                        for(int i = 0; i < 4; i++){
                            if(MBR.mbr_partition[i].part_start == -1 || (MBR.mbr_partition[i].part_status == '1' && MBR.mbr_partition[i].part_size>=size_bytes)){
                                if(i != numParticion){
                                    if(MBR.mbr_partition[bestIndex].part_size > MBR.mbr_partition[i].part_size){
                                        bestIndex = i;
                                        break;
                                    }
                                }
                            }
                        }
                        MBR.mbr_partition[bestIndex].part_type = 'P';
                        MBR.mbr_partition[bestIndex].part_fit = auxFit;
                        //start
                        if(bestIndex == 0){
                            MBR.mbr_partition[bestIndex].part_start = sizeof(MBR);
                        }else{
                            MBR.mbr_partition[bestIndex].part_start = MBR.mbr_partition[bestIndex-1].part_start + MBR.mbr_partition[bestIndex-1].part_size;
                        }
                        MBR.mbr_partition[bestIndex].part_size = size_bytes;
                        MBR.mbr_partition[bestIndex].part_status = '0';
                        strcpy(MBR.mbr_partition[bestIndex].part_name,nombre.toStdString().c_str());
                        //Se guarda de nuevo el MBR
                        fseek(Archivo,0,SEEK_SET);
                        fwrite(&MBR,sizeof(mbr),1,Archivo);
                        //Se guardan los bytes de la particion
                        fseek(Archivo,MBR.mbr_partition[bestIndex].part_start,SEEK_SET);
                        for(int i = 0; i < size_bytes; i++){
                            fwrite(&buffer,1,1,Archivo);
                        }
                        if(archivo == "principal") cout << "Particion primaria creada con exito" <<  endl;
                    }else if(MBR.dsk_fit == 'W'){//WORST FIT
                        int  worstIndex= numParticion;
                        for(int i = 0; i < 4; i++){
                            if(MBR.mbr_partition[i].part_start == -1 || (MBR.mbr_partition[i].part_status == '1' && MBR.mbr_partition[i].part_size>=size_bytes)){
                                if(i != numParticion){
                                    if(MBR.mbr_partition[worstIndex].part_size < MBR.mbr_partition[i].part_size){
                                        worstIndex = i;
                                        break;
                                    }
                                }
                            }
                        }
                        MBR.mbr_partition[worstIndex].part_type = 'P';
                        MBR.mbr_partition[worstIndex].part_fit = auxFit;
                        //start
                        if(worstIndex == 0){
                            MBR.mbr_partition[worstIndex].part_start = sizeof(MBR);
                        }else{
                            MBR.mbr_partition[worstIndex].part_start = MBR.mbr_partition[worstIndex-1].part_start + MBR.mbr_partition[worstIndex-1].part_size;
                        }
                        MBR.mbr_partition[worstIndex].part_size = size_bytes;
                        MBR.mbr_partition[worstIndex].part_status = '0';
                        strcpy(MBR.mbr_partition[worstIndex].part_name,nombre.toStdString().c_str());
                        //Se guarda de nuevo el MBR
                        fseek(Archivo,0,SEEK_SET);
                        fwrite(&MBR,sizeof(mbr),1,Archivo);
                        //Se guardan los bytes de la particion
                        fseek(Archivo,MBR.mbr_partition[worstIndex].part_start,SEEK_SET);
                        for(int i = 0; i < size_bytes; i++){
                            fwrite(&buffer,1,1,Archivo);
                        }
                        if(archivo == "principal") cout << "Particion primaria creada con exito" <<  endl;
                    }
                }else{
                    cout << "Error: ya existe una particion con ese nombre" << endl;
                }

            }else{
                cout << "Error: la particion a crear excede el espacio libre" << endl;
            }
        }else{
            cout << "Error: Ya existen 4 particiones, no se puede crear otra" << endl;
            cout << "Elimine alguna para poder crear una" << endl;
        }
    fclose(Archivo);
    }else{
        cout << "Error: no existe el disco" << endl;
    }
}

void coman_fdisk::crearParticionExtendida(QString path, QString nombre, int size, string fit, string unit, QString archivo){
    //std::cout<<"El valor de path en particion E es: "<<path.toStdString()<<"\n";
    //std::cout<<"El valor de name en particion E es: "<<nombre.toStdString()<<"\n";
    //std::cout<<"El valor de size en particion E es: "<<size<<"\n";
    //std::cout<<"El valor de fit en particion E es: "<<fit<<"\n";
    //std::cout<<"El valor de unit en particion E es: "<<unit<<"\n";

    char auxFit = 0;
    char auxUnit = 0;
    string auxPath = path.toStdString();
    int size_bytes = 1024;
    char buffer = '1';

    if(fit == "bf" || fit == "BF"){
        auxFit='B';
    }
    else if(fit == "ff" || fit == "FF"){
        auxFit='F';
    }
    else if(fit == "wf" || fit == "WF"){
        auxFit='W';
    }

    if(unit == "b" || unit == "B"){
        auxUnit='b';
        size_bytes = size;
    }
    else if(unit == "k" || unit == "K"){
        auxUnit='k';
        size_bytes = size * 1024;
    }
    else if(unit == "m" || unit == "M"){
        auxUnit='m';
        size_bytes = size*1024*1024;
    }

    FILE *Archivo;
    mbr MBR;
    if((Archivo = fopen(auxPath.c_str(), "rb+"))){
        bool flagParticion = false;//Flag para ver si hay una particion disponible
        bool flagExtendida = false;//Flag para ver si ya hay una particion extendida
        int numParticion = 0;//Que numero de particion es
        fseek(Archivo,0,SEEK_SET);
        fread(&MBR,sizeof(mbr),1,Archivo);
        for(int i = 0; i < 4; i++){
            if (MBR.mbr_partition[i].part_type == 'E'){
                flagExtendida = true;
                break;
            }
        }
        if(!flagExtendida){
            //Verificar si existe una particion disponible
            for(int i = 0; i < 4; i++){
                if(MBR.mbr_partition[i].part_start == -1 || (MBR.mbr_partition[i].part_status == '1' && MBR.mbr_partition[i].part_size>=size_bytes)){
                    flagParticion = true;
                    numParticion = i;
                    break;
                }
            }
            if(flagParticion){
                //Verificar el espacio libre del disco
                int espacioUsado = 0;
                for(int i = 0; i < 4; i++){
                    if(MBR.mbr_partition[i].part_status!='1'){
                       espacioUsado += MBR.mbr_partition[i].part_size;
                    }
                }
                if(archivo == "principal"){
                    cout << "Espacio disponible: " << (MBR.mbr_tamano - espacioUsado) <<" Bytes"<< endl;
                    cout << "Espacio Requerido:  " << size_bytes << " Bytes" << endl;
                }
                //Verificar que haya espacio suficiente para crear la particion
                if((MBR.mbr_tamano - espacioUsado) >= size_bytes){
                    if(!(existeParticion(path.toStdString(),nombre.toStdString()))){
                        if(MBR.dsk_fit == 'F'){
                            MBR.mbr_partition[numParticion].part_type = 'E';
                            MBR.mbr_partition[numParticion].part_fit = auxFit;
                            //start
                            if(numParticion == 0){
                                MBR.mbr_partition[numParticion].part_start = sizeof(MBR);
                            }else{
                                MBR.mbr_partition[numParticion].part_start =  MBR.mbr_partition[numParticion-1].part_start + MBR.mbr_partition[numParticion-1].part_size;
                            }
                            MBR.mbr_partition[numParticion].part_size = size_bytes;
                            MBR.mbr_partition[numParticion].part_status = '0';
                            strcpy(MBR.mbr_partition[numParticion].part_name,nombre.toStdString().c_str());
                            //Se guarda de nuevo el MBR
                            fseek(Archivo,0,SEEK_SET);
                            fwrite(&MBR,sizeof(mbr),1,Archivo);
                            //Se guarda la particion extendida
                            fseek(Archivo, MBR.mbr_partition[numParticion].part_start,SEEK_SET);
                            ebr EBR;
                            EBR.part_fit = auxFit;
                            EBR.part_status = '0';
                            EBR.part_start = MBR.mbr_partition[numParticion].part_start;
                            EBR.part_size = 0;
                            EBR.part_next = -1;
                            strcpy(EBR.part_name, "");
                            fwrite(&EBR,sizeof (ebr),1,Archivo);
                            for(int i = 0; i < (size_bytes - (int)sizeof(ebr)); i++){
                                fwrite(&buffer,1,1,Archivo);
                            }
                            if(archivo == "principal") cout << "Particion extendida creada con exito"<< endl;
                        }else if(MBR.dsk_fit == 'B'){
                            int bestIndex = numParticion;
                            for(int i = 0; i < 4; i++){
                                if(MBR.mbr_partition[i].part_start == -1 || (MBR.mbr_partition[i].part_status == '1' && MBR.mbr_partition[i].part_size>=size_bytes)){
                                    if(i != numParticion){
                                        if(MBR.mbr_partition[bestIndex].part_size > MBR.mbr_partition[i].part_size){
                                            bestIndex = i;
                                            break;
                                        }
                                    }
                                }
                            }
                            MBR.mbr_partition[bestIndex].part_type = 'E';
                            MBR.mbr_partition[bestIndex].part_fit = auxFit;
                            //start
                            if(bestIndex == 0){
                                MBR.mbr_partition[bestIndex].part_start = sizeof(MBR);
                            }else{
                                MBR.mbr_partition[bestIndex].part_start =  MBR.mbr_partition[bestIndex-1].part_start + MBR.mbr_partition[bestIndex-1].part_size;
                            }
                            MBR.mbr_partition[bestIndex].part_size = size_bytes;
                            MBR.mbr_partition[bestIndex].part_status = '0';
                            strcpy(MBR.mbr_partition[bestIndex].part_name,nombre.toStdString().c_str());
                            //Se guarda de nuevo el MBR
                            fseek(Archivo,0,SEEK_SET);
                            fwrite(&MBR,sizeof(mbr),1,Archivo);
                            //Se guarda la particion extendida
                            fseek(Archivo, MBR.mbr_partition[bestIndex].part_start,SEEK_SET);
                            ebr EBR;
                            EBR.part_fit = auxFit;
                            EBR.part_status = '0';
                            EBR.part_start = MBR.mbr_partition[bestIndex].part_start;
                            EBR.part_size = 0;
                            EBR.part_next = -1;
                            strcpy(EBR.part_name, "");
                            fwrite(&EBR,sizeof (ebr),1,Archivo);
                            for(int i = 0; i < (size_bytes - (int)sizeof(ebr)); i++){
                                fwrite(&buffer,1,1,Archivo);
                            }
                            if(archivo == "principal") cout << "Particion extendida creada con exito"<< endl;
                        }else if(MBR.dsk_fit == 'W'){
                            int  worstIndex= numParticion;
                            for(int i = 0; i < 4; i++){
                                if(MBR.mbr_partition[i].part_start == -1 || (MBR.mbr_partition[i].part_status == '1' && MBR.mbr_partition[i].part_size>=size_bytes)){
                                    if(i != numParticion){
                                        if(MBR.mbr_partition[worstIndex].part_size < MBR.mbr_partition[i].part_size){
                                            worstIndex = i;
                                            break;
                                        }
                                    }
                                }
                            }
                            MBR.mbr_partition[worstIndex].part_type = 'E';
                            MBR.mbr_partition[worstIndex].part_fit = auxFit;
                            //start
                            if(worstIndex == 0){
                                MBR.mbr_partition[worstIndex].part_start = sizeof(MBR);
                            }else{
                                MBR.mbr_partition[worstIndex].part_start =  MBR.mbr_partition[worstIndex-1].part_start + MBR.mbr_partition[worstIndex-1].part_size;
                            }
                            MBR.mbr_partition[worstIndex].part_size = size_bytes;
                            MBR.mbr_partition[worstIndex].part_status = '0';
                            strcpy(MBR.mbr_partition[worstIndex].part_name,nombre.toStdString().c_str());
                            //Se guarda de nuevo el MBR
                            fseek(Archivo,0,SEEK_SET);
                            fwrite(&MBR,sizeof(mbr),1,Archivo);
                            //Se guarda la particion extendida
                            fseek(Archivo, MBR.mbr_partition[worstIndex].part_start,SEEK_SET);
                            ebr EBR;
                            EBR.part_fit = auxFit;
                            EBR.part_status = '0';
                            EBR.part_start = MBR.mbr_partition[worstIndex].part_start;
                            EBR.part_size = 0;
                            EBR.part_next = -1;
                            strcpy(EBR.part_name, "");
                            fwrite(&EBR,sizeof (ebr),1,Archivo);
                            for(int i = 0; i < (size_bytes - (int)sizeof(ebr)); i++){
                                fwrite(&buffer,1,1,Archivo);
                            }
                            if(archivo == "principal") cout << "Particion extendida creada con exito"<< endl;
                        }
                    }else{
                        cout << "ERROR: ya existe una particion con ese nombre" << endl;
                    }
                }else{
                    cout << "Error: la particion a crear excede el tamano libre" << endl;
                }
            }else{
                cout << "Error: Ya existen 4 particiones, no se puede crear otra." << endl;
                cout << "Elimine alguna para poder crear una" << endl;
            }
        }else{
            cout << "Error: ya existe una particion extendida en este disco" << endl;
        }
    fclose(Archivo);
    }else{
        cout << "Error: no existe el disco" << endl;
    }
}

void coman_fdisk::crearParticionLogica(QString path, QString name, int size, string fit, string unit, QString archivo){
    char auxFit = 0;
    char auxUnit = 0;
    string auxPath = path.toStdString();
    int size_bytes = 1024;
    char buffer = '1';

    if(fit == "bf" || fit == "BF"){
        auxFit='B';
    }
    else if(fit == "ff" || fit == "FF"){
        auxFit='F';
    }
    else if(fit == "wf" || fit == "WF"){
        auxFit='W';
    }

    if(unit == "b" || unit == "B"){
        auxUnit='b';
        size_bytes = size;
    }
    else if(unit == "k" || unit == "K"){
        auxUnit='k';
        size_bytes = size * 1024;
    }
    else if(unit == "m" || unit == "M"){
        auxUnit='m';
        size_bytes = size*1024*1024;
    }

    FILE *Archivo;
    mbr MBR;
    if((Archivo = fopen(auxPath.c_str(), "rb+"))){
        int numExtendida = -1;
        fseek(Archivo,0,SEEK_SET);
        fread(&MBR,sizeof(mbr),1,Archivo);
        //Verificar si existe una particion extendida
        for(int i = 0; i < 4; i++){
            if(MBR.mbr_partition[i].part_type == 'E'){
                numExtendida = i;
                break;
            }
        }
        if(!existeParticion(path.toStdString(),name.toStdString())){
            if(numExtendida != -1){
                ebr EBR;
                int cont = MBR.mbr_partition[numExtendida].part_start;
                fseek(Archivo,cont,SEEK_SET);
                fread(&EBR, sizeof(ebr),1,Archivo);
                if(EBR.part_size == 0){//Si es la primera
                    if(MBR.mbr_partition[numExtendida].part_size < size_bytes){
                        if(archivo == "principal") cout << "Error: la particion logica a crear excede el espacio disponible de la particion extendida" << endl;
                    }else{
                        EBR.part_status = '0';
                        EBR.part_fit = auxFit;
                        EBR.part_start = ftell(Archivo) - sizeof(ebr); //Para regresar al inicio de la extendida
                        EBR.part_size = size_bytes;
                        EBR.part_next = -1;
                        strcpy(EBR.part_name, name.toStdString().c_str());
                        fseek(Archivo, MBR.mbr_partition[numExtendida].part_start ,SEEK_SET);
                        fwrite(&EBR,sizeof(ebr),1,Archivo);
                        if(archivo == "principal") cout << "Particion logica creada con exito"<< endl;
                    }
                }else{
                    while((EBR.part_next != -1) && (ftell(Archivo) < (MBR.mbr_partition[numExtendida].part_size + MBR.mbr_partition[numExtendida].part_start))){
                        fseek(Archivo,EBR.part_next,SEEK_SET);
                        fread(&EBR,sizeof(ebr),1,Archivo);
                    }
                    int espacioNecesario = EBR.part_start + EBR.part_size + size_bytes;
                    if(espacioNecesario <= (MBR.mbr_partition[numExtendida].part_size + MBR.mbr_partition[numExtendida].part_start)){
                        EBR.part_next = EBR.part_start + EBR.part_size;
                        //Escribimos el next del ultimo EBR
                        fseek(Archivo,ftell(Archivo) - sizeof (ebr),SEEK_SET);
                        fwrite(&EBR, sizeof(ebr),1 ,Archivo);
                        //Escribimos el nuevo EBR
                        fseek(Archivo,EBR.part_start + EBR.part_size, SEEK_SET);
                        EBR.part_status = 0;
                        EBR.part_fit = auxFit;
                        EBR.part_start = ftell(Archivo);
                        EBR.part_size = size_bytes;
                        EBR.part_next = -1;
                        strcpy(EBR.part_name, name.toStdString().c_str());
                        fwrite(&EBR,sizeof(ebr),1,Archivo);
                        if(archivo == "principal") cout << "Particion logica creada con exito"<< endl;
                    }else{
                        cout << "Error: la particion logica a crear excede el" << endl;
                        cout << "espacio disponible de la particion extendida" << endl;
                    }
                }
            }else{
                cout << "Error: se necesita una particion extendida donde guardar la logica" << endl;
            }
        }else{
            cout << "Error: ya existe una particion con ese nombre" << endl;
        }

    fclose(Archivo);
    }else{
        cout << "Error: no existe el disco" << endl;
    }

}

void coman_fdisk::eliminarParticion(QString path, QString name, string tipo_delete, QString archivo){
    //std::cout<<"El valor de path en eliminar particion es: "<<path.toStdString()<<"\n";
    //std::cout<<"El valor de name en eliminar particion es: "<<name.toStdString()<<"\n";
    //std::cout<<"El valor del tipo delete es: "<<tipo_delete<<"\n";
    string auxPath = path.toStdString();
    string auxNombre = name.toStdString();
    FILE *Archivo;
    if((Archivo = fopen(auxPath.c_str(), "rb+"))){
        //Verificar que la particion no este montada
        //bool mount = lista->buscarNodo(path,name);
        //if(!mount){
            mbr MBR;
            fseek(Archivo,0,SEEK_SET);
            fread(&MBR,sizeof (mbr),1,Archivo);
            int index = -1;
            int index_Extendida = -1;
            bool flagExtendida = false;
            //string opcion = "";
            char buffer = '\0';
            //Buscamos la particion primaria/extendida
            for(int i = 0; i < 4; i++){
                if((strcmp(MBR.mbr_partition[i].part_name, auxNombre.c_str())) == 0){
                    index = i;
                    if(MBR.mbr_partition[i].part_type == 'E')
                        flagExtendida = true;
                    break;
                }else if(MBR.mbr_partition[i].part_type == 'E'){
                    index_Extendida = i;
                }
            }
            //ELIMINA LAS PARTICIONES SI NO ESTAN MONTADAS
                if(index != -1){//Si se encontro en las principales
                    if(!flagExtendida){//primaria
                        if(tipo_delete == "fast"){
                            MBR.mbr_partition[index].part_status = '1';
                            strcpy(MBR.mbr_partition[index].part_name,"");
                            fseek(Archivo,0,SEEK_SET);
                            fwrite(&MBR,sizeof(mbr),1,Archivo);
                            if(archivo == "principal") cout << "Particion primaria eliminada con exito" << endl;

                        }else{//full
                            MBR.mbr_partition[index].part_status = '1';
                            strcpy(MBR.mbr_partition[index].part_name,"");
                            fseek(Archivo,0,SEEK_SET);
                            fwrite(&MBR,sizeof(mbr),1,Archivo);
                            fseek(Archivo,MBR.mbr_partition[index].part_start,SEEK_SET);
                            fwrite(&buffer,1,MBR.mbr_partition[index].part_size,Archivo);
                            if(archivo == "principal") cout << "Particion primaria eliminada con exito" << endl;
                        }
                    }else{//extendida
                        if(tipo_delete == "fast"){
                            MBR.mbr_partition[index].part_status = '1';
                            strcpy(MBR.mbr_partition[index].part_name,"");
                            fseek(Archivo,0,SEEK_SET);
                            fwrite(&MBR,sizeof(mbr),1,Archivo);
                            if(archivo == "principal") cout << "Particion extendida eliminada con exito" << endl;
                        }else{//full
                            MBR.mbr_partition[index].part_status = '1';
                            strcpy(MBR.mbr_partition[index].part_name,"");
                            fseek(Archivo,0,SEEK_SET);
                            fwrite(&MBR,sizeof(mbr),1,Archivo);
                            fseek(Archivo,MBR.mbr_partition[index].part_start,SEEK_SET);
                            fwrite(&buffer,1,MBR.mbr_partition[index].part_size,Archivo);
                            if(archivo == "principal") cout << "Particion extendida eliminada con exito" << endl;
                        }
                    }
                }else{//Si es una particion logica
                    if(index_Extendida != -1){
                        bool flag = false;//Bandera para saber si existe
                        ebr EBR;
                        fseek(Archivo,MBR.mbr_partition[index_Extendida].part_start, SEEK_SET);
                        fread(&EBR,sizeof(ebr),1,Archivo);
                        if(EBR.part_size!=0){
                            fseek(Archivo, MBR.mbr_partition[index_Extendida].part_start,SEEK_SET);
                            while((fread(&EBR,sizeof(ebr),1,Archivo))!=0 && (ftell(Archivo) < (MBR.mbr_partition[index_Extendida].part_start + MBR.mbr_partition[index_Extendida].part_size))) {
                                if(strcmp(EBR.part_name,name.toStdString().c_str()) == 0 && EBR.part_status != '1'){
                                    flag = true;
                                    break;
                                }else if(EBR.part_next == -1){//Ya es la ultima y no se encontro
                                    break;
                                }
                            }
                        }
                        if(flag){
                            if(tipo_delete == "fast"){
                                EBR.part_status = '1';
                                strcpy(EBR.part_name, "");
                                fseek(Archivo, ftell(Archivo)-sizeof(ebr),SEEK_SET);
                                fwrite(&EBR,sizeof(ebr),1,Archivo);
                                if(archivo == "principal") cout << "Particion logica eliminada con exito" << endl;
                            }else{//full
                                EBR.part_status = '1';
                                strcpy(EBR.part_name, "");
                                fseek(Archivo, ftell(Archivo)-sizeof(ebr),SEEK_SET);
                                fwrite(&EBR,sizeof(ebr),1,Archivo);
                                fwrite(&buffer,1,EBR.part_size,Archivo);
                                if(archivo == "principal") cout << "Particion logica eliminada con exito" << endl;
                            }
                        }else{
                            cout << "Error: no se encuentra la particion a eliminar" << endl;
                        }
                    }else{
                        cout << "Error: no se encuentra la particion a eliminar" << endl;
                    }
                }
        //}else{
            //cout << "ERROR: desmote primero la particion para poder eliminarlo" << endl;
        //}
    fclose(Archivo);
    }else{
        cout << "Error: el disco donde se va a eliminar no existe" << endl;
    }
}

void coman_fdisk::comando_add(QString path, QString name, int add, string unit, QString archivo){
    //std::cout<<"El valor de path para add es: "<<path.toStdString()<<"\n";
    //std::cout<<"El valor de name para add es: "<<name.toStdString()<<"\n";
    //std::cout<<"El valor de add es: "<<add<<"\n";
    //std::cout<<"El valor de unit para add es: "<<unit<<"\n";

    string auxPath = path.toStdString();
    string auxNombre = name.toStdString();
    int size_Bytes = 0;
    QString tipo = "";

    if(add > 0){
        tipo = "add";
    }

    if(tipo != "add"){
        add = add*(-1);
    }

    if(unit == "m" || unit == "M"){
        size_Bytes = add * 1024 * 1024;
    }
    else if(unit == "k" || unit == "K"){
        size_Bytes = add * 1024;
    }
    else{
        size_Bytes = add;
    }

    FILE *Archivo;
    if((Archivo = fopen(auxPath.c_str(), "rb+"))){
        //Verificar que la particion no este montada
        //bool mount = lista->buscarNodo(path,name);
        //if(!mount){
            mbr MBR;
            fseek(Archivo,0,SEEK_SET);
            fread(&MBR,sizeof(mbr),1,Archivo);
            int index = -1;
            int index_Extendida = -1;
            bool flagExtendida = false;
            //Buscamos la particion primaria/extendida
            for(int i = 0; i < 4; i++){
                if((strcmp(MBR.mbr_partition[i].part_name, auxNombre.c_str())) == 0){
                    index = i;
                    if(MBR.mbr_partition[i].part_type == 'E')
                        flagExtendida = true;
                    break;
                }else if(MBR.mbr_partition[i].part_type == 'E'){
                    index_Extendida = i;
                }
            }
            if(index != -1){//Si se encontro en las principales
                if(!flagExtendida){//Primaria
                    if(tipo == "add"){//Agregar
                        //Verificar que exista espacio libre a la derecha
                        if(index!=3){
                            int p1 = MBR.mbr_partition[index].part_start + MBR.mbr_partition[index].part_size;
                            int p2 = MBR.mbr_partition[index+1].part_start;
                            if((p2 - p1) != 0){//Hay fragmentacion
                                int fragmentacion = p2-p1;
                                if(fragmentacion >= size_Bytes){
                                    MBR.mbr_partition[index].part_size = MBR.mbr_partition[index].part_size + size_Bytes;
                                    fseek(Archivo,0,SEEK_SET);
                                    fwrite(&MBR,sizeof(mbr),1,Archivo);
                                    if(archivo == "principal") cout << "Se agrego espacio a la particion de manera exitosa." << endl;
                                }else{
                                    cout << "ERROR: no es posible agregar espacio a la particion porque no hay suficiente espacio disponible a su derecha" << endl;
                                }
                            }else{//Espacio no usado
                                if(MBR.mbr_partition[index + 1].part_status == '1'){
                                    if(MBR.mbr_partition[index + 1].part_size >= size_Bytes){
                                        MBR.mbr_partition[index].part_size = MBR.mbr_partition[index].part_size + size_Bytes;
                                        MBR.mbr_partition[index + 1].part_size = (MBR.mbr_partition[index + 1].part_size - size_Bytes);
                                        MBR.mbr_partition[index + 1].part_start = MBR.mbr_partition[index + 1].part_start + size_Bytes;
                                        fseek(Archivo,0,SEEK_SET);
                                        fwrite(&MBR,sizeof(mbr),1,Archivo);
                                        if(archivo == "principal") cout << "Se agrego espacio a la particion de manera exitosa" << endl;
                                    }else{
                                        cout << "Error: no es posible agregar espacio a la particion porque no hay suficiente espacio disponible a su derecha" << endl;
                                    }
                                }
                            }
                        }else{
                            int p = MBR.mbr_partition[index].part_start + MBR.mbr_partition[index].part_size;
                            int total = MBR.mbr_tamano + (int)sizeof(mbr);
                            if((total-p) != 0){
                                int fragmentacion = total - p;
                                if(fragmentacion >= size_Bytes){
                                    MBR.mbr_partition[index].part_size = MBR.mbr_partition[index].part_size + size_Bytes;
                                    fseek(Archivo,0,SEEK_SET);
                                    fwrite(&MBR,sizeof(mbr),1,Archivo);
                                    if(archivo == "principal") cout << "Se agrego espacio a la particion de manera exitosa" << endl;
                                }else{
                                    cout << "Error: no es posible agregar espacio a la particion porque no hay suficiente espacio disponible a su derecha" << endl;
                                }
                            }else{
                                cout << "Error: no es posible agregar espacio a la particion porque no hay espacio disponible a su derecha" << endl;
                            }
                        }
                    }else{//Quitar espacio
                        //Que no borre la particion
                        if(size_Bytes >= MBR.mbr_partition[index].part_size){
                            cout << "Error: no es posible quitarle esta cantidad de espacio a la particion porque la borraria" << endl;
                        }else{
                            MBR.mbr_partition[index].part_size = MBR.mbr_partition[index].part_size - size_Bytes;
                            fseek(Archivo,0,SEEK_SET);
                            fwrite(&MBR,sizeof(mbr),1,Archivo);
                            if(archivo == "principal") cout << "Se quito espacio a la particion de manera exitosa" << endl;
                        }
                    }
                }else{//Extendida
                    if(tipo == "add"){//Agregar
                        //Verificar que exista espacio libre a la derecha
                        if(index!=3){
                            int p1 = MBR.mbr_partition[index].part_start + MBR.mbr_partition[index].part_size;
                            int p2 = MBR.mbr_partition[index+1].part_start;
                            if((p2 - p1) != 0){//Hay fragmentacion
                                int fragmentacion = p2-p1;
                                if(fragmentacion >= size_Bytes){
                                    MBR.mbr_partition[index].part_size = MBR.mbr_partition[index].part_size + size_Bytes;
                                    fseek(Archivo,0,SEEK_SET);
                                    fwrite(&MBR,sizeof(mbr),1,Archivo);
                                    if(archivo == "principal") cout << "Se agrego espacio a la particion de manera exitosa" << endl;
                                }else{
                                    cout << "Error: no es posible agregar espacio a la particion porque no hay suficiente espacio disponible a su derecha" << endl;
                                }
                            }else{
                                if(MBR.mbr_partition[index + 1].part_status == '1'){
                                    if(MBR.mbr_partition[index + 1].part_size >= size_Bytes){
                                        MBR.mbr_partition[index].part_size = MBR.mbr_partition[index].part_size + size_Bytes;
                                        MBR.mbr_partition[index + 1].part_size = (MBR.mbr_partition[index + 1].part_size - size_Bytes);
                                        MBR.mbr_partition[index + 1].part_start = MBR.mbr_partition[index + 1].part_start + size_Bytes;
                                        fseek(Archivo,0,SEEK_SET);
                                        fwrite(&MBR,sizeof(mbr),1,Archivo);
                                        if(archivo == "principal") cout << "Se agrego espacio a la particion de manera exitosa" << endl;
                                    }else{
                                        cout << "Error: no es posible agregar espacio a la particion porque no hay suficiente espacio disponible a su derecha" << endl;
                                    }
                                }
                            }
                        }else{
                            int p = MBR.mbr_partition[index].part_start + MBR.mbr_partition[index].part_size;
                            int total = MBR.mbr_tamano + (int)sizeof(mbr);
                            if((total-p) != 0){//Hay fragmentacion
                                int fragmentacion = total - p;
                                if(fragmentacion >= size_Bytes){
                                    MBR.mbr_partition[index].part_size = MBR.mbr_partition[index].part_size + size_Bytes;
                                    fseek(Archivo,0,SEEK_SET);
                                    fwrite(&MBR,sizeof(mbr),1,Archivo);
                                    if(archivo == "principal") cout << "Se agrego espacio a la particion de manera exitosa" << endl;
                                }else{
                                    cout << "Error: no es posible agregar espacio a la particion porque no hay suficiente espacio disponible a su derecha" << endl;
                                }
                            }else{
                                cout << "Error: no es posible agregar espacio a la particion porque no hay espacio disponible a su derecha" << endl;
                            }
                        }
                    }else{//Quitar espacio
                        //Que no borre la particion
                        if(size_Bytes >= MBR.mbr_partition[index_Extendida].part_size){
                            cout << "Error: no es posible quitarle esta cantidad de espacio a la particion porque la borraria" << endl;
                        }else{
                            ebr EBR;
                            fseek(Archivo, MBR.mbr_partition[index_Extendida].part_start,SEEK_SET);
                            fread(&EBR,sizeof(ebr),1,Archivo);
                            while((EBR.part_next != -1) && (ftell(Archivo) < (MBR.mbr_partition[index_Extendida].part_size + MBR.mbr_partition[index_Extendida].part_start))){
                                fseek(Archivo,EBR.part_next,SEEK_SET);
                                fread(&EBR,sizeof(ebr),1,Archivo);
                            }
                            int ultimaLogica = EBR.part_start+EBR.part_size;
                            int aux = (MBR.mbr_partition[index_Extendida].part_start + MBR.mbr_partition[index_Extendida].part_size) - size_Bytes;
                            if(aux > ultimaLogica){//No toca ninguna logica
                                MBR.mbr_partition[index_Extendida].part_size = MBR.mbr_partition[index_Extendida].part_size - size_Bytes;
                                fseek(Archivo,0,SEEK_SET);
                                fwrite(&MBR,sizeof(mbr),1,Archivo);
                                if(archivo == "principal") cout << "Se quito espacio a la particion de manera exitosa" << endl;
                            }else{
                                cout << "Error: si quita ese espacio danaria una logica" << endl;
                            }
                        }
                    }
                }
            }else{//Posiblemente logica
                if(index_Extendida != -1){
                    int logica = buscarParticion_L(path, name);
                    if(logica != -1){
                        if(tipo == "add"){
                            //Verificar que exista espacio libre a su derecha
                            ebr EBR;
                            fseek(Archivo,logica,SEEK_SET);
                            fread(&EBR,sizeof(ebr),1,Archivo);

                        }else{//Quitar
                            //Verificar que no la elimine
                            ebr EBR;
                            fseek(Archivo,logica,SEEK_SET);
                            fread(&EBR,sizeof(ebr),1,Archivo);
                            if(size_Bytes >= EBR.part_size){
                                cout << "Error: si quita ese espacio eliminaria la logica" << endl;
                            }else{
                                EBR.part_size = EBR.part_size - size_Bytes;
                                fseek(Archivo,logica,SEEK_SET);
                                fwrite(&EBR,sizeof(ebr),1,Archivo);
                                if(archivo == "principal") cout << "Se quito espacio a la particion de manera exitosa" << endl;
                            }
                        }
                    }else{
                        cout << "Error: no se encuentra la particion" << endl;
                    }
                }else{
                    cout << "Error: no se encuentra la particion a redimensionar" << endl;
                }
            }
        //}else{
             //cout << "Error: desmonte primero la particion para poder redimensionar" << endl;
        //}
    fclose(Archivo);
    }else{
        cout << "Error: el disco donde se desea agregar/quitar unidades no existe" << endl;
    }
}

int coman_fdisk::buscarParticion_L(QString path, QString name){
    string auxPath = path.toStdString();
    string auxName = name.toStdString();
    FILE *Archivo;
    if((Archivo = fopen(auxPath.c_str(),"rb+"))){
        int extendida = -1;
        mbr MBR;
        fseek(Archivo,0,SEEK_SET);
        fread(&MBR,sizeof(mbr),1,Archivo);
        for(int i = 0; i < 4; i++){
            if(MBR.mbr_partition[i].part_type == 'E'){
                extendida = i;
                break;
            }
        }
        if(extendida != -1){
            ebr EBR;
            fseek(Archivo, MBR.mbr_partition[extendida].part_start,SEEK_SET);
            while(fread(&EBR,sizeof(ebr),1,Archivo)!=0 && (ftell(Archivo) < MBR.mbr_partition[extendida].part_start + MBR.mbr_partition[extendida].part_size)){
                if(strcmp(EBR.part_name, auxName.c_str()) == 0){
                    return (ftell(Archivo) - sizeof(ebr));
                }
            }
        }
        fclose(Archivo);
    }
    return -1;
}

bool coman_fdisk::existe_archivo(QString path){
    QFileInfo check_file(path);
    if (check_file.exists() && check_file.isFile()) {
        return true;
    } else {
        return false;
    }
}

bool coman_fdisk::existeParticion(string path, string name){
    int extendida = -1;
    FILE *Archivo;
    if((Archivo = fopen(path.c_str(),"rb+"))){
        mbr MBR;
        fseek(Archivo,0,SEEK_SET);
        fread(&MBR, sizeof(mbr),1,Archivo);
        for(int i = 0; i < 4; i++){
            if(strcmp(MBR.mbr_partition[i].part_name,name.c_str()) == 0){
                fclose(Archivo);
                return true;
            }else if(MBR.mbr_partition[i].part_type == 'E'){
                extendida = i;
            }
        }
        if(extendida != -1){
            fseek(Archivo, MBR.mbr_partition[extendida].part_start,SEEK_SET);
            ebr EBR;
            while((fread(&EBR,sizeof(ebr),1,Archivo))!=0 && (ftell(Archivo) < (MBR.mbr_partition[extendida].part_size + MBR.mbr_partition[extendida].part_start))){
                if(strcmp(EBR.part_name,name.c_str()) == 0){
                    fclose(Archivo);
                    return true;
                }
                if(EBR.part_next == -1){
                    fclose(Archivo);
                    return false;
                }
            }
        }
    }
    fclose(Archivo);
    return false;
}
