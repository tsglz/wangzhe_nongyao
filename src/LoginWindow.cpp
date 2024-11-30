#include "LoginWindow.h"
#include "./ui_LoginWindow.h"

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::LoginWindow)
      , registerWindow(nullptr)
      , prepareWindow(nullptr)
{
    ui->setupUi(this);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_register_2_clicked() // Register
{
    registerWindow = new RegisterWindow;
    registerWindow->show();

    this->hide();
}


void LoginWindow::on_login_clicked() // Login
{
    QLineEdit *username = ui->username;
    QLineEdit *password = ui->password;

    Login login;
    login.initDatabase();
    if (login.isLogin(username->text(), password->text())) {
        QMessageBox::information(this, "Info", "Login successfully!");

        prepareWindow = new PrepareWindow(username->text());
        prepareWindow->show();

        this->hide();
    } else {
        QMessageBox::information(this, "Info", "Username or Password is error!");
    }
}
