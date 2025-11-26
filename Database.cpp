#include "Database.h"

void DB::initializeDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("app.db");

    if (!db.open())
    {
        qDebug() << "Ошибка открытия БД: " << db.lastError().text();
        return;
    }

    QSqlQuery query;

    QString createUsers = R"(
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE NOT NULL,
            password TEXT NOT NULL
        )
    )";

    if (!query.exec(createUsers))
        qDebug() << "Ошибка создания таблицы users: " << db.lastError().text();

    QString createArrays = R"(
        CREATE TABLE IF NOT EXISTS arrays (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            user_id INTEGER NOT NULL,
            array TEXT NOT NULL,
            created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
            FOREIGN KEY (user_id) REFERENCES users(id)
        )
    )";

    if (!query.exec(createArrays))
        qDebug() << "Ошибка создания таблицы arrays: " << db.lastError().text();
}

bool DB::registerUser(const QString& username, const QString& password)
{
    QString hashed = DB::hashPassword(password);
    
    QSqlQuery query;

    query.prepare("INSERT INTO users(username, password) VALUES(:username, :password)");
    query.bindValue(":username", username);
    query.bindValue(":password", hashed);

    if (!query.exec()) {
        qDebug() << "Ошибка регистрации:" << query.lastError().text();
        return false;
    }
    
    return true;
}

bool DB::loginUser(const QString& username, const QString& password, int& userId)
{
    QString hashed = DB::hashPassword(password);
    
    QSqlQuery query;

    query.prepare("SELECT id FROM users WHERE username=:username AND password=:password");
    query.bindValue(":username", username);
    query.bindValue(":password", hashed);

    if (!query.exec()) {
        qDebug() << "Ошибка входа:" << query.lastError().text();
        return false;
    }

    userId = query.value(0).toInt();;

    return query.next();
}

QString DB::hashPassword(const QString& password)
{
    QByteArray hash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
    return QString(hash.toHex());
}