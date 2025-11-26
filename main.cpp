#include <QtCore/QCoreApplication>
#include <QtTest/QtTest>
#include "test_db.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    TestDB test;
    return QTest::qExec(&test, argc, argv);
}
