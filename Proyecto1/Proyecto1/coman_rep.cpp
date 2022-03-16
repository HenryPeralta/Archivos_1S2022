#include "coman_rep.h"

coman_rep::coman_rep()
{

}

void coman_rep::recorrer_rep(Nodo_arbol *raiz){
    bool bandera_error = false;
    bool bandera_name = false;
    bool bandera_path = false;
    bool bandera_id = false;
    QString valor_name = "";
    QString valor_path = "";
    QString valor_id = "";

    for(int i = 0; i < raiz->hijos.count(); i++){
        Nodo_arbol temp = raiz->hijos.at(i);
        if(temp.tipo_num == PATH){
            bandera_path = true;
            valor_path = temp.valor;
            valor_path.replace(QString("\""), QString(""));
        }else if(temp.tipo_num == NAME){
            bandera_name = true;
            valor_name = temp.hijos.at(0).valor;
            valor_name.replace(QString("\""), QString(""));
        }else if(temp.tipo_num == ID){
            bandera_id = true;
            valor_id = temp.valor;
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
    if(bandera_id == false){
        bandera_error = true;
        std::cout<<"Error: El parametro -id es obligatorio \n";
    }
    if(bandera_error == false){
        eleccion_repo(valor_path, valor_name, valor_id);
    }
}

void coman_rep::eleccion_repo(QString path, QString name, QString id){
    std::cout<<"El valor de path es: "<<path.toStdString()<<"\n";
    std::cout<<"El valor de name es: "<<name.toStdString()<<"\n";
    std::cout<<"El valor de id es: "<<id.toStdString()<<"\n";
    QString ruta = lista->getDireccion(id);
    QString extension = obtener_extension(path);
    if(path != "null"){
        n_particiones encontrado = lista->getParticionMontada(id);
        QString direccion = obtener_path(path);
        string comando = "sudo mkdir -p \'" + direccion.toStdString() + "\'";
        system(comando.c_str());
        string comando2 = "sudo chmod -R 777 \'" + direccion.toStdString() + "\'";
        system(comando2.c_str());
        if(name == "mbr"){
            graficarMBR(ruta, path, extension);
        }else if(name == "disk"){
            graficarDisk(ruta, path, extension);
        }
    }

}

QString coman_rep::obtener_extension(QString path){
    string aux = path.toStdString();
    string delimiter = ".";
    size_t pos = 0;
    while((pos = aux.find(delimiter))!=string::npos){
        aux.erase(0,pos+delimiter.length());
    }
    return QString::fromStdString(aux);
}

QString coman_rep::obtener_path(QString path){
    string aux = path.toStdString();
    string delimiter = "/";
    size_t pos = 0;
    string res = "";
    while((pos = aux.find(delimiter))!=string::npos){
        res += aux.substr(0,pos)+"/";
        aux.erase(0,pos + delimiter.length());
    }
    return QString::fromStdString(res);
}

void coman_rep::graficarMBR(QString path, QString destino, QString extension){
    string auxPath = path.toStdString();
    FILE *Archivo;
    FILE *graphDot;
    if((Archivo = fopen(auxPath.c_str(),"r"))){
        graphDot = fopen("grafica.dot", "w");
        fprintf(graphDot, "digraph G{ \n");
        fprintf(graphDot, "subgraph cluster{\n label=\"MBR\" fillcolor=\"cornflowerblue\" style=\"filled\"");
        fprintf(graphDot, "\ntbl[shape=box, label=<\n");
        fprintf(graphDot, "<table color=\'black\'  border=\'0\' cellborder=\'1\' cellspacing=\'0\' width=\'300\'  height=\'200\' >\n");
        fprintf(graphDot, "<tr>  <td width=\'150\' bgcolor=\"chartreuse1\"> <b>Nombre</b> </td> <td width=\'150\' bgcolor=\"chartreuse1\"> <b>Valor</b> </td>  </tr>\n");
        mbr MBR;
        fseek(Archivo, 0, SEEK_SET);
        fread(&MBR, sizeof(mbr), 1, Archivo);
        int tamanio = MBR.mbr_tamano;
        fprintf(graphDot, "<tr>  <td bgcolor=\"white\"><b>mbr_tamaño</b></td><td bgcolor=\"white\"><font color='black'>%d</font></td>  </tr>\n",tamanio);
        struct tm *tm;
        char fecha[100];
        tm = localtime(&MBR.mbr_fecha_creacion);
        strftime(fecha, 100, "%d/%m/%y %H:%S", tm);
        fprintf(graphDot,"<tr>  <td bgcolor=\"white\"><b>mbr_fecha_creacion</b></td> <td bgcolor=\"white\"><font color='black'>%s</font></td>  </tr>\n", fecha);
        fprintf(graphDot,"<tr>  <td bgcolor=\"white\"><b>mbr_disk_signature</b></td> <td bgcolor=\"white\"><font color='black'>%d</font></td>  </tr>\n", MBR.mbr_dsk_signature);
        fprintf(graphDot,"<tr>  <td bgcolor=\"white\"><b>Disk_fit</b></td> <td bgcolor=\"white\"><font color='black'>%c</font></td>  </tr>\n",MBR.dsk_fit);

        int indexExtendida = -1;
        for(int i = 0; i < 4; i++){
            if(MBR.mbr_partition[i].part_start != -1 && MBR.mbr_partition[i].part_status != '1'){
                if(MBR.mbr_partition[i].part_type == 'E'){
                    indexExtendida = i;
                }
                char status[3];
                if(MBR.mbr_partition[i].part_status == '0'){
                    strcpy(status, "0");
                }else if(MBR.mbr_partition[i].part_status == '2'){
                    strcpy(status, "2");
                }
                fprintf(graphDot,"<tr>  <td bgcolor=\"white\"><b>part_status_%d</b></td> <td bgcolor=\"white\"><font color='black'>%s</font></td>  </tr>\n",(i+1), status);
                fprintf(graphDot,"<tr>  <td bgcolor=\"white\"><b>part_type_%d</b></td> <td bgcolor=\"white\"><font color='black'>%c</font></td>  </tr>\n",(i+1), MBR.mbr_partition[i].part_type);
                fprintf(graphDot,"<tr>  <td bgcolor=\"white\"><b>part_fit_%d</b></td> <td bgcolor=\"white\"><font color='black'>%c</font></td>  </tr>\n",(i+1), MBR.mbr_partition[i].part_fit);
                fprintf(graphDot,"<tr>  <td bgcolor=\"white\"><b>part_start_%d</b></td> <td bgcolor=\"white\"><font color='black'>%d</font></td>  </tr>\n",(i+1), MBR.mbr_partition[i].part_start);
                fprintf(graphDot,"<tr>  <td bgcolor=\"white\"><b>part_size_%d</b></td> <td bgcolor=\"white\"><font color='black'>%d</font></td>  </tr>\n",(i+1), MBR.mbr_partition[i].part_size);
                fprintf(graphDot,"<tr>  <td bgcolor=\"white\"><b>part_name_%d</b></td> <td bgcolor=\"white\"><font color='black'>%s</font></td>  </tr>\n",(i+1), MBR.mbr_partition[i].part_name);
            }
        }
        fprintf(graphDot, "</table>\n");
        fprintf(graphDot, ">];\n}\n");

        if(indexExtendida != -1){
            int index_ebr = 1;
            ebr EBR;
            fseek(Archivo, MBR.mbr_partition[indexExtendida].part_start, SEEK_SET);
            while(fread(&EBR, sizeof(ebr), 1, Archivo) != 0 && (ftell(Archivo) < MBR.mbr_partition[indexExtendida].part_start + MBR.mbr_partition[indexExtendida].part_size)){
                if(EBR.part_status != '1'){
                    fprintf(graphDot,"subgraph cluster_%d{\n label=\"EBR_%d\" fillcolor=\"cornflowerblue\" style=\"filled\"\n", index_ebr,index_ebr);
                    fprintf(graphDot,"\ntbl_%d[shape=box, label=<\n ", index_ebr);
                    fprintf(graphDot, "<table color=\'black\' border=\'0\' cellborder=\'1\' cellspacing=\'0\'  width=\'300\' height=\'160\' >\n ");
                    fprintf(graphDot, "<tr>  <td width=\'150\' bgcolor=\"gold\"><b>Nombre</b></td> <td width=\'150\' bgcolor=\"gold\"><b>Valor</b></td>  </tr>\n");
                    char status[3];
                    if(EBR.part_status == '0'){
                        strcpy(status, "0");
                    }else if(EBR.part_status == '2'){
                        strcpy(status, "2");
                    }
                    fprintf(graphDot, "<tr>  <td bgcolor=\"white\"><b>part_status_1</b></td> <td bgcolor=\"white\"><font color='black'>%s</font></td>  </tr>\n",status);
                    fprintf(graphDot, "<tr>  <td bgcolor=\"white\"><b>part_fit_1</b></td> <td bgcolor=\"white\"><font color='black'>%c</font></td>  </tr>\n", EBR.part_fit);
                    fprintf(graphDot, "<tr>  <td bgcolor=\"white\"><b>part_start_1</b></td> <td bgcolor=\"white\"><font color='black'>%d</font></td>  </tr>\n", EBR.part_start);
                    fprintf(graphDot, "<tr>  <td bgcolor=\"white\"><b>part_size_1</b></td> <td bgcolor=\"white\"><font color='black'>%d</font></td>  </tr>\n", EBR.part_size);
                    fprintf(graphDot, "<tr>  <td bgcolor=\"white\"><b>part_next_1</b></td> <td bgcolor=\"white\"><font color='black'>%d</font></td>  </tr>\n", EBR.part_next);
                    fprintf(graphDot, "<tr>  <td bgcolor=\"white\"><b>part_name_1</b></td> <td bgcolor=\"white\"><font color='black'>%s</font></td>  </tr>\n", EBR.part_name);
                    fprintf(graphDot, "</table>\n");
                    fprintf(graphDot, ">];\n}\n");
                    index_ebr++;
                }
                if(EBR.part_next == -1){
                    break;
                }else{
                    fseek(Archivo, EBR.part_next, SEEK_SET);
                }
            }
        }
        fprintf(graphDot, "}\n");
        fclose(graphDot);
        fclose(Archivo);
        string comando = "dot -T"+extension.toStdString()+" grafica.dot -o "+destino.toStdString();
        system(comando.c_str());
        cout << "Reporte mbr generado correctamente" << endl;
    }
}

void coman_rep::graficarDisk(QString path, QString destino, QString extension){
    string auxPath = path.toStdString();
    FILE *Archivo;
    FILE *graphDot;
    if((Archivo = fopen(auxPath.c_str(),"r"))){
        graphDot = fopen("grafica.dot", "w");
        fprintf(graphDot,"digraph G{\n\n");
        fprintf(graphDot, "tbl [\n    shape=box\n    label=<\n");
        fprintf(graphDot, "<table border=\'0\' cellborder=\'2\' width=\'600\' height=\"200\" color=\'blue\'>\n");
        fprintf(graphDot, "<tr>\n");
        fprintf(graphDot, "<td height=\'200\' width=\'100\'> MBR </td>\n");
        mbr MBR;
        fseek(Archivo, 0, SEEK_SET);
        fread(&MBR, sizeof(mbr), 1, Archivo);
        int total = MBR.mbr_tamano;
        double espacioUsado = 0;
        for(int i = 0; i < 4; i++){
            int parcial = MBR.mbr_partition[i].part_size;
            if(MBR.mbr_partition[i].part_start != -1){
                double porcentaje_real =(parcial * 100)/total;
                double porcentaje_aux = (porcentaje_real * 500)/100;
                espacioUsado += porcentaje_real;
                if(MBR.mbr_partition[i].part_status != '1'){
                    if(MBR.mbr_partition[i].part_type == 'P'){
                        fprintf(graphDot, "<td height=\'200\' width=\'%.1f\'>PRIMARIA <br/>%.1f%c</td>\n",porcentaje_aux,porcentaje_real,'%');
                        if(i != 3){
                            int p1 = MBR.mbr_partition[i].part_start + MBR.mbr_partition[i].part_size;
                            int p2 = MBR.mbr_partition[i+1].part_start;
                            if(MBR.mbr_partition[i+1].part_start != -1){
                                if((p2-p1)!=0){
                                    int fragmentacion = p2-p1;
                                    double porcentaje_real = (fragmentacion*100)/total;
                                    double porcentaje_aux = (porcentaje_real*500)/100;
                                    fprintf(graphDot,"<td height=\'200\' width=\'%.1f\'>LIBRE<br/>%.1f%c</td>\n",porcentaje_aux,porcentaje_real,'%');
                                }
                            }
                        }else{
                            int p1 = MBR.mbr_partition[i].part_start + MBR.mbr_partition[i].part_size;
                            int mbr_size = total + (int)sizeof(mbr);
                            if((mbr_size-p1)!=0){
                                double libre = (mbr_size - p1) + sizeof(mbr);
                                double porcentaje_real = (libre*100)/total;
                                double porcentaje_aux = (porcentaje_real*500)/100;
                                fprintf(graphDot, "<td height=\'200\' width=\'%.1f\'>LIBRE<br/>%.1f%c</td>\n",porcentaje_aux, porcentaje_real, '%');
                            }
                        }
                    }else{
                        ebr EBR;
                        fprintf(graphDot,"<td  height=\'200\' width=\'%.1f\'>\n     <table border=\'0\'  height=\'200\' WIDTH=\'%.1f\' cellborder=\'1\'>\n",porcentaje_real,porcentaje_real);
                        fprintf(graphDot,"<tr><td height=\'60\' colspan=\'15\'>EXTENDIDA</td>  </tr>\n <tr>\n");
                        fseek(Archivo, MBR.mbr_partition[i].part_start,SEEK_SET);
                        fread(&EBR,sizeof(ebr),1,Archivo);
                        if(EBR.part_size != 0){
                            fseek(Archivo, MBR.mbr_partition[i].part_start,SEEK_SET);
                            while(fread(&EBR,sizeof(ebr),1,Archivo)!=0 && (ftell(Archivo) < (MBR.mbr_partition[i].part_start + MBR.mbr_partition[i].part_size))){
                                parcial = EBR.part_size;
                                porcentaje_real = (parcial*100)/total;
                                if(porcentaje_real != 0){
                                    if(EBR.part_status != '1'){
                                        fprintf(graphDot, "<td height=\'140\'>EBR</td>\n");
                                        fprintf(graphDot, "<td height=\'140\'>LOGICA<br/>%.1f%c</td>\n",porcentaje_real,'%');
                                    }else{
                                        fprintf(graphDot, "<td height=\'150\'>LIBRE <br/> %.1f%c</td>\n",porcentaje_real,'%');
                                    }
                                    if(EBR.part_next==-1){
                                        parcial = (MBR.mbr_partition[i].part_start + MBR.mbr_partition[i].part_size) - (EBR.part_start + EBR.part_size);
                                        porcentaje_real = (parcial*100)/total;
                                        if(porcentaje_real!=0){
                                            fprintf(graphDot, "<td height=\'150\'>LIBRE <br/> %.1f%c </td>\n",porcentaje_real,'%');
                                        }
                                        break;
                                    }else{
                                        fseek(Archivo,EBR.part_next,SEEK_SET);
                                    }
                                }
                            }
                        }else{
                            fprintf(graphDot,"<td height=\'140\'> Ocupado %.1f%c</td>",porcentaje_real,'%');
                        }
                        fprintf(graphDot,"</tr>\n </table>\n </td>\n");
                        if(i!=3){
                            int p1 = MBR.mbr_partition[i].part_start + MBR.mbr_partition[i].part_size;
                            int p2 = MBR.mbr_partition[i+1].part_start;
                            if(MBR.mbr_partition[i+1].part_start != -1){
                                if((p2-p1)!=0){
                                    int fragmentacion = p2-p1;
                                    double porcentaje_real = (fragmentacion*100)/total;
                                    double porcentaje_aux = (porcentaje_real*500)/100;
                                    fprintf(graphDot,"<td height=\'200\' width=\'%.1f\'>LIBRE<br/> %.1f%c</td>\n",porcentaje_aux,porcentaje_real,'%');
                                }
                            }
                        }else{
                            int p1 = MBR.mbr_partition[i].part_start + MBR.mbr_partition[i].part_size;
                            int mbr_size = total + (int)sizeof(MBR);
                            if((mbr_size-p1)!=0){//Libre
                                double libre = (mbr_size - p1) + sizeof(MBR);
                                double porcentaje_real = (libre*100)/total;
                                double porcentaje_aux = (porcentaje_real*500)/100;
                                fprintf(graphDot, "<td height=\'200\' width=\'%.1f\'>LIBRE<br/> %.1f%c</td>\n",porcentaje_aux, porcentaje_real, '%');
                            }
                        }
                    }
                }else{
                    fprintf(graphDot,"<td height=\'200\' width=\'%.1f\'>LIBRE <br/> %.1f%c</td>\n",porcentaje_aux,porcentaje_real,'%');
                }
            }
        }
        fprintf(graphDot,"</tr> \n </table> \n>];\n\n}");
        fclose(graphDot);
        fclose(Archivo);
        string comando = "dot -T"+extension.toStdString()+" grafica.dot -o "+destino.toStdString();
        system(comando.c_str());
        cout << "Reporte disk generado con exito" << endl;
    }else{
        cout << "Error: al crear el reporte disk" << endl;
    }
}

