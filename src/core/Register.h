#ifndef REGISTER_H
#define REGISTER_H

#include <QString>
#include <QDebug>
#include <QTextStream>
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>

class Register {
public:
    Register();

    void initDatabase();

    bool isRegister(const QString &username, const QString &password);

    ~Register();

private:
    QSqlDatabase db;

    void addUser(const QString &username, const QString &password);
};

#endif // REGISTER_H
