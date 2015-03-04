#ifndef ROBOT_HPP
#define ROBOT_HPP

#include <QVector>
#include <algorithm>
#include "pixmap.hpp"


class Robot{

    private:

        Pixmap*** cp_mapa;     //tener una copia del mapa
        Pixmap *ini, *fin, *actual, *vecino;    
        int** pos_ini_fin;
        int pos[2];
        int fil, col;

        QVector<Pixmap*> abierta, cerrada, total; //tres listas

        void hallar_vecinos(Pixmap* actual_);
        void manhattan(int x, int y);   //calcular idstancia manhattan
        void camino(Pixmap* current);
        void limpiar_camino();

    public:

        Robot(Pixmap***& copia, int** ini_fin, int fil_, int col_); 
        ~Robot();

        int A_estrella();   //implementacion del algoritmo
};

#endif // ROBOT_HPP
