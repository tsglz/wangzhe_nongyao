#include "Login.h"

Login::Login() {
}

void Login::initDatabase() {
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
}

bool Login::isLogin(const QString &username, const QString &password) {
    initDatabase();
    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE username = :username AND password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if (query.exec() && query.next()) {
        qDebug() << "Login successfully!";
        db.close();
        return true;
    } else {
        qWarning() << "Username or password is error!";
        db.close();
        return false;
    }
}

Login::~Login() {
}
