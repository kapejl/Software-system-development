#pragma once

#include <QtWidgets/QDialog>
#include "Lab3/x64/Debug/qt/uic/ui_HelpDialog.h"

class HelpDialog : public QDialog
{
    Q_OBJECT

public:
    HelpDialog(QWidget* parent = nullptr);
    ~HelpDialog();

private:
    Ui::HelpDialog* ui;
};
