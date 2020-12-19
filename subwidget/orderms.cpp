#include "orderms.h"
#include "ui_orderms.h"
#include "globalvars.h"
#include "execsql.h"

OrderMS::OrderMS(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OrderMS)
{
    ui->setupUi(this);

    m_searchCondition = SearchNone;
    ui->le_condition->setEnabled(false);
    on_pb_search_clicked();

    ui->le_id->setEnabled(false);
    ui->le_buyerid->setEnabled(false);
    ui->le_detailid->setEnabled(false);
    ui->le_count->setEnabled(false);
    ui->le_state->setEnabled(false);
    ui->le_createdate->setEnabled(false);
    ui->le_deliverydate->setEnabled(false);
    ui->le_finishdate->setEnabled(false);

    m_operationType = operationNone;

    ui->pb_add->setEnabled(true);
    ui->pb_delete->setEnabled(true);
    ui->pb_modify->setEnabled(true);
    ui->pb_cancel->setEnabled(false);
    ui->pb_ensure->setEnabled(false);
}

OrderMS::~OrderMS()
{
    delete ui;
}

void OrderMS::updateTableInfo(void)
{
    //设置表格行列
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(8);  //设置列数
    ui->tableWidget->setRowCount(GlobalVars::g_orderInfoList->count()); //设置行数

    //设置表头信息
    QStringList headers;
    headers << "订单编号" << "买家账号" << "商品详情编号" << "商品数量" << "订单状态" << "创建时间" << "发货日期" << "完成日期";
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    for(int i = 0; i < GlobalVars::g_orderInfoList->count(); i++)
    {
        //每个表格的小框相当于一个小界面
        QTableWidgetItem *item = new QTableWidgetItem(GlobalVars::g_orderInfoList->at(i).getID());
        ui->tableWidget->setItem(i, 0, item);    //setItem(行, 列, item);
        item = new QTableWidgetItem(GlobalVars::g_orderInfoList->at(i).getBuyID());
        ui->tableWidget->setItem(i, 1, item);
        item = new QTableWidgetItem(GlobalVars::g_orderInfoList->at(i).getDetailID());
        ui->tableWidget->setItem(i, 2, item);
        item = new QTableWidgetItem(GlobalVars::g_orderInfoList->at(i).getCount());
        ui->tableWidget->setItem(i, 3, item);
        item = new QTableWidgetItem(GlobalVars::g_orderInfoList->at(i).getState());
        ui->tableWidget->setItem(i, 4, item);
        item = new QTableWidgetItem(GlobalVars::g_orderInfoList->at(i).getCreateDate());
        ui->tableWidget->setItem(i, 5, item);
        item = new QTableWidgetItem(GlobalVars::g_orderInfoList->at(i).getDeliveryDate());
        ui->tableWidget->setItem(i, 6, item);
        item = new QTableWidgetItem(GlobalVars::g_orderInfoList->at(i).getFinishDate());
        ui->tableWidget->setItem(i, 7, item);
    }
}

void OrderMS::on_cb_condition_currentIndexChanged(int index)
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

void OrderMS::on_pb_search_clicked()
{
    if(m_searchCondition == SearchNone)
    {
        ExecSQL::selectAllOrders();
    }else if(m_searchCondition == SearchId)
    {
        ExecSQL::selectOrderInfoForID(ui->le_condition->text());
    }else if(m_searchCondition == SearchDetailID)
    {
        ExecSQL::selectOrderInfoForDetailID(ui->le_condition->text());
    }else if(m_searchCondition == SearchCount)
    {
        ExecSQL::selectOrderInfoForCount(ui->le_condition->text());
    }else if(m_searchCondition == SearchBuyerID)
    {
        ExecSQL::selectOrderInfoForBuyerID(ui->le_condition->text());
    }else if(m_searchCondition == SearchState)
    {
        ExecSQL::selectOrderInfoForState(ui->le_condition->text());
    }else if(m_searchCondition == SearchCreateDate)
    {
        ExecSQL::selectOrderInfoForCreateDate(ui->le_condition->text());
    }else if(m_searchCondition == SearchDeliveryDate)
    {
        ExecSQL::selectOrderInfoForDeliveryDate(ui->le_condition->text());
    }else if(m_searchCondition == SearchFinishDate)
    {
        ExecSQL::selectOrderInfoForFinishDate(ui->le_condition->text());
    }
    updateTableInfo();
}

