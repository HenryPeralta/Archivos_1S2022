#include "valores.h"

valores::valores()
{

}

void valores::formatearParticion(FILE *Archivo, particion particiones, string type, string fs){
    int no_struct = calNoStructs(particiones.part_size, particiones.part_type, fs);
    if(no_struct > 0){
        int inicio_byte = particiones.part_start;
        superbloque s_bloque;
        s_bloque.s_inodes_count = no_struct;
        s_bloque.s_blocks_count = (no_struct * 3);
        s_bloque.s_free_blocks_count = (no_struct * 3);
        s_bloque.s_free_inodes_count = no_struct;
        s_bloque.s_mtime = time(NULL);
        s_bloque.s_umtime = time(NULL);
        s_bloque.s_mnt_count = 1;
        s_bloque.s_magic = 0xEF53;
        s_bloque.s_inode_size = sizeof(inodos);
        s_bloque.s_block_size = SIZE_BLOCKS;
        s_bloque.s_firts_ino = 0;
        s_bloque.s_first_blo = 0;
        int fileSystem = 0;
        if(QString::compare(fs.c_str(), "3fs", Qt::CaseInsensitive)==0){
            fileSystem = 3;
        }else{
            fileSystem = 2;
        }

        switch(fileSystem){
            case 2:
                s_bloque.s_filesystem_type = 2;
                s_bloque.s_bm_inode_start = (inicio_byte + sizeof(superbloque));
                s_bloque.s_bm_block_start = (inicio_byte + sizeof(superbloque) + no_struct);
                s_bloque.s_inode_start = (inicio_byte + sizeof(superbloque) + no_struct + (3*no_struct));
                s_bloque.s_block_start = (inicio_byte + sizeof(superbloque) + no_struct + (3*no_struct) + (no_struct * sizeof(inodos)));
            break;
            case 3:
                s_bloque.s_filesystem_type = 3;
                s_bloque.s_bm_inode_start = (inicio_byte + sizeof(superbloque) + (no_struct * sizeof(journal)) );
                s_bloque.s_bm_block_start = (inicio_byte + sizeof(superbloque) + (no_struct * sizeof(journal)) +  no_struct);
                s_bloque.s_inode_start = (inicio_byte + sizeof(superbloque) + (no_struct * sizeof(journal)) + no_struct + (3*no_struct));
                s_bloque.s_block_start = (inicio_byte + sizeof(superbloque) + (no_struct * sizeof(journal)) + no_struct + (3*no_struct) + (no_struct * sizeof(inodos)));

                info_journal init;
                init.max = no_struct;
                init.last = 1;

                journal first;
                first.tipo = '0';

                first.date = time(NULL);
                first.next = -1;

                strcpy(first.nombre,"/");
                strcpy(first.operacion,"mkdir");
                strcpy(first.content,"-----");
                fseek(Archivo, inicio_byte + sizeof(superbloque), SEEK_SET);
                fwrite(&init, sizeof(info_journal), 1, Archivo);

                fseek(Archivo, inicio_byte + sizeof(superbloque) + sizeof(journal), SEEK_SET);
                fwrite(&first, sizeof(journal), 1, Archivo);
            break;
        }
        crearCarpetaRaiz(Archivo, s_bloque, inicio_byte);
        cout<<"Se ha formateado la partición correctamente"<<endl<<endl;
    }else{
        cout<<"Error: La particion o el -fs no es correcto"<<endl;
    }
}

void valores::formatearPart_logica(FILE *Archivo, ebr particion, string type, string fs){
    int no_struct = calNoStructs(particion.part_size, 'L', fs);
    if(no_struct > 0){
        int inicio_byte = particion.part_start + sizeof(ebr);
        superbloque s_bloque;
        s_bloque.s_inodes_count = no_struct;
        s_bloque.s_blocks_count = (no_struct * 3);
        s_bloque.s_free_blocks_count = (no_struct * 3);
        s_bloque.s_free_inodes_count = no_struct;
        s_bloque.s_mtime = time(NULL);
        s_bloque.s_umtime = time(NULL);
        s_bloque.s_mnt_count = 1;
        s_bloque.s_magic = 0xEF53;
        s_bloque.s_inode_size = sizeof(inodos);
        s_bloque.s_block_size = SIZE_BLOCKS;
        s_bloque.s_firts_ino = 0;
        s_bloque.s_first_blo = 0;

        int fileSystem = 0;
        if(QString::compare(fs.c_str(), "3fs", Qt::CaseInsensitive)==0){
            fileSystem = 3;
        }else{
            fileSystem = 2;
        }

        switch(fileSystem){
            case 2:
                s_bloque.s_filesystem_type = 2;
                s_bloque.s_bm_inode_start = (inicio_byte + sizeof(superbloque));
                s_bloque.s_bm_block_start = (inicio_byte + sizeof(superbloque) + no_struct);
                s_bloque.s_inode_start = (inicio_byte + sizeof(superbloque) + no_struct + (3*no_struct));
                s_bloque.s_block_start = (inicio_byte + sizeof(superbloque) + no_struct + (3*no_struct) + (no_struct * sizeof(inodos)));
            break;
            case 3:
                s_bloque.s_filesystem_type = 3;
                s_bloque.s_bm_inode_start = (inicio_byte + sizeof(superbloque) + (no_struct * sizeof(journal)) );
                s_bloque.s_bm_block_start = (inicio_byte + sizeof(superbloque) + (no_struct * sizeof(journal)) +  no_struct);
                s_bloque.s_inode_start = (inicio_byte + sizeof(superbloque) + (no_struct * sizeof(journal)) + no_struct + (3*no_struct));
                s_bloque.s_block_start = (inicio_byte + sizeof(superbloque) + (no_struct * sizeof(journal)) + no_struct + (3*no_struct) + (no_struct * sizeof(inodos)));

                info_journal init;
                init.max = no_struct;
                init.last = 1;

                journal first;
                first.tipo = '0';//Carpeta

                first.date = time(NULL);
                first.next = -1;
                strcpy(first.nombre,"/");
                strcpy(first.operacion,"mkdir");
                strcpy(first.content,"-----");
                fseek(Archivo, inicio_byte + sizeof(superbloque), SEEK_SET);
                fwrite(&init, sizeof(info_journal), 1, Archivo);

                fseek(Archivo, inicio_byte + sizeof(superbloque) + sizeof(journal), SEEK_SET);
                fwrite(&first, sizeof(journal), 1, Archivo);
            break;
        }
        crearCarpetaRaiz(Archivo, s_bloque, inicio_byte);
        cout<<"Se ha formateado la partición correctamente"<<endl<<endl;
    }else{
        cout<<"Error: La particion o el -fs no es correcto"<<endl;
    }
}

void valores::crearCarpetaRaiz(FILE *disco, superbloque &s_block, int inicio_byte){
    int no_struct = s_block.s_inodes_count;
    //Bitmap inodos
    char bitmap_inodos[no_struct];
    for(int i= 0; i < no_struct; i++){
        bitmap_inodos[i] = '0';
    }
    //Bitmap bloques
    char bitmap_blocks[(no_struct * 3)];
    for(int i= 0; i < (no_struct * 3); i++){
        bitmap_blocks[i] = '0';
    }

    //Crear Carpeta raiz
    inodos inodo;
    inodo.i_uid = 1;
    inodo.i_gid = 1;
    inodo.i_size = 0;
    inodo.i_atime = time(NULL);
    inodo.i_ctime = time(NULL);
    inodo.i_mtime = time(NULL);
    inodo.i_block = 0;
    inodo.i_type = '0';//Carpeta
    inodo.i_perm = 000;
    //Ocupamos el bloque 0 en el bitmap inodos
    bitmap_inodos[0] = '1';
    s_block.s_free_inodes_count--;

    //Crear Nodo apuntador----------------------------------------------
    bapuntador apuntador0;
    bitmap_blocks[0] = '1';//Ocupamos el primer espacio en bitmap bloques
    s_block.s_free_blocks_count--;
    //Ocupamos el primer espacio del bloque apuntador
    //y lo apuntamos a el bloque carpeta(bloque 1)
    apuntador0.b_pointers[0] = 1;
    for(int i= 1; i < 16 ; i++){
        apuntador0.b_pointers[i] = -1;
    }
    //Crer Bloque carpeta------------------------------------------------
    bcarpeta carpeta1;
    bitmap_blocks[1] = '1';//Ocupamos el segundo espacio en bitmap bloques
    s_block.s_free_blocks_count--;
    for (int i=0; i < 4; i++) {
        carpeta1.b_content[i].b_inodo = -1;
    }

    //Escribir el primer inodo en la posicion 0
    escribirInodo(disco, inodo, s_block.s_inode_start, 0);
    //Escribir bloques
    escribirBloque(disco, apuntador0, s_block.s_block_start, 0);
    escribirBloque(disco, carpeta1, s_block.s_block_start, 1);

    //Escribir bitmap_inodos
    fseek(disco, s_block.s_bm_inode_start, SEEK_SET);//Posicionamos el puntero al inicio de espacio bitmap inodos
    fwrite(&bitmap_inodos, 1, s_block.s_inodes_count, disco);//Escribimos el Bitmap inodos
    //Escribir bitmap_bloques
    fseek(disco, s_block.s_bm_block_start, SEEK_SET);//Posicionamos el puntero al inicio de espacio bitmap blocks
    fwrite(&bitmap_blocks, 1, s_block.s_blocks_count, disco);//Escribimos el Bitmap blocks
    //Escribir super bloque
    fseek(disco, inicio_byte, SEEK_SET);//Posicionamos el puntero al inicio de la particion
    fwrite(&s_block, sizeof(superbloque), 1, disco);//Escribimos el Superbloque
}

