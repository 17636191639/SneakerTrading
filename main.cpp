#include "mainwindow.h"
#include <QApplication>
#include "connectsql.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ConnectSQL db;
    if(db.connectMYSQL())  ///1.打开/链接数据库
    {
        qDebug() << "打开/链接数据库 成功";
    }

    MainWindow w;
    w.show();

    int res = a.exec();
    db.closeConnection();
    return res;
}
