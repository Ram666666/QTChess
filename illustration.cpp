#include "illustration.h"
#include "ui_illustration.h"

illustration::illustration(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::illustration)
{
    ui->setupUi(this);

}

illustration::~illustration()
{
    delete ui;
}
void illustration::show_illustration()
{
    this->show();
}
