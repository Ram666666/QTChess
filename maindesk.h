#ifndef WIDGET_H
#define WIDGET_H
#include"Game.h"
#include <QWidget>
#include <QMouseEvent>
#include"QPaintEvent"
#include"illustration.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
signals:
    void show_illus();
public slots:
 void start_again();
private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

private:
    illustration *ill;
    Ui::Widget *ui;
    Game *game_desk;
    end_game *enddialog;
    QPixmap *pixmapBackground;

   // void mousepressEvent(QMouseEvent *event);
};
#endif // WIDGET_H
