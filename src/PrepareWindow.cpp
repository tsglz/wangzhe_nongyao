#include "PrepareWindow.h"
#include "ui_PrepareWindow.h"

PrepareWindow::PrepareWindow(const QString &username, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PrepareWindow)
    , gameWindow(nullptr)
    , rankingWindow(nullptr)
    , username(username)
{
    ui->setupUi(this);
}

PrepareWindow::~PrepareWindow()
{
    delete ui;
}

void PrepareWindow::on_Game_clicked()
{
    gameWindow = new GameWindow(username);
    gameWindow->show();

    this->hide();
    qDebug() << "info: " << username;
}


void PrepareWindow::on_Ranking_clicked()
{
    rankingWindow = new RankingWindow(username);
    rankingWindow->show();

    this->hide();
}

