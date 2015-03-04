#include "mainwindow.hpp"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent):    //Constructor

            //En el constructor ativamos las sentencias que nos permitiran
            //mantener "alerta" los botones y demas

    QMainWindow(parent),
    ui(new Ui::MainWindow){

        ui->setupUi(this);

        scene = NULL;
        robot = NULL;
        ui->gv_Mapa->setScene(scene);

        connect(ui->spin_Filas, SIGNAL(valueChanged(int)), this, SLOT(bloquearResolver()));
        connect(ui->spin_Columnas, SIGNAL(valueChanged(int)), this, SLOT(bloquearResolver()));
        connect(ui->btn_Aumentar, SIGNAL(clicked()), this, SLOT(aumentarEscala()));
        connect(ui->btn_Reducir, SIGNAL(clicked()), this, SLOT(reducirEscala()));
        connect(ui->btn_GenerarMapa, SIGNAL(clicked()), this, SLOT(generarMapa()));

        connect(ui->btn_Aleatorio, SIGNAL(toggled(bool)), this, SLOT(setAleatorio()));
        connect(ui->slider_Aleatorio, SIGNAL(valueChanged(int)), this, SLOT(setAleatorioValor(int)));
        connect(ui->btn_GenerarAleatorio, SIGNAL(clicked()), this, SLOT(generarObstaculos()));

        connect(ui->btn_Manual, SIGNAL(toggled(bool)), this, SLOT(setManual()));
        connect(ui->btn_Inicio, SIGNAL(clicked()),this, SLOT(setInicio()));
        connect(ui->btn_Final, SIGNAL(clicked()),this, SLOT(setFinal()));
        connect(ui->btn_Nada, SIGNAL(clicked()),this, SLOT(setNada()));
        connect(ui->btn_Edificio, SIGNAL(clicked()),this, SLOT(setEdificio()));
        connect(ui->btn_Cono, SIGNAL(clicked()),this, SLOT(setCono()));
        connect(ui->btn_Arbol, SIGNAL(clicked()),this, SLOT(setArbol()));

        connect(ui->btn_Solucion, SIGNAL(clicked()), this, SLOT(generarSolucion()));

        connect(ui->action_Salir, SIGNAL(triggered()),qApp,SLOT(quit()));
}


MainWindow::~MainWindow(){      //Destructor

    delete ui;

    if (robot){
        delete robot;
        robot = NULL;
    }

    if (scene){
        delete scene;
        scene = NULL;
    }
}


void MainWindow::bloquearResolver(){        //Funcion que bloquea el boton para solucionar la busqueda

    ui->btn_Solucion->setEnabled(false);
}


void MainWindow::permitirResolver(){        //Funcion que activa el boton para solucionar la busqueda

    ui->btn_Solucion->setEnabled(true);
}


void MainWindow::aumentarEscala(){      //Funcion que usaremos para aumentar la escala del mapa

    ui->gv_Mapa->scale(1.2,1.2);
}


void MainWindow::reducirEscala(){       //Funcion que usaremos para reducir la escala del mapa

        ui->gv_Mapa->scale(1/1.2,1/1.2);
}


void MainWindow::setAleatorio(){        //Funcion que va a modificar la interfaz para posibilitar que podamos
                                        //generar un mapa de manera aleatoria

    ui->slider_Aleatorio->setEnabled(true);
    ui->btn_GenerarAleatorio->setEnabled(true);

    ui->gv_Mapa->setInteractive(false);

    ui->btn_Inicio->setEnabled(false);
    ui->btn_Final->setEnabled(false);
    ui->btn_Nada->setEnabled(false);
    ui->btn_Edificio->setEnabled(false);
    ui->btn_Cono->setEnabled(false);
    ui->btn_Arbol->setEnabled(false);

    ui->btn_Inicio->setChecked(false);
    ui->btn_Final->setChecked(false);
    ui->btn_Nada->setChecked(false);
    ui->btn_Edificio->setChecked(false);
    ui->btn_Cono->setChecked(false);
    ui->btn_Arbol->setChecked(false);
}


void MainWindow::setAleatorioValor(int valor){      //Funcion que nos va a permitir indicar que porcentaje de obstaculos
                                                    //generar en nuestro mapa aleatorio

    ui->progress_Aleatorio->setValue(valor);
}


void MainWindow::setManual(){       //Funcion que va a activar los botones para generar un mapa de manera manual

    ui->slider_Aleatorio->setEnabled(false);
    ui->btn_GenerarAleatorio->setEnabled(false);

    ui->gv_Mapa->setInteractive(true);

    ui->btn_Inicio->setEnabled(true);
    ui->btn_Final->setEnabled(true);
    ui->btn_Nada->setEnabled(true);
    ui->btn_Edificio->setEnabled(true);
    ui->btn_Cono->setEnabled(true);
    ui->btn_Arbol->setEnabled(true);

    ui->btn_Nada->setChecked(true);
}


