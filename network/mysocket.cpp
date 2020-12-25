#include "mysocket.h"
#include <QMap>
#include <QDataStream>
#include <QDebug>
#include "globalvars.h"
#include <QBuffer>
#include <QImage>

MySocket::MySocket(QTcpSocket *socket, QObject *parent) : QObject(parent)
{
    m_tcpBlockSize = 0;

    m_socket = socket;
    connect(m_socket, SIGNAL(disconnected()),
            m_socket, SLOT(deleteLater()));
    connect(m_socket, SIGNAL(readyRead()),
            this, SLOT(slotReadyRead()));
}
MySocket::~MySocket()
{

}
void MySocket::slotReadyRead()
{
    QDataStream in(m_socket);
    in.setVersion(QDataStream::Qt_4_6);

    if(m_tcpBlockSize == 0)
    {
        if(m_socket->bytesAvailable() < sizeof(quint16))
            return;

        in >> m_tcpBlockSize;
    }

    if(m_socket->bytesAvailable() < m_tcpBlockSize)
        return;

    QString msg;
    in >> msg;

    if(msg.at(0) == CMD_UserLogin_L)
    {
        parseUserLogin(msg);
    }else if(msg.at(0) == CMD_UserExit_X)
    {
        parseUserExit(msg);
    }else
    {
        GlobalVars::g_msgQueue.enqueue(msg);
        qDebug() << "g_msgQueue.enqueue: " << msg;
    }
    m_tcpBlockSize = 0;
}


void MySocket::parseUserLogin(QString msg)
{
    qDebug() << "MySocket::parseUserLogin" << msg;

    QStringList list = msg.remove("L#").split("|");
    QString id = list.at(0);
    QString pswd = list.at(1);

    if(GlobalVars::g_userInfoMap.contains(id))
    {
        UserInfoList::iterator it = GlobalVars::g_userInfoMap[id];
        it->display();
        if(it->getPswd() == pswd)
        {
            QString msg = QString(CMD_UserLogin_L)
                    + QString("#!|") + it->getID()
                    + QString("|") + it->getPswd()
                    + QString("|") + it->getRole()
                    + QString("|") + it->getDate();
            this->slotSendMsg(msg);
            emit signalRegisterSocket(id, this);
        }else
        {
            QString msg = QString(CMD_UserLogin_L)
                    + QString("#?|") + QString("Error: UID Or Pswd!");
            this->slotSendMsg(msg);
        }
    }
}
void MySocket::parseUserExit(QString msg)
{

}
bool MySocket::slotSendMsg(QString msg)
{
    QByteArray buffer;
    QDataStream out(&buffer, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_6);

    out << (quint16)0;
    out << msg;
    out.device()->seek(0);
    out << (quint16)(buffer.size() - sizeof(quint16));

    qDebug() << "Server Send: " << msg;
    return m_socket->write(buffer);
}
bool MySocket::slotSendPhoto(void)
{

    QString msg = QString(CMD_GetShoesPhoto_A) + QString("#!");   //合成消息
    msg += QString("|")
            + GlobalVars::g_photoInfoList->at(0).getID()
            + QString("&") + GlobalVars::g_photoInfoList->at(0).getPhotoCount()
            + QString("&") + GlobalVars::g_photoInfoList->at(0).getPhotoPath();
    QString imgPath = GlobalVars::g_photoInfoList->at(0).getPhotoPath() +
                                    GlobalVars::g_photoInfoList->at(0).getID() + QString(" (1).jpg");
    QImage img;
    bool loadImg = img.load(imgPath);

    if(loadImg)
    {
        qDebug() << "img size: " << img.size();
        QByteArray buffer;
        QDataStream out(&buffer, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_4_6);

        out << (quint16)0;
        out << msg;  //将命令流入


        QBuffer b;
        b.open(QIODevice::ReadWrite);
        img.save(&b,"jpg");

        out << b.data();

        out.device()->seek(0);
        out << (quint16)(buffer.size() - sizeof(quint16));  //将数据大小流入
        qDebug() << "buffer size：" << buffer.size();
        qDebug() << "photo size: " << b.size();
        m_socket->write(buffer);
    }



}