int valores::calNoStructs(int size_particion, char part_type, string fs){
    if(QString::compare(fs.c_str(), "2fs", Qt::CaseInsensitive) == 0){
        switch(part_type){
        case 'P':
            return floor((double)(size_particion - sizeof(superbloque))/(double)(4+sizeof(inodos)+(3*SIZE_BLOCKS)));
        case 'L':
            return floor((double)(size_particion - sizeof(superbloque)- sizeof(ebr))/(double)(4+sizeof(inodos)+(3*SIZE_BLOCKS)));
        default:
            return 0;
        }
    }else if(QString::compare(fs.c_str(), "3fs", Qt::CaseInsensitive) == 0){
        switch (part_type){
        case 'P':
            return floor((double)(size_particion - sizeof(superbloque))/(double)(4+sizeof(journal)+sizeof(inodos)+(3*SIZE_BLOCKS)));
        case 'L':
            return floor((double)(size_particion - sizeof(superbloque)- sizeof(ebr))/(double)(4+sizeof(journal)+sizeof(inodos)+(3*SIZE_BLOCKS)));
        default:
            return 0;
        }
    }else{
        return 0;
    }
}

void valores::userInformacion(QString user_name, int user_id, QString user_grp, int user_grp_id){
    this->user_name = user_name;
    this->user_id = user_id;
    this->user_grp = user_grp;
    this->user_grp_id = user_grp_id;
}

inodos valores::getInodo(FILE *Archivo, int inode_start, int posicion){
    inodos inodo;
    fseek(Archivo, inode_start + (sizeof(inodos) * posicion), SEEK_SET);
    fread(&inodo, sizeof(inodos), 1, Archivo);
    return inodo;
}

bapuntador valores::getBloqueApuntador(FILE *disco, int block_start, int posicion){
    bapuntador bloque;
    fseek(disco, block_start + (SIZE_BLOCKS * posicion), SEEK_SET);
    fread(&bloque, sizeof(bapuntador), 1, disco);
    return bloque;
}

bcarpeta valores::getBloqueCarpeta(FILE *disco, int block_start, int posicion){
    bcarpeta bloque;
    fseek(disco, block_start + (SIZE_BLOCKS * posicion), SEEK_SET);//Posicionamos el puntero al inicio del archivo
    fread(&bloque, sizeof(bcarpeta), 1, disco);
    return bloque;
}

void valores::escribirBloque(FILE *disco, bcarpeta block, int block_start, int posicion){
    //Posicionamos el puntero respecto donde inician los bloques en la particion
    fseek(disco, block_start + (SIZE_BLOCKS * posicion), SEEK_SET);
    //Escribimos el bloque en la particion
    fwrite(&block, sizeof(bcarpeta), 1, disco);
}

void valores::escribirBloque(FILE *disco, barchivo block, int block_start, int posicion){
    //Posicionamos el puntero respecto donde inician los bloques en la particion
    fseek(disco, block_start + (SIZE_BLOCKS * posicion), SEEK_SET);
    //Escribimos el bloque en la particion
    fwrite(&block, 1, SIZE_BLOCKS, disco);
}

void valores::escribirBloque(FILE *disco, bapuntador block, int block_start, int posicion){
    //Posicionamos el puntero respecto donde inician los bloques en la particion
    fseek(disco, block_start + (SIZE_BLOCKS * posicion), SEEK_SET);
    //Escribimos el bloque en la particion
    fwrite(&block, SIZE_BLOCKS, 1, disco);
}

void valores::escribirInodo(FILE *disco, inodos inodo, int inode_start, int posicion){
    //Posicionamos el puntero respecto donde inician los inodos en la particion
    fseek(disco, inode_start + (sizeof(inodos) * posicion), SEEK_SET);
    //Escribimos el inodo en la particion
    fwrite(&inodo, sizeof(inodos), 1, disco);
}

barchivo valores::getBloqueArchivo(FILE *disco, int block_start, int posicion){
    barchivo bloque;
    fseek(disco, block_start + (SIZE_BLOCKS * posicion), SEEK_SET);//Posicionamos el puntero al inicio del archivo
    fread(&bloque, 64, 1, disco);
    //cout<<endl<<"Bloque Get: "<<bloque.b_content[64]<<bloque.b_content[65]<<bloque.b_content[66]<<endl;
    return bloque;
}

QString valores::getPathString(QStringList path){
    QString txt;
    foreach (QString directory, path) {
        txt += "/"+directory;
    }
    return txt;
}

QString valores::getcontentString(QStringList content){
    QString txt;
    foreach (QString directory, content) {
        txt += directory;
        if(txt.size() > 130){break;}
    }
    return txt;
}

int valores::getFreeIndexBitmapInodo(){
    for (int i = 0; i < this->bitmap_inodo.size(); i ++) {
        if(bitmap_inodo[i] == '0'){
            bitmap_inodo[i] = '1';
            super.s_free_inodes_count--;
            return i;
        }
    }
    return -1;
}

void valores::agregarJournal(QString comando, QString nombre, QString contenido, char tipo){
    journal nuevo_journal;
    nuevo_journal.tipo = tipo;
    strcpy(nuevo_journal.operacion, comando.toStdString().c_str());
    strcpy(nuevo_journal.nombre, nombre.toStdString().c_str());
    strcpy(nuevo_journal.content, contenido.mid(0,230).toStdString().c_str());

    //EDITADO
    //time_t tiempo = time(0);
    //struct tm *tlocal = localtime(&tiempo);
    //strftime(nuevo_journal.date,16,"%d/%m/%y %H:%M",tlocal);



    nuevo_journal.date = time(NULL);



    nuevo_journal.next = -1;
    /*MODIFICACION PARA EL USUARIO*/
    strcpy(nuevo_journal.usuario, user_name.toStdString().c_str());

    if(journaling.size() == 0){
        journal_last.next = journal_info.last + 1;
    }
    else{
        journaling.last().next = journal_info.last + journaling.size() + 1;
    }
    journaling.append(nuevo_journal);
}

int valores::existInodobyName(inodos inodo_current, QString name_file_direc){
/* Retorna el indice(Mayor a 0) del inodo(Carpeta o archivo) que corresponde al nombre ingresado)
 * recorre todos los indices directos e indices indirectos.
 * Retorna -1 si no encontró algun inodo correspondiete al nombre
*/
    bapuntador inodo_apuntador = getBloqueApuntador(Archivo, super.s_block_start, inodo_current.i_block);
    for (int i = 0; i < 16; i++) {
        if(i <= 12){
            if(inodo_apuntador.b_pointers[i] >= 0){
                //Sacamos el bloque carpeta
                bcarpeta b_carpeta = getBloqueCarpeta(Archivo, super.s_block_start, inodo_apuntador.b_pointers[i]);
                for(int c = 0; c < 4; c++){
                    if(b_carpeta.b_content[c].b_inodo >= 0){
                        if(QString::compare(b_carpeta.b_content[c].b_name, name_file_direc,Qt::CaseSensitive) == 0){
                            return b_carpeta.b_content[c].b_inodo;
                        }
                    }
                }
            }
        }
        else if(i == 13){
            //Aparecen bloques apuntadores
            if(inodo_apuntador.b_pointers[i] >= 0){
                //Sacamos el bloque carpeta
                bapuntador b_apuntador = getBloqueApuntador(Archivo, super.s_block_start, inodo_apuntador.b_pointers[i]);
                int indice_inodo = getPositionInodobyName(name_file_direc, b_apuntador, 1);
                if(indice_inodo >= 0){
                    return indice_inodo;
                }

            }
        }
        else if(i == 14){
            //Aparecen bloques apuntadores
            if(inodo_apuntador.b_pointers[i] >= 0){
                //Sacamos el bloque carpeta
                bapuntador b_apuntador = getBloqueApuntador(Archivo, super.s_block_start, inodo_apuntador.b_pointers[i]);
                int indice_inodo = getPositionInodobyName(name_file_direc, b_apuntador, 2);
                if(indice_inodo >= 0){
                     return indice_inodo;
                }
            }

        }
        else if(i == 15){
            //Aparecen bloques apuntadores
            if(inodo_apuntador.b_pointers[i] >= 0){
                //Sacamos el bloque carpeta
                bapuntador b_apuntador = getBloqueApuntador(Archivo, super.s_block_start, inodo_apuntador.b_pointers[i]);
                int indice_inodo = getPositionInodobyName(name_file_direc, b_apuntador, 3);
                if(indice_inodo >= 0){
                     return indice_inodo;
                }
            }
        }
    }
    return -1;
}

