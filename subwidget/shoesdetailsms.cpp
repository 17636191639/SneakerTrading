#include "shoesdetailsms.h"
#include "ui_shoesdetailsms.h"
#include "globalvars.h"
#include "execsql.h"

ShoesDetailsMS::ShoesDetailsMS(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShoesDetailsMS)
{
    ui->setupUi(this);

    m_searchCondition = SearchNone;
    ui->le_condition->setEnabled(false);
    on_pb_search_clicked();

    ui->le_id->setEnabled(false);
    ui->le_shoesid->setEnabled(false);
    ui->le_photoid->setEnabled(false);
    ui->le_size->setEnabled(false);
    ui->le_color->setEnabled(false);
    ui->le_price->setEnabled(false);
//    ui->le_photocount->setEnabled(false);
//    ui->le_photopath->setEnabled(false);
    ui->le_stock->setEnabled(false);

    m_operationType = operationNone;

    ui->pb_add->setEnabled(true);
    ui->pb_delete->setEnabled(true);
    ui->pb_modify->setEnabled(true);
    ui->pb_cancel->setEnabled(false);
    ui->pb_ensure->setEnabled(false);


}

ShoesDetailsMS::~ShoesDetailsMS()
{
    delete ui;
}


void ShoesDetailsMS::updateTableInfo(void)
{
    //设置表格行列
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(7);  //设置列数
    ui->tableWidget->setRowCount(GlobalVars::g_shoesDetailsList->count()); //设置行数

    //设置表头信息
    QStringList headers;
    headers << "详情编号" << "商品编号" << "图片编号" << "尺码" << "颜色" << "价格" << "库存";
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    for(int i = 0; i < GlobalVars::g_shoesDetailsList->count(); i++)
    {
        //每个表格的小框相当于一个小界面
        QTableWidgetItem *item = new QTableWidgetItem(GlobalVars::g_shoesDetailsList->at(i).getID());
        ui->tableWidget->setItem(i, 0, item);    //setItem(行, 列, item);
        item = new QTableWidgetItem(GlobalVars::g_shoesDetailsList->at(i).getShoesID());
        ui->tableWidget->setItem(i, 1, item);
        item = new QTableWidgetItem(GlobalVars::g_shoesDetailsList->at(i).getPhotoID());
        ui->tableWidget->setItem(i, 2, item);
        item = new QTableWidgetItem(GlobalVars::g_shoesDetailsList->at(i).getSize());
        ui->tableWidget->setItem(i, 3, item);
        item = new QTableWidgetItem(GlobalVars::g_shoesDetailsList->at(i).getColor());
        ui->tableWidget->setItem(i, 4, item);
        item = new QTableWidgetItem(GlobalVars::g_shoesDetailsList->at(i).getPrice());
        ui->tableWidget->setItem(i, 5, item);
//        item = new QTableWidgetItem(GlobalVars::g_shoesDetailsList->at(i).getPhotoCount());
//        ui->tableWidget->setItem(i, 5, item);
//        item = new QTableWidgetItem(GlobalVars::g_shoesDetailsList->at(i).getPhotoPath());
//        ui->tableWidget->setItem(i, 6, item);
        item = new QTableWidgetItem(GlobalVars::g_shoesDetailsList ->at(i).getStock());
        ui->tableWidget->setItem(i, 6, item);
    }
}

void ShoesDetailsMS::on_cb_condition_currentIndexChanged(int index)
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

void ShoesDetailsMS::on_pb_search_clicked()
{
    if(m_searchCondition == SearchNone)
    {
        ExecSQL::selectAllShoesDetails();
    }else if(m_searchCondition == SearchId)
    {
        ExecSQL::selectShoesDetailsForID(ui->le_condition->text());
    }else if(m_searchCondition == SearchShoesID)
    {
        ExecSQL::selectShoesDetailsForShoesID(ui->le_condition->text());
    }else if(m_searchCondition == SearchPhotoID)
    {
        ExecSQL::selectShoesDetailsForPhotoID(ui->le_condition->text());
    }else if(m_searchCondition == SearchSize)
    {
        ExecSQL::selectShoesDetailsForSize(ui->le_condition->text());
    }else if(m_searchCondition == SearchColor)
    {
        ExecSQL::selectShoesDetailsForColor(ui->le_condition->text());
    }else if(m_searchCondition == SearchPrice)
    {
        ExecSQL::selectShoesDetailsForPrice(ui->le_condition->text());
    }else if(m_searchCondition == SearchStock)
    {
        ExecSQL::selectShoesDetailsForStock(ui->le_condition->text());
    }
    updateTableInfo();
}

