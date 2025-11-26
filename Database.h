#pragma once

#include <QFile>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QCryptographicHash>

class DB
{
public:
	static void initializeDatabase();
	static bool registerUser(const QString& username, const QString& password);
	static bool loginUser(const QString& username, const QString& password, int& userId);
private:
	static QString hashPassword(const QString& password);
};