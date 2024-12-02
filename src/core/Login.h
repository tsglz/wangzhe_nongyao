#ifndef LOGIN_H
#define LOGIN_H

#include <QString>
#include <QDebug>
#include <QTextStream>
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class Login {
public:
    Login();

    void initDatabase();

    bool isLogin(const QString &username, const QString &password);

    ~Login();

private:
    QSqlDatabase db;
};

#endif // LOGIN_H
