#include "shoesms.h"
#include "ui_shoesms.h"
#include "globalvars.h"
#include "execsql.h"
#include <QDebug>
ShoesMS::ShoesMS(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShoesMS)
{
    ui->setupUi(this);

    m_searchCondition = SearchNone;
    ui->le_condition->setEnabled(false);
    on_pb_search_clicked();

    ui->le_id->setEnabled(false);
    ui->le_storeid->setEnabled(false);
    ui->le_name->setEnabled(false);
    ui->le_bottomprice->setEnabled(false);
    ui->le_freight->setEnabled(false);

    m_operationType = operationNone;

    ui->pb_add->setEnabled(true);
    ui->pb_delete->setEnabled(true);
    ui->pb_modify->setEnabled(true);
    ui->pb_cancel->setEnabled(false);
    ui->pb_ensure->setEnabled(false);
}

ShoesMS::~ShoesMS()
{
    delete ui;
}
void ShoesMS::updateTableInfo(void)
{
    //设置表格行列
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(5);  //设置列数
    ui->tableWidget->setRowCount(GlobalVars::g_shoesInfoList->count()); //设置行数

    //设置表头信息
    QStringList headers;
    headers << "商品编号" << "店铺编号" << "商品名称" << "最低价格" << "运费";
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->setColumnWidth(2, 300);
    for(int i = 0; i < GlobalVars::g_shoesInfoList->count(); i++)
    {
        //每个表格的小框相当于一个小界面
        QTableWidgetItem *item = new QTableWidgetItem(GlobalVars::g_shoesInfoList->at(i).getID());
        ui->tableWidget->setItem(i, 0, item);    //setItem(行, 列, item);
        item = new QTableWidgetItem(GlobalVars::g_shoesInfoList->at(i).getStoreID());
        ui->tableWidget->setItem(i, 1, item);
        item = new QTableWidgetItem(GlobalVars::g_shoesInfoList->at(i).getShoesName());
        ui->tableWidget->setItem(i, 2, item);
        item = new QTableWidgetItem(GlobalVars::g_shoesInfoList->at(i).getBottomPrice());
        ui->tableWidget->setItem(i, 3, item);
        item = new QTableWidgetItem(GlobalVars::g_shoesInfoList->at(i).getFreight());
        ui->tableWidget->setItem(i, 4, item);
    }
}

void ShoesMS::on_cb_condition_currentIndexChanged(int index)
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

void ShoesMS::on_pb_search_clicked()
{
    if(m_searchCondition == SearchNone)
    {
        ExecSQL::selectAllShoes();
    }else if(m_searchCondition == SearchId)
    {
        ExecSQL::selectShoesInfoForID(ui->le_condition->text());
    }else if(m_searchCondition == SearchName)
    {
        ExecSQL::selectShoesInfoForShoesName(ui->le_condition->text());
    }else if(m_searchCondition == SearchBottomPrice)
    {
        ExecSQL::selectShoesInfoForBottomPrice(ui->le_condition->text());
    }else if(m_searchCondition == SearchFreight)
    {
        ExecSQL::selectShoesInfoForFreight(ui->le_condition->text());
    }
    updateTableInfo();
}

void ShoesMS::on_tableWidget_clicked(const QModelIndex &index)
{
    m_operationIndex = index;
    ui->le_id->setText(GlobalVars::g_shoesInfoList->at(index.row()).getID());
    ui->le_storeid->setText(GlobalVars::g_shoesInfoList->at(index.row()).getStoreID());
    ui->le_name->setText(GlobalVars::g_shoesInfoList->at(index.row()).getShoesName());
    ui->le_bottomprice->setText(GlobalVars::g_shoesInfoList->at(index.row()).getBottomPrice());
    ui->le_freight->setText(GlobalVars::g_shoesInfoList->at(index.row()).getFreight());
}

void ShoesMS::on_pb_modify_clicked()
{
    m_operationType = operationModify;
    ui->le_id->setEnabled(false);
    ui->le_storeid->setEnabled(true);
    ui->le_name->setEnabled(true);
    ui->le_bottomprice->setEnabled(true);
    ui->le_freight->setEnabled(true);

    ui->pb_add->setEnabled(true);
    ui->pb_delete->setEnabled(true);
    ui->pb_modify->setEnabled(false);
    ui->pb_cancel->setEnabled(true);
    ui->pb_ensure->setEnabled(true);
}

