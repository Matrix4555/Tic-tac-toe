#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QTime>
#include <ctime>
#include "choosefigure.h"
#include "chooserealorai.h"
#include "choosedifficulty.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    //-----------------

    QLabel* image[9];
    void setImage(int, QPushButton*);
    bool closeVictoryControl(int&);
    void enableButtons(bool);
    void victoryCheck();
    void resetField();
    void gameOver();
    bool newGame();
    int AIAction();

private slots:
    void realAction();
    void on_actionNew_game_1_vs_1_triggered();
    void on_actionNew_game_1_vs_AI_triggered();
    void on_actionEnglish_triggered();
    void on_actionRussian_triggered();
    void on_actionInformation_triggered();
    void on_actionCurrent_version_triggered();
    void on_actionDefault_triggered();
    void on_actionDark_triggered();
    void on_actionSunset_triggered();
    void on_actionGame_triggered();
    void on_actionCity_triggered();
    void on_actionCar_triggered();
};
#endif // MAINWINDOW_H
