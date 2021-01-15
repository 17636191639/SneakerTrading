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

    //解析买家命令
    case CMD_GetShoes_T: parseBuyerGetShoes(list.at(1)); break;
    case CMD_GetShoesPhoto_A:parseBuyerGetShoesPhoto(list.at(1)); break;
    case CMD_GetShoesDetails_F:parseBuyerGetShoesDetails(list.at(1));break;
    case CMD_ViewShopCart_P:parseBuyerViewShopCart(list.at(1));break;
    case CMD_GetShoesDetailFromDetailsID_f:parseBuyerGetShoesDetailsFromDetailsID(list.at(1));break;
    case CMD_GetOrder_O:parseBuyerGetOrder(list.at(1));break;
    case CMD_GetShoesDetailByOrder_o:parseBuyerGetShoesDetailsByOrder(list.at(1));break;
    case CMD_CommitOrderInfo_c:parsaeBuyerCommitOrderInfo(list.at(1));break;
    case CMD_AddToShopCart_p:parseBuyerAddToShopCart(list.at(1));break;
    case CMD_GetBuyerInfo_B:parseBuyerGetBuyerInfo(list.at(1));break;
    //解析卖家命令


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
    QString isAllPhoto = list.at(2);
    ExecSQL::selectPhotoInfoForID(photoID);
    if(!GlobalVars::g_photoInfoList->isEmpty())
    {
        if(isAllPhoto == "true")
        {
            emit signalSendPhotoToClient(buyerID, true);
        }else if(isAllPhoto == "false")
        {
            emit signalSendPhotoToClient(buyerID, false);
        }else
        {
            QString msg = QString(CMD_GetShoesPhoto_A) + QString("#?|") + buyerID + QString("|") + QString("图片申请指令错误！");
            emit signalSendMsgToClient(buyerID, msg);
        }



    }else
    {
        QString msg = QString(CMD_GetShoesPhoto_A) + QString("#?|") + buyerID + QString("|") + QString("无图片信息！");
        emit signalSendMsgToClient(buyerID, msg);
    }
}
void MsgProc::parseBuyerGetShoesDetails(QString data)
{
    //处理 MH-xxx|SH-xxxx  获取某一商品详情
    QStringList list = data.split("|");
    QString buyerID = list.at(0);
    QString shoesID = list.at(1);

    ExecSQL::selectShoesDetailsForShoesID(shoesID); //根据客户端的商品ID查找相关商品
    if(!GlobalVars::g_shoesDetailsList->isEmpty())
    {
        QString msg = QString(CMD_GetShoesDetails_F) + QString("#!|") + buyerID;
        for(int i = 0; i < GlobalVars::g_shoesDetailsList->count(); i++)
        {
            msg += QString("|")
                    + GlobalVars::g_shoesDetailsList->at(i).getID()
                    + QString("&") + GlobalVars::g_shoesDetailsList->at(i).getShoesID()
                    + QString("&") + GlobalVars::g_shoesDetailsList->at(i).getPhotoID()
                    + QString("&") + GlobalVars::g_shoesDetailsList->at(i).getSize()
                    + QString("&") + GlobalVars::g_shoesDetailsList->at(i).getColor()
                    + QString("&") + GlobalVars::g_shoesDetailsList->at(i).getPrice()
                    + QString("&") + GlobalVars::g_shoesDetailsList->at(i).getStock();

        }
        emit signalSendMsgToClient(buyerID, msg);
    }else
    {
        QString msg = QString(CMD_GetShoesDetails_F) + QString("#?|") + buyerID + QString("|") + QString("无详情信息！");
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
void MsgProc::parseBuyerViewShopCart(QString buyerID)
{
    //处理P#buyerID
    ExecSQL::selectShopCartInfoForID(buyerID);
    if(!GlobalVars::g_shopCartList->isEmpty())
    {
        QString msg = QString(CMD_ViewShopCart_P) + QString("#!");
        for(int i = 0; i < GlobalVars::g_shopCartList->count(); i++)
        {
            msg += QString("|")
                    + GlobalVars::g_shopCartList->at(i).getID()
                    + QString("&") + GlobalVars::g_shopCartList->at(i).getDetailID()
                    + QString("&") + GlobalVars::g_shopCartList->at(i).getCount();
        }
        emit signalSendMsgToClient(buyerID, msg);
    }else
    {
        QString msg = QString(CMD_ViewShopCart_P) + QString("#?") + buyerID + QString("没有查询到相关信息");
        emit signalSendMsgToClient(buyerID, msg);
    }

}
void MsgProc::parseBuyerGetShoesDetailsFromDetailsID(QString date)
{
    //处理buyerid|shoesDetailsID}
    QStringList list = date.split("|");
    QString buyerID = list.at(0);
    QString shoesDetailsID = list.at(1);
    ExecSQL::selectShoesDetailsForID(shoesDetailsID);
    if(!GlobalVars::g_shoesDetailsList->isEmpty())
    {
        QString msg = QString(CMD_GetShoesDetailFromDetailsID_f) + QString("#!|") + buyerID;
        for(int i = 0; i < GlobalVars::g_shoesDetailsList->count(); i++)
        {
            msg += QString("|")
                    + GlobalVars::g_shoesDetailsList->at(i).getID()
                    + QString("&") + GlobalVars::g_shoesDetailsList->at(i).getShoesID()
                    + QString("&") + GlobalVars::g_shoesDetailsList->at(i).getPhotoID()
                    + QString("&") + GlobalVars::g_shoesDetailsList->at(i).getSize()
                    + QString("&") + GlobalVars::g_shoesDetailsList->at(i).getColor()
                    + QString("&") + GlobalVars::g_shoesDetailsList->at(i).getPrice()
                    + QString("&") + GlobalVars::g_shoesDetailsList->at(i).getStock();
        }
        emit signalSendMsgToClient(buyerID, msg);
    }else
    {
        QString msg = QString(CMD_GetShoesDetailFromDetailsID_f) + QString("#?") + buyerID + QString("没有查询到相关信息");
        emit signalSendMsgToClient(buyerID, msg);
    }

}
void MsgProc::parseBuyerGetOrder(QString buyerID)
{
    //处理buyerid

    ExecSQL::selectOrderInfoForBuyerID(buyerID);
    if(!GlobalVars::g_orderInfoList->isEmpty())
    {
        QString msg = QString(CMD_GetOrder_O) + QString("#!|") + buyerID;
        for(int i = 0; i < GlobalVars::g_orderInfoList->count(); i++)
        {
            msg += QString("|")
                    + GlobalVars::g_orderInfoList->at(i).getID()
                    + QString("&") + GlobalVars::g_orderInfoList->at(i).getBuyID()
                    + QString("&") + GlobalVars::g_orderInfoList->at(i).getDetailID()
                    + QString("&") + GlobalVars::g_orderInfoList->at(i).getCount()
                    + QString("&") + GlobalVars::g_orderInfoList->at(i).getState()
                    + QString("&") + GlobalVars::g_orderInfoList->at(i).getCreateDate()
                    + QString("&") + GlobalVars::g_orderInfoList->at(i).getDeliveryDate()
                    + QString("&") + GlobalVars::g_orderInfoList->at(i).getFinishDate();
        }
        emit signalSendMsgToClient(buyerID, msg);
    }else
    {
        QString msg = QString(CMD_GetOrder_O) + QString("#?") + buyerID + QString("没有查询到相关信息");
        emit signalSendMsgToClient(buyerID, msg);
    }

}
void MsgProc::parseBuyerGetShoesDetailsByOrder(QString data)
{
    ////处理buyerid|orderID|shoesDetailsID}    CMD_GetShoesDetailByOrder_o
    QStringList list = data.split("|");
    QString buyerID = list.at(0);
    QString orderID = list.at(1);
    QString shoesDetailsID = list.at(2);
    ExecSQL::selectShoesDetailsForID(shoesDetailsID);
    if(!GlobalVars::g_shoesDetailsList->isEmpty())
    {
        QString msg = QString(CMD_GetShoesDetailByOrder_o) + QString("#!|") + buyerID + QString("|") + orderID;
        for(int i = 0; i < GlobalVars::g_shoesDetailsList->count(); i++)
        {
            msg += QString("|")
                    + GlobalVars::g_shoesDetailsList->at(i).getID()
                    + QString("&") + GlobalVars::g_shoesDetailsList->at(i).getShoesID()
                    + QString("&") + GlobalVars::g_shoesDetailsList->at(i).getPhotoID()
                    + QString("&") + GlobalVars::g_shoesDetailsList->at(i).getSize()
                    + QString("&") + GlobalVars::g_shoesDetailsList->at(i).getColor()
                    + QString("&") + GlobalVars::g_shoesDetailsList->at(i).getPrice()
                    + QString("&") + GlobalVars::g_shoesDetailsList->at(i).getStock();
        }
        emit signalSendMsgToClient(buyerID, msg);
    }else
    {
        QString msg = QString(CMD_GetShoesDetailByOrder_o) + QString("#?") + buyerID + QString("没有查询到相关信息");
        emit signalSendMsgToClient(buyerID, msg);
    }
}
void MsgProc::parsaeBuyerCommitOrderInfo(QString data)
{
    //c# MH-011|O-20210113203946&MH-011&D-0001&1&已付款&2021-01-13 20:39:46&null&null
    QStringList list = data.split("|");
    QString buyerID = list.at(0);
    QString orderInfo = list.at(1);

    QStringList infoList = orderInfo.split("&");
    OrderInfo info(infoList.at(0), infoList.at(1), infoList.at(2), infoList.at(3), infoList.at(4), infoList.at(5), infoList.at(6), infoList.at(7));
    if(ExecSQL::insertOrderInfo(info))
    {
        QString msg = QString(CMD_CommitOrderInfo_c) + QString("#!|") + buyerID;
        emit signalSendMsgToClient(buyerID, msg);
    }else
    {
        QString msg = QString(CMD_CommitOrderInfo_c) + QString("#?|") + buyerID + QString("|订单提交失败！");
        emit signalSendMsgToClient(buyerID, msg);

    }
}
void MsgProc::parseBuyerAddToShopCart(QString data)
{
    //{A#  buyerid|shopCartInfo}
    QStringList list = data.split("|");
    QString buyerID = list.at(0);
    QString shopCartInfo = list.at(1);
    QStringList infoList = shopCartInfo.split("&");
    ShopCart info(infoList.at(0), infoList.at(1), infoList.at(2));

    ExecSQL::selectShopCartInfoForIDAndDetailsID(info.getID(),info.getDetailID());
    if(GlobalVars::g_shopCartList->isEmpty())
    {
        ExecSQL::insertShopCart(info);
        QString msg = QString(CMD_AddToShopCart_p) + QString("#!|") + buyerID + QString("|添加购物车成功！");
        emit signalSendMsgToClient(buyerID, msg);
    }else
    {
        QString count = QString::number(GlobalVars::g_shopCartList->at(0).getCount().toInt() + info.getCount().toInt());
        ExecSQL::modifyShopCartInfoCount(info.getID(), info.getDetailID(), count);
        QString msg = QString(CMD_AddToShopCart_p) + QString("#!|") + buyerID + QString("|购物车商品数量增加！");
        emit signalSendMsgToClient(buyerID, msg);
    }
    //ExecSQL::insertShopCart()
}
void MsgProc::parseBuyerGetBuyerInfo(QString buyerID)
{
    //B#MH-011
    ExecSQL::selectBuyerInfoForID(buyerID);
    if(!GlobalVars::g_buyerInfoList->isEmpty())
    {
        QString sendMsg = QString(CMD_GetBuyerInfo_B) + QString("#!|") + buyerID +QString("|") +
                GlobalVars::g_buyerInfoList->at(0).getID() + QString("&") +
                GlobalVars::g_buyerInfoList->at(0).getName() + QString("&") +
                GlobalVars::g_buyerInfoList->at(0).getTel() + QString("&") +
                GlobalVars::g_buyerInfoList->at(0).getAddress();
        emit signalSendMsgToClient(buyerID, sendMsg);
    }else
    {
        QString sendMsg = QString(CMD_GetBuyerInfo_B) + QString("#?|") + buyerID +QString("|") + QString("未查找到相关用户信息");
        emit signalSendMsgToClient(buyerID, sendMsg);
    }

}
