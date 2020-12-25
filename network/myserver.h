#ifndef MYSERVER_H
#define MYSERVER_H
#include <QObject>
#include <QTcpServer>
#include "mysocket.h"
//#include "msgproc.h"

class MyServer : public QObject
{
    Q_OBJECT
public slots:
    void slotNewConnection();
    void slotRegisterSocket(QString id, MySocket *socket);
    void slotLogoutSocket(QString id, MySocket *socket);


public:
    explicit MyServer(QObject *parent = 0);
    ~MyServer();

private:
    QTcpServer *m_server;
    //MsgProc *m_msgProc;

};
#endif // MYSERVER_H
