#ifndef ILLUSTRATION_H
#define ILLUSTRATION_H

#include <QDialog>

namespace Ui {
class illustration;
}

class illustration : public QDialog
{
    Q_OBJECT

public:
    explicit illustration(QWidget *parent = nullptr);
    ~illustration();
public slots:
    void show_illustration();
private:
    Ui::illustration *ui;
};

#endif // ILLUSTRATION_H
