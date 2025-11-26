#include "MainWindow.h"
#include "HelpDialog.h"

MainWindow::MainWindow(int userId, QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    connect(ui.actionHelp, &QAction::triggered, this, &MainWindow::showHelp);
    connect(ui.btnGenerate, &QPushButton::clicked, this, &MainWindow::generateArray);
    connect(ui.btnSort, &QPushButton::clicked, this, &MainWindow::sortArray);
    connect(ui.btnSave, &QPushButton::clicked, this, &MainWindow::saveArray);
    connect(ui.btnRefresh, &QPushButton::clicked, this, &MainWindow::loadArrays);

    loadArrays();
}

MainWindow::~MainWindow()
{}

void MainWindow::showHelp()
{
    HelpDialog helpdialog(this);

    helpdialog.exec();
}

void MainWindow::cleanLabels()
{
    ui.labelStatus1->setStyleSheet("color: rgb(240, 240, 240);");
    ui.labelStatus2->setStyleSheet("color: rgb(240, 240, 240);");
    ui.labelStatus3->setStyleSheet("color: rgb(240, 240, 240);");
    ui.labelStatus4->setStyleSheet("color: rgb(240, 240, 240);");
    ui.labelStatus5->setStyleSheet("color: rgb(240, 240, 240);");
    ui.labelStatus6->setStyleSheet("color: rgb(240, 240, 240);");
    ui.labelStatus7->setStyleSheet("color: rgb(240, 240, 240);");
}

void MainWindow::generateArray()
{
    currentArray.clear();
    int size = QRandomGenerator::global()->bounded(2, 20);
    for (int i = 0; i < size; ++i)
        currentArray.append(QRandomGenerator::global()->bounded(-1000, 1000));

    ui.lineEdit->setText(arrayToString(currentArray));
    cleanLabels();
    ui.labelStatus1->raise();
    ui.labelStatus1->setStyleSheet("color: green;");
}

void MainWindow::sortArray()
{
    if (ui.lineEdit->text().isEmpty()) {
        cleanLabels();
        ui.labelStatus2->raise();
        ui.labelStatus2->setStyleSheet("color: red");
        return;
    }

    currentArray = stringToArray(ui.lineEdit->text());
    QVector<int> sorted = mergeSort(currentArray);

    ui.lineEdit->setText(arrayToString(sorted));
    cleanLabels();
    ui.labelStatus3->raise();
    ui.labelStatus3->setStyleSheet("color: green");
}

void MainWindow::saveArray()
{
    QString text = ui.lineEdit->text();
    qDebug() << "input text =" << text;
    currentArray = stringToArray(text);
    qDebug() << "parsed =" << currentArray;
    
    if (currentArray.isEmpty()) {
        cleanLabels();
        ui.labelStatus4->raise();
        ui.labelStatus4->setStyleSheet("color: red");
        return;
    }

    QSqlDatabase db = QSqlDatabase::database();
    db.setDatabaseName("app.db");
    db.open();
    QSqlQuery query(db);
    query.prepare("INSERT INTO arrays(user_id, array) VALUES(:uid, :arr)");
    query.bindValue(":uid", userId);
    query.bindValue(":arr", arrayToString(currentArray));

    if (!query.exec()) {
        cleanLabels();
        ui.labelStatus5->raise();
        ui.labelStatus5->setStyleSheet("color: red");
        return;
    }

    cleanLabels();
    ui.labelStatus6->raise();
    ui.labelStatus6->setStyleSheet("color: green");

    loadArrays();
}

void MainWindow::loadArrays()
{
    QSqlDatabase db = QSqlDatabase::database();
    db.setDatabaseName("app.db");
    QSqlQueryModel* model = new QSqlQueryModel(ui.listView);
    model->setQuery("SELECT array FROM arrays WHERE user_id = " + QString::number(userId), db);
    ui.listView->setModel(model);
    cleanLabels();
    ui.labelStatus7->raise();
    ui.labelStatus7->setStyleSheet("color: green");
}

QVector<int> MainWindow::mergeSort(const QVector<int>& arr)
{
    if (arr.size() <= 1)
        return arr;

    int mid = arr.size() / 2;
    QVector<int> left = mergeSort(arr.mid(0, mid));
    QVector<int> right = mergeSort(arr.mid(mid));

    return merge(left, right);
}

QVector<int> MainWindow::merge(const QVector<int>& left, const QVector<int>& right)
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

QString MainWindow::arrayToString(const QVector<int>& arr)
{
    QStringList list;
    for (int v : arr)
        list << QString::number(v);
    return list.join(" ");
}

QVector<int> MainWindow::stringToArray(const QString& str)
{
    QVector<int> arr;
    QString cleaned = str;
    cleaned.replace(",", " ");
    QStringList list = cleaned.split(" ", Qt::SkipEmptyParts);
    for (const QString& s : list)
        arr.append(s.toInt());
    return arr;
}