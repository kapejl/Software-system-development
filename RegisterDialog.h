#pragma once

#include <QtWidgets/QDialog>
#include <QtWidgets/QMessageBox>
#include <QSqlDatabase>
#include "Lab3/x64/Debug/qt/uic/ui_RegisterDialog.h"
#include "Database.h"

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    RegisterDialog(QWidget* parent = nullptr);
    ~RegisterDialog();

private slots:
    void on_btnCreate_clicked();

private:
    Ui::RegisterDialog* ui;
};
