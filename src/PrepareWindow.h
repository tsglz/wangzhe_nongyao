#ifndef PREPAREWINDOW_H
#define PREPAREWINDOW_H

#include <QDialog>
#include "GameWindow.h"
#include "RankingWindow.h"

namespace Ui {
class PrepareWindow;
}

class PrepareWindow : public QDialog
{
    Q_OBJECT

public:
    explicit PrepareWindow(const QString &username, QWidget *parent = nullptr);
    ~PrepareWindow();

private slots:
    void on_Game_clicked();

    void on_Ranking_clicked();

private:
    Ui::PrepareWindow *ui;
    GameWindow *gameWindow;
    RankingWindow *rankingWindow;
    QString username;
    QVector<QVector<int>> oppositeSkillsData;
    QVector<QVector<int>> selectedSkillsData;
};

#endif // PREPAREWINDOW_H
