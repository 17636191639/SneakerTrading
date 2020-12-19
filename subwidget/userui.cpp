#include "userui.h"
#include "ui_userui.h"

#include "execsql.h"
#include "globalvars.h"

UserUI::UserUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserUI)
{
    ui->setupUi(this);

    m_searchCondition = SearchNone;
    ui->le_condition->setEnabled(false);
    on_pb_search_clicked();

    ui->le_id->setEnabled(false);
    ui->le_pswd->setEnabled(false);
    ui->le_role->setEnabled(false);
    ui->le_date->setEnabled(false);
    m_operationType = operationNone;

    ui->pb_add->setEnabled(true);
    ui->pb_delete->setEnabled(true);
    ui->pb_modify->setEnabled(true);
    ui->pb_cancel->setEnabled(false);
    ui->pb_ensure->setEnabled(false);
}

UserUI::~UserUI()
{
    delete ui;
}

void UserUI::updateTableInfo(void)
{
    //设置表格行列
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(4);  //设置列数
    ui->tableWidget->setRowCount(GlobalVars::g_userInfoList->count()); //设置行数

    //设置表头信息
    QStringList headers;
    headers << "账号" << "密码" << "角色" << "日期";
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    for(int i = 0; i < GlobalVars::g_userInfoList->count(); i++)
    {
        //每个表格的小框相当于一个小界面
        QTableWidgetItem *item = new QTableWidgetItem(GlobalVars::g_userInfoList->at(i).getID());
        ui->tableWidget->setItem(i, 0, item);    //setItem(行, 列, item);
        item = new QTableWidgetItem(GlobalVars::g_userInfoList->at(i).getPswd());
        ui->tableWidget->setItem(i, 1, item);
        item = new QTableWidgetItem(GlobalVars::g_userInfoList->at(i).getRole());
        ui->tableWidget->setItem(i, 2, item);
        item = new QTableWidgetItem(GlobalVars::g_userInfoList->at(i).getDate());
        ui->tableWidget->setItem(i, 3, item);
    }
}
void UserUI::on_cb_condition_currentIndexChanged(int index)
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

void UserUI::on_pb_search_clicked()
{
    if(m_searchCondition == SearchNone)
    {
        ExecSQL::selectAllUsers();
    }else if(m_searchCondition == SearchId)
    {
        ExecSQL::selectUserInfoForId(ui->le_condition->text());
    }else if(m_searchCondition == SearchPswd)
    {
        ExecSQL::selectUserInfoForPswd(ui->le_condition->text());
    }else if(m_searchCondition == SearchRole)
    {
        ExecSQL::selectUserInfoForRole(ui->le_condition->text());
    }else if(m_searchCondition == SearchDate)
    {
        ExecSQL::selectUserInfoForDate(ui->le_condition->text());
    }
    updateTableInfo();
}

void UserUI::on_tableWidget_clicked(const QModelIndex &index)
{
    m_operationIndex = index;
    ui->le_id->setText(GlobalVars::g_userInfoList->at(index.row()).getID());
    ui->le_pswd->setText(GlobalVars::g_userInfoList->at(index.row()).getPswd());
    ui->le_role->setText(GlobalVars::g_userInfoList->at(index.row()).getRole());
    ui->le_date->setText(GlobalVars::g_userInfoList->at(index.row()).getDate());
}

void UserUI::on_pb_modify_clicked()
{
    m_operationType = operationModify;
    ui->le_id->setEnabled(false);
    ui->le_pswd->setEnabled(true);
    ui->le_role->setEnabled(true);
    ui->le_date->setEnabled(true);

    ui->pb_add->setEnabled(true);
    ui->pb_delete->setEnabled(true);
    ui->pb_modify->setEnabled(false);
    ui->pb_cancel->setEnabled(true);
    ui->pb_ensure->setEnabled(true);
}

void UserUI::on_pb_delete_clicked()
{
    m_operationType = operationDel;
    ui->le_id->setEnabled(false);
    ui->le_pswd->setEnabled(false);
    ui->le_role->setEnabled(false);
    ui->le_date->setEnabled(false);

    ui->pb_add->setEnabled(true);
    ui->pb_delete->setEnabled(false);
    ui->pb_modify->setEnabled(true);
    ui->pb_cancel->setEnabled(true);
    ui->pb_ensure->setEnabled(true);
}

void UserUI::on_pb_add_clicked()
{
    m_operationType = operationAdd;
    ui->le_id->setEnabled(true);
    ui->le_pswd->setEnabled(true);
    ui->le_role->setEnabled(true);
    ui->le_date->setEnabled(true);

    ui->pb_add->setEnabled(false);
    ui->pb_delete->setEnabled(true);
    ui->pb_modify->setEnabled(true);
    ui->pb_cancel->setEnabled(true);
    ui->pb_ensure->setEnabled(true);
}

void UserUI::on_pb_cancel_clicked()
{
    m_operationType = operationNone;
    ui->le_id->setText(GlobalVars::g_userInfoList->at(m_operationIndex.row()).getID());
    ui->le_pswd->setText(GlobalVars::g_userInfoList->at(m_operationIndex.row()).getPswd());
    ui->le_role->setText(GlobalVars::g_userInfoList->at(m_operationIndex.row()).getRole());
    ui->le_date->setText(GlobalVars::g_userInfoList->at(m_operationIndex.row()).getDate());

    ui->le_id->setEnabled(false);
    ui->le_pswd->setEnabled(false);
    ui->le_role->setEnabled(false);
    ui->le_date->setEnabled(false);

    ui->pb_add->setEnabled(true);
    ui->pb_delete->setEnabled(true);
    ui->pb_modify->setEnabled(true);
    ui->pb_cancel->setEnabled(false);
    ui->pb_ensure->setEnabled(false);
}

void UserUI::on_pb_ensure_clicked()
{
    if(m_operationType == operationNone)
    {

    }else if(m_operationType == operationDel)
    {
        ExecSQL::deleteUserInfo(ui->le_id->text());
        on_pb_search_clicked();
    }else if(m_operationType == operationAdd)
    {
        UserInfo info(ui->le_id->text(),ui->le_pswd->text(),ui->le_role->text(),ui->le_date->text());
        ExecSQL::insertUserInfo(info);
        on_pb_search_clicked();
    }else if(m_operationType == operationModify)
    {
        if(ui->le_pswd->text() != GlobalVars::g_userInfoList->at(m_operationIndex.row()).getPswd())
        {
            ExecSQL::modifyUserInfoPswd(ui->le_id->text(),ui->le_pswd->text());
        }
        if(ui->le_role->text() != GlobalVars::g_userInfoList->at(m_operationIndex.row()).getRole())
        {
            ExecSQL::modifyUserInfoRole(ui->le_id->text(),ui->le_role->text());
        }
        if(ui->le_date->text() != GlobalVars::g_userInfoList->at(m_operationIndex.row()).getDate())
        {
            ExecSQL::modifyUserInfoDate(ui->le_id->text(),ui->le_date->text());
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
