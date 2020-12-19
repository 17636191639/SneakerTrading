#ifndef SHOESMS_H
#define SHOESMS_H

#include <QWidget>
#include <QModelIndex>

namespace Ui {
class ShoesMS;
}

class ShoesMS : public QWidget
{
enum SearchCondition
{
    SearchNone = 0,
    SearchId,
    SearchStoreID,
    SearchName,
    SearchBottomPrice,
    SearchFreight
};
enum OperationType
{
    operationNone = 0,
    operationAdd,
    operationDel,
    operationModify
};

    Q_OBJECT

public:
    explicit ShoesMS(QWidget *parent = 0);
    ~ShoesMS();
    void updateTableInfo(void);
private slots:
    void on_cb_condition_currentIndexChanged(int index);

    void on_pb_search_clicked();

    void on_tableWidget_clicked(const QModelIndex &index);

    void on_pb_modify_clicked();

    void on_pb_delete_clicked();

    void on_pb_add_clicked();

    void on_pb_cancel_clicked();

    void on_pb_ensure_clicked();

private:
    Ui::ShoesMS *ui;

    int m_searchCondition;
    int m_operationType;
    QModelIndex m_operationIndex;

};

#endif // SHOESMS_H