int valores::getPositionInodobyName(QString name_file_direc, bapuntador b_apuntador,int nivel_puntero_indirecto){
/* Retorna la posición de un inodo ya sea archivo o carpeta, si no existe retornará -1
 * El metodo hará una busqueda en los bloques apuntadores, y dependerá del nivel especificado
 */
    if(nivel_puntero_indirecto >0 && nivel_puntero_indirecto <= 3){
        if(nivel_puntero_indirecto == 1){
            //Nivel indirecto  simple Hijos son bloques carptesa y archivos
            for (int i = 0; i < 16; i++) {
                int indice_b_carpeta = b_apuntador.b_pointers[i];
                if(indice_b_carpeta >= 0){
                    bcarpeta b_carpeta = getBloqueCarpeta(Archivo, super.s_inode_start, indice_b_carpeta);
                    for(int k = 0; k < 4; k++){
                        if( b_carpeta.b_content[k].b_inodo >= 0){
                            if(QString::compare(b_carpeta.b_content[k].b_name, name_file_direc, Qt::CaseSensitive)==0){
                                //Si el nombre es igual retornar el numero de inodo
                                return b_carpeta.b_content[k].b_inodo;
                            }
                        }
                    }
                }
            }
        }else if(nivel_puntero_indirecto == 2){
            //Nivel indirecto doble, Hijos son punteros indirectos simples
            //Recorriendo punteros dobles
            for (int i = 0; i < 16; i++) {
                int ind_b_indi_simple = b_apuntador.b_pointers[i];
                if(ind_b_indi_simple >= 0){
                    bapuntador b_apunt_simple = getBloqueApuntador(Archivo, super.s_inode_start, ind_b_indi_simple);
                    int resultado = getPositionInodobyName(name_file_direc, b_apunt_simple, 1);
                    if(resultado >= 0){
                        return resultado;
                    }
                }
            }

        }else{
            //Nivel indirecto triple, Hijos son punteros indirectos dobles
            //Recorriendo punteros triples
            for (int i = 0; i < 16; i++) {
                int ind_b_indi_doble = b_apuntador.b_pointers[i];
                if(ind_b_indi_doble >= 0){
                    bapuntador b_apunt_doble = getBloqueApuntador(Archivo, super.s_inode_start, ind_b_indi_doble);
                    int resultado = getPositionInodobyName(name_file_direc, b_apunt_doble, 2);
                    if(resultado >= 0){
                        return resultado;
                    }
                }
            }
        }
    }
    return -1;
}

int valores::crearArchivo(inodos inodo_current, QStringList contenido, QStringList &path, int pos_actual, bool p){
    /*
     * Retorna 0 si se guardó la carpeta
     * Retorna 1 con error
     * Retorna 2 no existen carpetas padres
     * Retorna 3 si el nombre ya existe
    */
    if((path.size() - pos_actual) == 1){
        //verificar si se tiene permiso de escritura del inodo actual
        //lectura, escritura, ejecucion
        if(user_id != 1){
            permiso p = verificarPermiso(inodo_current);
            if(p.escritura == 0){
                cout<<"\033[31mERROR: No tiene permisos para crear el archivo.\033[0m"<<endl<<endl;
                return 1;
            }
        }
        //Elimina si existe un archivo
        if(removerCarpeta_Archivo(inodo_current, path.value(pos_actual)) == 2){
            cout<<"\033[31mERROR: El archivo ya existe y no tiene permisos para sobreescribirlo.\033[0m"<<endl<<endl;
            return 1;
        }

        //En este caso estoy en el ultima carpeta del path
        //Por ello es la carpeta que se guarda y se buscará el espacio
        //Obtengo los apuntadores del inodo, el numero del bloque apuntador está en su variable i_block
        bapuntador inodo_apuntador = getBloqueApuntador(Archivo, super.s_block_start, inodo_current.i_block);
        //Recorremos los espacios de los apuntadores
        for(int b =0; b < 16; b++){
            int indice_puntero = inodo_apuntador.b_pointers[b];
            if(b <= 12 ){
                // De 0 a 12 es apuntador directo
                int resultado = escribirArchivo_(indice_puntero, path.value(pos_actual), contenido,0);
                if(resultado > 0){
                    inodo_apuntador.b_pointers[b] = resultado;
                    escribirBloque(Archivo, inodo_apuntador, super.s_block_start, inodo_current.i_block);
                    inodo_current.i_size += (contenido.size()*64);
                    agregarJournal("mkfile", getPathString(path), getcontentString(contenido), '1');
                    return 0;
                }else if(resultado == -1){
                    agregarJournal("mkfile", getPathString(path), getcontentString(contenido), '1');
                    return 0;
                }
            }
            else if(b == 13){
                //Aparecen bloques apuntadores nivel 1
                int resultado = escribirArchivo_(indice_puntero, path.value(pos_actual), contenido,1);
                if(resultado > 0){
                    inodo_apuntador.b_pointers[b] = resultado;
                    escribirBloque(Archivo, inodo_apuntador, super.s_block_start, inodo_current.i_block);
                    agregarJournal("mkfile", getPathString(path), getcontentString(contenido), '1');
                    return 0;
                }else if(resultado == -1){
                    agregarJournal("mkfile", getPathString(path), getcontentString(contenido), '1');
                    return 0;
                }
            }
            else if(b == 14){
                //Aparecen bloques apuntadores nivel 2
                int resultado = escribirArchivo_(indice_puntero, path.value(pos_actual), contenido,2);
                if(resultado > 0){
                    inodo_apuntador.b_pointers[b] = resultado;
                    escribirBloque(Archivo, inodo_apuntador, super.s_block_start, inodo_current.i_block);
                    agregarJournal("mkfile", getPathString(path), getcontentString(contenido), '1');
                    return 0;
                }else if(resultado == -1){
                    agregarJournal("mkfile", getPathString(path), getcontentString(contenido), '1');
                    return 0;
                }
            }
            else if(b == 15){
                //Aparecen bloques apuntadores nivel 3
                int resultado = escribirArchivo_(indice_puntero, path.value(pos_actual), contenido,3);
                if(resultado > 0){
                    inodo_apuntador.b_pointers[b] = resultado;
                    escribirBloque(Archivo, inodo_apuntador, super.s_block_start, inodo_current.i_block);
                    agregarJournal("mkfile", getPathString(path), getcontentString(contenido), '1');
                    return 0;
                }else if(resultado == -1){
                    agregarJournal("mkfile", getPathString(path), getcontentString(contenido), '1');
                    return 0;
                }
            }
        }
        return 1;
    }else{
        //En este caso aun tengo que llegar al final del path
        int indice_inodo_next = existInodobyName(inodo_current, path.value(pos_actual));
        int existeCarpeta = 2;
        if(indice_inodo_next > 0){
            inodos siguiente = getInodo(Archivo, super.s_inode_start, indice_inodo_next);
            if(siguiente.i_type == '0'){
                //Si el inodo es carpeta
                return crearArchivo_(siguiente, contenido, path, pos_actual+1, p);
            }
        }
        if(existeCarpeta == 2 && p){
            //Si no existe carptea y p = true crear todas las carpetas del path
            QStringList ruta;
            int resultado = 1;
            for(int i = 0; i < pos_actual; i++){
                ruta.append(path.value(i));
            }
            for (int i = pos_actual; i < path.size() ; i++) {
                ruta.append(path.value(i));
                if(i == path.size() -1){
                    resultado = crearArchivo_(inodo_current, contenido, ruta, pos_actual, false);
                }else{
                    resultado = crearCarpeta_(inodo_current, ruta, pos_actual,false);
                }
            }
            return resultado;
        }
        return 2;//Retorna cuando no existe las carpetas padres


    }
    return 0;
}

