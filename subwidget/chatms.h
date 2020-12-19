#ifndef CHATMS_H
#define CHATMS_H

#include <QWidget>
#include <QModelIndex>

namespace Ui {
class ChatMS;
}

class ChatMS : public QWidget
{
    enum SearchCondition
    {
        SearchNone = 0,
        SearchId,
        SearchBuyerID,
        SearchSellerID,
        SearchPhotoID,
        SearchContent,

        SearchDate
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
    explicit ChatMS(QWidget *parent = 0);
    ~ChatMS();
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
    Ui::ChatMS *ui;
    int m_searchCondition;
    int m_operationType;
    QModelIndex m_operationIndex;
};

#endif // CHATMS_H