void OrderMS::on_tableWidget_clicked(const QModelIndex &index)
{
    m_operationIndex = index;
    ui->le_id->setText(GlobalVars::g_orderInfoList->at(index.row()).getID());
    ui->le_buyerid->setText(GlobalVars::g_orderInfoList->at(index.row()).getBuyID());
    ui->le_detailid->setText(GlobalVars::g_orderInfoList->at(index.row()).getDetailID());
    ui->le_count->setText(GlobalVars::g_orderInfoList->at(index.row()).getCount());
    ui->le_state->setText(GlobalVars::g_orderInfoList->at(index.row()).getState());
    ui->le_createdate->setText(GlobalVars::g_orderInfoList->at(index.row()).getCreateDate());
    ui->le_deliverydate->setText(GlobalVars::g_orderInfoList->at(index.row()).getDeliveryDate());
    ui->le_finishdate->setText(GlobalVars::g_orderInfoList->at(index.row()).getFinishDate());
}

void OrderMS::on_pb_modify_clicked()
{
    m_operationType = operationModify;
    ui->le_id->setEnabled(false);
    ui->le_buyerid->setEnabled(true);
    ui->le_detailid->setEnabled(true);
    ui->le_count->setEnabled(true);
    ui->le_state->setEnabled(true);
    ui->le_createdate->setEnabled(true);
    ui->le_deliverydate->setEnabled(true);
    ui->le_finishdate->setEnabled(true);


    ui->pb_add->setEnabled(true);
    ui->pb_delete->setEnabled(true);
    ui->pb_modify->setEnabled(false);
    ui->pb_cancel->setEnabled(true);
    ui->pb_ensure->setEnabled(true);
}

void OrderMS::on_pb_delete_clicked()
{
    m_operationType = operationDel;

    ui->pb_add->setEnabled(true);
    ui->pb_delete->setEnabled(false);
    ui->pb_modify->setEnabled(true);
    ui->pb_cancel->setEnabled(true);
    ui->pb_ensure->setEnabled(true);
}

void OrderMS::on_pb_add_clicked()
{
    m_operationType = operationAdd;
    ui->le_id->setEnabled(true);
    ui->le_buyerid->setEnabled(true);
    ui->le_detailid->setEnabled(true);
    ui->le_count->setEnabled(true);
    ui->le_state->setEnabled(true);
    ui->le_createdate->setEnabled(true);
    ui->le_deliverydate->setEnabled(true);
    ui->le_finishdate->setEnabled(true);

    ui->pb_add->setEnabled(false);
    ui->pb_delete->setEnabled(true);
    ui->pb_modify->setEnabled(true);
    ui->pb_cancel->setEnabled(true);
    ui->pb_ensure->setEnabled(true);
}

void OrderMS::on_pb_cancel_clicked()
{
    m_operationType = operationNone;
    ui->le_id->setText(GlobalVars::g_orderInfoList->at(m_operationIndex.row()).getID());
    ui->le_buyerid->setText(GlobalVars::g_orderInfoList->at(m_operationIndex.row()).getBuyID());
    ui->le_detailid->setText(GlobalVars::g_orderInfoList->at(m_operationIndex.row()).getDetailID());
    ui->le_count->setText(GlobalVars::g_orderInfoList->at(m_operationIndex.row()).getCount());
    ui->le_state->setText(GlobalVars::g_orderInfoList->at(m_operationIndex.row()).getState());
    ui->le_createdate->setText(GlobalVars::g_orderInfoList->at(m_operationIndex.row()).getCreateDate());
    ui->le_deliverydate->setText(GlobalVars::g_orderInfoList->at(m_operationIndex.row()).getDeliveryDate());
    ui->le_finishdate->setText(GlobalVars::g_orderInfoList->at(m_operationIndex.row()).getFinishDate());



    ui->le_id->setEnabled(false);
    ui->le_buyerid->setEnabled(false);
    ui->le_detailid->setEnabled(false);
    ui->le_count->setEnabled(false);
    ui->le_state->setEnabled(false);
    ui->le_createdate->setEnabled(false);
    ui->le_deliverydate->setEnabled(false);
    ui->le_finishdate->setEnabled(false);


    ui->pb_add->setEnabled(true);
    ui->pb_delete->setEnabled(true);
    ui->pb_modify->setEnabled(true);
    ui->pb_cancel->setEnabled(false);
    ui->pb_ensure->setEnabled(false);
}

