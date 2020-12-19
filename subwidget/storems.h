#ifndef STOREMS_H
#define STOREMS_H

#include <QWidget>
#include <QModelIndex>

namespace Ui {
class StoreMS;
}

class StoreMS : public QWidget
{
    enum SearchCondition
    {
        SearchNone = 0,
        SearchId,
        SearchSellerID,
        SearchName,
        SearchBrand,
        SearchDate,
        SearchReputation
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
    explicit StoreMS(QWidget *parent = 0);
    ~StoreMS();
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
    Ui::StoreMS *ui;

    int m_searchCondition;
    int m_operationType;
    QModelIndex m_operationIndex;
};

#endif // STOREMS_H
