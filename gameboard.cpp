/**
    @mainpage The Wall
    @file gameboard.cpp
    @author Nic Mon
    @date 3/13/15
        @brief this file implements the GameBoard class for The Wall

*/

#include "gameboard.h"
#include "ui_gameboard.h"
#include <QTimer>
#include <vector>
#include <QSound>
#include <ctime>
#include <random>
#include <chrono>
#include <QSpacerItem>

//randomness macros
#define SEED (unsigned int)std::chrono::system_clock::now().time_since_epoch().count()
#define DEFAULT std::default_random_engine
#define DBERN std::bernoulli_distribution


GameBoard::GameBoard(MainWindow* main, QWidget *parent) :
    QWidget(parent), board_height(10), board_width(20), mw(main)
{
    Board = new QWidget;
    labels = new QLabel*[board_height*board_width];
    QGridLayout *Grid = new QGridLayout(Board);

    /*
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(updateWalkers()));
    timer->start(1000);
    */

    player_image = new QPixmap(":/Images/JonSnow");
    walker_image = new QPixmap(":/Images/Walker");
    knight_image = new QPixmap(":/Images/knight");
    bishop_image = new QPixmap(":/Images/bishop");
    rook_image = new QPixmap(":/Images/rook");
    queen_image = new QPixmap(":/Images/queen");

    kill_text = new QLabel("Kill Count: ");
    kills = new QLabel("0");
    kill_layout = new QHBoxLayout;
    kill_layout->addWidget(kill_text);
    kill_layout->addWidget(kills);

    points_text = new QLabel("Mana: ");
    points_label = new QLabel("0");
    points_label->setStyleSheet("font: 36pt; font-weight:600; color: blue");
    points_layout = new QVBoxLayout;
    points_layout->addWidget(points_text,0,Qt::AlignCenter);
    points_layout->addWidget(points_label,0,Qt::AlignCenter);

    knight_label = new QLabel;
    knight_label->setMinimumSize(60,60);
    knight_label->setMaximumSize(60,60);
    knight_label->setPixmap(*knight_image);
    knight_label->setScaledContents(true);
    knight_cost = new QLabel("Cost: 2");
    knight_layout = new QVBoxLayout;
    knight_layout->addWidget(knight_label,0,Qt::AlignCenter);
    knight_layout->addWidget(knight_cost,0,Qt::AlignCenter);

    bishop_label = new QLabel;
    bishop_label->setMinimumSize(60,60);
    bishop_label->setMaximumSize(60,60);
    bishop_label->setPixmap(*bishop_image);
    bishop_label->setScaledContents(true);
    bishop_cost = new QLabel("Cost: 5");
    bishop_layout = new QVBoxLayout;
    bishop_layout->addWidget(bishop_label,0,Qt::AlignCenter);
    bishop_layout->addWidget(bishop_cost,0,Qt::AlignCenter);

    rook_label = new QLabel;
    rook_label->setMinimumSize(60,60);
    rook_label->setMaximumSize(60,60);
    rook_label->setPixmap(*rook_image);
    rook_label->setScaledContents(true);
    rook_cost = new QLabel("Cost: 8");
    rook_layout = new QVBoxLayout;
    rook_layout->addWidget(rook_label,0,Qt::AlignCenter);
    rook_layout->addWidget(rook_cost,0,Qt::AlignCenter);

    queen_label = new QLabel;
    queen_label->setMinimumSize(60,60);
    queen_label->setMaximumSize(60,60);
    queen_label->setPixmap(*queen_image);
    queen_label->setScaledContents(true);
    queen_cost = new QLabel("Cost: 10");
    queen_layout = new QVBoxLayout;
    queen_layout->addWidget(queen_label,0,Qt::AlignCenter);
    queen_layout->addWidget(queen_cost,0,Qt::AlignCenter);

    for(int row=0; row<board_height; row++){

        labels[row*board_width] = new QLabel;
        labels[row*board_width]->setMinimumSize(40,40);
        labels[row*board_width]->setMaximumSize(40,40);
        labels[row*board_width]->setStyleSheet("QLabel { background-color: brown }");
        labels[row*board_width]->setFrameStyle(3);

        Grid -> addWidget(labels[row*board_width], row, 0);

        for(int column=1; column<board_width; column++){

            labels[row*board_width+column] = new QLabel;
            labels[row*board_width+column]->setMinimumSize(40,40);
            labels[row*board_width+column]->setMaximumSize(40,40);
            labels[row*board_width+column]->setStyleSheet("QLabel { background-color: white }");

            Grid -> addWidget(labels[row*board_width+column], row, column);
        }
    }

    //start player off at position (2,4)
    player_position = new QPoint(2,4);
    labels[4*board_width+2]->setPixmap(*player_image);
    labels[4*board_width+2]->setScaledContents(true);

    QVBoxLayout* main_layout = new QVBoxLayout;
    QHBoxLayout* header = new QHBoxLayout;

    header->addLayout(points_layout);
    header->addLayout(knight_layout);
    header->addLayout(bishop_layout);
    header->addLayout(rook_layout);
    header->addLayout(queen_layout);
    header->addLayout(kill_layout);


    QWidget* top;
    top = new QWidget;
    top->setLayout(header);

    main_layout->addWidget(top,0,Qt::AlignCenter);
    main_layout->addWidget(Board,0,Qt::AlignCenter);

    this->setLayout(main_layout);

    this->setWindowTitle("The Wall");

}

