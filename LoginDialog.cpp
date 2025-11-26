#include "LoginDialog.h"

LoginDialog::LoginDialog(QWidget* parent) :
    QDialog(parent), ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{}

void LoginDialog::on_btnLogin_clicked()
{
    QString username = ui->lineEditLogin->text();
    QString password = ui->lineEditPassword->text();

    if (username.isEmpty() || password.isEmpty()) {
        ui->labelStatus1->setStyleSheet("color: rgb(240, 240, 240);");
        ui->labelStatus2->setStyleSheet("color: rgb(240, 240, 240);");
        ui->labelStatus1->raise();
        ui->labelStatus1->setStyleSheet("color: rgb(255, 0, 0);");
        return;
    }

    if (DB::loginUser(username, password, userId)) {
        emit loginSuccess();
        accept();
    } else {
        ui->labelStatus1->setStyleSheet("color: rgb(240, 240, 240);");
        ui->labelStatus2->setStyleSheet("color: rgb(240, 240, 240);");
        ui->labelStatus2->raise();
        ui->labelStatus2->setStyleSheet("color: rgb(255, 0, 0);");
    }
}

void LoginDialog::on_btnRegister_clicked()
{
    RegisterDialog reg(this);
    reg.exec();
}