#include "connectsql.h"
#include <QSqlDatabase>
#include <QSqlError>

ConnectSQL::ConnectSQL()
{

}

bool ConnectSQL::connectMYSQL()
{
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setPort(3306);
    db.setUserName("root");
    db.setPassword("123456");
    db.setDatabaseName("sneaker");
    if(!db.open()){
        qCritical("Can't open database: %s(%s)",
                  db.lastError().text().toLocal8Bit().data(),
                  qt_error_string().toLocal8Bit().data());

        return false;
    }
    return true;

}
bool ConnectSQL::connectSQLite()
{
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../EduServer/database/ugedu.db");

    if(!db.open()){
        qCritical("Can't open database: %s(%s)",
                  db.lastError().text().toLocal8Bit().data(),
                  qt_error_string().toLocal8Bit().data());

        return false;
    }
    return true;
}
void ConnectSQL::closeConnection()
{
    QSqlDatabase::database().close();
}
