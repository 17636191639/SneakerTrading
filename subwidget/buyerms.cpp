#include "buyerms.h"
#include "ui_buyerms.h"
#include "globalvars.h"
#include "execsql.h"

BuyerMS::BuyerMS(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BuyerMS)
{
    ui->setupUi(this);

    m_searchCondition = SearchNone;
    ui->le_condition->setEnabled(false);
    on_pb_search_clicked();

    ui->le_id->setEnabled(false);
    ui->le_name->setEnabled(false);
    ui->le_tel->setEnabled(false);
    ui->le_address->setEnabled(false);
    ui->cb_province->setEnabled(false);
    ui->cb_city->setEnabled(false);
    ui->cb_region->setEnabled(false);

    m_operationType = operationNone;

    ui->pb_add->setEnabled(true);
    ui->pb_delete->setEnabled(true);
    ui->pb_modify->setEnabled(true);
    ui->pb_cancel->setEnabled(false);
    ui->pb_ensure->setEnabled(false);
}

BuyerMS::~BuyerMS()
{
    delete ui;
}
void BuyerMS::updateTableInfo(void)
{
    //设置表格行列
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(4);  //设置列数
    ui->tableWidget->setRowCount(GlobalVars::g_buyerInfoList->count()); //设置行数

    //设置表头信息
    QStringList headers;
    headers << "账号" << "姓名" << "电话" << "地址";
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    for(int i = 0; i < GlobalVars::g_buyerInfoList->count(); i++)
    {
        //每个表格的小框相当于一个小界面
        QTableWidgetItem *item = new QTableWidgetItem(GlobalVars::g_buyerInfoList->at(i).getID());
        ui->tableWidget->setItem(i, 0, item);    //setItem(行, 列, item);
        item = new QTableWidgetItem(GlobalVars::g_buyerInfoList->at(i).getName());
        ui->tableWidget->setItem(i, 1, item);
        item = new QTableWidgetItem(GlobalVars::g_buyerInfoList->at(i).getTel());
        ui->tableWidget->setItem(i, 2, item);
        item = new QTableWidgetItem(GlobalVars::g_buyerInfoList->at(i).getAddress());
        ui->tableWidget->setItem(i, 3, item);
    }
}

void BuyerMS::on_cb_condition_currentIndexChanged(int index)
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

void BuyerMS::on_pb_search_clicked()
{
    if(m_searchCondition == SearchNone)
    {
        ExecSQL::selectAllBuyers();
    }else if(m_searchCondition == SearchId)
    {
        ExecSQL::selectBuyerInfoForID(ui->le_condition->text());
    }else if(m_searchCondition == SearchName)
    {
        ExecSQL::selectBuyerInfoForName(ui->le_condition->text());
    }else if(m_searchCondition == SearchAddress)
    {
        ExecSQL::selectBuyerInfoForAddress(ui->le_condition->text());
    }
    updateTableInfo();
}

void BuyerMS::on_tableWidget_clicked(const QModelIndex &index)
{
    m_operationIndex = index;
    ui->le_id->setText(GlobalVars::g_buyerInfoList->at(index.row()).getID());
    ui->le_name->setText(GlobalVars::g_buyerInfoList->at(index.row()).getName());
    ui->le_tel->setText(GlobalVars::g_buyerInfoList->at(index.row()).getTel());
    ui->le_address->setText(GlobalVars::g_buyerInfoList->at(index.row()).getAddress());
}

void BuyerMS::on_pb_modify_clicked()
{
    m_operationType = operationModify;
    ui->le_id->setEnabled(false);
    ui->le_name->setEnabled(true);
    ui->le_tel->setEnabled(true);
    ui->le_address->setEnabled(true);

    ui->pb_add->setEnabled(true);
    ui->pb_delete->setEnabled(true);
    ui->pb_modify->setEnabled(false);
    ui->pb_cancel->setEnabled(true);
    ui->pb_ensure->setEnabled(true);
}

void BuyerMS::on_pb_delete_clicked()
{
    m_operationType = operationDel;
    ui->le_id->setEnabled(false);
    ui->le_name->setEnabled(false);
    ui->le_tel->setEnabled(false);
    ui->le_address->setEnabled(false);

    ui->pb_add->setEnabled(true);
    ui->pb_delete->setEnabled(false);
    ui->pb_modify->setEnabled(true);
    ui->pb_cancel->setEnabled(true);
    ui->pb_ensure->setEnabled(true);
}

void BuyerMS::on_pb_add_clicked()
{
    m_operationType = operationAdd;
    ui->le_id->setEnabled(true);
    ui->le_name->setEnabled(true);
    ui->le_tel->setEnabled(true);
    ui->le_address->setEnabled(true);

    ui->pb_add->setEnabled(false);
    ui->pb_delete->setEnabled(true);
    ui->pb_modify->setEnabled(true);
    ui->pb_cancel->setEnabled(true);
    ui->pb_ensure->setEnabled(true);
}

void BuyerMS::on_pb_cancel_clicked()
{
    m_operationType = operationNone;
    ui->le_id->setText(GlobalVars::g_buyerInfoList->at(m_operationIndex.row()).getID());
    ui->le_name->setText(GlobalVars::g_buyerInfoList->at(m_operationIndex.row()).getName());
    ui->le_tel->setText(GlobalVars::g_buyerInfoList->at(m_operationIndex.row()).getTel());
    ui->le_address->setText(GlobalVars::g_buyerInfoList->at(m_operationIndex.row()).getAddress());

    ui->le_id->setEnabled(false);
    ui->le_name->setEnabled(false);
    ui->le_tel->setEnabled(false);
    ui->le_address->setEnabled(false);

    ui->pb_add->setEnabled(true);
    ui->pb_delete->setEnabled(true);
    ui->pb_modify->setEnabled(true);
    ui->pb_cancel->setEnabled(false);
    ui->pb_ensure->setEnabled(false);
}

void BuyerMS::on_pb_ensure_clicked()
{
    if(m_operationType == operationNone)
    {

    }else if(m_operationType == operationDel)
    {
        ExecSQL::deleteBuyerInfo(ui->le_id->text());
        on_pb_search_clicked();
    }else if(m_operationType == operationAdd)
    {
        BuyerInfo info(ui->le_id->text(),ui->le_name->text(),ui->le_tel->text(),ui->le_address->text());
        ExecSQL::insertBuyerInfo(info);
        on_pb_search_clicked();
    }else if(m_operationType == operationModify)
    {
        if(ui->le_name->text() != GlobalVars::g_buyerInfoList->at(m_operationIndex.row()).getName())
        {
            ExecSQL::modifyBuyerInfoName(ui->le_id->text(),ui->le_name->text());
        }
        if(ui->le_tel->text() != GlobalVars::g_buyerInfoList->at(m_operationIndex.row()).getTel())
        {
            ExecSQL::modifyBuyerInfoTel(ui->le_id->text(),ui->le_tel->text());
        }
        if(ui->le_address->text() != GlobalVars::g_buyerInfoList->at(m_operationIndex.row()).getAddress())
        {
            ExecSQL::modifyBuyerInfoAddress(ui->le_id->text(),ui->le_address->text());
        }
        on_pb_search_clicked();
    }
    //updateTableInfo();

    ui->pb_add->setEnabled(true);
    ui->pb_delete->setEnabled(true);
    ui->pb_modify->setEnabled(true);
    ui->pb_cancel->setEnabled(false);
    ui->pb_ensure->setEnabled(false);
}
