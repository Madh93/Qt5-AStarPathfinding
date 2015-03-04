#include "scene.hpp"


Scene::Scene(int fil_, int col_){       //Constructor

    fil = fil_;
    col = col_;

    mapa_ = NULL;

    pos_ini_fin = new int* [2];
    for (int i=0; i<2; i++){
        pos_ini_fin[i] = new int [2];
        for (int j=0; j<2; j++)
            pos_ini_fin[i][j] = -1;     
            //Se inician las posiciones de inicio y final en posiciones negativas(inexistentes en el mapa)
    }

    img_actual = Nada;

    generarMapa();
}


Scene::~Scene(){        //Destructor

    if (mapa_){
        for (int i=0; i<fil; i++){
            for (int j=0; j<col; j++)
                delete mapa_[i][j];
            delete [] mapa_[i];
        }
        delete [] mapa_;
        mapa_ = NULL;
    }

    if (pos_ini_fin){
        for (int i=0; i<2; i++)
            delete [] pos_ini_fin[i];
        delete [] pos_ini_fin;
        pos_ini_fin = NULL;
    }

    fil = 0;
    col = 0;
}


void Scene::set_actual(Imagenes aux)
{
    switch (aux){
        case Inicio: img_actual = Inicio; break;
        case Final: img_actual = Final; break;
        case Nada: img_actual = Nada; break;
        case Edificio: img_actual = Edificio; break;
        case Cono: img_actual = Cono; break;
        case Arbol: img_actual = Arbol; break;
        case Recorrido: img_actual = Recorrido;
    }
}


void Scene::generarAleatorio(int valor){        //Funcion que genera un % de obstaculos en posiciones aleatorias

    srand(time(NULL));

    int aleatorio = valor;
    int size = fil*col;
    int n_casillas = (aleatorio*size)/100;      //calculamos el numero de obstaculos a generar en base al % definido
    int num[n_casillas];

    for(int i=0;i<n_casillas;i++)       
        num[i]=rand()%size;     //Generamos las n_casillas, aleatoriamente, que vamos a rellenar con obstaculos

    for(int i=0;i<n_casillas;i++){      //En cada casilla a rellenar con obstaculo
        int obst = rand()%3;            //rellenamos con un obstaculo aleatorio dentro de los posibles
        switch(obst){
            case 0: mapa_[num[i]/col][num[i]%col]->set_pixmap(Arbol); break;
            case 1: mapa_[num[i]/col][num[i]%col]->set_pixmap(Edificio); break;
            case 2: mapa_[num[i]/col][num[i]%col]->set_pixmap(Cono);
        }
    }
}


Pixmap*** Scene::get_mapa(){

    return mapa_;
}


int** Scene::get_pos_ini(){

    return pos_ini_fin;
}


void Scene::generarMapa(){

    int pos_x = 0, pos_y = 0;

    mapa_ = new Pixmap** [fil];
    for (int i=0; i<fil; i++)
        mapa_[i] = new Pixmap* [col];

    for (int i=0; i<fil; i++){
        for (int j=0; j<col; j++){      //Generamos tantas casillas como filas*columnas existan
            mapa_[i][j] = new Pixmap(Nada);
            mapa_[i][j]->setOffset(pos_x,pos_y);
            mapa_[i][j]->set_coords(i,j);
            this->addItem(mapa_[i][j]);
            pos_x += 20;        //Cada casilla es de 20px con lo que la x se ira desplazando por la fila de 20 en 20
        }
        pos_x = 0;
        pos_y += 20;            //Cada casilla es de 20px con lo que la y se ira desplazando por la columna de 20 en 20
    }
}


void Scene::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent){  //Funcion que nos permitira incluir obstaculos en el mapa manualmente

    QPointF pos = mouseEvent->lastScenePos();
    //Traducimos las posiciones del mapa que van de 20 en 20 a posiciones de 1 en 1:
    int x = pos.toPoint().y() / 20 / 1;
    int y = pos.toPoint().x() / 20 / 1;

    if (x<0 || y<0 || x>=fil || y>=col)     //Si pinchamos fuera del mapa salimos de la funcion
            return;

    if (mouseEvent->button()==Qt::RightButton)      //Con click derecho añadimos una casilla vacia
        mapa_[x][y]->set_pixmap(Nada);

    else if (mouseEvent->button()==Qt::LeftButton){ //Con el boton izquierdo añadimos un obstaculo

        if (img_actual == Inicio ){ //Si la imagen es inicio y la posicion esta dentro del mapa, añadimos a la casilla la imagen

            //Si la casilla no contiene ni al inicio ni al final entonces:
            if (((x != pos_ini_fin[0][0]) || (y != pos_ini_fin[0][1])) && ((x != pos_ini_fin[1][0]) || (y != pos_ini_fin[1][1]))){

                if(pos_ini_fin[0][0]!=-1)
                //Comprobamos que ya existia un inicio en el mapa y si existia se sustituye por una casilla vacia:
                //si alguna de sus coordenadas es positiva es que existe dentro del mapa
                    mapa_[pos_ini_fin[0][0]][pos_ini_fin[0][1]]->set_pixmap(Nada);
                //Actualizamos la posicion de inicio y añadimos en la casilla la imagen de inicio
                pos_ini_fin[0][0] = x;
                pos_ini_fin[0][1] = y;
                mapa_[x][y]->set_pixmap(img_actual);
            }
            //Si la casilla no contiene al final, es decir, contendra el inicio por exclusion del anterior if
            //se coloca la imagen de inicio sobre si misma:
            else if((x != pos_ini_fin[1][0]) || (y != pos_ini_fin[1][1]))
                mapa_[x][y]->set_pixmap(img_actual);
        }
        else if (img_actual == Final){  //Si la imagen es final y la posicion esta dentro del mapa, añadimos a la casilla la imagen

            //Si la casilla no contiene ni al inicio ni al final entonces:
            if (((x != pos_ini_fin[1][0]) || (y != pos_ini_fin[1][1]))&& ((x != pos_ini_fin[0][0]) || (y != pos_ini_fin[0][1]))){

                if(pos_ini_fin[1][0]!=-1)
                //Comprobamos que ya existia un final en el mapa y si existia se sustituye por una casilla vacia:
                //si alguna de sus coordenadas es positiva es que existe dentro del mapa
                    mapa_[pos_ini_fin[1][0]][pos_ini_fin[1][1]]->set_pixmap(Nada);
                //Actualizamos la posicion de final y añadimos en la casilla la imagen de final
                pos_ini_fin[1][0] = x;
                pos_ini_fin[1][1] = y;
                mapa_[x][y]->set_pixmap(img_actual);
            }
            //Si la casilla no contiene al final, es decir, contendra el inicio por exclusion del anterior if
            //se coloca la imagen de inicio sobre si misma:
            else if((x != pos_ini_fin[0][0]) || (y != pos_ini_fin[0][1]))
                mapa_[x][y]->set_pixmap(img_actual);
        }
        //Si no es ni inicio ni final, se coloca en la casilla la imagen actual
        //teniendo en cuenta que no podemos machacar ni el inicio ni el final
        else if (((x != pos_ini_fin[1][0]) || (y != pos_ini_fin[1][1])) && ((x != pos_ini_fin[0][0]) || (y != pos_ini_fin[0][1])))
            mapa_[x][y]->set_pixmap(img_actual);
    }
}
