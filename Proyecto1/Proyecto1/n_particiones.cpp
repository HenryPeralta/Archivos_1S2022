#include "n_particiones.h"

using namespace std;

n_particiones::n_particiones()
{
    path = "";
    name = "";
    letra = 0;
    num = 0;
    siguiente = nullptr;
    part_type = 0;
}

n_particiones::n_particiones(QString path, QString name, char letra, int num, char part_type){
    this->path = path;
    this->name = name;
    this->letra = letra;
    this->num = num;
    this->siguiente = nullptr;
    this->part_type = part_type;
}
