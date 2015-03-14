/**
    @mainpage The Wall
    @file mainwindow.cpp
    @author Nic Mon
    @date 3/13/15
        @brief this file implements the MainWindow class for The Wall
                which will be the first window to be shown

*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gameboard.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    instruct = new QLabel;
    instr_image = new QPixmap(":/Images/Instructions");
    instruct->setMinimumSize(584,508);
    instruct->setMaximumSize(584,508);
    instruct->setPixmap(*instr_image);
    instruct->setScaledContents(true);

    title_one = new QLabel("Welcome, Jon Snow!");
    title_two = new QLabel("Are You Ready To Defend");
    title_three = new QLabel("THE WALL");

    instr = new QPushButton("Instructions");
    start = new QPushButton("Start!");

    main_layout = new QVBoxLayout;

    main_layout->addWidget(title_one,0,Qt::AlignCenter);
    main_layout->addWidget(title_two,0,Qt::AlignCenter);
    main_layout->addWidget(title_three,0,Qt::AlignCenter);

    main_layout->addWidget(instr);
    main_layout->addWidget(start);


    central = new QWidget;
    central->setLayout(main_layout);

    this->setCentralWidget(central);

    connect(instr,SIGNAL(clicked()),instruct,SLOT(show()));
}

MainWindow::~MainWindow()
{

}

void MainWindow::setGameBoard(GameBoard *game_board){
    board = game_board;

    QObject::connect(start, SIGNAL(clicked()), board, SLOT(show()));
}