void GameBoard::keyPressEvent(QKeyEvent *event){

    int x = player_position->rx();
    int y = player_position->ry();

    switch(event->key()) {
    case Qt::Key_Left:
        if(player_position->rx() != 1)
            updatePlayer(x,y,x-1,y);
        break;

    case Qt::Key_Right:
        if(player_position->rx() != board_width-1)
            updatePlayer(x,y,x+1,y);
        break;

    case Qt::Key_Up:
        if(player_position->ry() != 0)
            updatePlayer(x,y,x,y-1);
        break;

    case Qt::Key_Down:
        if(player_position->ry() != board_height-1)
            updatePlayer(x,y,x,y+1);
        break;

    case Qt::Key_Z:
        if(points >= 2) {
            knight_attack(*player_position);
            points -= 2;
            points_label->setText(QString::number(points));
        }
        break;

    case Qt::Key_X:
        if(points >= 5) {
            bishop_attack(*player_position);
            points -= 5;
            points_label->setText(QString::number(points));
        }
        break;

    case Qt::Key_C:
        if(points >= 8) {
            rook_attack(*player_position);
            points -= 8;
            points_label->setText(QString::number(points));
        }
        break;

    case Qt::Key_V:
        if(points >= 10) {
            queen_attack(*player_position);
            points -= 10;
            points_label->setText(QString::number(points));
        }
        break;

    default:
        QWidget::keyPressEvent(event);
    }
    repaint();
    QCoreApplication::processEvents();
    return;
}

/** @function attempt_kill
    @brief this function attempts to kill a walker on QPoint p if there is one
*/
void GameBoard::attempt_kill(QPoint p){

    if( p.rx() > 0 && p.rx() < board_width && p.ry() >= 0 && p.ry() < board_height){
        if(p != *player_position)
            labels[p.ry()*board_width+p.rx()]->setStyleSheet("QLabel { background-color: blue }");

        auto it = std::find(walkers.begin(), walkers.end(), p);
        if (it != walkers.end()) {
            killCount++;
            points++;
            walkers.erase(it);
            clearWalker(p);
            kills->setText(QString::number(killCount));
            points_label->setText(QString::number(points));

            /*
            if(killCount%3 == 0) { knight_num++; knights->setText(QString::number(knight_num)); }
            if(killCount%5 == 0) { bishop_num++; bishops->setText(QString::number(bishop_num)); }
            if(killCount%10 == 0) { rook_num++; rooks->setText(QString::number(rook_num)); }
            if(killCount%20 == 0) { queen_num++; queens->setText(QString::number(queen_num)); }
            */
        }
    }
}

