#ifndef PIXMAP_HPP
#define PIXMAP_HPP

#include <QGraphicsPixmapItem>
#include <QDir>

typedef enum {Inicio, Final, Nada, Edificio, Cono, Arbol, Recorrido} Imagenes;  //Enumerable para identificar las imágenes
typedef enum {N, S, E, O} Vecinos;  //Enumerable para identificar a los vecinos por su localización


// Clase Pixmap: Encargada de mostrar cada uno de los elementos básicos del escenario
// conteniendo la información sobre posición, tipo de obstáculo, imagen, etc.

class Pixmap : public QGraphicsPixmapItem{

    private:

        Pixmap *predecesor,*vecinos[4];
        int x,y;
        int coste, heuristica;
        Imagenes tipo;
        bool obstaculo;

        int get_total() const;

    public:

        Pixmap(Imagenes);       //El constructor recibe una imagen
        ~Pixmap();

        int get_x();
        int get_y();
        void set_coords(int x, int y);
        int get_coste();
        void set_coste(int valor);
        void set_heuristica(int valor);

        Pixmap* get_predecesor();               //Devuelve el predecesor
        void set_predecesor(Pixmap* pred);
        Pixmap* get_vecinos(int i);             //Devuelve el vecino especificado
        void set_vecinos(Vecinos vecino, Pixmap* vec);  //Añadir un vecino en la posición especificada

        bool is_obstaculo();                    //Comprobar si se trata de un obstáculo
        void set_pixmap(Imagenes tipo_);        //Asinar una imagen al elemento

        bool operator <(const Pixmap* &pix) const;          //Sobrecarga del operador <
        bool operator ==(Pixmap*& pix);                     //Sobrecarga del operador ==
        static bool lessThan(Pixmap* pix1, Pixmap* pix2);   //Método auxiliar para el operador <
};

#endif // PIXMAP_HPP
