#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <QDialog>
#include "PrepareWindow.h"
#include "core/Register.h"

namespace Ui {
class RegisterWindow;
}

class RegisterWindow : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterWindow(QWidget *parent = nullptr);
    ~RegisterWindow();

private slots:
    void on_Register_clicked();

private:
    Ui::RegisterWindow *ui;
    PrepareWindow *prepareWindow;
};

#endif // REGISTERWINDOW_H
