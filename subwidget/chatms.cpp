#include "chatms.h"
#include "ui_chatms.h"
#include "globalvars.h"
#include "execsql.h"

ChatMS::ChatMS(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatMS)
{
    ui->setupUi(this);

    m_searchCondition = SearchNone;
    ui->le_condition->setEnabled(false);

    ui->le_id->setEnabled(false);
    ui->le_buyerid->setEnabled(false);
    ui->le_sellerid->setEnabled(false);
    ui->le_photoid->setEnabled(false);
    ui->le_content->setEnabled(false);
//    ui->le_photocount->setEnabled(false);
//    ui->le_photopath->setEnabled(false);
    ui->le_date->setEnabled(false);

    on_pb_search_clicked();
    m_operationType = operationNone;

    ui->pb_add->setEnabled(true);
    ui->pb_delete->setEnabled(true);
    ui->pb_modify->setEnabled(true);
    ui->pb_cancel->setEnabled(false);
    ui->pb_ensure->setEnabled(false);


}

ChatMS::~ChatMS()
{
    delete ui;
}

void ChatMS::updateTableInfo(void)
{
    //设置表格行列
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(6);  //设置列数
    ui->tableWidget->setRowCount(GlobalVars::g_chatInfoList->count()); //设置行数

    //设置表头信息
    QStringList headers;
    headers << "记录编号" << "买家账号" << "卖家账号" << "图片编号" << "聊天内容" << "聊天日期";
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    for(int i = 0; i < GlobalVars::g_chatInfoList->count(); i++)
    {
        //每个表格的小框相当于一个小界面
        QTableWidgetItem *item = new QTableWidgetItem(GlobalVars::g_chatInfoList->at(i).getID());
        ui->tableWidget->setItem(i, 0, item);    //setItem(行, 列, item);
        item = new QTableWidgetItem(GlobalVars::g_chatInfoList->at(i).getBuyerID());
        ui->tableWidget->setItem(i, 1, item);
        item = new QTableWidgetItem(GlobalVars::g_chatInfoList->at(i).getSellerID());
        ui->tableWidget->setItem(i, 2, item);
        item = new QTableWidgetItem(GlobalVars::g_chatInfoList->at(i).getPhotoID());
        ui->tableWidget->setItem(i, 3, item);
        item = new QTableWidgetItem(GlobalVars::g_chatInfoList->at(i).getContent());
        ui->tableWidget->setItem(i, 4, item);
//        item = new QTableWidgetItem(GlobalVars::g_chatInfoList->at(i).getPhotoCount());
//        ui->tableWidget->setItem(i, 4, item);
//        item = new QTableWidgetItem(GlobalVars::g_chatInfoList->at(i).getPhotoPath());
//        ui->tableWidget->setItem(i, 5, item);
        item = new QTableWidgetItem(GlobalVars::g_chatInfoList ->at(i).getDate());
        ui->tableWidget->setItem(i, 5, item);
    }
}

void ChatMS::on_cb_condition_currentIndexChanged(int index)
{
    m_searchCondition = index;
    if(m_searchCondition == SearchNone)
    {
        ui->le_condition->setEnabled(false);
    }else
    {
       ui->le_condition->setEnabled(true);
    }
}

void ChatMS::on_pb_search_clicked()
{
    if(m_searchCondition == SearchNone)
    {
        ExecSQL::selectAllChats();
    }else if(m_searchCondition == SearchId)
    {
        ExecSQL::selectChatInfoForID(ui->le_condition->text());
    }else if(m_searchCondition == SearchBuyerID)
    {
        ExecSQL::selectChatInfoForBuyerID(ui->le_condition->text());
    }else if(m_searchCondition == SearchSellerID)
    {
        ExecSQL::selectChatInfoForSellerID(ui->le_condition->text());
    }else if(m_searchCondition == SearchPhotoID)
    {
        ExecSQL::selectChatInfoForPhotoID(ui->le_condition->text());
    }else if(m_searchCondition == SearchContent)
    {
        ExecSQL::selectChatInfoForContent(ui->le_condition->text());
    }else if(m_searchCondition == SearchDate)
    {
        ExecSQL::selectChatInfoForDate(ui->le_condition->text());
    }
    updateTableInfo();
}

