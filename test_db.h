#pragma once

#include <QtTest/QtTest>
#include <QtSql>
#include <QVector>
#include <QDebug>
#include "../Lab3/Database.h"
#include "../Lab3/MainWindow.h"

class TestDB : public QObject
{
	Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();

    void testDB_100();
    void testDB_1000();
    void testDB_10000();
public:
    static QVector<int> generateArray();
};

void testAddArrays(int numArrays);
void testLoadAndSortArrays(int numArrays);
void testClearDatabase(int numArrays);

QString arrayToStringTests(const QVector<int>& arr);
QVector<int> stringToArrayTests(const QString& str);
QVector<int> mergeSortTests(const QVector<int>& arr);
QVector<int> mergeTests(const QVector<int>& left, const QVector<int>& right);