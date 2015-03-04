#include "mainwindow.hpp"
#include <QApplication>
//main del programa en el que se muestra la ventana grafica
int main(int argc, char *argv[]){

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