int valores::escribirArchivo(QStringList contenido){
/* Crea un inodod carpeta, su bloque apuntador y su bloque carpeta,
 * escribe las 3 estructuras en el archivo(disco)
 * Retorna el indice del inodo creado
 * Retorna -1 si hay error
*/

    int libre_inodo = getFreeIndexBitmapInodo();
    int bloque_apuntador_libre = getFreeIndexBitmapBlock();
    if(libre_inodo >= 0 && bloque_apuntador_libre >= 0 ){
        //Crear Carpeta raiz
        inodos inodo;
        inodo.i_uid = user_id;
        inodo.i_gid = user_grp_id;
        inodo.i_size = (contenido.size()*64);
        inodo.i_atime = time(NULL);
        inodo.i_ctime = time(NULL);
        inodo.i_mtime = time(NULL);
        inodo.i_block = bloque_apuntador_libre;//enlazamos inodo con blooque apuntador
        inodo.i_type = '1';//Archivo
        inodo.i_perm = 664;

        //Crear Nodo apuntador----------------------------------------------
        bapuntador apuntador;
        //Ocupamos el primer espacio del bloque apuntador
        //y lo apuntamos a el bloque carpeta(bloque 1)
        //apuntador.b_pointers[0] = bloque_carpeta_libre;

        for(int i= 0; i < 16 ; i++){
            apuntador.b_pointers[i] = -1;
        }

        if(contenido.size() > 0){
            //Si hay contenido lo crea
            int resultado = 0;
            QListIterator<QString> iter(contenido);
            resultado = crearBloquesArchivo(iter, apuntador);
            if(resultado != 0 ){return -1;}
        }
        //Escribir el inodo
        escribirInodo(Archivo, inodo, this->super.s_inode_start, libre_inodo);
        //Escribir bloques
        escribirBloque(Archivo, apuntador, this->super.s_block_start, bloque_apuntador_libre);
        return libre_inodo;

    }else{cout<<"\033[31mERROR: Ya no hay espacio para crear carpetas o archivos.\033[0m"<<endl<<endl; return -1;}
}

int valores::crearArchivo_(inodos inodo_current, QStringList contenido, QStringList &path, int pos_actual, bool p){
    /*
     * Retorna 0 si se guardó la carpeta
     * Retorna 1 con error
     * Retorna 2 no existen carpetas padres
     * Retorna 3 si el nombre ya existe
    */
    if((path.size() - pos_actual) == 1){
        //verificar si se tiene permiso de escritura del inodo actual
        //lectura, escritura, ejecucion
        if(user_id != 1){
            permiso p = verificarPermiso(inodo_current);
            if(p.escritura == 0){
                cout<<"\033[31mERROR: No tiene permisos para crear el archivo.\033[0m"<<endl<<endl;
                return 1;
            }
        }
        //Elimina si existe un archivo
        if(removerCarpeta_Archivo(inodo_current, path.value(pos_actual)) == 2){
            cout<<"\033[31mERROR: El archivo ya existe y no tiene permisos para sobreescribirlo.\033[0m"<<endl<<endl;
            return 1;
        }

        //En este caso estoy en el ultima carpeta del path
        //Por ello es la carpeta que se guarda y se buscará el espacio
        //Obtengo los apuntadores del inodo, el numero del bloque apuntador está en su variable i_block
        bapuntador inodo_apuntador = getBloqueApuntador(Archivo, super.s_block_start, inodo_current.i_block);
        //Recorremos los espacios de los apuntadores
        for(int b =0; b < 16; b++){
            int indice_puntero = inodo_apuntador.b_pointers[b];
            if(b <= 12 ){
                // De 0 a 12 es apuntador directo
                int resultado = escribirArchivo_(indice_puntero, path.value(pos_actual), contenido,0);
                if(resultado > 0){
                    inodo_apuntador.b_pointers[b] = resultado;
                    escribirBloque(Archivo, inodo_apuntador, super.s_block_start, inodo_current.i_block);
                    inodo_current.i_size += (contenido.size()*64);
                    agregarJournal("mkfile", getPathString(path), getcontentString(contenido), '1');
                    return 0;
                }else if(resultado == -1){
                    agregarJournal("mkfile", getPathString(path), getcontentString(contenido), '1');
                    return 0;
                }
            }
            else if(b == 13){
                //Aparecen bloques apuntadores nivel 1
                int resultado = escribirArchivo_(indice_puntero, path.value(pos_actual), contenido,1);
                if(resultado > 0){
                    inodo_apuntador.b_pointers[b] = resultado;
                    escribirBloque(Archivo, inodo_apuntador, super.s_block_start, inodo_current.i_block);
                    agregarJournal("mkfile", getPathString(path), getcontentString(contenido), '1');
                    return 0;
                }else if(resultado == -1){
                    agregarJournal("mkfile", getPathString(path), getcontentString(contenido), '1');
                    return 0;
                }
            }
            else if(b == 14){
                //Aparecen bloques apuntadores nivel 2
                int resultado = escribirArchivo_(indice_puntero, path.value(pos_actual), contenido,2);
                if(resultado > 0){
                    inodo_apuntador.b_pointers[b] = resultado;
                    escribirBloque(Archivo, inodo_apuntador, super.s_block_start, inodo_current.i_block);
                    agregarJournal("mkfile", getPathString(path), getcontentString(contenido), '1');
                    return 0;
                }else if(resultado == -1){
                    agregarJournal("mkfile", getPathString(path), getcontentString(contenido), '1');
                    return 0;
                }
            }
            else if(b == 15){
                //Aparecen bloques apuntadores nivel 3
                int resultado = escribirArchivo_(indice_puntero, path.value(pos_actual), contenido,3);
                if(resultado > 0){
                    inodo_apuntador.b_pointers[b] = resultado;
                    escribirBloque(Archivo, inodo_apuntador, super.s_block_start, inodo_current.i_block);
                    agregarJournal("mkfile", getPathString(path), getcontentString(contenido), '1');
                    return 0;
                }else if(resultado == -1){
                    agregarJournal("mkfile", getPathString(path), getcontentString(contenido), '1');
                    return 0;
                }
            }
        }
        return 1;
    }else{
        //En este caso aun tengo que llegar al final del path
        int indice_inodo_next = existInodobyName(inodo_current, path.value(pos_actual));
        int existeCarpeta = 2;
        if(indice_inodo_next > 0){
            inodos siguiente = getInodo(Archivo, super.s_inode_start, indice_inodo_next);
            if(siguiente.i_type == '0'){
                //Si el inodo es carpeta
                return crearArchivo_(siguiente, contenido, path, pos_actual+1, p);
            }
        }
        if(existeCarpeta == 2 && p){
            //Si no existe carptea y p = true crear todas las carpetas del path
            QStringList ruta;
            int resultado = 1;
            for(int i = 0; i < pos_actual; i++){
                ruta.append(path.value(i));
            }
            for (int i = pos_actual; i < path.size() ; i++) {
                ruta.append(path.value(i));
                if(i == path.size() -1){
                    resultado = crearArchivo_(inodo_current, contenido, ruta, pos_actual, false);
                }else{
                    resultado = crearCarpeta_(inodo_current, ruta, pos_actual,false);
                }
            }
            return resultado;
        }
        return 2;//Retorna cuando no existe las carpetas padres


    }
    return 0;
}

int valores::crearCarpeta_(inodos inodo_current, QStringList &path, int pos_actual, bool p){
    /*
     * Retorna 0 si se guardó la carpeta
     * Retorna 1 con error
     * Retorna 2 no existen carpetas padres
     * Retorna 3 si el nombre ya existe
    */
    if((path.size() - pos_actual) == 1){
        //verificar si se tiene permiso de escritura del inodo actual
        //lectura, escritura, ejecucion
        if(user_id != 1){
            permiso p = verificarPermiso(inodo_current);
            if(p.escritura == 0){
                cout<<"\033[31mERROR: No tiene permisos para crear la carpeta.\033[0m"<<endl<<endl;
                return 1;
            }
        }
        int nombre_existe =existInodobyName(inodo_current, path.value(pos_actual));
        if(nombre_existe > 0){return 3;}
        //En este caso estoy en el ultima carpeta del path
        //Por ello es la carpeta que se guarda y se buscará el espacio
        //Obtengo los apuntadores del inodo, el numero del bloque apuntador está en su variable i_block
        bapuntador inodo_apuntador = getBloqueApuntador(Archivo, super.s_block_start, inodo_current.i_block);
        //Recorremos los espacios de los apuntadores
        for(int b =0; b < 16; b++){
            int indice_puntero = inodo_apuntador.b_pointers[b];
            if(b <= 12 ){
                // De 0 a 12 es apuntador directo
                int resultado = escribirCarpeta_(indice_puntero, path.value(pos_actual),0);
                if(resultado > 0){
                    inodo_apuntador.b_pointers[b] = resultado;
                    escribirBloque(Archivo, inodo_apuntador, super.s_block_start, inodo_current.i_block);
                    agregarJournal("mkdir", getPathString(path), "-----", '0');
                    return 0;
                }else if(resultado == -1){
                    agregarJournal("mkdir", getPathString(path), "-----", '0');
                    return 0;
                }
            }
            else if(b == 13){
                //Aparecen bloques apuntadores nivel 1
                int resultado = escribirCarpeta_(indice_puntero, path.value(pos_actual),1);
                if(resultado > 0){
                    inodo_apuntador.b_pointers[b] = resultado;
                    escribirBloque(Archivo, inodo_apuntador, super.s_block_start, inodo_current.i_block);
                    agregarJournal("mkdir", getPathString(path), "-----", '0');
                    return 0;
                }else if(resultado == -1){
                    agregarJournal("mkdir", getPathString(path), "-----", '0');
                    return 0;
                }
            }
            else if(b == 14){
                //Aparecen bloques apuntadores nivel 2
                int resultado = escribirCarpeta_(indice_puntero, path.value(pos_actual),2);
                if(resultado > 0){
                    inodo_apuntador.b_pointers[b] = resultado;
                    escribirBloque(Archivo, inodo_apuntador, super.s_block_start, inodo_current.i_block);
                    agregarJournal("mkdir", getPathString(path), "-----", '0');
                    return 0;
                }else if(resultado == -1){
                    agregarJournal("mkdir", getPathString(path), "-----", '0');
                    return 0;
                }
            }
            else if(b == 15){
                //Aparecen bloques apuntadores nivel 3
                int resultado = escribirCarpeta_(indice_puntero, path.value(pos_actual),3);
                if(resultado > 0){
                    inodo_apuntador.b_pointers[b] = resultado;
                    escribirBloque(Archivo, inodo_apuntador, super.s_block_start, inodo_current.i_block);
                    agregarJournal("mkdir", getPathString(path), "-----", '0');
                    return 0;
                }else if(resultado == -1){
                    agregarJournal("mkdir", getPathString(path), "-----", '0');
                    return 0;
                }
            }
        }
        return 1;
    }else{
        //En este caso aun tengo que llegar al final del path

        int indice_inodo_next = existInodobyName(inodo_current, path.value(pos_actual));
        int existeCarpeta = 2;
        if(indice_inodo_next > 0){
            inodos siguiente = getInodo(Archivo, super.s_inode_start, indice_inodo_next);
            if(siguiente.i_type == '0'){
                //Si el inodo es carpeta
                return crearCarpeta_(siguiente, path, pos_actual+1, p);
            }
        }
        if(existeCarpeta == 2 && p){
            //Si no existe carptea y p = true crear todas las carpetas del path
            QStringList ruta;
            int resultado = 1;
            for(int i = 0; i < pos_actual; i++){
                ruta.append(path.value(i));
            }
            for (int i = pos_actual; i < path.size(); i++) {
                ruta.append(path.value(i));
                resultado = crearCarpeta_(inodo_current, ruta, pos_actual,false);
            }
            return resultado;
        }
        return 2;//Retorna cuando no existe las carpetas padres
    }
}