void ShoesDetailsMS::on_tableWidget_clicked(const QModelIndex &index)
{
    m_operationIndex = index;
    ui->le_id->setText(GlobalVars::g_shoesDetailsList->at(index.row()).getID());
    ui->le_shoesid->setText(GlobalVars::g_shoesDetailsList->at(index.row()).getShoesID());
    ui->le_photoid->setText(GlobalVars::g_shoesDetailsList->at(index.row()).getPhotoID());
    ui->le_size->setText(GlobalVars::g_shoesDetailsList->at(index.row()).getSize());
    ui->le_color->setText(GlobalVars::g_shoesDetailsList->at(index.row()).getColor());
    ui->le_price->setText(GlobalVars::g_shoesDetailsList->at(index.row()).getPrice());
//    ui->le_photocount->setText(GlobalVars::g_shoesDetailsList->at(index.row()).getPhotoCount());
//    ui->le_photopath->setText(GlobalVars::g_shoesDetailsList->at(index.row()).getPhotoPath());
    ui->le_stock->setText(GlobalVars::g_shoesDetailsList->at(index.row()).getStock());
}

void ShoesDetailsMS::on_pb_modify_clicked()
{
    m_operationType = operationModify;
    ui->le_id->setEnabled(false);
    ui->le_shoesid->setEnabled(true);
    ui->le_photoid->setEnabled(true);
    ui->le_size->setEnabled(true);
    ui->le_color->setEnabled(true);
    ui->le_price->setEnabled(true);
//    ui->le_photocount->setEnabled(true);
//    ui->le_photopath->setEnabled(true);
    ui->le_stock->setEnabled(true);


    ui->pb_add->setEnabled(true);
    ui->pb_delete->setEnabled(true);
    ui->pb_modify->setEnabled(false);
    ui->pb_cancel->setEnabled(true);
    ui->pb_ensure->setEnabled(true);
}

void ShoesDetailsMS::on_pb_delete_clicked()
{
    m_operationType = operationDel;

    ui->pb_add->setEnabled(true);
    ui->pb_delete->setEnabled(false);
    ui->pb_modify->setEnabled(true);
    ui->pb_cancel->setEnabled(true);
    ui->pb_ensure->setEnabled(true);
}

void ShoesDetailsMS::on_pb_add_clicked()
{
    m_operationType = operationAdd;
    ui->le_id->setEnabled(true);
    ui->le_shoesid->setEnabled(true);
    ui->le_photoid->setEnabled(true);
    ui->le_size->setEnabled(true);
    ui->le_color->setEnabled(true);
    ui->le_price->setEnabled(true);
//    ui->le_photocount->setEnabled(true);
//    ui->le_photopath->setEnabled(true);
    ui->le_stock->setEnabled(true);

    ui->pb_add->setEnabled(false);
    ui->pb_delete->setEnabled(true);
    ui->pb_modify->setEnabled(true);
    ui->pb_cancel->setEnabled(true);
    ui->pb_ensure->setEnabled(true);
}

void ShoesDetailsMS::on_pb_cancel_clicked()
{
    m_operationType = operationNone;
    ui->le_id->setText(GlobalVars::g_shoesDetailsList->at(m_operationIndex.row()).getID());
    ui->le_shoesid->setText(GlobalVars::g_shoesDetailsList->at(m_operationIndex.row()).getShoesID());
    ui->le_photoid->setText(GlobalVars::g_shoesDetailsList->at(m_operationIndex.row()).getPhotoID());
    ui->le_size->setText(GlobalVars::g_shoesDetailsList->at(m_operationIndex.row()).getSize());
    ui->le_color->setText(GlobalVars::g_shoesDetailsList->at(m_operationIndex.row()).getColor());
    ui->le_price->setText(GlobalVars::g_shoesDetailsList->at(m_operationIndex.row()).getPrice());
//    ui->le_photocount->setText(GlobalVars::g_shoesDetailsList->at(m_operationIndex.row()).getPhotoCount());
//    ui->le_photopath->setText(GlobalVars::g_shoesDetailsList->at(m_operationIndex.row()).getPhotoPath());
    ui->le_stock->setText(GlobalVars::g_shoesDetailsList->at(m_operationIndex.row()).getStock());



    ui->le_id->setEnabled(false);
    ui->le_shoesid->setEnabled(false);
    ui->le_photoid->setEnabled(false);
    ui->le_size->setEnabled(false);
    ui->le_color->setEnabled(false);
    ui->le_price->setEnabled(false);
//    ui->le_photocount->setEnabled(false);
//    ui->le_photopath->setEnabled(false);
    ui->le_stock->setEnabled(false);


    ui->pb_add->setEnabled(true);
    ui->pb_delete->setEnabled(true);
    ui->pb_modify->setEnabled(true);
    ui->pb_cancel->setEnabled(false);
    ui->pb_ensure->setEnabled(false);
}

