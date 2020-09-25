#ifndef CHOOSEFIGURE_H
#define CHOOSEFIGURE_H

#include <QDialog>

namespace Ui {
class chooseFigure;
}

class chooseFigure : public QDialog
{
    Q_OBJECT

public:
    explicit chooseFigure(QWidget *parent = nullptr);
    ~chooseFigure();

    void changeText(QString);

private slots:
    void on_pushButton_selectRing_clicked();
    void on_pushButton_selectCross_clicked();

private:
    Ui::chooseFigure *ui;
};

#endif // CHOOSEFIGURE_H
