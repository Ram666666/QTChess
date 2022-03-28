#include "Game.h"
#include "ui_Game.h"
#include"QPainter"
#include"QMouseEvent"
#include"QDebug"
#include"end_game.h"
#include<QSound>
#include"QTimer"
#include"qmenu.h"
Game::Game(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Game)
{   ui->setupUi(this);
    enddialog=new end_game(this);
    //设置下棋音效和胜利音效
    mediaplayer=new QMediaPlayer;
    mediaplayer2=new QMediaPlayer;
    //计时器，计算秒数
    timer= new QTimer(this) ;
    timer->start(1000);
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(display()));
    //把鼠标变成小手
    QCursor cursor;
    cursor.setShape(Qt::ClosedHandCursor);
    setCursor(cursor);
    //这个是设置按钮样式的
    ui->pushButton->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
    ui->pushButton_2->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
    ui->pushButton_3->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
    ui->pushButton_4->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
enddialog=new end_game();
QObject::connect(enddialog,SIGNAL(send_start_again()),this,SLOT(send_start_again_2()));
}

Game::~Game()
{
    delete ui;
}
//绘图函数
void Game::paintEvent(QPaintEvent *)
{
  paint=new QPainter;
  paint->begin(this);
  paint->setPen(QPen(Qt::black,2,Qt::SolidLine));//钢笔工具：颜色，线号，实线
  //画size+1条横线
  for(int i=0;i<boardsize+1;i++)
    {
      paint->drawLine(x,y+width*i,x+width*(boardsize),y+width*i);//画线函数：x1,y1,x2,y2:画从(x1,y1)到(x2,y2)的线
    }
  //画size+1条竖线
  for(int i=0;i<boardsize+1;i++)
    {
      paint->drawLine(x+width*i,y,x+width*i,y+width*(boardsize));
    }
  //画棋子的函数
    QBrush brush;
       brush.setStyle(Qt::SolidPattern);
       for (int i=0;i<15;i++)
       {
           for (int j=0;j<15;j++)
           {
               if (chessboard[i][j]==1)
               {
                   brush.setColor(Qt::black);
                   paint->setBrush(brush);
                   paint->drawEllipse(j*40+23,i*40+20,32,32);

               }
               else if(chessboard[i][j]==-1)
               {
                   brush.setColor(Qt::white);
                   paint->setBrush(brush);
                   paint->drawEllipse(j*40+23,i*40+20,32,32);

               }
           }
       }


paint->end();
}
//6种判断情况
//右方
int Game::check1(int x,int y)
{if(y<=10&&y>=3)
    for(int i=y-3;i<=y;i++)
    if(chessboard[x][i]==chessboard[x][i+1]
            &&chessboard[x][i]==chessboard[x][i+2]
            &&chessboard[x][i]==chessboard[x][i+3]
            &&chessboard[x][i]==chessboard[x][i+4])
        return 1;
 if(y==2)
    for(int i=y-2;i<=y;i++)
        if(chessboard[x][i]==chessboard[x][i+1]
                &&chessboard[x][i]==chessboard[x][i+2]
                &&chessboard[x][i]==chessboard[x][i+3]
                &&chessboard[x][i]==chessboard[x][i+4])
       return 1;
 if(y==1)
     for(int i=y-1;i<=y;i++)
         if(chessboard[x][i]==chessboard[x][i+1]
                 &&chessboard[x][i]==chessboard[x][i+2]
                 &&chessboard[x][i]==chessboard[x][i+3]
                 &&chessboard[x][i]==chessboard[x][i+4])
        return 1;
 if(y==0)
         if(chessboard[x][y]==chessboard[x][y+1]
                 &&chessboard[x][y]==chessboard[x][y+2]
                 &&chessboard[x][y]==chessboard[x][y+3]
                 &&chessboard[x][y]==chessboard[x][y+4])
        return 1;
    return 0;
}
//上方
int Game::check2(int x,int y)
{if(x>=4)
    if(chessboard[x][y]==chessboard[x-1][y]
           &&chessboard[x][y]==chessboard[x-2][y]
           &&chessboard[x][y]==chessboard[x-3][y]
           &&chessboard[x][y]==chessboard[x-4][y])
        return 1;
    return 0;
}
//左方
int Game::check3(int x,int y)
{   if(y>=4)
    if(chessboard[x][y]==chessboard[x][y-1]
           &&chessboard[x][y]==chessboard[x][y-2]
           &&chessboard[x][y]==chessboard[x][y-3]
           &&chessboard[x][y]==chessboard[x][y-4])
        return 1;
    return 0;
}
//下方
int Game::check4(int x,int y)
{if(x<=10&&x>=3)
        for(int i=x-3;i<=x;i++)
    if(chessboard[i][y]==chessboard[i+1][y]
            &&chessboard[i][y]==chessboard[i+2][y]
            &&chessboard[i][y]==chessboard[i+3][y]
            &&chessboard[i][y]==chessboard[i+4][y])
        return 1;
if(x==2)
    for(int i=x-2;i<=x;i++)
if(chessboard[i][y]==chessboard[i+1][y]
        &&chessboard[i][y]==chessboard[i+2][y]
        &&chessboard[i][y]==chessboard[i+3][y]
        &&chessboard[i][y]==chessboard[i+4][y])
    return 1;
if(x==1)
    for(int i=x-2;i<=x;i++)
    if(chessboard[i][y]==chessboard[i+1][y]
        &&chessboard[i][y]==chessboard[i+2][y]
        &&chessboard[i][y]==chessboard[i+3][y]
        &&chessboard[i][y]==chessboard[i+4][y])
    return 1;
if(x==0)
    if(chessboard[x][y]==chessboard[x+1][y]
            &&chessboard[x][y]==chessboard[x+2][y]
            &&chessboard[x][y]==chessboard[x+3][y]
            &&chessboard[x][y]==chessboard[x+4][y])
        return 1;
        return 0;
}
//左下方
int Game::check5(int x,int y)
{/*if(x>=4&&y<=10&&y>=3&&x<=11)
        for(int i=x+3,j=y-3;i>=x;i--,j++)
    if(chessboard[i][j]==chessboard[i-1][j+1]
            &&chessboard[i][j]==chessboard[i-2][j+2]
            &&chessboard[i][j]==chessboard[i-3][j+3]
            &&chessboard[i][j]==chessboard[i-4][j+4]
            )
        return 1;
*/

    for (int i=0;i<5;i++)
       {
           if(x+i<15&&x+i-4>0&&
               y-i>0&&y-i+4<15&&
               chessboard[x+i][y-i]==chessboard[x+i-1][y-i+1]&&
               chessboard[x+i][y-i]==chessboard[x+i-2][y-i+2]&&
               chessboard[x+i][y-i]==chessboard[x+i-3][y-i+3]&&
               chessboard[x+i][y-i]==chessboard[x+i-4][y-i+4])
               return 1;
       }


    return 0;
}
//右下方
int Game::check6(int x,int y)
{ for (int i=0;i<5;i++)
    {
        if( x-i>0&&
            x-i+4<15&&
            y-i>0&&
            y-i+4<15&&
            chessboard[x-i][y-i]==chessboard[x-i+1][y-i+1]&&
            chessboard[x-i][y-i]==chessboard[x-i+2][y-i+2]&&
            chessboard[x-i][y-i]==chessboard[x-i+3][y-i+3]&&
            chessboard[x-i][y-i]==chessboard[x-i+4][y-i+4])
            return 1;
    }
    return 0;
}

