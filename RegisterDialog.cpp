#include "RegisterDialog.h"

RegisterDialog::RegisterDialog(QWidget* parent) :
    QDialog(parent), ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
}

RegisterDialog::~RegisterDialog()
{}

void RegisterDialog::on_btnCreate_clicked()
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

    if (DB::registerUser(username, password)) {
        accept();
    }
    else {
        ui->labelStatus1->setStyleSheet("color: rgb(240, 240, 240);");
        ui->labelStatus2->setStyleSheet("color: rgb(240, 240, 240);");
        ui->labelStatus2->raise();
        ui->labelStatus2->setStyleSheet("color: rgb(255, 0, 0);");
    }
}