#include "test_db.h"

void TestDB::initTestCase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "test_connection");
    db.setDatabaseName("test_test.db");
    QVERIFY(db.open());

    QSqlQuery query(db);
    QVERIFY(query.exec("CREATE TABLE IF NOT EXISTS arrays (id INTEGER PRIMARY KEY AUTOINCREMENT, array TEXT NOT NULL)"));
}

void TestDB::cleanupTestCase()
{
    QSqlDatabase db = QSqlDatabase::database("test_connection");
    db.close();
    QFile::remove("test_test.db");
}

void TestDB::testDB_100() {
    testAddArrays(100); testLoadAndSortArrays(100); testClearDatabase(100);
}
void TestDB::testDB_1000() { 
    testAddArrays(1000); testLoadAndSortArrays(1000); testClearDatabase(1000);
}
void TestDB::testDB_10000() { 
    testAddArrays(10000); testLoadAndSortArrays(10000); testClearDatabase(10000);
}

QVector<int> TestDB::generateArray()
{
    QVector<int> arr;
    int size = QRandomGenerator::global()->bounded(2, 250);
    for (int i = 0; i < size; ++i)
        arr.append(QRandomGenerator::global()->bounded(-1000, 1000));

    return arr;
}

void testAddArrays(int numArrays)
{
    QSqlDatabase db = QSqlDatabase::database("test_connection");

    QElapsedTimer timer;
    timer.start();

    bool success = true;
    for (int i = 0; i < numArrays; ++i) {
        QVector<int> arr = TestDB::generateArray();
        QSqlQuery query(db);
        query.prepare("INSERT INTO arrays(array) VALUES(:arr)");
        query.bindValue(":arr", arrayToStringTests(arr));
        if (!query.exec()) success = false;
    }

    qDebug() << QString::fromUtf8("Adding ") << numArrays << QString::fromUtf8(" records in ") << timer.elapsed() << QString::fromUtf8(" ms");
    QVERIFY(success);
}

void testLoadAndSortArrays(int numArrays)
{
    QSqlDatabase db = QSqlDatabase::database("test_connection");
    QSqlQuery query(db);
    QVERIFY(query.exec("SELECT array FROM arrays LIMIT 100"));

    QElapsedTimer timer;
    timer.start();

    while (query.next()) {
        QString str = query.value(0).toString();
        QVector<int> arr = stringToArrayTests(str);
        QVector<int> sorted = mergeSortTests(arr);
        QVERIFY(!sorted.isEmpty());
    }

    qDebug() << QString::fromUtf8("Loading and sorting 100 arrays from a database with ") << numArrays << QString::fromUtf8(" records in ") << (timer.elapsed() / 100) << QString::fromUtf8(" ms");
}

void testClearDatabase(int numArrays)
{
    QSqlDatabase db = QSqlDatabase::database("test_connection");
    QSqlQuery query(db);
    QElapsedTimer timer;
    timer.start();
    QVERIFY(query.exec("DELETE FROM arrays"));
    qDebug() << QString::fromUtf8("Cleaning the database of ") << numArrays << QString::fromUtf8(" records in ") << timer.elapsed() << QString::fromUtf8(" ms");
}

QString arrayToStringTests(const QVector<int>& arr)
{
    QStringList list;
    for (int v : arr)
        list << QString::number(v);
    return list.join(" ");
}

QVector<int> stringToArrayTests(const QString& str)
{
    QVector<int> arr;
    QString cleaned = str;
    cleaned.replace(",", " ");
    QStringList list = cleaned.split(" ", Qt::SkipEmptyParts);
    for (const QString& s : list)
        arr.append(s.toInt());
    return arr;
}

QVector<int> mergeSortTests(const QVector<int>& arr)
{
    if (arr.size() <= 1)
        return arr;

    int mid = arr.size() / 2;
    QVector<int> left = mergeSortTests(arr.mid(0, mid));
    QVector<int> right = mergeSortTests(arr.mid(mid));

    return mergeTests(left, right);
}

QVector<int> mergeTests(const QVector<int>& left, const QVector<int>& right)
{
    QVector<int> result;
    int i = 0, j = 0;
    while (i < left.size() && j < right.size()) {
        if (left[i] < right[j])
            result.append(left[i++]);
        else
            result.append(right[j++]);
    }

    while (i < left.size())
        result.append(left[i++]);
    while (j < right.size())
        result.append(right[j++]);

    return result;
}