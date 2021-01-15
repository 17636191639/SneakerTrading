#ifndef MSGPROC_H
#define MSGPROC_H
#include <QThread>
#include "userinfo.h"
#include "myserver.h"
#include <QByteArray>

class MsgProc : public QThread
{
     Q_OBJECT
signals:
    void signalSendMsgToClient(QString id, QString msg);
    void signalSendPhotoToClient(QString id, bool isAll);
//    void signalLoginSucess(UserInfo);
//    void signalLoginFail(QString);
public:
    explicit MsgProc(QObject *parent = 0);
    void exitThread(void);

    QByteArray getImageData(const QImage&);

protected:
    void run();

private:
    bool m_isExit;
    MyServer *m_server;

    ///解析命令函数
    void parseUserAsk(QString msg);/////协议解析
    //解析买家协议
    void parseBuyerGetShoes(QString data);
    void parseBuyerGetShoesPhoto(QString data);
    void parseBuyerGetShoesDetails(QString data);
    void parseBuyerViewShopCart(QString data);
    void parseBuyerGetShoesDetailsFromDetailsID(QString data);
    void parseBuyerGetOrder(QString data);
    void parseBuyerGetShoesDetailsByOrder(QString data);
    void parsaeBuyerCommitOrderInfo(QString data);
    void parseBuyerAddToShopCart(QString data);
    void parseBuyerGetBuyerInfo(QString data);
};

#endif // MSGPROC_H