void ShoesMS::on_pb_delete_clicked()
{
    m_operationType = operationDel;
    ui->le_id->setEnabled(false);
    ui->le_storeid->setEnabled(false);
    ui->le_name->setEnabled(false);
    ui->le_bottomprice->setEnabled(false);
    ui->le_freight->setEnabled(false);

    ui->pb_add->setEnabled(true);
    ui->pb_delete->setEnabled(false);
    ui->pb_modify->setEnabled(true);
    ui->pb_cancel->setEnabled(true);
    ui->pb_ensure->setEnabled(true);
}

void ShoesMS::on_pb_add_clicked()
{
    m_operationType = operationAdd;
    ui->le_id->setEnabled(true);
    ui->le_storeid->setEnabled(true);
    ui->le_name->setEnabled(true);
    ui->le_bottomprice->setEnabled(true);
    ui->le_freight->setEnabled(true);

    ui->pb_add->setEnabled(false);
    ui->pb_delete->setEnabled(true);
    ui->pb_modify->setEnabled(true);
    ui->pb_cancel->setEnabled(true);
    ui->pb_ensure->setEnabled(true);
}
void ShoesMS::on_pb_cancel_clicked()
{
    m_operationType = operationNone;
    ui->le_id->setText(GlobalVars::g_shoesInfoList->at(m_operationIndex.row()).getID());
    ui->le_storeid->setText(GlobalVars::g_shoesInfoList->at(m_operationIndex.row()).getStoreID());
    ui->le_name->setText(GlobalVars::g_shoesInfoList->at(m_operationIndex.row()).getShoesName());
    ui->le_bottomprice->setText(GlobalVars::g_shoesInfoList->at(m_operationIndex.row()).getBottomPrice());
    ui->le_freight->setText(GlobalVars::g_shoesInfoList->at(m_operationIndex.row()).getFreight());

    ui->le_id->setEnabled(false);
    ui->le_storeid->setEnabled(false);
    ui->le_name->setEnabled(false);
    ui->le_bottomprice->setEnabled(false);
    ui->le_freight->setEnabled(false);

    ui->pb_add->setEnabled(true);
    ui->pb_delete->setEnabled(true);
    ui->pb_modify->setEnabled(true);
    ui->pb_cancel->setEnabled(false);
    ui->pb_ensure->setEnabled(false);
}

void ShoesMS::on_pb_ensure_clicked()
{
    if(m_operationType == operationNone)
    {

    }else if(m_operationType == operationDel)
    {
        ExecSQL::deleteShoesInfo(ui->le_id->text());
        on_pb_search_clicked();
        m_operationIndex = ui->tableWidget->indexAt(QPoint(1,1));
    }else if(m_operationType == operationAdd)
    {
        ShoesInfo info(ui->le_id->text(),ui->le_storeid->text(),ui->le_name->text(),ui->le_bottomprice->text(),ui->le_freight->text());
        ExecSQL::insertShoesInfo(info);
        on_pb_search_clicked();
    }else if(m_operationType == operationModify)
    {
        int row = m_operationIndex.row();
        if(ui->le_name->text() != GlobalVars::g_shoesInfoList->at(row).getShoesName())
        {
            ExecSQL::modifyShoesInfoShoesName(ui->le_id->text(),ui->le_name->text());
            ExecSQL::selectAllShoes();
        }
        if(ui->le_storeid->text() != GlobalVars::g_shoesInfoList->at(row).getStoreID())
        {
            ExecSQL::modifyShoesInfoStoreID(ui->le_id->text(),ui->le_storeid->text());
            ExecSQL::selectAllShoes();
        }
        if(ui->le_bottomprice->text() != GlobalVars::g_shoesInfoList->at(row).getBottomPrice())
        {
            ExecSQL::modifyShoesInfoBottomPrice(ui->le_id->text(),ui->le_bottomprice->text());
            ExecSQL::selectAllShoes();
        }
        if(ui->le_freight->text() != GlobalVars::g_shoesInfoList->at(row).getFreight())
        {
            ExecSQL::modifyShoesInfoFreight(ui->le_id->text(),ui->le_freight->text());
            ExecSQL::selectAllShoes();
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
    ui->le_storeid->setEnabled(false);
    ui->le_name->setEnabled(false);
    ui->le_bottomprice->setEnabled(false);
    ui->le_freight->setEnabled(false);

}
