#ifndef APPRECIATE_H
#define APPRECIATE_H

#include <QWidget>

namespace Ui {
class Appreciate;
}

class Appreciate : public QWidget
{
    Q_OBJECT

public:
    int index=0;
    explicit Appreciate(QWidget *parent = nullptr);
    ~Appreciate();

private:
    Ui::Appreciate *ui;
};

#endif // APPRECIATE_H