void ChatMS::on_tableWidget_clicked(const QModelIndex &index)
{
    m_operationIndex = index;
    ui->le_id->setText(GlobalVars::g_chatInfoList->at(index.row()).getID());
    ui->le_buyerid->setText(GlobalVars::g_chatInfoList->at(index.row()).getBuyerID());
    ui->le_sellerid->setText(GlobalVars::g_chatInfoList->at(index.row()).getSellerID());
    ui->le_photoid->setText(GlobalVars::g_chatInfoList->at(index.row()).getPhotoID());
    ui->le_content->setText(GlobalVars::g_chatInfoList->at(index.row()).getContent());
//    ui->le_photocount->setText(GlobalVars::g_chatInfoList->at(index.row()).getPhotoCount());
//    ui->le_photopath->setText(GlobalVars::g_chatInfoList->at(index.row()).getPhotoPath());
    ui->le_date->setText(GlobalVars::g_chatInfoList->at(index.row()).getDate());
}

void ChatMS::on_pb_modify_clicked()
{
    m_operationType = operationModify;
    ui->le_id->setEnabled(false);
    ui->le_buyerid->setEnabled(true);
    ui->le_sellerid->setEnabled(true);

    ui->le_content->setEnabled(true);
//    ui->le_photocount->setEnabled(true);
//    ui->le_photopath->setEnabled(true);
    ui->le_date->setEnabled(true);


    ui->pb_add->setEnabled(true);
    ui->pb_delete->setEnabled(true);
    ui->pb_modify->setEnabled(false);
    ui->pb_cancel->setEnabled(true);
    ui->pb_ensure->setEnabled(true);
}

void ChatMS::on_pb_delete_clicked()
{
    m_operationType = operationDel;

    ui->pb_add->setEnabled(true);
    ui->pb_delete->setEnabled(false);
    ui->pb_modify->setEnabled(true);
    ui->pb_cancel->setEnabled(true);
    ui->pb_ensure->setEnabled(true);
}

void ChatMS::on_pb_add_clicked()
{
    m_operationType = operationAdd;
    ui->le_id->setEnabled(true);
    ui->le_buyerid->setEnabled(true);
    ui->le_sellerid->setEnabled(true);

    ui->le_content->setEnabled(true);
//    ui->le_photocount->setEnabled(true);
//    ui->le_photopath->setEnabled(true);
    ui->le_date->setEnabled(true);

    ui->pb_add->setEnabled(false);
    ui->pb_delete->setEnabled(true);
    ui->pb_modify->setEnabled(true);
    ui->pb_cancel->setEnabled(true);
    ui->pb_ensure->setEnabled(true);
}

void ChatMS::on_pb_cancel_clicked()
{
    m_operationType = operationNone;
    if(!m_operationIndex.isValid())
    {
        ui->le_id->setText(GlobalVars::g_chatInfoList->at(m_operationIndex.row()).getID());
        ui->le_buyerid->setText(GlobalVars::g_chatInfoList->at(m_operationIndex.row()).getBuyerID());
        ui->le_sellerid->setText(GlobalVars::g_chatInfoList->at(m_operationIndex.row()).getSellerID());
        ui->le_photoid->setText(GlobalVars::g_chatInfoList->at(m_operationIndex.row()).getPhotoID());
        ui->le_content->setText(GlobalVars::g_chatInfoList->at(m_operationIndex.row()).getContent());
    //    ui->le_photocount->setText(GlobalVars::g_chatInfoList->at(m_operationIndex.row()).getPhotoCount());
    //    ui->le_photopath->setText(GlobalVars::g_chatInfoList->at(m_operationIndex.row()).getPhotoPath());
        ui->le_date->setText(GlobalVars::g_chatInfoList->at(m_operationIndex.row()).getDate());
    }




    ui->le_id->setEnabled(false);
    ui->le_buyerid->setEnabled(false);
    ui->le_sellerid->setEnabled(false);
    ui->le_photoid->setEnabled(false);
    ui->le_content->setEnabled(false);
//    ui->le_photocount->setEnabled(false);
//    ui->le_photopath->setEnabled(false);
    ui->le_date->setEnabled(false);


    ui->pb_add->setEnabled(true);
    ui->pb_delete->setEnabled(true);
    ui->pb_modify->setEnabled(true);
    ui->pb_cancel->setEnabled(false);
    ui->pb_ensure->setEnabled(false);
}

