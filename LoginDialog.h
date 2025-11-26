#pragma once

#include <QtWidgets/QDialog>
#include <QtWidgets/QMessageBox>
#include <QSqlDatabase>
#include "Lab3/x64/Debug/qt/uic/ui_LoginDialog.h"
#include "RegisterDialog.h"
#include "Database.h"

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    LoginDialog(QWidget* parent = nullptr);
    ~LoginDialog();

    int getUserId() const { return userId; }

private slots:
    void on_btnLogin_clicked();
    void on_btnRegister_clicked();

signals:
    void loginSuccess();

private:
    Ui::LoginDialog* ui;
    int userId = -1;
};
