#include "storems.h"
#include "ui_storems.h"
#include "globalvars.h"
#include "execsql.h"

StoreMS::StoreMS(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StoreMS)
{
    ui->setupUi(this);

    m_searchCondition = SearchNone;
    ui->le_condition->setEnabled(false);
    on_pb_search_clicked();

    ui->le_id->setEnabled(false);
    ui->le_sellerID->setEnabled(false);
    ui->le_name->setEnabled(false);
    ui->le_brand->setEnabled(false);
    ui->le_date->setEnabled(false);
    ui->le_reputation->setEnabled(false);

    m_operationType = operationNone;

    ui->pb_add->setEnabled(true);
    ui->pb_delete->setEnabled(true);
    ui->pb_modify->setEnabled(true);
    ui->pb_cancel->setEnabled(false);
    ui->pb_ensure->setEnabled(false);
}

StoreMS::~StoreMS()
{
    delete ui;
}
void StoreMS::updateTableInfo(void)
{
    //设置表格行列
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(6);  //设置列数
    ui->tableWidget->setRowCount(GlobalVars::g_storeInfoList->count()); //设置行数

    //设置表头信息
    QStringList headers;
    headers << "店铺编号" << "卖家账号" << "店铺名称" << "品牌" << "开店日期" << "信誉";
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    //ui->tableWidget->setColumnWidth(2, 300);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);//列宽匹配字长

    for(int i = 0; i < GlobalVars::g_storeInfoList->count(); i++)
    {
        //每个表格的小框相当于一个小界面
        QTableWidgetItem *item = new QTableWidgetItem(GlobalVars::g_storeInfoList->at(i).getID());
        ui->tableWidget->setItem(i, 0, item);    //setItem(行, 列, item);
        item = new QTableWidgetItem(GlobalVars::g_storeInfoList->at(i).getSellerID());
        ui->tableWidget->setItem(i, 1, item);
        item = new QTableWidgetItem(GlobalVars::g_storeInfoList->at(i).getStoreName());
        ui->tableWidget->setItem(i, 2, item);
        item = new QTableWidgetItem(GlobalVars::g_storeInfoList->at(i).getBrand());
        ui->tableWidget->setItem(i, 3, item);
        item = new QTableWidgetItem(GlobalVars::g_storeInfoList->at(i).getDate());
        ui->tableWidget->setItem(i, 4, item);
        item = new QTableWidgetItem(GlobalVars::g_storeInfoList->at(i).getReputation());
        ui->tableWidget->setItem(i, 5, item);
    }
}

void StoreMS::on_cb_condition_currentIndexChanged(int index)
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

void StoreMS::on_pb_search_clicked()
{
    if(m_searchCondition == SearchNone)
    {
        ExecSQL::selectAllStores();
    }else if(m_searchCondition == SearchId)
    {
        ExecSQL::selectStoreInfoForID(ui->le_condition->text());
    }else if(m_searchCondition == SearchName)
    {
        ExecSQL::selectStoreInfoForStoreName(ui->le_condition->text());
    }else if(m_searchCondition == SearchBrand)
    {
        ExecSQL::selectStoreInfoForBrand(ui->le_condition->text());
    }else if(m_searchCondition == SearchDate)
    {
        ExecSQL::selectStoreInfoForDate(ui->le_condition->text());
    }else if(m_searchCondition == SearchReputation)
    {
        ExecSQL::selectStoreInfoForReputation(ui->le_condition->text());
    }
    updateTableInfo();
}

void StoreMS::on_tableWidget_clicked(const QModelIndex &index)
{
    m_operationIndex = index;
    ui->le_id->setText(GlobalVars::g_storeInfoList->at(index.row()).getID());
    ui->le_sellerID->setText(GlobalVars::g_storeInfoList->at(index.row()).getSellerID());
    ui->le_name->setText(GlobalVars::g_storeInfoList->at(index.row()).getStoreName());
    ui->le_brand->setText(GlobalVars::g_storeInfoList->at(index.row()).getBrand());
    ui->le_date->setText(GlobalVars::g_storeInfoList->at(index.row()).getDate());
    ui->le_reputation->setText(GlobalVars::g_storeInfoList->at(index.row()).getReputation());
}

void StoreMS::on_pb_modify_clicked()
{
    m_operationType = operationModify;
    ui->le_id->setEnabled(false);
    ui->le_sellerID->setEnabled(true);
    ui->le_name->setEnabled(true);
    ui->le_brand->setEnabled(true);
    ui->le_date->setEnabled(true);
    ui->le_reputation->setEnabled(true);

    ui->pb_add->setEnabled(true);
    ui->pb_delete->setEnabled(true);
    ui->pb_modify->setEnabled(false);
    ui->pb_cancel->setEnabled(true);
    ui->pb_ensure->setEnabled(true);
}

