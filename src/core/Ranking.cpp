#include "Ranking.h"

Ranking::Ranking() {
}

Ranking::~Ranking() {
}

QVector<QPair<QString, float>> Ranking::showHeroRank() {
    const QString connectionName = "UserConnection";

    // Check if the connection already exists
    if (!QSqlDatabase::contains(connectionName)) {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", connectionName);
        db.setDatabaseName("User");

        if (!db.open()) {
            qDebug() << "Failed to open database.";
            return {};
        }
    } else {
        qDebug() << "Reusing existing database connection.";
    }

    // Get the existing connection
    QSqlDatabase db = QSqlDatabase::database(connectionName);

    QSqlQuery query(db);
    QMap<QString, QPair<int, int>> heroStats; // Map to store heroName to <totalGames, wins>

    // Query to get total games and wins for each hero
    if (query.exec("SELECT heroName, result FROM hero")) {
        while (query.next()) {
            QString heroName = query.value(0).toString();
            int result = query.value(1).toInt();

            if (!heroStats.contains(heroName)) {
                heroStats[heroName] = qMakePair(0, 0);
            }

            heroStats[heroName].first++; // Increment total games
            if (result == 1) {
                heroStats[heroName].second++; // Increment wins
            }
        }
    } else {
        qDebug() << "Failed to execute query.";
        return {};
    }

    QVector<QPair<QString, float>> heroWinRates;

    Hero hero;
    auto heroList = hero.showHeroes();
    QStringList heroNames = {};

    for (size_t i = 0; i < heroList.size(); i++) {
        heroNames.append(heroList[i].name);
    }

    // Calculate win rates for specified heroes
    for (const QString &heroName : heroNames) {
        if (heroStats.contains(heroName)) {
            int totalGames = heroStats[heroName].first;
            int wins = heroStats[heroName].second;
            float winRate = totalGames > 0 ? static_cast<float>(wins) / totalGames : 0.0;
            heroWinRates.append(qMakePair(heroName, winRate));
        } else {
            // If the hero is not found in the stats, add them with a win rate of 0
            heroWinRates.append(qMakePair(heroName, 0.0));
        }
    }

    return heroWinRates;
}

