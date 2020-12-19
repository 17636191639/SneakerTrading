#include "myserver.h"
#include <QTcpSocket>
#include <QDebug>
#include <QMap>
#include "mysocket.h"


MyServer::MyServer(QObject *parent) : QObject(parent)
{
    m_socketMap.clear();
    m_msgProc = new MsgProc;
    m_server = new QTcpServer(this);
    connect(m_server, SIGNAL(newConnection()),
            this, SLOT(slotNewConnection()));
    connect(m_msgProc, SIGNAL(signalSendMsgToClient(QString,QString)),
            this, SLOT(slotSendMsgToClient(QString,QString)));
    m_server->listen(QHostAddress::Any, 5555);
    m_msgProc->start();

}

MyServer::~MyServer()
{
    m_msgProc->exitThread();
    if(m_msgProc->wait())
    {
        delete m_msgProc;
    }
}


void MyServer::slotNewConnection()
{
    qDebug() << "ServerUI::slotNewConnection()";
    QTcpSocket *socket = m_server->nextPendingConnection();

    MySocket *Socket = new MySocket(socket);
    connect(Socket, SIGNAL(signalRegisterSocket(QString,MySocket*)),
            this, SLOT(slotRegisterSocket(QString,MySocket*)));
    connect(Socket, SIGNAL(signalLogoutSocket(QString,MySocket*)),
            this, SLOT(slotLogoutSocket(QString,MySocket*)));
}

void MyServer::slotRegisterSocket(QString id, MySocket *socket)
{
    m_socketMap.insert(id, socket); //登录成功，添加Socket到g_socketMap
}

void MyServer::slotLogoutSocket(QString id, MySocket *socket)
{
    if(m_socketMap.contains(id))
    {
        //delete socket;
        m_socketMap.remove(id);
    }
}

void MyServer::slotSendMsgToClient(QString id, QString msg)
{
    if(m_socketMap.contains(id))
    {
        m_socketMap[id]->slotSendMsg(msg);
    }
}