int valores::escribirCarpeta_(int puntero_actual, QString nombre_carpeta, int nivel_puntero_indirecto){
/*
 * Busca un espacio entre puntadores directos e indirectos
 * retorna un numero mayor igual 0 si se necesita enlazar
 * retorna -1 si la carpeta se creo
 * retorna -2 ecurrio un error no se creo la carpeta(Posiblemente no haya espacio para mas bloques)
 */

    if(nivel_puntero_indirecto >= 0 && nivel_puntero_indirecto <= 3){
        if(nivel_puntero_indirecto == 0){
            //Puntero directo
            if(puntero_actual == -1){

                int libre_bloque = getFreeIndexBitmapBlock();
                int libre_inodo = escribirCarpeta();
                if(libre_inodo >= 0){
                    bcarpeta carpeta;
                    carpeta.b_content[0].b_inodo = libre_inodo;
                    strcpy(carpeta.b_content[0].b_name, nombre_carpeta.toStdString().c_str());
                    for (int i=1; i < 4; i++) {
                        carpeta.b_content[i].b_inodo = -1;
                    }
                    escribirBloque(Archivo, carpeta, super.s_block_start, libre_bloque);
                    //cout<<"Carpeta creada correctamente"<<endl<<endl;
                    return libre_bloque;//para enlazar con puntero actual
                }
            }else{
                //Sacamos el bloque carpeta
                bcarpeta b_carpeta = getBloqueCarpeta(Archivo, super.s_block_start, puntero_actual);
                for(int i = 0; i < 4; i++){
                    if(b_carpeta.b_content[i].b_inodo == -1){
                        int libre_inodo = escribirCarpeta();
                        if(libre_inodo >= 0){
                            b_carpeta.b_content[i].b_inodo = libre_inodo;
                            strcpy(b_carpeta.b_content[i].b_name, nombre_carpeta.toStdString().c_str());
                            escribirBloque(Archivo, b_carpeta, super.s_block_start,puntero_actual);
                            //cout<<"Carpeta creada correctamente"<<endl<<endl;
                            return -1;
                        }
                    }
                }
            }
        }else{
            //puntero indirecto simple
            if(puntero_actual == -1){
                //Crear Bloques nivel 1 y crear carpeta
                int indice_nuevo = getFreeIndexBitmapBlock();
                bapuntador b_nuevo;
                for (int i = 0; i < 16; i++) {
                    b_nuevo.b_pointers[i] = -1;
                }
                int resultado = escribirCarpeta_(-1, nombre_carpeta, nivel_puntero_indirecto-1);
                if(resultado > 0){
                    b_nuevo.b_pointers[0] = resultado;
                    escribirBloque(Archivo, b_nuevo, super.s_block_start, indice_nuevo);
                    return indice_nuevo;
                }
            }else{
                //Recorrer bloques nivel 1, buscar espacio vacio(-1)
                //Nivel indirecto  simple Hijos son bloques carptesa y archivos
                bapuntador b_apuntador = getBloqueApuntador(Archivo, super.s_block_start, puntero_actual);
                for (int i = 0; i < 16; i++) {
                    int indice_b_carpeta = b_apuntador.b_pointers[i];
                    int resultado = escribirCarpeta_(indice_b_carpeta, nombre_carpeta, nivel_puntero_indirecto -1);
                    if(resultado > 0){
                        b_apuntador.b_pointers[i] = resultado;
                        escribirBloque(Archivo, b_apuntador, super.s_block_start, puntero_actual);
                        return -1;
                    }
                }
            }
        }
    }
    return -2;
}

int valores::escribirCarpeta(){
/* Crea un inodod carpeta, su bloque apuntador y su bloque carpeta,
 * escribe las 3 estructuras en el archivo(disco)
 * Retorna el indice del inodo creado
 * Retorna -1 si hay error
*/
    int libre_inodo = getFreeIndexBitmapInodo();
    int bloque_apuntador_libre = getFreeIndexBitmapBlock();
    int bloque_carpeta_libre = getFreeIndexBitmapBlock();
    if(libre_inodo >= 0 && bloque_apuntador_libre >= 0 && bloque_carpeta_libre > 0){
        //Crear Carpeta raiz
        inodos inodo;
        inodo.i_uid = user_id;
        inodo.i_gid = user_grp_id;
        inodo.i_size = 0;
        inodo.i_atime = time(NULL);
        inodo.i_ctime = time(NULL);
        inodo.i_mtime = time(NULL);
        inodo.i_block = bloque_apuntador_libre;//enlazamos inodo con blooque apuntador
        inodo.i_type = '0';//Carpeta
        inodo.i_perm = 664;

        //Crear Nodo apuntador----------------------------------------------
        bapuntador apuntador;
        //Ocupamos el primer espacio del bloque apuntador
        //y lo apuntamos a el bloque carpeta(bloque 1)
        apuntador.b_pointers[0] = bloque_carpeta_libre;
        for(int i= 1; i < 16 ; i++){
            apuntador.b_pointers[i] = -1;
        }
        //Crer Bloque carpeta------------------------------------------------
        bcarpeta carpeta;
        for (int i=0; i < 4; i++) {
            carpeta.b_content[i].b_inodo = -1;
        }

        //Escribir el inodo
        escribirInodo(Archivo, inodo, this->super.s_inode_start, libre_inodo);
        //Escribir bloques
        escribirBloque(Archivo, apuntador, this->super.s_block_start, bloque_apuntador_libre);
        escribirBloque(Archivo, carpeta, this->super.s_block_start, bloque_carpeta_libre);

        return libre_inodo;

    }else{cout<<"\033[31mERROR: Ya no hay espacio para crear carpetas o archivos.\033[0m"<<endl<<endl; return -1;}
}

permiso valores::getPermisoInodo(int permisos, char categoria){
    int digito = 0;
    switch (categoria) {
        case 'u': case 'U':
            digito = (float)permisos/(float)100;//resultado ultimo digito
        break;
        case 'g': case 'G':
            digito = (float)permisos/(float)10;
            digito = digito % 10;
        break;
        case 'o': case 'O':
            digito = permisos % 10;
        break;
        default:
            digito = 0;
    }
    permiso r;
    switch (digito) {
        case 0://000
            r.lectura = 0; r.escritura = 0; r.ejecucion = 0;
        break;
        case 1:
            r.lectura = 0; r.escritura = 0; r.ejecucion = 1;
        break;
        case 2:
            r.lectura = 0; r.escritura = 1; r.ejecucion = 0;
        break;
        case 3:
            r.lectura = 0; r.escritura = 1; r.ejecucion = 1;
        break;
        case 4:
            r.lectura = 1; r.escritura = 0; r.ejecucion = 0;
        break;
        case 5:
            r.lectura = 1; r.escritura = 0; r.ejecucion = 1;
        break;
        case 6:
            r.lectura = 1; r.escritura = 1; r.ejecucion = 0;
        break;
        case 7:
            r.lectura = 1; r.escritura = 1; r.ejecucion = 1;
        break;
        default:
            r.lectura = 0; r.escritura = 0; r.ejecucion = 0;
        break;
    }
    return r;
}

