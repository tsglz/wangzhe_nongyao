#include "RankingWindow.h"
#include "ui_RankingWindow.h"
#include "PrepareWindow.h"

RankingWindow::RankingWindow(const QString &username, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RankingWindow)
    , prepareWindow(nullptr)
    , username(username)
{
    ui->setupUi(this);
}

RankingWindow::~RankingWindow()
{
    delete ui;
}

void RankingWindow::on_return_2_clicked()
{
    prepareWindow = new PrepareWindow(username);
    prepareWindow->show();

    this->hide();
}

