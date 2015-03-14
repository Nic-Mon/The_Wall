/**
    @mainpage The Wall
    @file mainwindow.h
    @author Nic Mon
    @date 3/13/15
        @brief this file declares the MainWindow class for The Wall
                which will be the first window to be shown

*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QLabel>
#include <QRadioButton>
#include <QPushButton>
#include <QBoxLayout>


class GameBoard;
class Instructions;

/** @class MainWindow
    @brief this class codes up the opening window of the wall
            it will have a button to start, and a button to display instructions
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setGameBoard(GameBoard *game_board);

    GameBoard* board;
    QLabel* instruct;
    QPixmap* instr_image;

    QLabel *title_one;
    QLabel *title_two;
    QLabel *title_three;

    QPushButton *instr;
    QPushButton *start;

    QVBoxLayout *main_layout;
    QWidget *central;
};

#endif // MAINWINDOW_H
