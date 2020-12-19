#ifndef USERUI_H
#define USERUI_H

#include <QWidget>
#include <QModelIndex>

namespace Ui {
class UserUI;

}

class UserUI : public QWidget
{
    enum SearchCondition
    {
        SearchNone = 0,
        SearchId,
        SearchPswd,
        SearchRole,
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
    explicit UserUI(QWidget *parent = 0);
    ~UserUI();

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
    Ui::UserUI *ui;
    int m_searchCondition;
    int m_operationType;
    QModelIndex m_operationIndex;
};

#endif // USERUI_H
