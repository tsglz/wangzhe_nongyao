#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "RegisterWindow.h"
#include "PrepareWindow.h"
#include "core/Login.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class LoginWindow;
}
QT_END_NAMESPACE

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void on_register_2_clicked();

    void on_login_clicked();

private:
    Ui::LoginWindow *ui;
    RegisterWindow *registerWindow;
    PrepareWindow *prepareWindow;
};
#endif // LOGINWINDOW_H
