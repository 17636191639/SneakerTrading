#include "evaluationms.h"
#include "ui_evaluationms.h"
#include "execsql.h"
#include "globalvars.h"

EvaluationMS::EvaluationMS(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EvaluationMS)
{
    ui->setupUi(this);

    m_searchCondition = SearchNone;
    ui->le_condition->setEnabled(false);

    ui->le_id->setEnabled(false);
    ui->le_shoesid->setEnabled(false);
    ui->le_buyerid->setEnabled(false);
    ui->le_photoid->setEnabled(false);
    ui->le_grade->setEnabled(false);
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

EvaluationMS::~EvaluationMS()
{
    delete ui;
}

void EvaluationMS::updateTableInfo(void)
{
    //设置表格行列
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(7);  //设置列数
    ui->tableWidget->setRowCount(GlobalVars::g_evaluationInfoList->count()); //设置行数

    //设置表头信息
    QStringList headers;
    headers << "评价编号" << "商品编号" << "买家账号" <<  "图片编号" << "评价等级" << "评价内容" << "评价日期";
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    for(int i = 0; i < GlobalVars::g_evaluationInfoList->count(); i++)
    {
        //每个表格的小框相当于一个小界面
        QTableWidgetItem *item = new QTableWidgetItem(GlobalVars::g_evaluationInfoList->at(i).getID());
        ui->tableWidget->setItem(i, 0, item);    //setItem(行, 列, item);
        item = new QTableWidgetItem(GlobalVars::g_evaluationInfoList->at(i).getShoesID());
        ui->tableWidget->setItem(i, 1, item);
        item = new QTableWidgetItem(GlobalVars::g_evaluationInfoList->at(i).getBuyerID());
        ui->tableWidget->setItem(i, 2, item);
        item = new QTableWidgetItem(GlobalVars::g_evaluationInfoList->at(i).getPhotoID());
        ui->tableWidget->setItem(i, 3, item);
        item = new QTableWidgetItem(GlobalVars::g_evaluationInfoList->at(i).getGrade());
        ui->tableWidget->setItem(i, 4, item);
        item = new QTableWidgetItem(GlobalVars::g_evaluationInfoList->at(i).getContent());
        ui->tableWidget->setItem(i, 5, item);
//        item = new QTableWidgetItem(GlobalVars::g_evaluationInfoList->at(i).getPhotoCount());
//        ui->tableWidget->setItem(i, 5, item);
//        item = new QTableWidgetItem(GlobalVars::g_evaluationInfoList->at(i).getPhotoPath());
//        ui->tableWidget->setItem(i, 6, item);
        item = new QTableWidgetItem(GlobalVars::g_evaluationInfoList ->at(i).getDate());
        ui->tableWidget->setItem(i, 6, item);
    }
}

void EvaluationMS::on_cb_condition_currentIndexChanged(int index)
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

void EvaluationMS::on_pb_search_clicked()
{
    if(m_searchCondition == SearchNone)
    {
        ExecSQL::selectAllEvaluations();
    }else if(m_searchCondition == SearchId)
    {
        ExecSQL::selectEvaluationInfoForID(ui->le_condition->text());
    }else if(m_searchCondition == SearchShoesID)
    {
        ExecSQL::selectEvaluationInfoForShoesID(ui->le_condition->text());
    }else if(m_searchCondition == SearchBuyerID)
    {
        ExecSQL::selectEvaluationInfoForBuyerID(ui->le_condition->text());
    }else if(m_searchCondition == SearchPhotoID)
    {
        ExecSQL::selectEvaluationInfoForPhotoID(ui->le_condition->text());
    }else if(m_searchCondition == SearchGrade)
    {
        ExecSQL::selectEvaluationInfoForGrade(ui->le_condition->text());
    }else if(m_searchCondition == SearchContent)
    {
        ExecSQL::selectEvaluationInfoForContent(ui->le_condition->text());
    }else if(m_searchCondition == SearchDate)
    {
        ExecSQL::selectEvaluationInfoForDate(ui->le_condition->text());
    }
    updateTableInfo();
}

void EvaluationMS::on_tableWidget_clicked(const QModelIndex &index)
{
    m_operationIndex = index;
    ui->le_id->setText(GlobalVars::g_evaluationInfoList->at(index.row()).getID());
    ui->le_shoesid->setText(GlobalVars::g_evaluationInfoList->at(index.row()).getShoesID());
    ui->le_buyerid->setText(GlobalVars::g_evaluationInfoList->at(index.row()).getBuyerID());
    ui->le_photoid->setText(GlobalVars::g_evaluationInfoList->at(index.row()).getPhotoID());
    ui->le_grade->setText(GlobalVars::g_evaluationInfoList->at(index.row()).getGrade());
    ui->le_content->setText(GlobalVars::g_evaluationInfoList->at(index.row()).getContent());
//    ui->le_photocount->setText(GlobalVars::g_evaluationInfoList->at(index.row()).getPhotoCount());
//    ui->le_photopath->setText(GlobalVars::g_evaluationInfoList->at(index.row()).getPhotoPath());
    ui->le_date->setText(GlobalVars::g_evaluationInfoList->at(index.row()).getDate());
}

void EvaluationMS::on_pb_modify_clicked()
{
    m_operationType = operationModify;
    ui->le_id->setEnabled(false);
    ui->le_shoesid->setEnabled(true);
    ui->le_buyerid->setEnabled(true);
    ui->le_photoid->setEnabled(true);
    ui->le_grade->setEnabled(true);
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

void EvaluationMS::on_pb_delete_clicked()
{
    m_operationType = operationDel;

    ui->pb_add->setEnabled(true);
    ui->pb_delete->setEnabled(false);
    ui->pb_modify->setEnabled(true);
    ui->pb_cancel->setEnabled(true);
    ui->pb_ensure->setEnabled(true);
}

void EvaluationMS::on_pb_add_clicked()
{
    m_operationType = operationAdd;
    ui->le_id->setEnabled(true);
    ui->le_shoesid->setEnabled(true);
    ui->le_buyerid->setEnabled(true);
    ui->le_photoid->setEnabled(true);
    ui->le_grade->setEnabled(true);
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

void EvaluationMS::on_pb_cancel_clicked()
{
    m_operationType = operationNone;
    ui->le_id->setText(GlobalVars::g_evaluationInfoList->at(m_operationIndex.row()).getID());
    ui->le_shoesid->setText(GlobalVars::g_evaluationInfoList->at(m_operationIndex.row()).getShoesID());
    ui->le_buyerid->setText(GlobalVars::g_evaluationInfoList->at(m_operationIndex.row()).getBuyerID());
    ui->le_photoid->setText(GlobalVars::g_evaluationInfoList->at(m_operationIndex.row()).getPhotoID());
    ui->le_grade->setText(GlobalVars::g_evaluationInfoList->at(m_operationIndex.row()).getGrade());
    ui->le_content->setText(GlobalVars::g_evaluationInfoList->at(m_operationIndex.row()).getContent());
//    ui->le_photocount->setText(GlobalVars::g_evaluationInfoList->at(m_operationIndex.row()).getPhotoCount());
//    ui->le_photopath->setText(GlobalVars::g_evaluationInfoList->at(m_operationIndex.row()).getPhotoPath());
    ui->le_date->setText(GlobalVars::g_evaluationInfoList->at(m_operationIndex.row()).getDate());



    ui->le_id->setEnabled(false);
    ui->le_shoesid->setEnabled(false);
    ui->le_buyerid->setEnabled(false);
    ui->le_photoid->setEnabled(false);
    ui->le_grade->setEnabled(false);
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

void EvaluationMS::on_pb_ensure_clicked()
{
    if(m_operationType == operationNone)
    {

    }else if(m_operationType == operationDel)
    {
        ExecSQL::deleteEvaluationInfo(ui->le_id->text());
        on_pb_search_clicked();
        m_operationIndex = ui->tableWidget->indexAt(QPoint(1,1));
    }else if(m_operationType == operationAdd)
    {
        EvaluationInfo info(ui->le_id->text(),ui->le_shoesid->text(),ui->le_buyerid->text(), ui->le_photoid->text(), ui->le_grade->text(),
                       ui->le_content->text(), ui->le_date->text());
        ExecSQL::insertEvaluationInfo(info);
        on_pb_search_clicked();
    }else if(m_operationType == operationModify)
    {
        int row = m_operationIndex.row();
        if(ui->le_shoesid->text() != GlobalVars::g_evaluationInfoList->at(row).getShoesID())
        {
            ExecSQL::modifyEvaluationInfoShoesID(ui->le_id->text(),ui->le_shoesid->text());
            ExecSQL::selectAllEvaluations();
        }
        if(ui->le_buyerid->text() != GlobalVars::g_evaluationInfoList->at(row).getBuyerID())
        {
            ExecSQL::modifyEvaluationInfoBuyerID(ui->le_id->text(),ui->le_buyerid->text());
            ExecSQL::selectAllEvaluations();
        }
        if(ui->le_photoid->text() != GlobalVars::g_evaluationInfoList->at(row).getPhotoID())
        {
            ExecSQL::modifyEvaluationInfoPhotoID(ui->le_id->text(),ui->le_photoid->text());
            ExecSQL::selectAllEvaluations();
        }
        if(ui->le_grade->text() != GlobalVars::g_evaluationInfoList->at(row).getGrade())
        {
            ExecSQL::modifyEvaluationInfoGrade(ui->le_id->text(), ui->le_grade->text());
            ExecSQL::selectAllEvaluations();
        }
        if(ui->le_content->text() != GlobalVars::g_evaluationInfoList->at(row).getContent())
        {
            ExecSQL::modifyEvaluationInfoContent(ui->le_id->text(), ui->le_content->text());
            ExecSQL::selectAllEvaluations();
        }
//        if(ui->le_photocount->text() != GlobalVars::g_evaluationInfoList->at(row).getPhotoCount())
//        {
//            ExecSQL::modifyEvaluationInfoPhotoCount(ui->le_id->text(), ui->le_photocount->text());
//            ExecSQL::selectAllEvaluations();
//        }
//        if(ui->le_photopath->text() != GlobalVars::g_evaluationInfoList->at(row).getPhotoPath())
//        {
//            ExecSQL::modifyEvaluationInfoPhotoPath(ui->le_id->text(), ui->le_photopath->text());
//            ExecSQL::selectAllEvaluations();
//        }
        if(ui->le_date->text() != GlobalVars::g_evaluationInfoList->at(row).getDate())
        {
            ExecSQL::modifyEvaluationInfoDate(ui->le_id->text(), ui->le_date->text());
            ExecSQL::selectAllEvaluations();
        }
        updateTableInfo();
    }


    ui->pb_add->setEnabled(true);
    ui->pb_delete->setEnabled(true);
    ui->pb_modify->setEnabled(true);
    ui->pb_cancel->setEnabled(false);
    ui->pb_ensure->setEnabled(false);

    ui->le_id->setEnabled(false);
    ui->le_shoesid->setEnabled(false);
    ui->le_buyerid->setEnabled(false);
    ui->le_photoid->setEnabled(false);
    ui->le_grade->setEnabled(false);
    ui->le_content->setEnabled(false);
//    ui->le_photocount->setEnabled(false);
//    ui->le_photopath->setEnabled(false);
    ui->le_date->setEnabled(false);
}