permiso valores::verificarPermiso(inodos inodo){
    //Si no es un usuario root
    int permisos = inodo.i_perm;
    if(inodo.i_uid == user_id){
        //La carpeta es propiedad del usuario(U)
        return getPermisoInodo(permisos, 'u');
    }
    else{
        //La carpeta no es propiedad del usuario
        if(inodo.i_gid == user_grp_id){
            return getPermisoInodo(permisos, 'g');
        }else{
            //Es otro usuario (O)
            return getPermisoInodo(permisos, 'o');
        }
    }
}

int valores::removerCarpeta_Archivo(inodos inodo_current, QString name_file_direc){
    //Retorna 0 si encontró y elimino la carpeta y archivo
    //Retorna 1 si no eliminó nada
        //Obtenemos los 16 apuntadores del inodo actual
        bapuntador inodo_apuntador = getBloqueApuntador(Archivo, super.s_block_start, inodo_current.i_block);
        int resultado = -1;
        //Buscamos espacios ocupados en los 16 apuntadores
        for (int i = 0; i < 16; i++) {
            if(resultado == 0){break;}
            if(i <= 12){
                resultado = removerCarpeta_Archivo2(name_file_direc, inodo_apuntador.b_pointers[i], 0);
            }
            else if(i == 13){
                resultado = removerCarpeta_Archivo2(name_file_direc, inodo_apuntador.b_pointers[i], 1);
            }
            else if(i == 14){
                resultado = removerCarpeta_Archivo2(name_file_direc, inodo_apuntador.b_pointers[i], 2);
            }
            else if(i == 15){
                resultado = removerCarpeta_Archivo2(name_file_direc, inodo_apuntador.b_pointers[i], 3);
            }
        }
        return resultado;
}

int valores::removerCarpeta_Archivo2(QString name_file_direc, int espacio_apuntador, int nivel_puntero_indirecto){
    //Retorna 0 si encontró y elimino la carpeta y archivo
    //Retorna 1 si no eliminó nada
    //Retorna 2 si no tiene permiso de eliminar
    if(nivel_puntero_indirecto >= 0 && nivel_puntero_indirecto <= 3){
        if(nivel_puntero_indirecto == 0){
            if(espacio_apuntador >= 0){
                //Sacamos el bloque carpeta
                bcarpeta b_carpeta = getBloqueCarpeta(Archivo, super.s_block_start, espacio_apuntador);
                //Buscamos en bloque carpeta si el nombre existe
                for(int c = 0; c < 4; c++){
                    if(b_carpeta.b_content[c].b_inodo >= 0){
                        if(QString::compare(b_carpeta.b_content[c].b_name, name_file_direc,Qt::CaseSensitive) == 0){
                            //Si el nombre de la carpeta o archivo existe entonces
                            //Eliminamos el inodo del bloque carpeta y el bitmap inodo
                            int indice_inodo = b_carpeta.b_content[c].b_inodo;
                            inodos encontrado = getInodo(Archivo, super.s_inode_start, indice_inodo);
                            if(user_id != 1){
                                permiso p = verificarPermiso(encontrado);
                                if(p.escritura == 0){
                                    return 2;
                                }
                            }
                            //Eliminamos todos los bloques e inodos
                            if(removeInodoHijos(encontrado) == 2){return 2;}
                            //Eliminamos el inodo del bloque carpeta
                            b_carpeta.b_content[c].b_inodo = -1;
                            //Eliminamos el inodo del bitmapInodo
                            liberarBitmapInodo(indice_inodo);
                             //Eliminamos el bloque apuntadores indirectos y directos
                            liberarBitmapBlock(encontrado.i_block);
                            //Actualizamos el bloque
                            escribirBloque(Archivo, b_carpeta,super.s_block_start, espacio_apuntador);
                            return 0;
                        }
                    }
                }
            }
        }
        else{
            if(espacio_apuntador >= 0){
                //Sacamos el bloque carpeta
                bapuntador b_apuntador = getBloqueApuntador(Archivo, super.s_block_start, espacio_apuntador);
                int result = 0;
                for (int i = 0; i < 16; i++) {
                    int verificar_espacio = b_apuntador.b_pointers[i];
                    result = removerCarpeta_Archivo2(name_file_direc, verificar_espacio, nivel_puntero_indirecto -1 );
                    if(result == 2){
                        return 2;
                    }
                }
            }
        }
    }
    return 1;
}

int valores::removeInodoHijos(inodos inodo){
    //Retorna 0 si elimino
    //Retorna 1 no se eliminó nada
    //Retorna 2 si no tiene permisos de eliminar
        bapuntador inodo_apuntador = getBloqueApuntador(Archivo, super.s_block_start, inodo.i_block);
        //Inodo Carpeta
        if(inodo.i_type == '0'){
            int result = 0;
            for (int i = 0; i < 16; i++) {
                if(i <= 12){
                    result = removeCarpetaHijos(inodo_apuntador.b_pointers[i], 0);
                }
                else if(i == 13){
                    result = removeCarpetaHijos(inodo_apuntador.b_pointers[i], 1);
                }
                else if(i == 14){
                    result = removeCarpetaHijos(inodo_apuntador.b_pointers[i], 2);
                }
                else if(i == 15){
                    result = removeCarpetaHijos(inodo_apuntador.b_pointers[i], 3);
                }
                if(result == 2){return 2;}
            }
            return 0;
        }
        //Inodo Archivo
        else if(inodo.i_type == '1'){
            for (int i = 0; i < 16; i++) {
                if(inodo_apuntador.b_pointers[i] == -1){break;}
                if(i <= 12){
                    removeFileHijos(inodo_apuntador.b_pointers[i], 0);
                }
                else if(i == 13){
                    removeFileHijos(inodo_apuntador.b_pointers[i], 1);
                }
                else if(i == 14){
                    removeFileHijos(inodo_apuntador.b_pointers[i], 2);
                }
                else if(i == 15){
                    removeFileHijos(inodo_apuntador.b_pointers[i], 3);
                }
            }
            return 0;
        }
        return 1;
}

int valores::removeCarpetaHijos(int espacio_apuntador, int nivel){
//Las carpetas tienen hijos carpetas y archivos
//Retorna 0 si se elimino correcto
//Retorna 1 si no elimino nada
//Retorna 2 si no tiene permiso de eliminar
    if(nivel >= 0 && nivel <= 3){
        if(nivel == 0){
            //Cuanndo es nivel 0 tiene un bloque carpeta
            if(espacio_apuntador >= 0){
                //Sacamos el bloque carpeta
                bcarpeta b_carpeta = getBloqueCarpeta(Archivo, super.s_block_start, espacio_apuntador);
                //Eliminamos el bloque carpeta
                liberarBitmapBlock(espacio_apuntador);
                //Buscamos en bloque carpeta si el nombre existe
                int indice_inodo =-1;
                for(int c = 0; c < 4; c++){
                    indice_inodo = b_carpeta.b_content[c].b_inodo;
                    if(indice_inodo >= 0){
                        inodos encontrado = getInodo(Archivo, super.s_inode_start, indice_inodo);
                        if(user_id != 1){
                            permiso p = verificarPermiso(encontrado);
                            if(p.escritura == 0){ return 2;}
                        }
                        //Eliminamos todos los hijos bloques e hijos inodos
                        if(removeInodoHijos(encontrado) == 2){ return 2;}
                        //Eliminamos el inodo
                        liberarBitmapInodo(indice_inodo);
                        //Eliminamos el bloque apuntadores indirectos y directos
                        liberarBitmapBlock(encontrado.i_block);
                    }
                }
                return 0;
            }
        }
        else{
            if(espacio_apuntador >= 0){
            //Sacamos el bloque carpeta
            bapuntador b_apuntador = getBloqueApuntador(Archivo, super.s_block_start, espacio_apuntador);
            //Eliminamos el bloque apuntador de los apuntadores indirectos
            liberarBitmapBlock(espacio_apuntador);
            int result = 0 ;
            for (int i = 0; i < 16; i++) {
                int verificar_espacio = b_apuntador.b_pointers[i];
                result = removeCarpetaHijos(verificar_espacio, nivel-1);
                if(result == 2){return 2;}
            }
            return result;
            }
        }
    }
    return 1;
}

void valores::removeFileHijos(int espacio_apuntador, int nivel){
    //Retorna 0 si encontró y elimino la carpeta y archivo
    //Retorna 1 si no eliminó nada
    if(nivel >= 0 && nivel <= 3){
        if(nivel == 0){
            if(espacio_apuntador >= 0){
                //Hay bloques contenidos
                //Eliminamos el bloque del espacio inodo
                liberarBitmapBlock(espacio_apuntador);
            }
        }
        else{
            if(espacio_apuntador >= 0){
                //Sacamos el bloque carpeta
                bapuntador b_apuntador = getBloqueApuntador(Archivo, super.s_block_start, espacio_apuntador);
                //Eliminamos el bloque apuntador de los apuntadores indirectos
                liberarBitmapBlock(espacio_apuntador);
                for (int i = 0; i < 16; i++) {
                    int verificar_espacio = b_apuntador.b_pointers[i];
                    if(verificar_espacio == -1){break;}
                    removeFileHijos(verificar_espacio, nivel-1);
                }
            }
        }
    }
}