//判断输赢
int Game::wingame(int a,int b)
{
    return check1(a,b)||check2(a,b)||check3(a,b)||check4(a,b)||check5(a,b)||check6(a,b);
}
//判断死局
bool Game::
deadgame()
{
    for(int i=1;i<15;i++)
        for(int j=1;j<15;j++)
        {
            if(chessboard[i][j]==0)
                return false;
        }
    return true;
}
//鼠标点击事件
void Game::mousePressEvent(QMouseEvent *event)
{  //a，b用来记录鼠标的坐标
    paint=new QPainter;
    QBrush brush;
    endgame=new end_game(this);
    int a,b;
    qDebug()<<"x="<<event->x()<<"y="<<event->y();
    a=(event->x()-20)/40;
    b=(event->y()-17)/40;
    qDebug()<<a<<b;
    //音效
    mediaplayer->setMedia(QUrl::fromLocalFile("c:/QT project/chess/chess/5390.wav"));
    mediaplayer->setVolume(200);
    mediaplayer2->setMedia(QUrl::fromLocalFile("c:/QT project/chess/chess/winning.mp3"));
    mediaplayer2->setVolume(200);
    //判断是否在棋盘内且格子是否为0,0就是空，1是黑棋，-1是白棋。//每次点击，用update函数重新绘制画面。
    if(event->button()==Qt::LeftButton)
  if((chessboard[b][a]==0)&&
          (event->x()>20&&event->x()<642)&&
          (event->y()>17&&event->y()<630))
   { if(player==1)
    {   mediaplayer->play();//播放音频
        chessboard[b][a]=1;
        chessboard_2[b][a]=turn;
        turn++;//turn记录了棋子的编码（按顺序）
        player=0;
        qDebug()<<"黑棋";
        ui->label_3->setText("下一手:白棋");
         update();
        if(wingame(b,a))
           {    mediaplayer2->play();
               qDebug()<<"游戏结束,黑棋胜";
                enddialog->setWindowTitle("黑棋胜利！");
                enddialog->exec();
                this->close();
           }
        if(deadgame())
            {
            enddialog->setWindowTitle("平局！");
            enddialog->exec();
            this->close();
            }
    }
    else if(player==0)
    {   mediaplayer->play();
        chessboard[b][a]=-1;
        chessboard_2[b][a]=turn;
        turn++;//turn记录了棋子的编码（按顺序）
        player=1;
        qDebug()<<"白棋";
         ui->label_3->setText("下一手:黑棋");
         update();
        if(wingame(b,a))
           {    mediaplayer2->play();
               qDebug()<<"游戏结束,白棋胜";
               enddialog->setWindowTitle("白棋胜利！");
               enddialog->exec();
               this->close();


           }
         if(deadgame())
            {
              enddialog->setWindowTitle("平局！");
              enddialog->exec();
              this->close();

            }
    }
  }



 }

