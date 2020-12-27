#include "msgproc.h"
#include "globalvars.h"
#include <QDebug>
#include "execsql.h"
#include <QImage>
#include <QBuffer>
#include <QPixmap>

MsgProc::MsgProc(QObject *parent) :
    QThread(parent)
{
    m_server = new MyServer;
//        connect(this, SIGNAL(signalSendMsgToClient(QString,QString)),
//                this, SLOT(slotSendMsgToClient(QString,QString)));
    m_isExit = false;
}

void MsgProc::exitThread(void)
{
    m_isExit = true;
}

void MsgProc::run()
{
    while(!m_isExit)
    {
        if(!GlobalVars::g_msgQueue.isEmpty())
        {
            QString msg = GlobalVars::g_msgQueue.dequeue();
            //解析msg
            parseUserAsk(msg);
        }
        msleep(20);
    }
}
void MsgProc::parseUserAsk(QString msg)
{
    QStringList list = msg.split("#");
    int cmd = msg.at(0).toLatin1();
    switch (cmd)
    {
    ///通用请求命令
    //case CMD_UserLogin_L: parseUserLogin(list.at(1)); break;
    //解析买家命令
    case CMD_GetShoes_T: parseBuyerGetShoes(list.at(1)); break;
    case CMD_GetShoesPhoto_A:parseBuyerGetShoesPhoto(list.at(1)); break;
    default:
        break;
    }
}
void MsgProc::parseBuyerGetShoes(QString data)
{
    QString buyerID = data;
    ExecSQL::selectAllShoes();
    if(!GlobalVars::g_shoesInfoList->isEmpty())
    {
        QString msg = QString(CMD_GetShoes_T) + QString("#!");
        for(int i = 0; i < GlobalVars::g_shoesInfoList->count(); i++)
        {
            msg += QString("|")
                    + GlobalVars::g_shoesInfoList->at(i).getID()
                    + QString("&") + GlobalVars::g_shoesInfoList->at(i).getStoreID()
                    + QString("&") + GlobalVars::g_shoesInfoList->at(i).getPhotoID()
                    + QString("&") + GlobalVars::g_shoesInfoList->at(i).getShoesName()
                    + QString("&") + GlobalVars::g_shoesInfoList->at(i).getBottomPrice()
                    + QString("&") + GlobalVars::g_shoesInfoList->at(i).getFreight();
        }
        emit signalSendMsgToClient(buyerID, msg);
    }else
    {
        QString msg = QString(CMD_GetShoes_T) + QString("#?|") + buyerID + QString("|") + QString("无商品！");
        emit signalSendMsgToClient(buyerID, msg);

    }


}
void MsgProc::parseBuyerGetShoesPhoto(QString data)
{
    QStringList list = data.split("|");
    QString buyerID = list.at(0);
    QString photoID = list.at(1);
    ExecSQL::selectPhotoInfoForID(photoID);
    if(!GlobalVars::g_photoInfoList->isEmpty())
    {
//        QString imgPath = GlobalVars::g_photoInfoList->at(0).getPhotoPath() +
//                                GlobalVars::g_photoInfoList->at(0).getID() + QString(" (1).jpg"); //获取要发送的图片路径
//        QImage image(imgPath);
//        QByteArray imgByteArray;
//        QBuffer buf(&imgByteArray);
//        image.save(&buf, "jpg");
//        QByteArray hexed = imgByteArray.toBase64();
//        buf.close();
//        QString strImage(hexed);
//        qDebug() << strImage;
// 将图片转失败，暂时无法使用此方法
//        QImage img(imgPath);
//        QString imageData = getImageData(img);     //将要发送的图片转换成字符
//        qDebug() << "图片信息： " << imageData;
//        QString msg = QString(CMD_GetShoesPhoto_A) + QString("#!");   //合成消息
//        msg += QString("|")
//                + GlobalVars::g_photoInfoList->at(0).getID()
//                + QString("&") + GlobalVars::g_photoInfoList->at(0).getPhotoCount()
//                + QString("&") + GlobalVars::g_photoInfoList->at(0).getPhotoPath();
//                //+ QString("&") + imageData;

        emit signalSendPhotoToClient(buyerID);

    }else
    {
        QString msg = QString(CMD_GetShoesPhoto_A) + QString("#?|") + buyerID + QString("|") + QString("无图片信息！");
        emit signalSendMsgToClient(buyerID, msg);
    }
}


QByteArray MsgProc::getImageData(const QImage &image)  //将图片转换成base64字符串
{
    QByteArray imageData;
    QBuffer buffer(&imageData);
    image.save(&buffer, "jpg");
    imageData = imageData.toBase64();

    return imageData;
}
