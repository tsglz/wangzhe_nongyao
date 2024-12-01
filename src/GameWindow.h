#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QDialog>
#include <QStandardItemModel>
#include "core/Hero.h"
#include "core/Hero.h"
#include "core/Game.h"

class PrepareWindow;

namespace Ui {
    class GameWindow;
}

class GameWindow : public QDialog {
    Q_OBJECT

public:
    explicit GameWindow(const QString &username, QVector<QVector<int>> *oppositeSkillsPtr, QVector<QVector<int>> *selectedSkillsPtr, QWidget *parent = nullptr);

    ~GameWindow();

private slots:
    void on_comfirm_clicked();

    void on_return_2_clicked();

    void on_hero_0_clicked();

    void on_hero_1_clicked();

    void on_hero_2_clicked();

private:
    Ui::GameWindow *ui;
    QStandardItemModel *gameViewModel;
    PrepareWindow *prepareWindow;
    QString username;
    Hero hero;
    QVector<int> selectedHeroes; // [0, 0, 1, 0, ...] 共 15 个元素
    QVector<int> oppositeRandomSelectedHeroes = hero.oppositeRandomSelectedHeroes();
    int selectedHeroCount = 0;
    int round = 0, win = 0, lose = 0, draw = 0;
    QVector<QVector<int>> *oppositeSkills;
    QVector<QVector<int>> *selectedSkills;

    void printOnGameView(QString content);

    void playGame(int heroSelected);
};

#endif // GAMEWINDOW_H
