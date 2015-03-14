/**
    @mainpage The Wall
    @file main.cpp
    @author Nic Mon
    @date 3/13/15
        @brief this file includes main, initialized the mainwindow and first GameBoard

*/

#include "mainwindow.h"
#include "gameboard.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Q_INIT_RESOURCE(Images);

    MainWindow* w = new MainWindow;
    GameBoard* b = new GameBoard(w);

    w->setGameBoard(b);

    w->show();


    return a.exec();
}
