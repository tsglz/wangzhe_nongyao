#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QDialog>
#include <QStandardItemModel>
#include "core/Hero.h"
#include "core/Hero.h"

class PrepareWindow;

namespace Ui {
    class GameWindow;
}

class GameWindow : public QDialog {
    Q_OBJECT

public:
    explicit GameWindow(const QString &username, QWidget *parent = nullptr);

    ~GameWindow();

private slots:
    void on_comfirm_clicked();

    void on_return_2_clicked();

    void on_hero_0_clicked();

private:
    Ui::GameWindow *ui;
    QStandardItemModel *gameViewModel;
    PrepareWindow *prepareWindow;
    QString username;
    Hero hero;
    QVector<int> selectedHeroes;
    int selectedHeroCount = 0;

    void printOnGameView(QString content);
};

#endif // GAMEWINDOW_H
