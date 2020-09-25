#include "choosedifficulty.h"
#include "ui_choosedifficulty.h"

chooseDifficulty::chooseDifficulty(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chooseDifficulty)
{
    ui->setupUi(this);


    setWindowTitle("Difficulty");
    setWindowFlags(Qt::WindowTitleHint);
}

chooseDifficulty::~chooseDifficulty()
{
    delete ui;
}

void chooseDifficulty::changeText(QString words)
{
    ui->label->setText(words);
}
