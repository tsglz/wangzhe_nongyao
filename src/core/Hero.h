#ifndef HERO_H
#define HERO_H

#include <QString>
#include <QVector>
#include <random>

class Hero {
public:
    Hero();

    struct Attributes {
        QString name;
        int scissors;
        int rock;
        int paper;
    };

    Attributes heroAttributes;

    QVector<Attributes> showHeroes();

    QVector<int> oppositeRandomSelectedHeroes();

    ~Hero();

private:
    QVector<Attributes> heroList;
};

#endif // HERO_H
