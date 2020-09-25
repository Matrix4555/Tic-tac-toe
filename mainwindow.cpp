#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "choosefigure.h"
#include "chooserealorai.h"
#include "choosedifficulty.h"
#include <ctime>
#include <QTime>

enum localization{ENG, RUS};
localization language = ENG;

bool mode;          //false is without ai; true is with ai
enum difficulty {EASY, NORMAL, HARD};
difficulty level;

bool figure;        //false is cross; true is ring
QLabel* image[9];
int stepsForCode;

int steps;
int crossScore;
int ringScore;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //---------------------------------------------------------------------
    setWindowTitle("Tic-tac-toe");

    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(realAction()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(realAction()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(realAction()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(realAction()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(realAction()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(realAction()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(realAction()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(realAction()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(realAction()));

    chooseRealOrAI select1;
    select1.exec();

    chooseFigure select2;
    select2.exec();

    for(int i = 0; i < 9; i++)
        image[i]=nullptr;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::realAction()
{
    QPushButton* button = (QPushButton*)sender();                       //clarify what's button get clicked

    int index = 1;
    for(; index <= 9; index++)
        if(button->objectName().contains(QString::number(index)))       //find needed digit for image index from name of button (e.g. button 1 is index 0 etc)
        {
            index--;
            break;
        }

    setImage(index, button);

    if(mode)                        //if play with ai
    {
        QPushButton* tempButton;
        int temp = AIAction();      //set ai's image index

        switch(temp)                //set ai's button
        {
        case 0:
            tempButton = ui->pushButton_1;
            break;
        case 1:
            tempButton = ui->pushButton_2;
            break;
        case 2:
            tempButton = ui->pushButton_3;
            break;
        case 3:
            tempButton = ui->pushButton_4;
            break;
        case 4:
            tempButton = ui->pushButton_5;
            break;
        case 5:
            tempButton = ui->pushButton_6;
            break;
        case 6:
            tempButton = ui->pushButton_7;
            break;
        case 7:
            tempButton = ui->pushButton_8;
            break;
        case 8:
            tempButton = ui->pushButton_9;
            break;
        }

        setImage(temp, tempButton);
    }
}

void MainWindow::setImage(int index, QPushButton* button)
{
    QPixmap cross(":/imgs/images/cross2.0.png"), ring(":/imgs/images/ring2.0.png");

    image[index] = new QLabel(this);                                                                  //create a new image
    image[index]->setVisible(true);
    image[index]->setGeometry(button->x()+20, button->y()+140, button->width(), button->height());    //place an image from data of acted button

    if(figure)      //ring
    {
        image[index]->setPixmap(ring);
        image[index]->setScaledContents(true);
        figure=false;
        ui->whoWalks->setPixmap(cross);
        if(language==ENG)
            ui->statusbar->showMessage("A ring took a step");
        else
            ui->statusbar->showMessage("Кружок сделал ход");
    }
    else            //cross
    {
        image[index]->setPixmap(cross);
        image[index]->setScaledContents(true);
        figure=true;
        ui->whoWalks->setPixmap(ring);
        if(language==ENG)
            ui->statusbar->showMessage("A cross took a step");
        else
            ui->statusbar->showMessage("Крестик сделал ход");
    }

    button->setVisible(false);
    ui->label_countSteps->setText(QString::number(++steps));
    stepsForCode++;

    if(stepsForCode >= 5)
        victoryCheck();
}

int MainWindow::AIAction()
{
   srand(time(NULL));
   int way = -1;

   if(level==EASY || !closeVictoryControl(way))     //if mode is easy always random step will occur also if mode isn't easy and
       while(true)                                  //ai doesn't feel "close victory for self or enemy" it will select random step too
       {
           way = rand() % 9;
           if(image[way]==nullptr)
               break;
       }

    return way;     //return ai's image index
}

void MainWindow::victoryCheck()
{
    if(image[6]!=nullptr && image[7]!=nullptr && image[8]!=nullptr &&
            (*image[6]->pixmap() == *image[7]->pixmap()) && (*image[7]->pixmap() == *image[8]->pixmap()))
        gameOver();
    else if(image[3]!=nullptr && image[4]!=nullptr && image[5]!=nullptr &&
            (*image[3]->pixmap() == *image[4]->pixmap()) && (*image[4]->pixmap() == *image[5]->pixmap()))
        gameOver();
    else if(image[0]!=nullptr && image[1]!=nullptr && image[2]!=nullptr &&
            (*image[0]->pixmap() == *image[1]->pixmap()) && (*image[1]->pixmap() == *image[2]->pixmap()))
        gameOver();
    else if(image[6]!=nullptr && image[3]!=nullptr && image[0]!=nullptr &&
            (*image[6]->pixmap() == *image[3]->pixmap()) && (*image[3]->pixmap() == *image[0]->pixmap()))
        gameOver();
    else if(image[7]!=nullptr && image[4]!=nullptr && image[1]!=nullptr &&
            (*image[7]->pixmap() == *image[4]->pixmap()) && (*image[4]->pixmap() == *image[1]->pixmap()))
        gameOver();
    else if(image[8]!=nullptr && image[5]!=nullptr && image[2]!=nullptr &&
            (*image[8]->pixmap() == *image[5]->pixmap()) && (*image[5]->pixmap() == *image[2]->pixmap()))
        gameOver();
    else if(image[6]!=nullptr && image[4]!=nullptr && image[2]!=nullptr &&
            (*image[6]->pixmap() == *image[4]->pixmap()) && (*image[4]->pixmap() == *image[2]->pixmap()))
        gameOver();
    else if(image[8]!=nullptr && image[4]!=nullptr && image[0]!=nullptr &&
            (*image[8]->pixmap() == *image[4]->pixmap()) && (*image[4]->pixmap() == *image[0]->pixmap()))
        gameOver();
    else if(stepsForCode>=9)        //if all are filled
    {
        if(language==ENG)
            QMessageBox::information(this, "Info", "Draw!");
        else
            QMessageBox::information(this, "Инфо", "Ничья!");
        resetField();
        stepsForCode = 0;
    }
}

void MainWindow::gameOver()
{
    enableButtons(false);           //block buttons during delay acts

    QTime timer;                    //delay after victory
    timer.start();
    for(;timer.elapsed() < 700;)
       qApp->processEvents();

    enableButtons(true);            //unblock after delay completed

    resetField();
    stepsForCode = 0;               //grid is empty
    if(figure)
        ui->label_scoreCross->setText(QString::number(++crossScore));
    else
        ui->label_scoreRing->setText(QString::number(++ringScore));
}

void MainWindow::enableButtons(bool turn)
{
    ui->pushButton_1->setEnabled(turn);
    ui->pushButton_2->setEnabled(turn);
    ui->pushButton_3->setEnabled(turn);
    ui->pushButton_4->setEnabled(turn);
    ui->pushButton_5->setEnabled(turn);
    ui->pushButton_6->setEnabled(turn);
    ui->pushButton_7->setEnabled(turn);
    ui->pushButton_8->setEnabled(turn);
    ui->pushButton_9->setEnabled(turn);
}

void MainWindow::resetField()
{
    ui->pushButton_1->setVisible(true);
    ui->pushButton_2->setVisible(true);
    ui->pushButton_3->setVisible(true);
    ui->pushButton_4->setVisible(true);
    ui->pushButton_5->setVisible(true);
    ui->pushButton_6->setVisible(true);
    ui->pushButton_7->setVisible(true);
    ui->pushButton_8->setVisible(true);
    ui->pushButton_9->setVisible(true);

    for(int i = 0; i < 9; i++)
    {
        delete image[i];
        image[i] = nullptr;
    }
}

bool MainWindow::closeVictoryControl(int& way)
{
    if(level==HARD)
    {
        QPixmap checkImg;

        if(figure)
            checkImg = QPixmap(":/imgs/images/ring2.0.png");
        else
            checkImg = QPixmap(":/imgs/images/cross2.0.png");

        if(image[6] != nullptr && image[7] != nullptr &&  image[8] == nullptr && (*image[6]->pixmap() == checkImg) && (*image[6]->pixmap() == *image[7]->pixmap()))
            way=8;
        else if(image[6] != nullptr && image[8] != nullptr &&  image[7] == nullptr && (*image[6]->pixmap() == checkImg) && (*image[6]->pixmap() == *image[8]->pixmap()))
            way=7;
        else if(image[7] != nullptr && image[8] != nullptr &&  image[6] == nullptr && (*image[7]->pixmap() == checkImg) && (*image[7]->pixmap() == *image[8]->pixmap()))
            way=6;
        else if(image[3] != nullptr && image[4] != nullptr &&  image[5] == nullptr && (*image[3]->pixmap() == checkImg) && (*image[3]->pixmap() == *image[4]->pixmap()))
            way=5;
        else if(image[3] != nullptr && image[5] != nullptr &&  image[4] == nullptr && (*image[3]->pixmap() == checkImg) && (*image[3]->pixmap() == *image[5]->pixmap()))
            way=4;
        else if(image[4] != nullptr && image[5] != nullptr &&  image[3] == nullptr && (*image[4]->pixmap() == checkImg) && (*image[4]->pixmap() == *image[5]->pixmap()))
            way=3;
        else if(image[0] != nullptr && image[1] != nullptr &&  image[2] == nullptr && (*image[0]->pixmap() == checkImg) && (*image[0]->pixmap() == *image[1]->pixmap()))
            way=2;
        else if(image[0] != nullptr && image[2] != nullptr &&  image[1] == nullptr && (*image[0]->pixmap() == checkImg) && (*image[0]->pixmap() == *image[2]->pixmap()))
            way=1;
        else if(image[1] != nullptr && image[2] != nullptr &&  image[0] == nullptr && (*image[1]->pixmap() == checkImg) && (*image[1]->pixmap() == *image[2]->pixmap()))
            way=0;
        else if(image[6] != nullptr && image[3] != nullptr &&  image[0] == nullptr && (*image[6]->pixmap() == checkImg) && (*image[6]->pixmap() == *image[3]->pixmap()))
            way=0;
        else if(image[6] != nullptr && image[0] != nullptr &&  image[3] == nullptr && (*image[6]->pixmap() == checkImg) && (*image[6]->pixmap() == *image[0]->pixmap()))
            way=3;
        else if(image[3] != nullptr && image[0] != nullptr &&  image[6] == nullptr && (*image[3]->pixmap() == checkImg) && (*image[3]->pixmap() == *image[0]->pixmap()))
            way=6;
        else if(image[7] != nullptr && image[4] != nullptr &&  image[1] == nullptr && (*image[7]->pixmap() == checkImg) && (*image[7]->pixmap() == *image[4]->pixmap()))
            way=1;
        else if(image[7] != nullptr && image[1] != nullptr &&  image[4] == nullptr && (*image[7]->pixmap() == checkImg) && (*image[7]->pixmap() == *image[1]->pixmap()))
            way=4;
        else if(image[4] != nullptr && image[1] != nullptr &&  image[7] == nullptr && (*image[4]->pixmap() == checkImg) && (*image[4]->pixmap() == *image[1]->pixmap()))
            way=7;
        else if(image[8] != nullptr && image[5] != nullptr &&  image[2] == nullptr && (*image[8]->pixmap() == checkImg) && (*image[8]->pixmap() == *image[5]->pixmap()))
            way=2;
        else if(image[8] != nullptr && image[2] != nullptr &&  image[5] == nullptr && (*image[8]->pixmap() == checkImg) && (*image[8]->pixmap() == *image[2]->pixmap()))
            way=5;
        else if(image[5] != nullptr && image[2] != nullptr &&  image[8] == nullptr && (*image[5]->pixmap() == checkImg) && (*image[5]->pixmap() == *image[2]->pixmap()))
            way=8;
        else if(image[0] != nullptr && image[4] != nullptr &&  image[8] == nullptr && (*image[0]->pixmap() == checkImg) && (*image[0]->pixmap() == *image[4]->pixmap()))
            way=8;
        else if(image[0] != nullptr && image[8] != nullptr &&  image[4] == nullptr && (*image[0]->pixmap() == checkImg) && (*image[0]->pixmap() == *image[8]->pixmap()))
            way=4;
        else if(image[4] != nullptr && image[8] != nullptr &&  image[0] == nullptr && (*image[4]->pixmap() == checkImg) && (*image[4]->pixmap() == *image[8]->pixmap()))
            way=0;
        else if(image[6] != nullptr && image[4] != nullptr &&  image[2] == nullptr && (*image[6]->pixmap() == checkImg) && (*image[6]->pixmap() == *image[4]->pixmap()))
            way=2;
        else if(image[6] != nullptr && image[2] != nullptr &&  image[4] == nullptr && (*image[6]->pixmap() == checkImg) && (*image[6]->pixmap() == *image[2]->pixmap()))
            way=4;
        else if(image[4] != nullptr && image[2] != nullptr &&  image[6] == nullptr && (*image[4]->pixmap() == checkImg) && (*image[4]->pixmap() == *image[2]->pixmap()))
            way=6;

        if(way > -1)        //if everything doesn't fit function is continuing
            return true;
    }

    if(image[6] != nullptr && image[7] != nullptr &&  image[8] == nullptr && (*image[6]->pixmap() == *image[7]->pixmap()))
        way=8;
    else if(image[6] != nullptr && image[8] != nullptr &&  image[7] == nullptr && (*image[6]->pixmap() == *image[8]->pixmap()))
        way=7;
    else if(image[7] != nullptr && image[8] != nullptr &&  image[6] == nullptr && (*image[7]->pixmap() == *image[8]->pixmap()))
        way=6;
    else if(image[3] != nullptr && image[4] != nullptr &&  image[5] == nullptr && (*image[3]->pixmap() == *image[4]->pixmap()))
        way=5;
    else if(image[3] != nullptr && image[5] != nullptr &&  image[4] == nullptr && (*image[3]->pixmap() == *image[5]->pixmap()))
        way=4;
    else if(image[4] != nullptr && image[5] != nullptr &&  image[3] == nullptr && (*image[4]->pixmap() == *image[5]->pixmap()))
        way=3;
    else if(image[0] != nullptr && image[1] != nullptr &&  image[2] == nullptr && (*image[0]->pixmap() == *image[1]->pixmap()))
        way=2;
    else if(image[0] != nullptr && image[2] != nullptr &&  image[1] == nullptr && (*image[0]->pixmap() == *image[2]->pixmap()))
        way=1;
    else if(image[1] != nullptr && image[2] != nullptr &&  image[0] == nullptr && (*image[1]->pixmap() == *image[2]->pixmap()))
        way=0;
    else if(image[6] != nullptr && image[3] != nullptr &&  image[0] == nullptr && (*image[6]->pixmap() == *image[3]->pixmap()))
        way=0;
    else if(image[6] != nullptr && image[0] != nullptr &&  image[3] == nullptr && (*image[6]->pixmap() == *image[0]->pixmap()))
        way=3;
    else if(image[3] != nullptr && image[0] != nullptr &&  image[6] == nullptr && (*image[3]->pixmap() == *image[0]->pixmap()))
        way=6;
    else if(image[7] != nullptr && image[4] != nullptr &&  image[1] == nullptr && (*image[7]->pixmap() == *image[4]->pixmap()))
        way=1;
    else if(image[7] != nullptr && image[1] != nullptr &&  image[4] == nullptr && (*image[7]->pixmap() == *image[1]->pixmap()))
        way=4;
    else if(image[4] != nullptr && image[1] != nullptr &&  image[7] == nullptr && (*image[4]->pixmap() == *image[1]->pixmap()))
        way=7;
    else if(image[8] != nullptr && image[5] != nullptr &&  image[2] == nullptr && (*image[8]->pixmap() == *image[5]->pixmap()))
        way=2;
    else if(image[8] != nullptr && image[2] != nullptr &&  image[5] == nullptr && (*image[8]->pixmap() == *image[2]->pixmap()))
        way=5;
    else if(image[5] != nullptr && image[2] != nullptr &&  image[8] == nullptr && (*image[5]->pixmap() == *image[2]->pixmap()))
        way=8;
    else if(image[0] != nullptr && image[4] != nullptr &&  image[8] == nullptr && (*image[0]->pixmap() == *image[4]->pixmap()))
        way=8;
    else if(image[0] != nullptr && image[8] != nullptr &&  image[4] == nullptr && (*image[0]->pixmap() == *image[8]->pixmap()))
        way=4;
    else if(image[4] != nullptr && image[8] != nullptr &&  image[0] == nullptr && (*image[4]->pixmap() == *image[8]->pixmap()))
        way=0;
    else if(image[6] != nullptr && image[4] != nullptr &&  image[2] == nullptr && (*image[6]->pixmap() == *image[4]->pixmap()))
        way=2;
    else if(image[6] != nullptr && image[2] != nullptr &&  image[4] == nullptr && (*image[6]->pixmap() == *image[2]->pixmap()))
        way=4;
    else if(image[4] != nullptr && image[2] != nullptr &&  image[6] == nullptr && (*image[4]->pixmap() == *image[2]->pixmap()))
        way=6;
    else
        return false;       //if everything doesn't fit
    return true;
}

bool MainWindow::newGame()
{
    bool temp = false;

    switch(language)
    {
    case ENG:
        QMessageBox::StandardButton answer;
        answer = QMessageBox::question(this, "Reset", "Are you sure you want to reset the current score?", QMessageBox::Yes | QMessageBox::No);
        if(answer==QMessageBox::Yes)
            temp=true;
        break;
    case RUS:
        QMessageBox tempMes;                //create separate window to its buttons will be with russian words
        tempMes.setWindowTitle("Сброс");
        tempMes.setWindowIcon(QIcon(":/imgs/images/logo.png"));
        tempMes.setIcon(QMessageBox::Question);
        tempMes.setText("Вы уверены что хотите сбросить текущий счёт?");
        QAbstractButton* answerRus = tempMes.addButton("Да", QMessageBox::YesRole);
        tempMes.addButton("Нет", QMessageBox::NoRole);
        tempMes.exec();
        if(tempMes.clickedButton() == answerRus)
            temp=true;
        break;
    }

    if(temp)        //if answer is yes
    {
        resetField();
        ui->label_scoreCross->setText(QString::number(0));
        ui->label_scoreRing->setText(QString::number(0));
        ui->label_countSteps->setText("0");
        crossScore = 0;
        ringScore = 0;
        stepsForCode = 0;
        steps = 0;
    }

    return temp;
}

void MainWindow::on_actionNew_game_1_vs_1_triggered()       //new game 1 vs 1
{
    if(newGame())
    {
        mode=false;
        chooseFigure select;
        if(language==RUS)
            select.changeText("Выберите кто будет ходить первым");
        select.exec();
    }
}

void MainWindow::on_actionNew_game_1_vs_AI_triggered()      // new game 1 vs ai
{
    if(newGame())
    {
        mode=true;
        chooseDifficulty select1;
        if(language==RUS)
            select1.changeText("Выберите уровень сложности");
        select1.exec();
        chooseFigure select2;
        if(language==RUS)
            select2.changeText("Выберите кто будет ходить первым");
        select2.exec();
    }
}

void MainWindow::on_actionEnglish_triggered()
{
    language=ENG;
    ui->menuNewGame->setTitle("New game");
    ui->actionNew_game_1_vs_1->setText("1 vs 1");
    ui->actionNew_game_1_vs_AI->setText("1 vs AI");
    ui->menuOptions->setTitle("Options");
    ui->menuLanguage->setTitle("Language");
    ui->actionEnglish->setText("English");
    ui->actionRussian->setText("Russian");
    ui->menuBackground->setTitle("Background");
    ui->menuAbout_game->setTitle("About game");
    ui->actionInformation->setText("Information");
    ui->actionCurrent_version->setText("Current version");
    ui->groupBox_data->setTitle("Data");
    ui->label_stepsDone->setText("Steps done:");
    ui->label_whoWalks->setText("Who walks:");
    ui->label_score->setText("Score:");
    ui->groupBox_field->setTitle("Field of Game");

    QFont temp = ui->label_stepsDone->font();
    temp.setPointSize(14);
    ui->label_stepsDone->setFont(temp);
}

void MainWindow::on_actionRussian_triggered()
{
    language=RUS;
    ui->menuNewGame->setTitle("Новая игра");
    ui->actionNew_game_1_vs_1->setText("1 против 1");
    ui->actionNew_game_1_vs_AI->setText("1 против ИИ");
    ui->menuOptions->setTitle("Настройки");
    ui->menuLanguage->setTitle("Язык");
    ui->actionEnglish->setText("Английский");
    ui->actionRussian->setText("Русский");
    ui->menuBackground->setTitle("Задний фон");
    ui->menuAbout_game->setTitle("Об игре");
    ui->actionInformation->setText("Информация");
    ui->actionCurrent_version->setText("Текущая версия");
    ui->groupBox_data->setTitle("Данные");
    ui->label_stepsDone->setText("Шагов сделано:");
    ui->label_whoWalks->setText("Кто ходит:");
    ui->label_score->setText("Счёт:");
    ui->groupBox_field->setTitle("Поле игры");

    QFont temp = ui->label_stepsDone->font();
    temp.setPointSize(12);
    ui->label_stepsDone->setFont(temp);
}

void MainWindow::on_actionInformation_triggered()
{
    if(language==ENG)
        QMessageBox::information(this, "Info", "Tic-tac-toe (American English), noughts and crosses (Commonwealth English), or Xs and Os is a paper-and-pencil game for two players, X and O, "
                                               "who take turns marking the spaces in a 3×3 grid. The player who succeeds in placing three of their marks in a horizontal, vertical, or diagonal "
                                               "row is the winner.");
    else
        QMessageBox::information(this, "Info", "Кре́стики-но́лики — логическая игра между двумя противниками на квадратном поле 3 на 3 клетки или большего размера (вплоть до «бесконечного поля»)."
                                               " Один из игроков играет «крестиками», второй — «ноликами». Игрок, которому удалось закрасить 3 клетки своей фигурой горизонтально, вертикально "
                                               "или диагонально, становится победителем.");
}

void MainWindow::on_actionCurrent_version_triggered()
{
    if(language==ENG)
        QMessageBox::information(this, "Info", "Tic-tac-toe 1.0\n"
                                       "This is my first window application xD");
    else
        QMessageBox::information(this, "Info", "Tic-tac-toe 1.0\n"
                                       "Это моё первое оконное приложение xD");
}

void chooseRealOrAI::on_pushButton_selectRing_clicked()
{
   mode = false;
   this->close();
}

void chooseRealOrAI::on_pushButton_selectCross_clicked()
{
    mode = true;
    this->close();
    chooseDifficulty selectLevel;
    selectLevel.exec();
}

void chooseDifficulty::on_pushButton_selectRing_clicked()
{
    level = EASY;
    this->close();
}

void chooseDifficulty::on_pushButton_selectCross_clicked()
{
    level = NORMAL;
    this->close();
}

void chooseDifficulty::on_pushButton_hard_clicked()
{
    level = HARD;
    this->close();
}

void chooseFigure::on_pushButton_selectRing_clicked()
{
    figure=true;
    this->close();
}

void chooseFigure::on_pushButton_selectCross_clicked()
{
    figure=false;
    this->close();
}

void MainWindow::on_actionDefault_triggered()
{
    this->setStyleSheet("");
    ui->statusbar->setStyleSheet("");
}

void MainWindow::on_actionDark_triggered()
{
    this->setStyleSheet("QMainWindow{background-color: rgb(67, 67, 67);}");
    ui->statusbar->setStyleSheet("color: rgb(255, 255, 255);");
}

void MainWindow::on_actionSunset_triggered()
{
    this->setStyleSheet("QMainWindow{background-image: url(:/imgs/images/skyBackground.png);}");
    ui->statusbar->setStyleSheet("color: rgb(255, 255, 255);");
}

void MainWindow::on_actionGame_triggered()
{
    this->setStyleSheet("QMainWindow{background-image: url(:/imgs/images/gameBackground.png);}");
    ui->statusbar->setStyleSheet("color: rgb(255, 255, 255);");
}

void MainWindow::on_actionCity_triggered()
{
    this->setStyleSheet("QMainWindow{background-image: url(:/imgs/images/cityBackground.png);}");
    ui->statusbar->setStyleSheet("color: rgb(255, 255, 255);");
}

void MainWindow::on_actionCar_triggered()
{
    this->setStyleSheet("QMainWindow{background-image: url(:/imgs/images/carBackground.png);}");
    ui->statusbar->setStyleSheet("color: rgb(255, 255, 255);");
}
