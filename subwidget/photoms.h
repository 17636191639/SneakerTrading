#ifndef PHOTOMS_H
#define PHOTOMS_H

#include <QWidget>
#include <QModelIndex>

namespace Ui {
class PhotoMS;
}

class PhotoMS : public QWidget
{
    enum SearchCondition
    {
        SearchNone = 0,
        SearchId,
        SearchPhotoCount,
        SearchPhotoPath
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
    explicit PhotoMS(QWidget *parent = 0);
    ~PhotoMS();
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
    Ui::PhotoMS *ui;

    int m_searchCondition;
    int m_operationType;
    QModelIndex m_operationIndex;
};

#endif // PHOTOMS_H
