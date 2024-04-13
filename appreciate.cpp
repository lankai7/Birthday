#include "appreciate.h"
#include "ui_appreciate.h"

Appreciate::Appreciate(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Appreciate)
{
    ui->setupUi(this);
}

Appreciate::~Appreciate()
{
    delete ui;
}