void valores::liberarBitmapBlock(int posBlock){
    this->bitmap_block[posBlock] = '0';
    super.s_free_blocks_count++;
}

int valores::getFreeIndexBitmapBlock(){
    for (int i = 0; i < this->bitmap_block.size(); i ++) {
        if(bitmap_block[i] == '0'){
            bitmap_block[i] = '1';
            super.s_free_blocks_count--;
            return i;
        }
    }
    return -1;
}

void valores::liberarBitmapInodo(int posInodo){
    this->bitmap_inodo[posInodo] = '0';
    super.s_inodes_count++;
}

int valores::escribirArchivo_(int puntero_actual, QString nombre_archivo, QStringList contenido, int nivel_puntero_indirecto){
 /*
 * Busca un espacio entre puntadores directos e indirectos
 * retorna un numero mayor igual 0 si se necesita enlazar
 * retorna -1 si el archivo se creo
 * retorna -2 ecurrio un error no se creo la carpeta(Posiblemente no haya espacio para mas bloques)
 */

    if(nivel_puntero_indirecto >= 0 && nivel_puntero_indirecto <= 3){
        if(nivel_puntero_indirecto == 0){

            //Puntero directo
            if(puntero_actual == -1){

                int libre_bloque = getFreeIndexBitmapBlock();
                int libre_inodo = escribirArchivo(contenido);
                if(libre_inodo >= 0){
                    bcarpeta carpeta;
                    carpeta.b_content[0].b_inodo = libre_inodo;
                    strcpy(carpeta.b_content[0].b_name, nombre_archivo.toStdString().c_str());
                    for (int i=1; i < 4; i++) {
                        carpeta.b_content[i].b_inodo = -1;
                    }
                    escribirBloque(Archivo, carpeta, super.s_block_start, libre_bloque);
                    //cout<<"Carpeta creada correctamente"<<endl<<endl;
                    return libre_bloque;//para enlazar con puntero actual
                }
            }else{
                //Sacamos el bloque carpeta
                bcarpeta b_carpeta = getBloqueCarpeta(Archivo, super.s_block_start, puntero_actual);
                for(int i = 0; i < 4; i++){
                    if(b_carpeta.b_content[i].b_inodo == -1){
                        int libre_inodo = escribirArchivo(contenido);
                        if(libre_inodo >= 0){
                            strcpy(b_carpeta.b_content[i].b_name, nombre_archivo.mid(0,12).toStdString().c_str());
                            b_carpeta.b_content[i].b_inodo = libre_inodo;
                            escribirBloque(Archivo, b_carpeta, super.s_block_start,puntero_actual);
                            //cout<<"Carpeta creada correctamente"<<endl<<endl;
                            return -1;
                        }
                    }
                }
            }
        }else{
            //puntero indirecto simple
            if(puntero_actual == -1){
                //Crear Bloques nivel 1 y crear carpeta
                int indice_nuevo = getFreeIndexBitmapBlock();
                bapuntador b_nuevo;
                for (int i = 0; i < 16; i++) {
                    b_nuevo.b_pointers[i] = -1;
                }
                int resultado = escribirArchivo_(-1, nombre_archivo, contenido,nivel_puntero_indirecto-1);
                if(resultado > 0){
                    b_nuevo.b_pointers[0] = resultado;
                    escribirBloque(Archivo, b_nuevo, super.s_block_start, indice_nuevo);
                    return indice_nuevo;
                }
            }else{
                //Recorrer bloques nivel 1, buscar espacio vacio(-1)
                //Nivel indirecto  simple Hijos son bloques carptesa y archivos
                bapuntador b_apuntador = getBloqueApuntador(Archivo, super.s_block_start, puntero_actual);
                for (int i = 0; i < 16; i++) {
                    int indice_b_carpeta = b_apuntador.b_pointers[i];
                    int resultado = escribirArchivo_(indice_b_carpeta, nombre_archivo, contenido, nivel_puntero_indirecto -1);
                    if(resultado > 0){
                        b_apuntador.b_pointers[i] = resultado;
                        escribirBloque(Archivo, b_apuntador, super.s_block_start, puntero_actual);
                        return -1;
                    }
                }
            }
        }
    }
    return -2;
}

int valores::crearBloquesArchivo(QListIterator<QString> &content, bapuntador& b_apuntador){
//retorna -1 si hay error
    for (int i = 0; i < 16;i++) {
        if(!content.hasNext()){break;}
        if(i >= 0 && i <=12){
            int resultado = escribirContenidos(content, b_apuntador.b_pointers[i], 0);
            if(resultado >= 0 ){
                b_apuntador.b_pointers[i] = resultado;
            }else if(resultado == -2){break;}
        }else if(i == 13){
            int resultado = escribirContenidos(content, b_apuntador.b_pointers[i], 1);
            if(resultado >= 0 ){
                b_apuntador.b_pointers[i] = resultado;
            }else if(resultado == -2){break;}
        }else if(i == 14){
            int resultado = escribirContenidos(content, b_apuntador.b_pointers[i], 2);
            if(resultado >= 0 ){
                b_apuntador.b_pointers[i] = resultado;
            }else if(resultado == -2){break;}
        }else if(i == 15){
            int resultado = escribirContenidos(content, b_apuntador.b_pointers[i], 3);
            if(resultado >= 0 ){
                b_apuntador.b_pointers[i] = resultado;
            }else if(resultado == -2){break;}
        }
    }
    if(content.hasNext()){
        //Si el contenido tiene datos sin agregar, se retorna con error
        return -1;
    }else{
        //Si el contenido ya no tiene datos entonces se retorna sin error
        return 0;
    }
}

int valores::escribirContenidos(QListIterator<QString> &content, int espacio_actual, int nivel){
    /*
     * Busca un espacio entre puntadores directos e indirectos
     * retorna un numero mayor igual 0 si se necesita enlazar
     * retorna -1 si la carpeta se creo
     * retorna -2 ecurrio un error no se creo la carpeta(Posiblemente no haya espacio para mas bloques)
     */
    if(nivel >= 0 && nivel <= 3){
        if(nivel == 0){
        //Puntero directo
            if(espacio_actual == -1){
                if(content.hasNext()){
                    int libre_bloque = getFreeIndexBitmapBlock();
                    barchivo nuevo;
                    //QString write = content.next();
                    strcpy(nuevo.b_content, content.next().toStdString().c_str());
                    //cout<<nuevo.b_content<<endl;
                    escribirBloque(Archivo, nuevo, super.s_block_start, libre_bloque);
                    //cout<<"Carpeta creada correctamente"<<endl<<endl;
                    return libre_bloque;//para enlazar con puntero actual
                }
            }
            return -1;
        }else{
            if(espacio_actual == -1){
                //Crear Bloques nivel 1 y crear carpeta
                if(content.hasNext()){
                    int indice_nuevo = getFreeIndexBitmapBlock();
                    bapuntador b_nuevo;
                    for (int i = 0; i < 16; i++) {
                        b_nuevo.b_pointers[i] = -1;
                    }
                    escribirBloque(Archivo, b_nuevo, super.s_block_start, indice_nuevo);
                    escribirContenidos(content, indice_nuevo , nivel);
                    return indice_nuevo;
                }
                return -1;
            }else{
                //Recorrer bloques nivel 1, buscar espacio vacio(-1)
                //Nivel indirecto  simple Hijos son bloques carptesa y archivos
                if(content.hasNext()){
                    bapuntador b_apuntador = getBloqueApuntador(Archivo, super.s_block_start, espacio_actual);
                    for (int i = 0; i < 16; i++) {
                        int indice_b_carpeta = b_apuntador.b_pointers[i];
                        int resultado = escribirContenidos(content, indice_b_carpeta, nivel -1);
                        if(resultado > 0){
                            b_apuntador.b_pointers[i] = resultado;
                        }
                        else if(resultado == -2){return -2;}
                    }
                    escribirBloque(Archivo, b_apuntador, super.s_block_start, espacio_actual);
                }
                return -1;
            }
        }
    }
    return -2;
}

void valores::actualizarSuperBloque(){
    actualizarSB();
    actualizarBitmaps();
    actualizarJournal();
}

void valores::actualizarSB(){
    int first_ino = getFreeIndexBitmapInodo();
    int first_blo = getFreeIndexBitmapBlock();
    liberarBitmapBlock(first_blo);
    liberarBitmapInodo(first_ino);
    super.s_first_blo = first_blo;
    super.s_firts_ino = first_ino;

    fseek(Archivo, inicio_byte, SEEK_SET);//Posicionamos el puntero al inicio de la particion
    fwrite(&super, sizeof(superbloque), 1, Archivo);//Escribimos el Superbloque
}

