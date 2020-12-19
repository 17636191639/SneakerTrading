#ifndef SELLERMS_H
#define SELLERMS_H

#include <QWidget>
#include <QModelIndex>

namespace Ui {
class SellerMS;
}

class SellerMS : public QWidget
{
    enum SearchCondition
    {
        SearchNone = 0,
        SearchId,
        SearchName,
        SearchTel,
        SearchAddress
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
    explicit SellerMS(QWidget *parent = 0);
    ~SellerMS();
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
    Ui::SellerMS *ui;

    int m_searchCondition;
    int m_operationType;
    QModelIndex m_operationIndex;

};

#endif // SELLERMS_H
