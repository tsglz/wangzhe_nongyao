#ifndef RANKINGWINDOW_H
#define RANKINGWINDOW_H

#include <QDialog>

class PrepareWindow;

namespace Ui {
class RankingWindow;
}

class RankingWindow : public QDialog
{
    Q_OBJECT

public:
    explicit RankingWindow(const QString &username, QWidget *parent = nullptr);
    ~RankingWindow();

private slots:
    void on_return_2_clicked();

private:
    Ui::RankingWindow *ui;
    PrepareWindow *prepareWindow;
    QString username;
};

#endif // RANKINGWINDOW_H
