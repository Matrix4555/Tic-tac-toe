#include "choosefigure.h"
#include "ui_choosefigure.h"

chooseFigure::chooseFigure(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chooseFigure)
{
    ui->setupUi(this);


    setWindowTitle("Figures");
    setWindowFlags(Qt::WindowTitleHint);
}

chooseFigure::~chooseFigure()
{
    delete ui;
}

void chooseFigure::changeText(QString words)
{
    ui->label->setText(words);
}
