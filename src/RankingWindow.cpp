#include "RankingWindow.h"
#include "ui_RankingWindow.h"
#include "PrepareWindow.h"

RankingWindow::RankingWindow(const QString &username, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RankingWindow)
    , prepareWindow(nullptr)
    , gameViewModel(new QStandardItemModel)
    , username(username)
{
    ui->setupUi(this);
    ui->heroListView->setModel(gameViewModel);

    auto heroRanking = ranking.showHeroRank();
    for (auto i : heroRanking) {
        printOnGameView(i.first + " " + QString::number(i.second));
    }
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

void RankingWindow::printOnGameView(QString content) {
    auto item = new QStandardItem(content);
    gameViewModel->appendRow(item);
    auto rowCount = gameViewModel->rowCount();
    if (rowCount > 0) {
        QModelIndex lastIndex = gameViewModel->index(rowCount - 1, 0);

        // 确保滚动到最后一行
        ui->heroListView->scrollTo(lastIndex, QAbstractItemView::PositionAtBottom);
    }
}