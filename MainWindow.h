#pragma once

#include <QtWidgets/QMainWindow>
#include <QtSql>
#include <QVector>
#include "Lab3/x64/Debug/qt/uic/ui_MainWindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(int userId, QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindowClass ui;

    QVector<int> currentArray;
    int userId;

    QString arrayToString(const QVector<int>& arr);
    QVector<int> stringToArray(const QString& str);

    void cleanLabels();
    QVector<int> mergeSort(const QVector<int>& arr);
    QVector<int> merge(const QVector<int>& left, const QVector<int>& right);

private slots:
    void showHelp();
    void generateArray();
    void sortArray();
    void saveArray();
    void loadArrays();
};
