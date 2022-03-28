#ifndef END_GAME_H
#define END_GAME_H
#include <QDialog>

namespace Ui {
class end_game;
}

class end_game : public QDialog
{
    Q_OBJECT

public:
    explicit end_game(QWidget *parent = nullptr);
    ~end_game();

public slots:



signals:

private slots:


private:
    Ui::end_game *ui;
};

#endif // END_GAME_H
