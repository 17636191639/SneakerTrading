#include "msgproc.h"
#include "globalvars.h"
#include <QDebug>
#include "execsql.h"

MsgProc::MsgProc(QObject *parent) :
    QThread(parent)
{
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
