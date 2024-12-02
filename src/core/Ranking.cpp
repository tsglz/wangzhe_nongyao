#include "Ranking.h"

Ranking::Ranking() {
}

Ranking::~Ranking() {
}

QPair<QString, float> Ranking::showHeroRank() {
    const QString connectionName = "UserConnection";

    // 检查是否已经存在该连接
    if (!QSqlDatabase::contains(connectionName)) {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", connectionName);
        db.setDatabaseName("User");

        if (!db.open()) {
            qDebug() << "Failed to open database.";
        }
    } else {
        qDebug() << "Reusing existing database connection.";
    }

    // 获取现有连接
    QSqlDatabase db = QSqlDatabase::database(connectionName);

    return {"", 0.0};
}
