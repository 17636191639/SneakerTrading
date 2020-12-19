#include "sellerms.h"
#include "ui_sellerms.h"

#include "globalvars.h"
#include "execsql.h"

SellerMS::SellerMS(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SellerMS)
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

SellerMS::~SellerMS()
{
    delete ui;
}
void SellerMS::updateTableInfo(void)
{
    //设置表格行列
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(4);  //设置列数
    ui->tableWidget->setRowCount(GlobalVars::g_sellerInfoList->count()); //设置行数

    //设置表头信息
    QStringList headers;
    headers << "账号" << "姓名" << "电话" << "地址";
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    for(int i = 0; i < GlobalVars::g_sellerInfoList->count(); i++)
    {
        //每个表格的小框相当于一个小界面
        QTableWidgetItem *item = new QTableWidgetItem(GlobalVars::g_sellerInfoList->at(i).getID());
        ui->tableWidget->setItem(i, 0, item);    //setItem(行, 列, item);
        item = new QTableWidgetItem(GlobalVars::g_sellerInfoList->at(i).getName());
        ui->tableWidget->setItem(i, 1, item);
        item = new QTableWidgetItem(GlobalVars::g_sellerInfoList->at(i).getTel());
        ui->tableWidget->setItem(i, 2, item);
        item = new QTableWidgetItem(GlobalVars::g_sellerInfoList->at(i).getAddress());
        ui->tableWidget->setItem(i, 3, item);
    }
}

void SellerMS::on_cb_condition_currentIndexChanged(int index)
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

void SellerMS::on_pb_search_clicked()
{
    if(m_searchCondition == SearchNone)
    {
        ExecSQL::selectAllSellers();
    }else if(m_searchCondition == SearchId)
    {
        ExecSQL::selectSellerInfoForID(ui->le_condition->text());
    }else if(m_searchCondition == SearchName)
    {
        ExecSQL::selectSellerInfoForName(ui->le_condition->text());
    }else if(m_searchCondition == SearchAddress)
    {
        ExecSQL::selectSellerInfoForAddress(ui->le_condition->text());
    }
    updateTableInfo();
}

void SellerMS::on_tableWidget_clicked(const QModelIndex &index)
{
    m_operationIndex = index;
    ui->le_id->setText(GlobalVars::g_sellerInfoList->at(index.row()).getID());
    ui->le_name->setText(GlobalVars::g_sellerInfoList->at(index.row()).getName());
    ui->le_tel->setText(GlobalVars::g_sellerInfoList->at(index.row()).getTel());
    ui->le_address->setText(GlobalVars::g_sellerInfoList->at(index.row()).getAddress());
}

void SellerMS::on_pb_modify_clicked()
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

void SellerMS::on_pb_delete_clicked()
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

void SellerMS::on_pb_add_clicked()
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

void SellerMS::on_pb_cancel_clicked()
{
    m_operationType = operationNone;
    ui->le_id->setText(GlobalVars::g_sellerInfoList->at(m_operationIndex.row()).getID());
    ui->le_name->setText(GlobalVars::g_sellerInfoList->at(m_operationIndex.row()).getName());
    ui->le_tel->setText(GlobalVars::g_sellerInfoList->at(m_operationIndex.row()).getTel());
    ui->le_address->setText(GlobalVars::g_sellerInfoList->at(m_operationIndex.row()).getAddress());

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

void SellerMS::on_pb_ensure_clicked()
{
    if(m_operationType == operationNone)
    {

    }else if(m_operationType == operationDel)
    {
        ExecSQL::deleteSellerInfo(ui->le_id->text());
        on_pb_search_clicked();
    }else if(m_operationType == operationAdd)
    {
        SellerInfo info(ui->le_id->text(),ui->le_name->text(),ui->le_tel->text(),ui->le_address->text());
        ExecSQL::insertSellerInfo(info);
        on_pb_search_clicked();
    }else if(m_operationType == operationModify)
    {
        if(ui->le_name->text() != GlobalVars::g_sellerInfoList->at(m_operationIndex.row()).getName())
        {
            ExecSQL::modifySellerInfoName(ui->le_id->text(),ui->le_name->text());
            ExecSQL::selectAllSellers();
        }
        if(ui->le_tel->text() != GlobalVars::g_sellerInfoList->at(m_operationIndex.row()).getTel())
        {
            ExecSQL::modifySellerInfoTel(ui->le_id->text(),ui->le_tel->text());
            ExecSQL::selectAllSellers();
        }
        if(ui->le_address->text() != GlobalVars::g_sellerInfoList->at(m_operationIndex.row()).getAddress())
        {
            ExecSQL::modifySellerInfoAddress(ui->le_id->text(),ui->le_address->text());
            ExecSQL::selectAllSellers();
        }
        updateTableInfo();

    }

    ui->pb_add->setEnabled(true);
    ui->pb_delete->setEnabled(true);
    ui->pb_modify->setEnabled(true);
    ui->pb_cancel->setEnabled(false);
    ui->pb_ensure->setEnabled(false);
}