void valores::actualizarBitmaps(){
    //Escribir bitmap_inodos
    fseek(Archivo, super.s_bm_inode_start, SEEK_SET);//Posicionamos el puntero al inicio de espacio bitmap inodos
    fwrite(bitmap_inodo.data(), 1, super.s_inodes_count, Archivo);//Escribimos el Bitmap inodos
    //Escribir bitmap_bloques
    fseek(Archivo, super.s_bm_block_start, SEEK_SET);//Posicionamos el puntero al inicio de espacio bitmap blocks
    fwrite(bitmap_block.data(), 1, super.s_blocks_count, Archivo);//Escribimos el Bitmap blocks
}

void valores::actualizarJournal(){
    if(super.s_filesystem_type == 3){
        int inicio_journaling = this->inicio_byte + sizeof (superbloque);
        int new_last = journal_info.last;
        int old_last = journal_info.last;
        foreach (journal aux, journaling) {
            new_last++;
            if(new_last > journal_info.max){break;}
            fseek(Archivo, inicio_journaling + (new_last * sizeof(journal)), SEEK_SET);//Posicionamos el puntero al inicio de bitmaps
            fwrite(&aux, sizeof(journal), 1, Archivo);

        }
        journal_info.last = new_last;
        fseek(Archivo, inicio_journaling + (0 * sizeof(journal)), SEEK_SET);//Posicionamos el puntero al inicio de bitmaps
        fwrite(&journal_info, sizeof(info_journal), 1, Archivo);

        fseek(Archivo, inicio_journaling + (old_last * sizeof(journal)), SEEK_SET);//Posicionamos el puntero al inicio de bitmaps
        fwrite(&journal_last, sizeof(journal), 1, Archivo);
    }
}

valores::valores(FILE*disco, n_particiones *particion, int iniciobyte){
    this->Archivo = disco;
    this->inicio_byte = iniciobyte;
    getSuperBlock(particion);
    getBitmaps();
    getJournal();
}

void valores::getSuperBlock(FILE* disco, n_particiones part_montada, superbloque &superBlock){
    if(part_montada.part_type == 'p' || part_montada.part_type == 'P'){
        particion particiones = part_montada.particiones;
        fseek(disco, particiones.part_start, SEEK_SET);//Posicionamos el puntero al inicio de la particion
        fread(&superBlock, sizeof (superbloque), 1, disco);
    }
    else if(part_montada.part_type == 'l' || part_montada.part_type == 'L'){
        ebr logica = part_montada.particion_logica;
        fseek(disco, logica.part_start + sizeof (ebr), SEEK_SET);//Posicionamos el puntero al inicio de la particion
        fread(&superBlock, sizeof (superbloque), 1, disco);
    }else{
        superbloque empty;
        empty.s_filesystem_type = -1;
        superBlock = empty;
    }
}

void valores::getSuperBlock(n_particiones *part_montada){
    if(part_montada->part_type == 'p' || part_montada->part_type == 'P'){
        particion particiones = part_montada->particiones;
        fseek(Archivo, particiones.part_start, SEEK_SET);//Posicionamos el puntero al inicio de la particion
        fread(&this->super, sizeof(superbloque), 1, Archivo);
    }
    else if(part_montada->part_type == 'l' || part_montada->part_type == 'L'){
        ebr logica = part_montada->particion_logica;
        fseek(Archivo, logica.part_start + sizeof (ebr), SEEK_SET);//Posicionamos el puntero al inicio de la particion
        fread(&this->super, sizeof (superbloque), 1, Archivo);
    }else{
        superbloque empty;
        empty.s_filesystem_type = -1;
        this->super = empty;
    }
}

void valores::getBitmaps(){
    //Obtener bitmaps inodos
    char bit_inodos[super.s_inodes_count];
    char bit_blocks[super.s_blocks_count];
    fseek(Archivo, this->super.s_bm_inode_start, SEEK_SET);//Posicionamos el puntero al inicio de bitmaps
    fread(&bit_inodos, 1, super.s_inodes_count, Archivo);
    //Obtener bitmaps bloques
    fseek(Archivo, this->super.s_bm_block_start, SEEK_SET);//Posicionamos el puntero al inicio de bitmaps
    fread(&bit_blocks, 1, super.s_blocks_count, Archivo);
    QByteArray bm_inodos(bit_inodos);
    QByteArray bm_bloques(bit_blocks);
    this->bitmap_block = bm_bloques;
    this->bitmap_inodo = bm_inodos;
}

void valores::getJournal(){
    if(super.s_filesystem_type == 3){
        int inicio_journaling = this->inicio_byte + sizeof (superbloque);
        //Obtenemos el info journal
        fseek(Archivo, inicio_journaling, SEEK_SET);//Posicionamos el puntero al inicio de bitmaps
        fread(&this->journal_info, sizeof (info_journal), 1, Archivo);
        //Obtenemos el ultimo Journal
        fseek(Archivo, inicio_journaling + (journal_info.last * sizeof(journal)), SEEK_SET);//Posicionamos el puntero al inicio de bitmaps
        fread(&this->journal_last, sizeof(journal), 1, Archivo);
        //cout<<" LastJounal: tipo=" <<journal_last.tipo<<" nombre="<<journal_last.nombre<<" content="<<journal_last.content<<" Operacion="<<journal_last.operacion<<" Next="<<journal_last.next<<endl;
    }
}

journal valores::getJournal(int posicion){
    journal find;
    find.next = -1;
    int inicio_journaling = this->inicio_byte + sizeof (superbloque);
    //Obtenemos el ultimo Journal
    fseek(Archivo, inicio_journaling + (posicion * sizeof(journal)), SEEK_SET);//Posicionamos el puntero al inicio de bitmaps
    fread(&find, sizeof(journal), 1, Archivo);
    return find;
}

int valores::iniciarSesion(QString user, QString psw){
    QListIterator<QString> rows = getDatosUsers();
    QHash<QString, int> grupos;
    while (rows.hasNext()) {
        QString dato = rows.next();
        if(dato.size() == 0){break;}
        QStringList lista = dato.split(',');
        if(QString::compare(lista.value(1).trimmed(), "u", Qt::CaseInsensitive) == 0){
            int id = lista.value(0).trimmed().toInt();
            if(user.compare(lista.value(3).trimmed(), Qt::CaseSensitive) == 0 &&
               psw.compare(lista.value(4).trimmed(), Qt::CaseSensitive) == 0 &&  id > 0){
                group = lista.value(2).trimmed();
                group_id = grupos[lista.value(2).trimmed()];
                return id;
            }
        }
        else{
            grupos[lista.value(2).trimmed()] = lista.value(0).trimmed().toInt();
        }
    }
    return -1;
}

QListIterator<QString> valores::getDatosUsers(){
    inodos inodo_users = getInodo(Archivo, super.s_inode_start, 1);
    QString content = getFileContent(inodo_users);
    QListIterator<QString> rows(content.split('\n'));
    return rows;
}

QString valores::getFileContent_(int espacio_apuntador, int nivel){
    QString retornar = "";
    if(nivel >= 0 && nivel <= 3){
        if(nivel == 0){
            if(espacio_apuntador >= 0){
                //Hay bloques contenidos
                barchivo contenido = getBloqueArchivo(Archivo, super.s_block_start, espacio_apuntador);
                QString addcontent(contenido.b_content);
                retornar += addcontent.mid(0,64);
                //cout<<"<INIT>"<<addcontent.toStdString()<<"<END>"<<endl<<endl;
            }
        }
        else{
            if(espacio_apuntador >= 0){
                //Sacamos el bloque carpeta
                bapuntador b_apuntador = getBloqueApuntador(Archivo, super.s_block_start, espacio_apuntador);
                for (int i = 0; i < 16; i++) {
                    int verificar_espacio = b_apuntador.b_pointers[i];
                    if(verificar_espacio == -1){break;}
                    retornar += getFileContent_(verificar_espacio, nivel-1);
                }
            }
        }
    }
    return retornar;
}

QString valores:: getFileContent(inodos inodo){
    if(inodo.i_type == '0'){return "";}
    //Obtenemos los 16 apuntadores del inodo actual
    bapuntador inodo_apuntador = getBloqueApuntador(Archivo, super.s_block_start, inodo.i_block);
    QString resultado = "";
    //Buscamos espacios ocupados en los 16 apuntadores
    for (int i = 0; i < 16; i++) {
        if(i <= 12){
            resultado += getFileContent_(inodo_apuntador.b_pointers[i], 0);
        }
        else if(i == 13){
            resultado += getFileContent_(inodo_apuntador.b_pointers[i], 1);
        }
        else if(i == 14){
            resultado += getFileContent_(inodo_apuntador.b_pointers[i], 2);
        }
        else if(i == 15){
            resultado += getFileContent_(inodo_apuntador.b_pointers[i], 3);
        }
    }
    return resultado;
}
