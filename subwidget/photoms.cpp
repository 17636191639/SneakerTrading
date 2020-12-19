#include "photoms.h"
#include "ui_photoms.h"
#include "execsql.h"
#include "globalvars.h"

PhotoMS::PhotoMS(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PhotoMS)
{
    ui->setupUi(this);
    m_searchCondition = SearchNone;
    ui->le_condition->setEnabled(false);
    on_pb_search_clicked();

    ui->le_id->setEnabled(false);
    ui->le_photocount->setEnabled(false);
    ui->le_photopath->setEnabled(false);

    m_operationType = operationNone;

    ui->pb_add->setEnabled(true);
    ui->pb_delete->setEnabled(true);
    ui->pb_modify->setEnabled(true);
    ui->pb_cancel->setEnabled(false);
    ui->pb_ensure->setEnabled(false);
}

PhotoMS::~PhotoMS()
{
    delete ui;
}

void PhotoMS::updateTableInfo(void)
{
    //设置表格行列
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(3);  //设置列数
    ui->tableWidget->setRowCount(GlobalVars::g_photoInfoList->count()); //设置行数

    //设置表头信息
    QStringList headers;
    headers << "图片编号" << "图片数量" << "图片路径" ;
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    for(int i = 0; i < GlobalVars::g_photoInfoList->count(); i++)
    {
        //每个表格的小框相当于一个小界面
        QTableWidgetItem *item = new QTableWidgetItem(GlobalVars::g_photoInfoList->at(i).getID());
        ui->tableWidget->setItem(i, 0, item);    //setItem(行, 列, item);
        item = new QTableWidgetItem(GlobalVars::g_photoInfoList->at(i).getPhotoCount());
        ui->tableWidget->setItem(i, 1, item);
        item = new QTableWidgetItem(GlobalVars::g_photoInfoList->at(i).getPhotoPath());
        ui->tableWidget->setItem(i, 2, item);
    }
}

void PhotoMS::on_cb_condition_currentIndexChanged(int index)
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

void PhotoMS::on_pb_search_clicked()
{
    if(m_searchCondition == SearchNone)
    {
        ExecSQL::selectAllPhotos();
    }else if(m_searchCondition == SearchId)
    {
        ExecSQL::selectPhotoInfoForID(ui->le_condition->text());
    }else if(m_searchCondition == SearchPhotoCount)
    {
        ExecSQL::selectPhotoInfoForPhotoCount(ui->le_condition->text());
    }else if(m_searchCondition == SearchPhotoPath)
    {
        ExecSQL::selectPhotoInfoForPhotoPath(ui->le_condition->text());
    }
    updateTableInfo();
}

void PhotoMS::on_tableWidget_clicked(const QModelIndex &index)
{
    m_operationIndex = index;
    ui->le_id->setText(GlobalVars::g_photoInfoList->at(index.row()).getID());
    ui->le_photocount->setText(GlobalVars::g_photoInfoList->at(index.row()).getPhotoCount());
    ui->le_photopath->setText(GlobalVars::g_photoInfoList->at(index.row()).getPhotoPath());
}

void PhotoMS::on_pb_modify_clicked()
{
    m_operationType = operationModify;
    ui->le_id->setEnabled(false);
    ui->le_photocount->setEnabled(true);
    ui->le_photopath->setEnabled(true);


    ui->pb_add->setEnabled(true);
    ui->pb_delete->setEnabled(true);
    ui->pb_modify->setEnabled(false);
    ui->pb_cancel->setEnabled(true);
    ui->pb_ensure->setEnabled(true);
}

void PhotoMS::on_pb_delete_clicked()
{
    m_operationType = operationDel;
    ui->le_id->setEnabled(false);
    ui->le_photocount->setEnabled(false);
    ui->le_photopath->setEnabled(false);


    ui->pb_add->setEnabled(true);
    ui->pb_delete->setEnabled(false);
    ui->pb_modify->setEnabled(true);
    ui->pb_cancel->setEnabled(true);
    ui->pb_ensure->setEnabled(true);
}

void PhotoMS::on_pb_add_clicked()
{
    m_operationType = operationAdd;
    ui->le_id->setEnabled(true);
    ui->le_photocount->setEnabled(true);
    ui->le_photopath->setEnabled(true);

    ui->pb_add->setEnabled(false);
    ui->pb_delete->setEnabled(true);
    ui->pb_modify->setEnabled(true);
    ui->pb_cancel->setEnabled(true);
    ui->pb_ensure->setEnabled(true);
}

void PhotoMS::on_pb_cancel_clicked()
{
    m_operationType = operationNone;
    ui->le_id->setText(GlobalVars::g_photoInfoList->at(m_operationIndex.row()).getID());
    ui->le_photocount->setText(GlobalVars::g_photoInfoList->at(m_operationIndex.row()).getPhotoCount());
    ui->le_photopath->setText(GlobalVars::g_photoInfoList->at(m_operationIndex.row()).getPhotoPath());



    ui->le_id->setEnabled(false);
    ui->le_photocount->setEnabled(false);
    ui->le_photopath->setEnabled(false);


    ui->pb_add->setEnabled(true);
    ui->pb_delete->setEnabled(true);
    ui->pb_modify->setEnabled(true);
    ui->pb_cancel->setEnabled(false);
    ui->pb_ensure->setEnabled(false);
}

void PhotoMS::on_pb_ensure_clicked()
{
    if(m_operationType == operationNone)
    {

    }else if(m_operationType == operationDel)
    {
        ExecSQL::deletePhotoInfo(ui->le_id->text());
        on_pb_search_clicked();
        m_operationIndex = ui->tableWidget->indexAt(QPoint(1,1));
    }else if(m_operationType == operationAdd)
    {
        PhotoInfo info(ui->le_id->text(),ui->le_photocount->text(),ui->le_photopath->text());
        ExecSQL::insertPhotoInfo(info);
        on_pb_search_clicked();
    }else if(m_operationType == operationModify)
    {
        int row = m_operationIndex.row();
        if(ui->le_photocount->text() != GlobalVars::g_photoInfoList->at(row).getPhotoCount())
        {
            ExecSQL::modifyPhotoInfoPhotoCount(ui->le_id->text(),ui->le_photocount->text());
            ExecSQL::selectAllPhotos();
        }
        if(ui->le_photopath->text() != GlobalVars::g_photoInfoList->at(row).getPhotoPath())
        {
            ExecSQL::modifyPhotoInfoPhotoPath(ui->le_id->text(),ui->le_photopath->text());
            ExecSQL::selectAllPhotos();
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
    ui->le_photocount->setEnabled(false);
    ui->le_photopath->setEnabled(false);

}
