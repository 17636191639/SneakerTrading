#ifndef MYSOCKET_H
#define MYSOCKET_H

#include <QObject>
#include <QTcpSocket>

class MySocket : public QObject
{
    Q_OBJECT
signals:
    void signalRegisterSocket(QString id, MySocket *socket);
    void signalLogoutSocket(QString id, MySocket *socket);

public slots:
    void slotReadyRead();
    bool slotSendMsg(QString msg);

public:
    explicit MySocket(QTcpSocket *socket, QObject *parent = 0);
    ~MySocket();

    QString m_localUid;

private:
    quint16 m_tcpBlockSize;
    QTcpSocket *m_socket;

    void parseUserLogin(QString msg);
    void parseUserExit(QString msg);
};

typedef QMap<QString, MySocket*> SocketMap;//id, socket
#endif // MYSOCKET_H