void ChatMS::on_pb_ensure_clicked()
{
    if(m_operationType == operationNone)
    {

    }else if(m_operationType == operationDel)
    {
        ExecSQL::deleteChatInfo(ui->le_id->text());
        on_pb_search_clicked();
        m_operationIndex = ui->tableWidget->indexAt(QPoint(1,1));
    }else if(m_operationType == operationAdd)
    {
        ChatInfo info(ui->le_id->text(),ui->le_buyerid->text(),ui->le_sellerid->text(),
                      ui->le_photoid->text(), ui->le_content->text(), ui->le_date->text());
        ExecSQL::insertChatInfo(info);
        on_pb_search_clicked();
    }else if(m_operationType == operationModify)
    {
        int row = m_operationIndex.row();
        if(ui->le_buyerid->text() != GlobalVars::g_chatInfoList->at(row).getBuyerID())
        {
            ExecSQL::modifyChatInfoBuyerID(ui->le_id->text(),ui->le_buyerid->text());
            ExecSQL::selectAllChats();
        }
        if(ui->le_sellerid->text() != GlobalVars::g_chatInfoList->at(row).getSellerID())
        {
            ExecSQL::modifyChatInfoBuyerID(ui->le_id->text(),ui->le_sellerid->text());
            ExecSQL::selectAllChats();
        }
        if(ui->le_photoid->text() != GlobalVars::g_chatInfoList->at(row).getPhotoID())
        {
            ExecSQL::modifyChatInfoPhotoID(ui->le_id->text(),ui->le_photoid->text());
            ExecSQL::selectAllChats();
        }
        if(ui->le_content->text() != GlobalVars::g_chatInfoList->at(row).getContent())
        {
            ExecSQL::modifyChatInfoContent(ui->le_id->text(), ui->le_content->text());
            ExecSQL::selectAllChats();
        }
//        if(ui->le_photocount->text() != GlobalVars::g_chatInfoList->at(row).getPhotoCount())
//        {
//            ExecSQL::modifyChatInfoPhotoCount(ui->le_id->text(), ui->le_photocount->text());
//            ExecSQL::selectAllChats();
//        }
//        if(ui->le_photopath->text() != GlobalVars::g_chatInfoList->at(row).getPhotoPath())
//        {
//            ExecSQL::modifyChatInfoPhotoPath(ui->le_id->text(), ui->le_photopath->text());
//            ExecSQL::selectAllChats();
//        }
        if(ui->le_date->text() != GlobalVars::g_chatInfoList->at(row).getDate())
        {
            ExecSQL::modifyChatInfoDate(ui->le_id->text(), ui->le_date->text());
            ExecSQL::selectAllChats();
        }
        updateTableInfo();
    }


    ui->pb_add->setEnabled(true);
    ui->pb_delete->setEnabled(true);
    ui->pb_modify->setEnabled(true);
    ui->pb_cancel->setEnabled(false);
    ui->pb_ensure->setEnabled(false);

    ui->le_id->setEnabled(false);
    ui->le_buyerid->setEnabled(false);
    ui->le_sellerid->setEnabled(false);
    ui->le_photoid->setEnabled(false);
    ui->le_content->setEnabled(false);
//    ui->le_photocount->setEnabled(false);
//    ui->le_photopath->setEnabled(false);
    ui->le_date->setEnabled(false);
}
