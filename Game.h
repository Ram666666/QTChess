#ifndef GAME_H
#define GAME_H
#include <QWidget>
#include <QMouseEvent>
#include"end_game.h"
#include<QSound>
#include <QMediaPlayer>

namespace Ui {
class Game;
}

class Game : public QWidget
{
    Q_OBJECT

public:
     QTimer *timer;
    explicit Game(QWidget *parent = nullptr);
    ~Game();
    const int boardsize=15;//决定棋盘大小
    const int width=40;//棋盘方格宽度
    const int x=20,y=17;//从（20,17）为左上角开始画
    const int chess_r=18;//棋子半径大小
    end_game *enddialog;
public slots:
    void on_pushButton_clicked();
    void close_slot();
    void display();
    void on_pushButton_2_clicked();
    void start_again_2();
private:

    //两个音效
    QMediaPlayer *mediaplayer;
    QMediaPlayer *mediaplayer2;
    Ui::Game *ui;
    void paintEvent(QPaintEvent *);//这是绘图函数
    void mousePressEvent(QMouseEvent *event);//这是鼠标事件
     QPainter *paint;
     int chessboard[15][15]={{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0}};//棋盘数组
     int chessboard_2[15][15]={{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0}};//用来悔棋
     int turn=2;
     //判断输赢
     int wingame(int a,int b);
     //判断是否有五个棋子连线
     int check1(int x,int y);
     int check2(int x,int y);
     int check3(int x,int y);
     int check4(int x,int y);
     int check5(int x,int y);
     int check6(int x,int y);
     //判断是否死局
     bool deadgame();
     //玩家
     int player=1;
     end_game *endgame;
signals:
     void restart();
private slots:
     int on_pushButton_3_clicked();
     void on_pushButton_4_clicked();
     void on_Game_customContextMenuRequested(const QPoint &pos);
};

#endif // GAME_H
