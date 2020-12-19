#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "userui.h"
#include "buyerms.h"
#include "sellerms.h"
#include "shoesms.h"
#include "storems.h"
#include "shopcartms.h"
#include "orderms.h"
#include "shoesdetailsms.h"
#include "evaluationms.h"
#include "chatms.h"
#include "photoms.h"
#include "myserver.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionShoesMS_triggered();

    void on_actionOrderMS_triggered();

    void on_actionEvaluationMS_triggered();

    void on_actionUserMS_triggered();

    void on_actionStoreMS_triggered();

    void on_actionShopCart_triggered();

    void on_actionShoesDetailsMS_triggered();

    void on_actionSellerMS_triggered();

    void on_actionBuyerMS_triggered();

    void on_actionChatMS_triggered();

    void on_actionPhotoMS_triggered();

private:
    Ui::MainWindow *ui;

    UserUI *m_userUI;
    BuyerMS *m_buyerMS;
    SellerMS *m_sellerMS;
    ShoesMS *m_shoesMS;
    StoreMS *m_storeMS;
    ShopCartMS *m_shopCartMS;
    OrderMS *m_orderMS;
    ShoesDetailsMS *m_shoesDetailsMS;
    EvaluationMS *m_evaluationMS;
    ChatMS *m_chatMS;
    PhotoMS *m_photoMS;
    MyServer *m_myServer;
};

#endif // MAINWINDOW_H
