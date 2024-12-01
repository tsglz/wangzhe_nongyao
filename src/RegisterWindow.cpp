#include "RegisterWindow.h"
#include "ui_RegisterWindow.h"

RegisterWindow::RegisterWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterWindow)
    , prepareWindow(nullptr)
{
    ui->setupUi(this);
}

RegisterWindow::~RegisterWindow()
{
    delete ui;
}

void RegisterWindow::on_Register_clicked()
{
    QLineEdit *username = ui->username;
    QLineEdit *password = ui->password;

    Register registerClass;
    if(registerClass.isRegister(username->text(), password->text())) {
        QMessageBox::information(this, "Info", "Register successfully!");

        prepareWindow = new PrepareWindow(username->text());
        prepareWindow->show();

        this->hide();
    } else {
        QMessageBox::information(this, "Info", "Register failed!");
    }
}