/** @function knight_attack
    @brief this function performs a knight attack from a given QPoint
*/
void GameBoard::knight_attack(QPoint p){
    int x = p.rx();
    int y = p.ry();

    attempt_kill(QPoint(x+1,y+2));
    attempt_kill(QPoint(x+2,y+1));
    attempt_kill(QPoint(x+2,y-1));
    attempt_kill(QPoint(x+1,y-2));
    attempt_kill(QPoint(x-1,y-2));
    attempt_kill(QPoint(x-2,y-1));
    attempt_kill(QPoint(x-2,y+1));
    attempt_kill(QPoint(x-1,y+2));

}

/** @function bishop_attack
    @brief this function performs a bishop attack from a given QPoint
*/
void GameBoard::bishop_attack(QPoint p){
    int x = p.rx();
    int y = p.ry();

    for(int i=1; i<board_height; i++) {
        attempt_kill(QPoint(x+i,y+i));
        attempt_kill(QPoint(x+i,y-i));
        attempt_kill(QPoint(x-i,y-i));
        attempt_kill(QPoint(x-i,y+i));
    }
}

/** @function rook_attack
    @brief this function performs a rook attack from a given QPoint
*/
void GameBoard::rook_attack(QPoint p){
    int x = p.rx();
    int y = p.ry();

    for(int i=0; i<board_height; i++){
        attempt_kill(QPoint(x,i));
    }
    for(int i=1; i<board_width; i++){
        attempt_kill(QPoint(i,y));
    }
}

/** @function queen_attack
    @brief this function performs a queen attack from a given QPoint
*/
void GameBoard::queen_attack(QPoint p){
    rook_attack(p);
    bishop_attack(p);
}

void GameBoard::clearWalker(QPoint p){
    labels[p.y()*board_width+p.x()]->clear();
}

void GameBoard::paintWalker(QPoint p){
    labels[p.y()*board_width+p.x()]->setPixmap(*walker_image);
    labels[p.y()*board_width+p.x()]->setScaledContents(true);
}

void GameBoard::paintEvent(QPaintEvent *e) {

    int x = player_position->rx();
    int y = player_position->ry();

    labels[y*board_width+x]->setPixmap(*player_image);
    labels[y*board_width+x]->setScaledContents(true);

    for(auto &w: walkers) { paintWalker(w); }

}

/** @function walk
    @breif this function moves a QPoint 1 unit to the left, ends game if x=0
*/
void GameBoard::walk(QPoint &p){
    p.rx()--;
    if(p.x() == 0) gameOver();
}

/** @function updateWalkers
    @brief this function moves the walkers and genereates new walker(s)
*/
void GameBoard::updateWalkers(){



    for(auto &w: walkers) { clearWalker(w); walk(w); }

    //generate walker
    DEFAULT generator(SEED);
    double x = (2 + sqrt(killCount))/50;
    DBERN bern(x);

    for(int i=0; i<board_height; i++)
        if(bern(generator)) walkers.push_back(QPoint(19,i));

}

/** @function updatePlayer
    @brief this function moves the player, attempting a kill on the new position
*/
void GameBoard::updatePlayer(int px, int py, int nx, int ny){
    if(counter%2 == 0)
        updateWalkers();

    for(int x=1; x<board_width; x++)
        for(int y=0; y<board_height; y++)
            labels[y*board_width+x]->setStyleSheet("QLabel { background-color: white }");

    attempt_kill(*player_position);

    labels[py*board_width+px]->clear();
    player_position->setX(nx);
    player_position->setY(ny);

    attempt_kill(*player_position);

    counter++;
}

/** @function gameOver
    @brief this function end the Game
*/
void GameBoard::gameOver(){
    youdied* window = new youdied(killCount, this, mw);
    window->show();
}


GameBoard::~GameBoard()
{

}
