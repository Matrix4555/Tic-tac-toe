#ifndef CHOOSEREALORAI_H
#define CHOOSEREALORAI_H

#include <QDialog>

namespace Ui {
class chooseRealOrAI;
}

class chooseRealOrAI : public QDialog
{
    Q_OBJECT

public:
    explicit chooseRealOrAI(QWidget *parent = nullptr);
    ~chooseRealOrAI();

private slots:
    void on_pushButton_selectRing_clicked();
    void on_pushButton_selectCross_clicked();

private:
    Ui::chooseRealOrAI *ui;
};

#endif // CHOOSEREALORAI_H