void MainWindow::setInicio(){       //Funcion que va a activar el selector de inicio y desactiva los demas

    scene-> set_actual(Inicio);

    ui->btn_Inicio->setChecked(false);
    ui->btn_Final->setChecked(false);
    ui->btn_Nada->setChecked(false);
    ui->btn_Edificio->setChecked(false);
    ui->btn_Cono->setChecked(false);
    ui->btn_Arbol->setChecked(false);
}


void MainWindow::setFinal(){        //Funcion que va a activar el selector de final y desactiva los demas

    scene-> set_actual(Final);

    ui->btn_Inicio->setChecked(false);
    ui->btn_Final->setChecked(true);
    ui->btn_Nada->setChecked(false);
    ui->btn_Edificio->setChecked(false);
    ui->btn_Cono->setChecked(false);
    ui->btn_Arbol->setChecked(false);
}


void MainWindow::setNada(){     //Funcion que va a activar el selector de nada y desactiva los demas

    scene-> set_actual(Nada);

    ui->btn_Inicio->setChecked(false);
    ui->btn_Final->setChecked(false);
    ui->btn_Nada->setChecked(true);
    ui->btn_Edificio->setChecked(false);
    ui->btn_Cono->setChecked(false);
    ui->btn_Arbol->setChecked(false);
}


void MainWindow::setEdificio(){     //Funcion que va a activar el selector de edificio y desactiva los demas

    scene-> set_actual(Edificio);

    ui->btn_Inicio->setChecked(false);
    ui->btn_Final->setChecked(false);
    ui->btn_Nada->setChecked(false);
    ui->btn_Edificio->setChecked(true);
    ui->btn_Cono->setChecked(false);
    ui->btn_Arbol->setChecked(false);
}


void MainWindow::setCono(){     //Funcion que va a activar el selector de cono y desactiva los demas

    scene-> set_actual(Cono);

    ui->btn_Inicio->setChecked(false);
    ui->btn_Final->setChecked(false);
    ui->btn_Nada->setChecked(false);
    ui->btn_Edificio->setChecked(false);
    ui->btn_Cono->setChecked(true);
    ui->btn_Arbol->setChecked(false);
}


void MainWindow::setArbol(){        //Funcion que va a activar el selector de arbol y desactiva los demas

    scene-> set_actual(Arbol);

    ui->btn_Inicio->setChecked(false);
    ui->btn_Final->setChecked(false);
    ui->btn_Nada->setChecked(false);
    ui->btn_Edificio->setChecked(false);
    ui->btn_Cono->setChecked(false);
    ui->btn_Arbol->setChecked(true);
}


void MainWindow::generarObstaculos(){       //Funcion que va a llamar a la funcion de la clase del atributo 

    generarMapa();
    scene->generarAleatorio(ui->progress_Aleatorio->value());
}


void MainWindow::generarMapa(){

    if (robot){                         //Si hubiese un robot se destruiria
        delete robot;
        robot = NULL;
    }

    if (scene){                         //Si hubiese una escena se destruiria
        delete scene;
        scene = NULL;
    }

    int filas = ui->spin_Filas->value();        
    int columnas = ui->spin_Columnas->value();

    scene = new Scene(filas,columnas);  //Se crea una nueva escena
//  Se pasara a generar el mapa
//  {
    scene->setSceneRect(0,0,0,0);
    ui->gv_Mapa->setScene(scene);
    ui->gv_Mapa->fitInView(QRectF(0,0,filas*20,columnas*20),Qt::KeepAspectRatioByExpanding);

    ui->btn_Manual->setEnabled(true);
    ui->btn_Inicio->setChecked(false);
    ui->btn_Final->setChecked(false);
    ui->btn_Edificio->setChecked(false);
    ui->btn_Cono->setChecked(false);
    ui->btn_Arbol->setChecked(false);

    if(ui->btn_Manual->isChecked())
        ui->btn_Nada->setChecked(true);
    else
        ui->btn_Nada->setChecked(false);

    permitirResolver();
//  }
}


void MainWindow::generarSolucion(){

    if (robot){                     //Si hubiese un robot se destruiria
        delete robot;
        robot = NULL;
    }

    if (solucionable()){            //Si esta permitido solucionar entonces:

        int filas = ui->spin_Filas->value();
        int columnas = ui->spin_Columnas->value();
        Pixmap*** cp_mapa = scene->get_mapa();  //se crea una copia del mapa

        //Se crea un robot pasandole el mapa, la posicion de inicio y final y sus dimensiones
        robot = new Robot(cp_mapa,scene->get_pos_ini(), filas, columnas);   

        //Luego el robot resolvera el problema mediante A_estrella
        if (robot->A_estrella() == -1){     //En caso de que A_estrella devuelva -1 no hay solucion
            QMessageBox alerta;     //Se crea un mensaje de alerta
            alerta.setWindowTitle("UPS!!");
            alerta.setText("No existe solución para el camino introducido.");
            alerta.exec();
        }
    }
}


bool MainWindow::solucionable(){
    //El problema sera resoluble si existen un inicio y un final en el mapa
    int** ini_fin = scene->get_pos_ini();

    if ((ini_fin[0][0] != -1) && (ini_fin[1][0] != -1))
        //Si existen inicio y fin dentro del mapa, es resoluble
        return true;
    else
        return false;
}
