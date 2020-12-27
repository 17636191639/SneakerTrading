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
    if(m_socket->bytesAvailable() == 65536)  //接受数据满包说明没发完
    {
        m_byte.append(m_socket->readAll());
    }else
    {
        m_byte.append(m_socket->readAll());



        //int bagSize = 0;
        //bool isFirst = true;
        //处理粘包
        int readSize = 0;
        QByteArray tempByte = m_byte;
        while(m_byte.size() - readSize)
        {
            QDataStream in(tempByte);
            in.setVersion(QDataStream::Qt_4_6);

            if(m_tcpBlockSize == 0)
            {
                if(tempByte.size() < sizeof(quint32))
                {
                    return;
                }
                in >> m_tcpBlockSize;  //获取数据的长度
            }
            //处理半包   数据只接受了一半  跳出函数继续接受

            if(tempByte.size() - sizeof(quint32) < m_tcpBlockSize) //总接受大小-2个字节就是数据大小
            {
                return;
            }
            //qDebug() << "当前处理数据包大小：" << tempByte.size();
            QString msg;
            in >> msg;
            qDebug() << "Client Recv: " << msg;


            if(msg.at(0) == CMD_UserLogin_L)  //登录
            {
                parseUserLogin(msg);
            }else if(msg.at(0) == CMD_UserExit_X)  //退出登录
            {
                parseUserExit(msg);
            }else
            {
                GlobalVars::g_msgQueue.enqueue(msg);  //进入消息队列
            }
            readSize += m_tcpBlockSize + sizeof(quint32);
            //qDebug() << "占位符大小：" << m_tcpBlockSize << "已读数据" << readSize;
            tempByte = m_byte.right(m_byte.size() - readSize);
            m_tcpBlockSize = 0;
        }
        m_byte.clear();
    }

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

    out << (quint32)0;
    out << msg;
    out.device()->seek(0);
    out << (quint32)(buffer.size() - sizeof(quint32));

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

    if(img.load(imgPath))
    {
        qDebug() << "img size: " << img.size();
        QByteArray buffer;
        QDataStream out(&buffer, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_4_6);

        out << (quint32)0;
        out << msg;  //将命令流入


        QBuffer b;
        b.open(QIODevice::ReadWrite);
        img.save(&b,"jpg");

        out << b.data();

        out.device()->seek(0);
        out << (quint32)(buffer.size() - sizeof(quint32));  //将数据大小流入
        qDebug() << "buffer size：" << buffer.size();
        qDebug() << "photo size: " << b.size();
        m_socket->write(buffer);
    }



}