//关闭界面槽
void Game::close_slot()
{
    this->close();
}
//中途结束按钮
void Game::on_pushButton_clicked()
{   endgame=new end_game(this);
    endgame->setWindowTitle("退出啦");
    endgame->exec();
    this->close();
}
//显示计时器
void Game::display()
{
static int count = 0;
count++;
ui->label->setText(QString::number(count));
}
//重新开始,回到主界面
void Game::on_pushButton_2_clicked()
{   this->close();
    emit restart();
}
void Game::start_again_2()
{

   this->show();
}
//悔棋
int Game::on_pushButton_3_clicked()
{
    for(int i=0;i<15;i++)
    {for(int j=0;j<15;j++)
            if(chessboard_2[i][j]==turn-1)
             { qDebug()<<turn-1;
               chessboard[i][j]=0;
               chessboard_2[i][j]=0;

               update();
            if(player==1)
                  player=0;
            else if(player==0)
                 player=1;
              turn--;
              return 0;
            }

  }

}
//清屏
void Game::on_pushButton_4_clicked()
{
    for(int i=0;i<15;i++)
        for(int j=0;j<15;j++)
        {
            chessboard[i][j]=0;
            chessboard_2[i][j]=0;
        }
    turn=2;
    player=1;
    update();

}
//右键菜单
void Game::on_Game_customContextMenuRequested(const QPoint &pos)
{
     QMenu *Menu = new QMenu(this);
     QAction *rechess = new QAction(tr("悔棋"), this);
     QAction *restart = new QAction(tr("重新开始"), this);
     QAction *back = new QAction(tr("返回主菜单"), this);
//在菜单中加入动作
     Menu->addAction(restart);
     Menu->addAction(back);
     Menu->addAction(rechess);
//把信号和之前的槽连接
     connect(rechess, SIGNAL(triggered()), this, SLOT(on_pushButton_3_clicked()));
     connect(restart, SIGNAL(triggered()), this, SLOT(on_pushButton_4_clicked()));
     connect(back, SIGNAL(triggered()), this, SLOT(on_pushButton_2_clicked()));
//菜单的左上角在鼠标处
     Menu->exec(cursor().pos());
//这段用来释放内存？

     QList<QAction*> list = Menu->actions();
       foreach (QAction* pAction, list) delete pAction;
       delete Menu;
}
