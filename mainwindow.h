#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QPainter>

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

private slots:
    void realAction();
    void setImage(int, QPushButton*);
    int AIAction();
    void victoryCheck();
    void gameOver();
    void enableButtons(bool);
    bool newGame();
    void on_actionNew_game_1_vs_1_triggered();
    void on_actionNew_game_1_vs_AI_triggered();
    void resetField();
    bool closeVictoryControl(int&);
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
