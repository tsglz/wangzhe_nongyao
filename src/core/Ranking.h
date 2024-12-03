#ifndef RANKING_H
#define RANKING_H
#include <QSqlDatabase>
#include <QVector>
#include <QSqlQuery>
#include "Hero.h"


class Ranking {
public:
    Ranking();

    ~Ranking();

    QVector<QPair<QString, float>> showHeroRank();

private:
    QSqlDatabase db;
};

#endif // RANKING_H
