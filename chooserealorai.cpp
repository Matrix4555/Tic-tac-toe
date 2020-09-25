#include "chooserealorai.h"
#include "ui_chooserealorai.h"

chooseRealOrAI::chooseRealOrAI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chooseRealOrAI)
{
    ui->setupUi(this);


    setWindowTitle("Mode of game");
    setWindowFlags(Qt::WindowTitleHint);
}

chooseRealOrAI::~chooseRealOrAI()
{
    delete ui;
}
