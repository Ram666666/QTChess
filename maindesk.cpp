#include "maindesk.h"
#include "ui_maindesk.h"
#include"QDebug"
#include"Game.h"
#include"QFileDialog"
#include <QMouseEvent>
#include"end_game.h"
#include"illustration.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    enddialog=new end_game(this);
    ill =new illustration(this);
    ill->setWindowTitle("游戏说明");


    QObject::connect(this,SIGNAL(show_illus()),ill,SLOT(show_illustration()));
}

Widget::~Widget()
{   delete  game_desk;
    delete ui;
}


void Widget::on_pushButton_2_clicked()//点击开始游戏 进入游戏界面
{   this->hide();
    game_desk=new Game();
    game_desk->setWindowTitle("五子棋");
   QObject::connect(game_desk,SIGNAL(restart()),this,SLOT(start_again()));
    qDebug()<<"open a new window";
    game_desk->show();

}

void Widget::on_pushButton_3_clicked()//说明按钮
{
    emit show_illus();
}

void Widget::start_again()
{
    this->show();
}
