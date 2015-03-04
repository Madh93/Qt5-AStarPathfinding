#ifndef SCENE_HPP
#define SCENE_HPP

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <cstdlib>
#include <ctime>
#include "pixmap.hpp"


class Scene : public QGraphicsScene{

    Q_OBJECT

    private:

        Pixmap*** mapa_;
        int** pos_ini_fin;  //Posiciones en las que se encuentra el inicio y el final
        int fil, col;       //Numero de filas y columnas
        Imagenes img_actual;

        void generarMapa();

    public:

        Scene(int fil_, int col_);
        ~Scene();

        void set_actual(Imagenes aux);
        void generarAleatorio(int aleatorio);
        Pixmap*** get_mapa();
        int** get_pos_ini();

    protected:

        //Funcion que nos permitira incluir obstaculos en el mapa manualmente
        virtual void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);
};

#endif // SCENE_HPP
