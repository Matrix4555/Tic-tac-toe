#ifndef CHOOSEDIFFICULTY_H
#define CHOOSEDIFFICULTY_H

#include <QDialog>

namespace Ui {
class chooseDifficulty;
}

class chooseDifficulty : public QDialog
{
    Q_OBJECT

public:
    explicit chooseDifficulty(QWidget *parent = nullptr);
    ~chooseDifficulty();
    //------------------

    void changeText(QString);   // change text on the top of this window

private slots:
    void on_pushButton_selectRing_clicked();
    void on_pushButton_selectCross_clicked();
    void on_pushButton_hard_clicked();

private:
    Ui::chooseDifficulty *ui;

};

#endif // CHOOSEDIFFICULTY_H
