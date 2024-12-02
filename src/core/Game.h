#ifndef GAME_H
#define GAME_H

#include <QString>
#include <QVector>
#include <QPair>
#include "Hero.h"
#include <random>
#include <QSqlQuery>

class Game {
public:
    Game();

    int hasGame(QString username, QVector<QVector<int> > &oppositeSkills, QVector<QVector<int> > &selectedSkills,
                int round, QPair<int, int> heroSelected, QPair<int, int> oppositeHeroSelected);

    void appendDatabase(QPair<int, int> heroSelected, QPair<int, int> oppositeHeroSelected, int result);

    ~Game();

private:
    Hero hero;
    QVector<int> oppositeRandomHeroes = hero.oppositeRandomSelectedHeroes();

    void appendDatabase(); // 应该有两种添加，一种是每一局完成以后，添加英雄以及胜负情况到 hero table，另一种是完成了全部对局，将胜负情况加入 ranking table

    int sum(QVector<int> list);

    int randomChoose(QVector<int> list, QVector<QVector<int> > &skills, QPair<int, int> heroSelected);

    void initDatabase();

    void addDatabase(QString heroName, QString skill, int result);

    QSqlDatabase db;
};
#endif // GAME_H
