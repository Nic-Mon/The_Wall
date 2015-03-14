/**
    @mainpage The Wall
    @file gameboard.h
    @author Nic Mon
    @date 3/13/15
        @brief this file declares the GameBoard class for The Wall

*/

#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "mainwindow.h"
#include "youdied.h"
#include <QWidget>
#include <QLabel>
#include <QMainWindow>
#include <QKeyEvent>
#include <QGridLayout>
#include <QBoxLayout>
#include <QPixmap>
#include <QPoint>
#include <vector>
#include <algorithm>


/** @class GameBoard
    @brief codes board for game to be played on
            uses an array of QLabels for the board-grid
            stores enemies in a vector of QPoints
            contains the necessary functions for game to run
*/
class GameBoard : public QWidget
{
    Q_OBJECT

public slots:
    //void updateBoard();
   void updateWalkers();
   void gameOver();

public:
    explicit GameBoard(MainWindow* mw, QWidget *parent = 0);
    ~GameBoard();

    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *e);
    //void closeEvent(QCloseEvent *e);

    void clearWalker(QPoint p);
    void paintWalker(QPoint p);
    void walk(QPoint &p);

    //player attacks
    void knight_attack(QPoint p);
    void bishop_attack(QPoint p);
    void rook_attack(QPoint p);
    void queen_attack(QPoint p);

    void attempt_kill(QPoint p);

    void updatePlayer(int px, int py, int nx, int ny);


private:
    //variable to hold counters
    unsigned int killCount = 0;
    unsigned int counter = 0;
    unsigned int points = 0;

    /*
    unsigned int knight_num = 0;
    unsigned int bishop_num = 0;
    unsigned int rook_num = 0;
    unsigned int queen_num = 0;
    */

    MainWindow* mw;


    QPixmap* player_image;
    QPixmap* walker_image;
    QPixmap* knight_image;
    QPixmap* bishop_image;
    QPixmap* rook_image;
    QPixmap* queen_image;

    QPoint* player_position;
    std::vector<QPoint> walkers;

    QTimer* timer;


    // Top Widgets
    QLabel* kill_text;
    QLabel* kills;
    QHBoxLayout* kill_layout;

    QLabel* points_text;
    QLabel* points_label;
    QVBoxLayout* points_layout;

    QLabel* knight_label;
    QLabel* knight_cost;
    QVBoxLayout* knight_layout;

    QLabel* bishop_label;
    QLabel* bishop_cost;
    QVBoxLayout* bishop_layout;

    QLabel* rook_label;
    QLabel* rook_cost;
    QVBoxLayout* rook_layout;

    QLabel* queen_label;
    QLabel* queen_cost;
    QVBoxLayout* queen_layout;

    // Board Variables
    QWidget *Board;
    int board_height;
    int board_width;
    QLabel** labels;

};

#endif // GAMEBOARD_H
