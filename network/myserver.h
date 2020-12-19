#ifndef MYSERVER_H
#define MYSERVER_H
#include <QObject>
#include <QTcpServer>
#include "mysocket.h"
#include "msgproc.h"

class MyServer : public QObject
{
    Q_OBJECT
public slots:
    void slotNewConnection();
    void slotRegisterSocket(QString id, MySocket *socket);
    void slotLogoutSocket(QString id, MySocket *socket);
    void slotSendMsgToClient(QString id, QString msg);

public:
    explicit MyServer(QObject *parent = 0);
    ~MyServer();

private:
    QTcpServer *m_server;
    MsgProc *m_msgProc;
    SocketMap m_socketMap;
};
#endif // MYSERVER_H