void ShoesDetailsMS::on_pb_ensure_clicked()
{
    if(m_operationType == operationNone)
    {

    }else if(m_operationType == operationDel)
    {
        ExecSQL::deleteShoesDetails(ui->le_id->text());
        on_pb_search_clicked();
        m_operationIndex = ui->tableWidget->indexAt(QPoint(1,1));
    }else if(m_operationType == operationAdd)
    {
        ShoesDetails info(ui->le_id->text(),ui->le_shoesid->text(), ui->le_photoid->text(),
                          ui->le_size->text(), ui->le_color->text(),ui->le_price->text(), ui->le_stock->text());
        ExecSQL::insertShoesDetails(info);
        on_pb_search_clicked();
    }else if(m_operationType == operationModify)
    {
        int row = m_operationIndex.row();
        if(ui->le_shoesid->text() != GlobalVars::g_shoesDetailsList->at(row).getShoesID())
        {
            ExecSQL::modifyShoesDetailsShoesID(ui->le_id->text(),ui->le_shoesid->text());
            ExecSQL::selectAllShoesDetails();
        }
        if(ui->le_photoid->text() != GlobalVars::g_shoesDetailsList->at(row).getPhotoID())
        {
            ExecSQL::modifyShoesDetailsPhotoID(ui->le_id->text(),ui->le_photoid->text());
            ExecSQL::selectAllShoesDetails();
        }
        if(ui->le_size->text() != GlobalVars::g_shoesDetailsList->at(row).getSize())
        {
            ExecSQL::modifyShoesDetailsSize(ui->le_id->text(),ui->le_size->text());
            ExecSQL::selectAllShoesDetails();
        }
        if(ui->le_color->text() != GlobalVars::g_shoesDetailsList->at(row).getColor())
        {
            ExecSQL::modifyShoesDetailsColor(ui->le_id->text(), ui->le_color->text());
            ExecSQL::selectAllShoesDetails();
        }
        if(ui->le_price->text() != GlobalVars::g_shoesDetailsList->at(row).getPrice())
        {
            ExecSQL::modifyShoesDetailsPrice(ui->le_id->text(), ui->le_price->text());
            ExecSQL::selectAllShoesDetails();
        }
//        if(ui->le_photocount->text() != GlobalVars::g_shoesDetailsList->at(row).getPhotoCount())
//        {
//            ExecSQL::modifyShoesDetailsPhotoCount(ui->le_id->text(), ui->le_photocount->text());
//            ExecSQL::selectAllShoesDetails();
//        }
//        if(ui->le_photopath->text() != GlobalVars::g_shoesDetailsList->at(row).getPhotoPath())
//        {
//            ExecSQL::modifyShoesDetailsPhotoPath(ui->le_id->text(), ui->le_photopath->text());
//            ExecSQL::selectAllShoesDetails();
//        }
        if(ui->le_stock->text() != GlobalVars::g_shoesDetailsList->at(row).getStock())
        {
            ExecSQL::modifyShoesDetailsStock(ui->le_id->text(), ui->le_stock->text());
            ExecSQL::selectAllShoesDetails();
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
    ui->le_photoid->setEnabled(false);
    ui->le_size->setEnabled(false);
    ui->le_color->setEnabled(false);
    ui->le_price->setEnabled(false);
//    ui->le_photocount->setEnabled(false);
//    ui->le_photopath->setEnabled(false);
    ui->le_stock->setEnabled(false);
}

void ShoesDetailsMS::on_tableWidget_doubleClicked(const QModelIndex &index)
{
//    QString photoPath = GlobalVars::g_shoesDetailsList->at(index.row()).getPhotoPath();
//    QString shoesName = GlobalVars::g_shoesDetailsList->at(index.row()).getID();
//    QString pathName = photoPath + shoesName + QString(" (1).jpg");
//    if(m_showPhoto != NULL)
//    {
//        m_showPhoto->close();
//    }
//    m_showPhoto = new ShowPhoto(pathName);
//    m_showPhoto->show();
}