void OrderMS::on_pb_ensure_clicked()
{
    if(m_operationType == operationNone)
    {

    }else if(m_operationType == operationDel)
    {
        ExecSQL::deleteOrderInfo(ui->le_id->text());
        on_pb_search_clicked();
        m_operationIndex = ui->tableWidget->indexAt(QPoint(1,1));
    }else if(m_operationType == operationAdd)
    {
        OrderInfo info(ui->le_id->text(),ui->le_buyerid->text(),ui->le_detailid->text(), ui->le_count->text(),
                       ui->le_state->text(), ui->le_createdate->text(), ui->le_deliverydate->text(), ui->le_finishdate->text());
        ExecSQL::insertOrderInfo(info);
        on_pb_search_clicked();
    }else if(m_operationType == operationModify)
    {
        int row = m_operationIndex.row();
        if(ui->le_buyerid->text() != GlobalVars::g_orderInfoList->at(row).getBuyID())
        {
            ExecSQL::modifyOrderInfoBuyerID(ui->le_id->text(),ui->le_buyerid->text());
            ExecSQL::selectAllOrders();
        }
        if(ui->le_detailid->text() != GlobalVars::g_orderInfoList->at(row).getDetailID())
        {
            ExecSQL::modifyOrderInfoDetailID(ui->le_id->text(),ui->le_detailid->text());
            ExecSQL::selectAllOrders();
        }
        if(ui->le_count->text() != GlobalVars::g_orderInfoList->at(row).getDetailID())
        {
            ExecSQL::modifyOrderInfoCount(ui->le_id->text(),ui->le_detailid->text(), ui->le_buyerid->text(), ui->le_count->text());
            ExecSQL::selectAllOrders();
        }
        if(ui->le_state->text() != GlobalVars::g_orderInfoList->at(row).getDetailID())
        {
            ExecSQL::modifyOrderInfoState(ui->le_id->text(),ui->le_detailid->text(), ui->le_buyerid->text(), ui->le_state->text());
            ExecSQL::selectAllOrders();
        }
        if(ui->le_createdate->text() != GlobalVars::g_orderInfoList->at(row).getDetailID())
        {
            ExecSQL::modifyOrderInfoCreateDate(ui->le_id->text(),ui->le_detailid->text(), ui->le_buyerid->text(), ui->le_createdate->text());
            ExecSQL::selectAllOrders();
        }
        if(ui->le_deliverydate->text() != GlobalVars::g_orderInfoList->at(row).getDetailID())
        {
            ExecSQL::modifyOrderInfoDeliveryDate(ui->le_id->text(),ui->le_detailid->text(), ui->le_buyerid->text(), ui->le_deliverydate->text());
            ExecSQL::selectAllOrders();
        }
        if(ui->le_finishdate->text() != GlobalVars::g_orderInfoList->at(row).getDetailID())
        {
            ExecSQL::modifyOrderInfoFinishDate(ui->le_id->text(),ui->le_detailid->text(), ui->le_buyerid->text(), ui->le_finishdate->text());
            ExecSQL::selectAllOrders();
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
    ui->le_detailid->setEnabled(false);
    ui->le_count->setEnabled(false);
    ui->le_state->setEnabled(false);
    ui->le_createdate->setEnabled(false);
    ui->le_deliverydate->setEnabled(false);
    ui->le_finishdate->setEnabled(false);
}
