/**
    @mainpage The Wall
    @file youdied.cpp
    @author Nic Mon
    @date 3/13/15
        @brief this file declares the MainWindow class for The Wall
                which will be the first window to be shown

*/

#include "youdied.h"
#include "ui_youdied.h"

youdied::youdied(int kills, GameBoard* gb, MainWindow* main, QWidget *parent) :
    QWidget(parent),
    kill_count(kills),
    board(gb),
    mw(main),
    ui(new Ui::youdied)

{
    ui->setupUi(this);

    text = new QLabel("You Know Nothing, Jon Snow");
    count_text = new QLabel("Walkers Killed:");
    kills_num = new QLabel(QString::number(kill_count));

    retry = new QPushButton("Retry");
    quit = new QPushButton("Quit");

    main_layout = new QVBoxLayout;

    main_layout->addWidget(text,0,Qt::AlignHCenter);
    main_layout->addWidget(count_text,0,Qt::AlignCenter);
    main_layout->addWidget(kills_num,0,Qt::AlignCenter);
    main_layout->addWidget(retry);
    main_layout->addWidget(quit);

    this->setLayout(main_layout);
    this->setWindowTitle("Game Over");

    QObject::connect(retry,SIGNAL(clicked()),this,SLOT(new_game()));
    QObject::connect(quit,SIGNAL(clicked()),this,SLOT(quit_game()));

}

/** @function new_game
    @brief this function deletes the old GameBoard, makes a new one and
            starts a new game
*/
void youdied::new_game(){
    delete board;
    GameBoard* new_board = new GameBoard(mw);
    mw->setGameBoard(new_board);
    new_board->show();
    delete this;
}

/** @function quit_game
    @brief this function closes the game and deletes all the windows
*/
void youdied::quit_game(){
    delete mw;
    delete board;
    this->close();
    delete this;
}

youdied::~youdied()
{
    delete ui;
}
