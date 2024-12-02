#ifndef RANKING_H
#define RANKING_H
#include <QSqlDatabase>
#include <QVector>

class Ranking {
public:
    Ranking();

    ~Ranking();

    QPair<QString, float> showHeroRank();

private:
    QSqlDatabase db;
};

#endif // RANKING_H
