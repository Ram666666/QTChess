#include "end_game.h"
#include "ui_end_game.h"
#include"Game.h"

#include"QDebug"
end_game::end_game(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::end_game)
{
    ui->setupUi(this);

   }

end_game::~end_game()
{
    delete ui;
}



