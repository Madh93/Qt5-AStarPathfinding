#include "robot.hpp"


Robot::Robot(Pixmap*** &copia, int** ini_fin, int fil_, int col_){

    cp_mapa = copia;
    pos_ini_fin = ini_fin;

    ini = cp_mapa[ini_fin[0][0]][ini_fin[0][1]];    //tener la posicion del inicio
    fin = cp_mapa[ini_fin[1][0]][ini_fin[1][1]];    //tener la posicion del final
    actual = NULL;
    vecino = NULL;

    pos[0] = pos_ini_fin[0][0];
    pos[1] = pos_ini_fin[0][1];

    fil = fil_;
    col = col_;
    abierta.resize(0);
    cerrada.resize(0);
    total.resize(0);
}


Robot::~Robot(){

    limpiar_camino();

    cp_mapa = NULL;

    ini = NULL;
    fin = NULL;
    actual = NULL;
    vecino = NULL;

    pos_ini_fin = NULL;
    pos[0] = 0;
    pos[1] = 0;
    fil = 0;
    col = 0;
}


int Robot::A_estrella(){    //Implementacion, explicado en el informe

    abierta.push_back(ini);
    ini->set_coste(0);
    manhattan(pos[0],pos[1]);

    while (!abierta.empty()){

        std::sort(abierta.begin(), abierta.end(), Pixmap::lessThan);

        actual = abierta.front();
        pos[0] = actual->get_x();
        pos[1] = actual->get_y();

        if (actual == fin){
            camino(fin);
            return 0;
        }

        abierta.erase(abierta.begin());

        if(std::find(cerrada.begin(),cerrada.end(), actual) != cerrada.end()){

            QVector<Pixmap*>::iterator i = std::find(cerrada.begin(),cerrada.end(), actual);

            if(actual<*(i)){
                cerrada.erase(i);
                cerrada.push_back(actual);
            }
        }

        else
            cerrada.push_back(actual);

        hallar_vecinos(actual);

        for(int i=0; i<4; i++){

            vecino = actual->get_vecinos(i);

            if (vecino){

                if ((std::find(cerrada.begin(),cerrada.end(), vecino) != cerrada.end()))
                    continue;

                int tentativa = actual->get_coste() + 1;

                if ((std::find(abierta.begin(),abierta.end(), vecino) == abierta.end()) || (tentativa < vecino->get_coste())){

                    vecino->set_predecesor(actual);
                    vecino->set_coste(tentativa);
                    manhattan(vecino->get_x(),vecino->get_y());

                    if (std::find(abierta.begin(),abierta.end(), vecino) == abierta.end())
                        abierta.push_back(vecino);
                }
            }
        }
    }

    return -1;
}


void Robot::hallar_vecinos(Pixmap* actual_){    //hallar vecinos teniendo como limites
                                                //las dimensiones de l mapa
    if ( pos[0]-1 >= 0 && pos[1] >= 0 && pos[0]-1 <fil && pos[1] <col)
        if (!cp_mapa[pos[0]-1][pos[1]]->is_obstaculo())
            actual_->set_vecinos(N,cp_mapa[pos[0]-1][pos[1]]);
    if ( pos[0]+1 >= 0 && pos[1] >= 0 && pos[0]+1 <fil && pos[1] <col)
        if (!cp_mapa[pos[0]+1][pos[1]]->is_obstaculo())
            actual_->set_vecinos(S,cp_mapa[pos[0]+1][pos[1]]);
    if ( pos[0] >= 0 && pos[1]+1 >= 0 && pos[0] <fil && pos[1]+1 <col)
         if (!cp_mapa[pos[0]][pos[1]+1]->is_obstaculo())
            actual_->set_vecinos(E,cp_mapa[pos[0]][pos[1]+1]);
    if ( pos[0] >= 0 && pos[1]-1 >= 0 && pos[0] <fil && pos[1]-1 <col)
         if (!cp_mapa[pos[0]][pos[1]-1]->is_obstaculo())
            actual_->set_vecinos(O,cp_mapa[pos[0]][pos[1]-1]);
}


void Robot::manhattan(int x, int y){

    cp_mapa[x][y]->set_heuristica(abs((x-pos_ini_fin[1][0])) + abs((y-pos_ini_fin[1][1])));
}


void Robot::camino(Pixmap* current){

    total.push_back(current);

    while (current != NULL){

        if ((current != ini) && (current != fin))
            current->set_pixmap(Recorrido);
        current = current->get_predecesor();
        total.push_back(current);
    }
}


void Robot::limpiar_camino(){

    for (int i=0; i<total.size()-1;i++)
        if ((total[i] != ini) && (total[i] != fin))
            total[i]->set_pixmap(Nada);

    total.resize(0);
    abierta.resize(0);
    cerrada.resize(0);
}
