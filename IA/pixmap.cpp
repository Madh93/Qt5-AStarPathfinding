#include "pixmap.hpp"


Pixmap::Pixmap(Imagenes tipo_){

    this->set_pixmap(tipo_);    //Asignarle la imagen a la casilla

    predecesor = NULL;
    for (int i=0; i<4; i++)
        vecinos[i] = NULL;

    x = y = -1;
    coste = 1;
    heuristica = 0;
    obstaculo = false;
}


Pixmap::~Pixmap(){

    if (predecesor){
        predecesor = NULL;
    }

    for (int i=0; i<4; i++){
        if (vecinos[i])
            vecinos[i] = NULL;
    }

    x = y = -1;
    coste = 1;
    heuristica = 0;
    obstaculo = false;
}


int Pixmap::get_x(){

    return x;
}


int Pixmap::get_y(){

    return y;
}


void Pixmap::set_coords(int x_, int y_){

    x = x_;
    y = y_;
}


int Pixmap::get_coste(){

    return coste;
}


void Pixmap::set_coste(int valor){

    coste = valor;
}


void Pixmap::set_heuristica(int valor){

    heuristica = valor;
}


Pixmap* Pixmap::get_predecesor(){

    return predecesor;
}


void Pixmap::set_predecesor(Pixmap *pred){

    predecesor = pred;
}


Pixmap* Pixmap::get_vecinos(int i){

    return vecinos[i];
}


void Pixmap::set_vecinos(Vecinos vecino, Pixmap *vec){

    switch (vecino){
        case N: vecinos[0] = vec; break;        //Segun la coordenada especificada
        case S: vecinos[1] = vec; break;        //el vecino se almacena en una posicion
        case E: vecinos[2] = vec; break;        //determinada del vector vecinos
        case O: vecinos[3] = vec;
    }
}


bool Pixmap::is_obstaculo(){

    return obstaculo;
}


void Pixmap::set_pixmap(Imagenes tipo_){

    tipo = tipo_;
    if (tipo == Arbol || tipo == Cono || tipo == Edificio)  //Especificar que imagenes corresponden
        obstaculo = true;                                   //como un obstaculo
    else
        obstaculo = false;

    QString path = QDir::currentPath();     //Seleccionar el path
    while (!path.endsWith('/'))             //donde estan las imagenes
            path.chop(1);

    switch (tipo){      //Seleccionar el archivo de la imagen correspondiente
        case Inicio: this->setPixmap(path + "img/taxi.png"); break;
        case Final: this->setPixmap(path + "img/persona.png"); break;
        case Nada: this->setPixmap(path + "img/blanco.png"); break;
        case Edificio: this->setPixmap(path + "img/edificio.png"); break;
        case Cono: this->setPixmap(path + "img/cono.png"); break;
        case Arbol: this->setPixmap(path + "img/arbol.png"); break;
        case Recorrido: this->setPixmap(path + "img/recorrido.png");
    }
}


bool Pixmap::operator <(const Pixmap*& pix) const{

    return (get_total() < pix->get_total());        //comparar segun el coste total
}


bool Pixmap::operator ==(Pixmap* &pix){

    return((x == pix->get_x())&&(y == pix->get_y()));       //comparar la posicion
}


bool Pixmap::lessThan(Pixmap* pix1, Pixmap* pix2){

    return (pix1->get_total() < pix2->get_total()); //comparar segun el coste total
}


int Pixmap::get_total() const{

    return coste + heuristica;
}