void StoreMS::on_pb_delete_clicked()
{
    m_operationType = operationDel;
    ui->le_id->setEnabled(false);
    ui->le_sellerID->setEnabled(false);
    ui->le_name->setEnabled(false);
    ui->le_brand->setEnabled(false);
    ui->le_date->setEnabled(false);
    ui->le_reputation->setEnabled(false);

    ui->pb_add->setEnabled(true);
    ui->pb_delete->setEnabled(false);
    ui->pb_modify->setEnabled(true);
    ui->pb_cancel->setEnabled(true);
    ui->pb_ensure->setEnabled(true);

}

void StoreMS::on_pb_add_clicked()
{
    m_operationType = operationAdd;
    ui->le_id->setEnabled(true);
    ui->le_sellerID->setEnabled(true);
    ui->le_name->setEnabled(true);
    ui->le_brand->setEnabled(true);
    ui->le_date->setEnabled(true);
    ui->le_reputation->setEnabled(true);

    ui->pb_add->setEnabled(false);
    ui->pb_delete->setEnabled(true);
    ui->pb_modify->setEnabled(true);
    ui->pb_cancel->setEnabled(true);
    ui->pb_ensure->setEnabled(true);
}

void StoreMS::on_pb_cancel_clicked()
{
    m_operationType = operationNone;
    ui->le_id->setText(GlobalVars::g_storeInfoList->at(m_operationIndex.row()).getID());
    ui->le_sellerID->setText(GlobalVars::g_storeInfoList->at(m_operationIndex.row()).getSellerID());
    ui->le_name->setText(GlobalVars::g_storeInfoList->at(m_operationIndex.row()).getStoreName());
    ui->le_brand->setText(GlobalVars::g_storeInfoList->at(m_operationIndex.row()).getBrand());
    ui->le_date->setText(GlobalVars::g_storeInfoList->at(m_operationIndex.row()).getDate());
    ui->le_reputation->setText(GlobalVars::g_storeInfoList->at(m_operationIndex.row()).getReputation());


    ui->le_id->setEnabled(false);
    ui->le_sellerID->setEnabled(false);
    ui->le_name->setEnabled(false);
    ui->le_brand->setEnabled(false);
    ui->le_date->setEnabled(false);
    ui->le_reputation->setEnabled(false);

    ui->pb_add->setEnabled(true);
    ui->pb_delete->setEnabled(true);
    ui->pb_modify->setEnabled(true);
    ui->pb_cancel->setEnabled(false);
    ui->pb_ensure->setEnabled(false);
}

void StoreMS::on_pb_ensure_clicked()
{
    if(m_operationType == operationNone)
    {

    }else if(m_operationType == operationDel)
    {
        ExecSQL::deleteStoreInfo(ui->le_id->text());
        on_pb_search_clicked();
        m_operationIndex = ui->tableWidget->indexAt(QPoint(1,1));
    }else if(m_operationType == operationAdd)
    {
        StoreInfo info(ui->le_id->text(),ui->le_sellerID->text(),ui->le_name->text(),
                        ui->le_brand->text(), ui->le_date->text(), ui->le_reputation->text());
        ExecSQL::insertStoreInfo(info);
        on_pb_search_clicked();
    }else if(m_operationType == operationModify)
    {
        int row = m_operationIndex.row();
        if(ui->le_name->text() != GlobalVars::g_storeInfoList->at(row).getStoreName())
        {
            ExecSQL::modifyStoreInfoStoreName(ui->le_id->text(),ui->le_name->text());
            ExecSQL::selectAllStores();
        }
        if(ui->le_sellerID->text() != GlobalVars::g_storeInfoList->at(row).getSellerID())
        {
            ExecSQL::modifyStoreInfoStoreSellerID(ui->le_id->text(),ui->le_sellerID->text());
            ExecSQL::selectAllStores();
        }
        if(ui->le_brand->text() != GlobalVars::g_storeInfoList->at(row).getBrand())
        {
            ExecSQL::modifyStoreInfoBrand(ui->le_id->text(),ui->le_brand->text());
            ExecSQL::selectAllStores();
        }
        if(ui->le_date->text() != GlobalVars::g_storeInfoList->at(row).getDate())
        {
            ExecSQL::modifyStoreInfoDate(ui->le_id->text(),ui->le_date->text());
            ExecSQL::selectAllStores();
        }
        if(ui->le_reputation->text() != GlobalVars::g_storeInfoList->at(row).getReputation())
        {
            ExecSQL::modifyStoreInfoReputation(ui->le_id->text(),ui->le_reputation->text());
            ExecSQL::selectAllStores();
        }
        updateTableInfo();
        //on_pb_search_clicked();
    }


    ui->pb_add->setEnabled(true);
    ui->pb_delete->setEnabled(true);
    ui->pb_modify->setEnabled(true);
    ui->pb_cancel->setEnabled(false);
    ui->pb_ensure->setEnabled(false);

    ui->le_id->setEnabled(false);
    ui->le_sellerID->setEnabled(false);
    ui->le_name->setEnabled(false);
    ui->le_brand->setEnabled(false);
    ui->le_date->setEnabled(false);
    ui->le_reputation->setEnabled(false);
}
