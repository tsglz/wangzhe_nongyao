#include "Register.h"

Register::Register() {
}

void Register::initDatabase() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("User");
    if (!db.open()) {
        qWarning() << "Failed to open database";
        exit(0);
    }
    QSqlQuery query;
    QString createTableQuery = R"(
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE NOT NULL,
            password TEXT NOT NULL
        )
    )"; // Create a table called "users"
    if (!query.exec(createTableQuery)) {
        qWarning() << "Failed to create table: " << query.lastError().text();
    } else {
        qDebug() << "Table 'users' created or already exists.";
    }
}

bool Register::isRegister(const QString &username, const QString &password) {
    initDatabase();

    QSqlQuery query;
    query.prepare("INSERT INTO users (username, password) VALUES (:username, :password)");

    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if (!query.exec()) {
        qWarning() << "Unable to add user: " << query.lastError().text();
        return false;
    } else {
        qDebug() << "User added successfully!";
    }

    query.prepare("SELECT COUNT(*) FROM users WHERE username = :username AND password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if (!query.exec()) {
        return false;
    }

    if (query.next() && query.value(0).toInt() > 0) {
        return true;
    }
}

Register::~Register() {
    db.close();
}

/**
 * @brief Only used in `isRegister(const QString &username, const QString &password)`
 * @param username
 * @param password
 */
// void Register::addUser(const QString &username, const QString &password) {
//     QSqlQuery query;
//     query.prepare("INSERT INTO users (username, password) VALUES (:username, :password)");
//
//     query.bindValue(":username", username);
//     query.bindValue(":password", password);
//
//     if (!query.exec()) {
//         qWarning() << "Unable to add user: " << query.lastError().text();
//     } else {
//         qDebug() << "User added successfully!";
//     }
// }
