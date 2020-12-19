#include "shopcartms.h"
#include "ui_shopcartms.h"
#include "globalvars.h"
#include "execsql.h"

ShopCartMS::ShopCartMS(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShopCartMS)
{
    ui->setupUi(this);

    m_searchCondition = SearchNone;
    ui->le_condition->setEnabled(false);
    on_pb_search_clicked();

    ui->le_id->setEnabled(false);
    ui->le_detailID->setEnabled(false);
    ui->le_count->setEnabled(false);

    m_operationType = operationNone;

    ui->pb_add->setEnabled(true);
    ui->pb_delete->setEnabled(true);
    ui->pb_modify->setEnabled(true);
    ui->pb_cancel->setEnabled(false);
    ui->pb_ensure->setEnabled(false);
}

ShopCartMS::~ShopCartMS()
{
    delete ui;
}

void ShopCartMS::updateTableInfo(void)
{
    //设置表格行列
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(3);  //设置列数
    ui->tableWidget->setRowCount(GlobalVars::g_shopCartList->count()); //设置行数

    //设置表头信息
    QStringList headers;
    headers << "购物车编号" << "商品详情编号" << "商品数量" ;
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    for(int i = 0; i < GlobalVars::g_shopCartList->count(); i++)
    {
        //每个表格的小框相当于一个小界面
        QTableWidgetItem *item = new QTableWidgetItem(GlobalVars::g_shopCartList->at(i).getID());
        ui->tableWidget->setItem(i, 0, item);    //setItem(行, 列, item);
        item = new QTableWidgetItem(GlobalVars::g_shopCartList->at(i).getDetailID());
        ui->tableWidget->setItem(i, 1, item);
        item = new QTableWidgetItem(GlobalVars::g_shopCartList->at(i).getCount());
        ui->tableWidget->setItem(i, 2, item);
    }
}

void ShopCartMS::on_cb_condition_currentIndexChanged(int index)
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

void ShopCartMS::on_pb_search_clicked()
{
    if(m_searchCondition == SearchNone)
    {
        ExecSQL::selectAllShopCart();
    }else if(m_searchCondition == SearchId)
    {
        ExecSQL::selectShopCartInfoForID(ui->le_condition->text());
    }else if(m_searchCondition == SearchDetailID)
    {
        ExecSQL::selectShopCartInfoForDatailID(ui->le_condition->text());
    }else if(m_searchCondition == SearchCount)
    {
        ExecSQL::selectShopCartInfoForCount(ui->le_condition->text());
    }
    updateTableInfo();
}

void ShopCartMS::on_tableWidget_clicked(const QModelIndex &index)
{
    m_operationIndex = index;
    ui->le_id->setText(GlobalVars::g_shopCartList->at(index.row()).getID());
    ui->le_detailID->setText(GlobalVars::g_shopCartList->at(index.row()).getDetailID());
    ui->le_count->setText(GlobalVars::g_shopCartList->at(index.row()).getCount());
}

void ShopCartMS::on_pb_modify_clicked()
{
    m_operationType = operationModify;
    ui->le_id->setEnabled(false);
    ui->le_detailID->setEnabled(true);
    ui->le_count->setEnabled(true);


    ui->pb_add->setEnabled(true);
    ui->pb_delete->setEnabled(true);
    ui->pb_modify->setEnabled(false);
    ui->pb_cancel->setEnabled(true);
    ui->pb_ensure->setEnabled(true);
}

void ShopCartMS::on_pb_delete_clicked()
{
    m_operationType = operationDel;
    ui->le_id->setEnabled(false);
    ui->le_detailID->setEnabled(false);
    ui->le_count->setEnabled(false);


    ui->pb_add->setEnabled(true);
    ui->pb_delete->setEnabled(false);
    ui->pb_modify->setEnabled(true);
    ui->pb_cancel->setEnabled(true);
    ui->pb_ensure->setEnabled(true);
}

void ShopCartMS::on_pb_add_clicked()
{
    m_operationType = operationAdd;
    ui->le_id->setEnabled(true);
    ui->le_detailID->setEnabled(true);
    ui->le_count->setEnabled(true);

    ui->pb_add->setEnabled(false);
    ui->pb_delete->setEnabled(true);
    ui->pb_modify->setEnabled(true);
    ui->pb_cancel->setEnabled(true);
    ui->pb_ensure->setEnabled(true);
}

void ShopCartMS::on_pb_cancel_clicked()
{
    m_operationType = operationNone;
    ui->le_id->setText(GlobalVars::g_shopCartList->at(m_operationIndex.row()).getID());
    ui->le_detailID->setText(GlobalVars::g_shopCartList->at(m_operationIndex.row()).getDetailID());
    ui->le_count->setText(GlobalVars::g_shopCartList->at(m_operationIndex.row()).getCount());



    ui->le_id->setEnabled(false);
    ui->le_detailID->setEnabled(false);
    ui->le_count->setEnabled(false);


    ui->pb_add->setEnabled(true);
    ui->pb_delete->setEnabled(true);
    ui->pb_modify->setEnabled(true);
    ui->pb_cancel->setEnabled(false);
    ui->pb_ensure->setEnabled(false);
}

void ShopCartMS::on_pb_ensure_clicked()
{
    if(m_operationType == operationNone)
    {

    }else if(m_operationType == operationDel)
    {
        ExecSQL::deleteShopCart(ui->le_id->text());
        on_pb_search_clicked();
        m_operationIndex = ui->tableWidget->indexAt(QPoint(1,1));
    }else if(m_operationType == operationAdd)
    {
        ShopCart info(ui->le_id->text(),ui->le_detailID->text(),ui->le_count->text());
        ExecSQL::insertShopCart(info);
        on_pb_search_clicked();
    }else if(m_operationType == operationModify)
    {
        int row = m_operationIndex.row();
        if(ui->le_detailID->text() != GlobalVars::g_shopCartList->at(row).getDetailID())
        {
            ExecSQL::modifyShopCartInfoDatailID(ui->le_id->text(),ui->le_detailID->text());
            ExecSQL::selectAllShopCart();
        }
        if(ui->le_count->text() != GlobalVars::g_shopCartList->at(row).getCount())
        {
            ExecSQL::modifyShopCartInfoCount(ui->le_id->text(),ui->le_detailID->text(),ui->le_count->text());
            ExecSQL::selectAllShopCart();
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
    ui->le_detailID->setEnabled(false);
    ui->le_count->setEnabled(false);

}
