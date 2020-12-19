#ifndef MSGPROC_H
#define MSGPROC_H
#include <QThread>
#include "userinfo.h"

class MsgProc : public QThread
{
     Q_OBJECT
signals:
    void signalSendMsgToClient(QString id, QString msg);
//    void signalLoginSucess(UserInfo);
//    void signalLoginFail(QString);
public:
    explicit MsgProc(QObject *parent = 0);
    void exitThread(void);

protected:
    void run();

private:
    bool m_isExit;

    ///解析命令函数
    void parseUserAsk(QString msg);/////协议解析
    //解析买家协议
    void parseBuyerGetShoes(QString data);
};

#endif // MSGPROC_H
