#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QMessageBox>
#include "scene.hpp"
#include "robot.hpp"


//Clase en la que vamos a implementar la ventana grafica
//con la que se interactuará para resolver las búsquedas


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow{

    Q_OBJECT

    private:

        Ui::MainWindow *ui;
        Scene* scene;
        Robot* robot;

    public:

        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    public slots:

        void bloquearResolver();                //Funcion que bloquea el boton para solucionar la busqueda
        void permitirResolver();                //Funcion que activa el boton para solucionar la busqueda

        void aumentarEscala();                  //Funcion que usaremos para aumentar la escala del mapa
        void reducirEscala();                   //Funcion que usaremos para reducir la escala del mapa

        void setAleatorio();                    //Funcion que va a modificar la interfaz para posibilitar que podamos
                                                //generar un mapa de manera aleatoria
        void setAleatorioValor(int valor);      //Funcion que nos va a permitir indicar que porcentaje de obstaculos
                                                //generar en nuestro mapa aleatorio

        void setManual();       //Funcion que va a activar los botones para generar un mapa de manera manual
        void setInicio();       //Funcion que va a activar el selector de inicio y desactiva los demas
        void setFinal();        //Funcion que va a activar el selector de final y desactiva los demas
        void setNada();         //Funcion que va a activar el selector de nada y desactiva los demas
        void setEdificio();     //Funcion que va a activar el selector de edificio y desactiva los demas
        void setCono();         //Funcion que va a activar el selector de cono y desactiva los demas
        void setArbol();        //Funcion que va a activar el selector de arbol y desactiva los demas

        void generarObstaculos();       //Funcion que va a llamar a la funcion de la clase del atributo 
                                        //para generar los obstaculos de manera aleatoria
        void generarMapa();             //Funcion que nos va a generar un mapa en blanco
        void generarSolucion();         //Funcion que va a indicar a nuestro atributo 'robot' que resuelva

        bool solucionable();            //Funcion que controlara cuando se puede o no resolver
};

#endif // MAINWINDOW_HPP
