#include "coman_mount.h"

coman_mount::coman_mount()
{

}

void coman_mount::recorrer_mount(QList<Nodo_arbol> *hijos){
    bool bandera_path = false;
    bool bandera_name = false;
    QString valor_path = "";
    QString valor_name = "";
    for(int c = 0; c < hijos->length(); c++){
        if(hijos->at(c).tipo.toStdString().compare("path") == 0){
            bandera_path = true;
            valor_path = hijos->at(c).valor;
            valor_path.replace(QString("\""), QString(""));
        }else if(hijos->at(c).tipo.toStdString().compare("name") == 0){
            bandera_name = true;
            valor_name = hijos->at(c).valor;
            valor_name.replace(QString("\""), QString(""));
        }
    }
    if(bandera_path == false){
        std::cout<<"Error: El parametro -path es obligatorio \n";
    }

    if(bandera_name == false){
        std::cout<<"Error: El parametro -name es obligatorio \n";
    }

    if(bandera_path == true && bandera_name == true){
        crear_mount(valor_path, valor_name);
    }
}

void coman_mount::crear_mount(QString path, QString name){
    //std::cout<<"El valor de path es: "<<path.toStdString()<<"\n";
    //std::cout<<"El valor de name es: "<<name.toStdString()<<"\n";

    int indexP = buscarParticion_P_E(path, name);
    if(indexP != -1){
        FILE *Archivo;
        if((Archivo = fopen(path.toStdString().c_str(), "rb+"))){
            mbr MBR;
            fseek(Archivo,0,SEEK_SET);
            fread(&MBR, sizeof(mbr), 1, Archivo);
            MBR.mbr_partition[indexP].part_status = '2';
            char temp_type = MBR.mbr_partition[indexP].part_type;
            particion temp_part = MBR.mbr_partition[indexP];
            fseek(Archivo, 0, SEEK_SET);
            fwrite(&MBR, sizeof(mbr), 1, Archivo);
            fclose(Archivo);
            int letra = lista->buscarLetra(path, name);
            if(letra == -1){
                cout<<"Error: la particion ya esta montada"<<endl;
            }else{
                int num = lista->buscarNumero(path, name);
                //cout<<"numero que deberia llevar: "<<num<<endl;
                char auxLetra = static_cast<char>(letra);
                string id = "89";
                id += to_string(num) + auxLetra;
                n_particiones *n = new n_particiones(path, name, auxLetra, num, temp_type);
                n->particiones = temp_part;
                lista->insertarNodo(n);
                cout<<"Particion montada con exito"<<endl;
            }
        }else{
            cout<<"Error: no se encontro el disco"<<endl;
        }
    }else{
        int indexP = buscarParticion_L(path, name);
        if(indexP != -1){
            FILE *Archivo;
            if((Archivo = fopen(path.toStdString().c_str(), "rb+"))){
                ebr EBR;
                fseek(Archivo, indexP, SEEK_SET);
                fread(&EBR,sizeof(ebr),1,Archivo);
                EBR.part_status = '2';
                ebr temp_part = EBR;
                fseek(Archivo,indexP,SEEK_SET);
                fwrite(&EBR,sizeof(ebr),1,Archivo);
                fclose(Archivo);

                int letra = lista->buscarLetra(path, name);
                if(letra == -1){
                    cout<<"Error: la particion ya esta montada"<<endl;
                }else{
                    int num = lista->buscarNumero(path, name);
                    char auxLetra = static_cast<char>(letra);
                    string id = "89";
                    id += to_string(num) + auxLetra;
                    n_particiones *n = new n_particiones(path, name, auxLetra, num, 'l');
                    n->particion_logica = temp_part;
                    lista->insertarNodo(n);
                    cout<<"Particion montada con exito"<<endl;
                }
            }else{
                cout<<"Error: no se encontro el disco"<<endl;
            }
        }else{
            cout<<"No se encuentra la particion a montar"<<endl;
        }
    }
}

int coman_mount::buscarParticion_P_E(QString path, QString name){
    string auxPath = path.toStdString();
    string auxName = name.toStdString();
    FILE *Archivo;
    if((Archivo = fopen(auxPath.c_str(), "rb+"))){
        mbr MBR;
        fseek(Archivo,0,SEEK_SET);
        fread(&MBR,sizeof(mbr),1,Archivo);
        for(int i = 0; i < 4; i++){
            if(MBR.mbr_partition[i].part_status != '1'){
                if(strcmp(MBR.mbr_partition[i].part_name, auxName.c_str()) == 0){
                    return i;
                }
            }
        }
    }
    return -1;
}

int coman_mount::buscarParticion_L(QString path, QString name){
    string auxPath = path.toStdString();
    string auxName = name.toStdString();
    FILE *Archivo;
    if((Archivo = fopen(auxPath.c_str(), "rb+"))){
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
            fseek(Archivo, MBR.mbr_partition[extendida].part_start, SEEK_SET);
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




