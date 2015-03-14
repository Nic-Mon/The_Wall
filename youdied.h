/**
    @mainpage The Wall
    @file youdied.h
    @author Nic Mon
    @date 3/13/15
        @brief this file implements the youdied class for The Wall

*/

#ifndef YOUDIED_H
#define YOUDIED_H

#include <QWidget>
#include "gameboard.h"
#include "mainwindow.h"

namespace Ui {
class youdied;
}

/** @class youdied
    @brief this class codes the window that pops up when the game is over
            shows the Kill Count, and has buttons to retry and quit
*/
class youdied : public QWidget
{
    Q_OBJECT

public slots:
    void new_game();
    void quit_game();

public:
    explicit youdied(int kills, GameBoard* gb, MainWindow* main, QWidget *parent = 0);
    ~youdied();

private:
    QLabel* text;
    QLabel* count_text;
    QLabel* kills_num;

    int kill_count;

    GameBoard* board;
    MainWindow* mw;

    QPushButton* retry;
    QPushButton* quit;

    QVBoxLayout* main_layout;

    QBoxLayout* central;

    Ui::youdied *ui;
};

#endif // YOUDIED_H
