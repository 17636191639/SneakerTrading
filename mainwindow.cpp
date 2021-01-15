#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "globalvars.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_userUI = new UserUI(ui->widget);
    m_buyerMS = new BuyerMS(ui->widget);
    m_sellerMS = new SellerMS(ui->widget);
    m_shoesMS = new ShoesMS(ui->widget);
    m_storeMS = new StoreMS(ui->widget);
    m_shopCartMS = new ShopCartMS(ui->widget);
    m_orderMS = new OrderMS(ui->widget);
    m_shoesDetailsMS = new ShoesDetailsMS(ui->widget);
    m_evaluationMS = new EvaluationMS(ui->widget);
    m_chatMS = new ChatMS(ui->widget);
    m_photoMS = new PhotoMS(ui->widget);

    //m_myServer = new MyServer;
    m_myProc = new MsgProc;
    connect(m_myProc, SIGNAL(signalSendMsgToClient(QString,QString)),
            this, SLOT(slotSendMsgToClient(QString,QString)));
    connect(m_myProc, SIGNAL(signalSendPhotoToClient(QString, bool)),
            this, SLOT(slotSendPhotoToClient(QString, bool)));
    m_myProc->start();

    menuBar()->hide();
    statusBar()->hide();
    this->setWindowTitle("麦孩后台管理系统");
    this->setCentralWidget(ui->widget);

    m_userUI->show();
    m_buyerMS->hide();
    m_sellerMS->hide();
    m_shoesMS->hide();
    m_storeMS->hide();
    m_shopCartMS->hide();
    m_orderMS->hide();
    m_shoesDetailsMS->hide();
    m_evaluationMS->hide();
    m_chatMS->hide();
    m_photoMS->hide();

    ui->actionUserMS->setEnabled(false);
    ui->actionBuyerMS->setEnabled(true);
    ui->actionSellerMS->setEnabled(true);
    ui->actionShoesMS->setEnabled(true);
    ui->actionShoesDetailsMS->setEnabled(true);
    ui->actionStoreMS->setEnabled(true);
    ui->actionShopCart->setEnabled(true);
    ui->actionOrderMS->setEnabled(true);
    ui->actionEvaluationMS->setEnabled(true);
    ui->actionChatMS->setEnabled(true);
    ui->actionPhotoMS->setEnabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
    m_myProc->exitThread();
    if(m_myProc->wait())
    {
        delete m_myProc;
    }
}

void MainWindow::on_actionShoesMS_triggered()
{
    m_userUI->hide();
    m_buyerMS->hide();
    m_sellerMS->hide();
    m_shoesMS->show();
    m_storeMS->hide();
    m_shopCartMS->hide();
    m_orderMS->hide();
    m_shoesDetailsMS->hide();
    m_evaluationMS->hide();
    m_chatMS->hide();
    m_photoMS->hide();
    ui->actionUserMS->setEnabled(true);
    ui->actionBuyerMS->setEnabled(true);
    ui->actionSellerMS->setEnabled(true);
    ui->actionShoesMS->setEnabled(false); ////
    ui->actionShoesDetailsMS->setEnabled(true);
    ui->actionStoreMS->setEnabled(true);
    ui->actionShopCart->setEnabled(true);
    ui->actionOrderMS->setEnabled(true);
    ui->actionEvaluationMS->setEnabled(true);
    ui->actionChatMS->setEnabled(true);
    ui->actionPhotoMS->setEnabled(true);
}

void MainWindow::on_actionOrderMS_triggered()
{
    m_userUI->hide();
    m_buyerMS->hide();
    m_sellerMS->hide();
    m_shoesMS->hide();
    m_storeMS->hide();
    m_shopCartMS->hide();
    m_orderMS->show();
    m_shoesDetailsMS->hide();
    m_evaluationMS->hide();
    m_chatMS->hide();
    m_photoMS->hide();
    ui->actionUserMS->setEnabled(true);
    ui->actionBuyerMS->setEnabled(true);
    ui->actionSellerMS->setEnabled(true);
    ui->actionShoesMS->setEnabled(true);
    ui->actionShoesDetailsMS->setEnabled(true);
    ui->actionStoreMS->setEnabled(true);
    ui->actionShopCart->setEnabled(true);
    ui->actionOrderMS->setEnabled(false); ////
    ui->actionEvaluationMS->setEnabled(true);
    ui->actionChatMS->setEnabled(true);
    ui->actionPhotoMS->setEnabled(true);
}

void MainWindow::on_actionEvaluationMS_triggered()
{
    m_userUI->hide();
    m_buyerMS->hide();
    m_sellerMS->hide();
    m_shoesMS->hide();
    m_storeMS->hide();
    m_shopCartMS->hide();
    m_orderMS->hide();
    m_shoesDetailsMS->hide();
    m_evaluationMS->show();
    m_chatMS->hide();
    m_photoMS->hide();
    ui->actionUserMS->setEnabled(true);
    ui->actionBuyerMS->setEnabled(true);
    ui->actionSellerMS->setEnabled(true);
    ui->actionShoesMS->setEnabled(true);
    ui->actionShoesDetailsMS->setEnabled(true);
    ui->actionStoreMS->setEnabled(true);
    ui->actionShopCart->setEnabled(true);
    ui->actionOrderMS->setEnabled(true);
    ui->actionEvaluationMS->setEnabled(false); ////
    ui->actionChatMS->setEnabled(true);
    ui->actionPhotoMS->setEnabled(true);
}

void MainWindow::on_actionUserMS_triggered()
{
    m_userUI->show();
    m_buyerMS->hide();
    m_sellerMS->hide();
    m_shoesMS->hide();
    m_storeMS->hide();
    m_shopCartMS->hide();
    m_orderMS->hide();
    m_shoesDetailsMS->hide();
    m_evaluationMS->hide();
    m_chatMS->hide();
    m_photoMS->hide();
    ui->actionUserMS->setEnabled(false); ////
    ui->actionBuyerMS->setEnabled(true);
    ui->actionSellerMS->setEnabled(true);
    ui->actionShoesMS->setEnabled(true);
    ui->actionShoesDetailsMS->setEnabled(true);
    ui->actionStoreMS->setEnabled(true);
    ui->actionShopCart->setEnabled(true);
    ui->actionOrderMS->setEnabled(true);
    ui->actionEvaluationMS->setEnabled(true);
    ui->actionChatMS->setEnabled(true);
    ui->actionPhotoMS->setEnabled(true);
}

void MainWindow::on_actionStoreMS_triggered()
{
    m_userUI->hide();
    m_buyerMS->hide();
    m_sellerMS->hide();
    m_shoesMS->hide();
    m_storeMS->show();
    m_shopCartMS->hide();
    m_orderMS->hide();
    m_shoesDetailsMS->hide();
    m_evaluationMS->hide();
    m_chatMS->hide();
    m_photoMS->hide();
    ui->actionUserMS->setEnabled(true);
    ui->actionBuyerMS->setEnabled(true);
    ui->actionSellerMS->setEnabled(true);
    ui->actionShoesMS->setEnabled(true);
    ui->actionShoesDetailsMS->setEnabled(true);
    ui->actionStoreMS->setEnabled(false); ////
    ui->actionShopCart->setEnabled(true);
    ui->actionOrderMS->setEnabled(true);
    ui->actionEvaluationMS->setEnabled(true);
    ui->actionChatMS->setEnabled(true);
    ui->actionPhotoMS->setEnabled(true);
}

void MainWindow::on_actionShopCart_triggered()
{
    m_userUI->hide();
    m_buyerMS->hide();
    m_sellerMS->hide();
    m_shoesMS->hide();
    m_storeMS->hide();
    m_shopCartMS->show();
    m_orderMS->hide();
    m_shoesDetailsMS->hide();
    m_evaluationMS->hide();
    m_chatMS->hide();
    m_photoMS->hide();
    ui->actionUserMS->setEnabled(true);
    ui->actionBuyerMS->setEnabled(true);
    ui->actionSellerMS->setEnabled(true);
    ui->actionShoesMS->setEnabled(true);
    ui->actionShoesDetailsMS->setEnabled(true);
    ui->actionStoreMS->setEnabled(true);
    ui->actionShopCart->setEnabled(false); ////
    ui->actionOrderMS->setEnabled(true);
    ui->actionEvaluationMS->setEnabled(true);
    ui->actionChatMS->setEnabled(true);
    ui->actionPhotoMS->setEnabled(true);
}

void MainWindow::on_actionShoesDetailsMS_triggered()
{
    m_userUI->hide();
    m_buyerMS->hide();
    m_sellerMS->hide();
    m_shoesMS->hide();
    m_storeMS->hide();
    m_shopCartMS->hide();
    m_orderMS->hide();
    m_shoesDetailsMS->show();
    m_evaluationMS->hide();
    m_chatMS->hide();
    m_photoMS->hide();
    ui->actionUserMS->setEnabled(true);
    ui->actionBuyerMS->setEnabled(true);
    ui->actionSellerMS->setEnabled(true);
    ui->actionShoesMS->setEnabled(true);
    ui->actionShoesDetailsMS->setEnabled(false); ////
    ui->actionStoreMS->setEnabled(true);
    ui->actionShopCart->setEnabled(true);
    ui->actionOrderMS->setEnabled(true);
    ui->actionEvaluationMS->setEnabled(true);
    ui->actionChatMS->setEnabled(true);
    ui->actionPhotoMS->setEnabled(true);
}

void MainWindow::on_actionSellerMS_triggered()
{
    m_userUI->hide();
    m_buyerMS->hide();
    m_sellerMS->show();
    m_shoesMS->hide();
    m_storeMS->hide();
    m_shopCartMS->hide();
    m_orderMS->hide();
    m_shoesDetailsMS->hide();
    m_evaluationMS->hide();
    m_chatMS->hide();
    m_photoMS->hide();
    ui->actionUserMS->setEnabled(true);
    ui->actionBuyerMS->setEnabled(true);
    ui->actionSellerMS->setEnabled(false); ////
    ui->actionShoesMS->setEnabled(true);
    ui->actionShoesDetailsMS->setEnabled(true);
    ui->actionStoreMS->setEnabled(true);
    ui->actionShopCart->setEnabled(true);
    ui->actionOrderMS->setEnabled(true);
    ui->actionEvaluationMS->setEnabled(true);
    ui->actionChatMS->setEnabled(true);
    ui->actionPhotoMS->setEnabled(true);
}

void MainWindow::on_actionBuyerMS_triggered()
{
    m_userUI->hide();
    m_buyerMS->show();
    m_sellerMS->hide();
    m_shoesMS->hide();
    m_storeMS->hide();
    m_shopCartMS->hide();
    m_orderMS->hide();
    m_shoesDetailsMS->hide();
    m_evaluationMS->hide();
    m_chatMS->hide();
    m_photoMS->hide();

    ui->actionUserMS->setEnabled(true);
    ui->actionBuyerMS->setEnabled(false); ////
    ui->actionSellerMS->setEnabled(true);
    ui->actionShoesMS->setEnabled(true);
    ui->actionShoesDetailsMS->setEnabled(true);
    ui->actionStoreMS->setEnabled(true);
    ui->actionShopCart->setEnabled(true);
    ui->actionOrderMS->setEnabled(true);
    ui->actionEvaluationMS->setEnabled(true);
    ui->actionChatMS->setEnabled(true);
    ui->actionPhotoMS->setEnabled(true);
}

void MainWindow::on_actionChatMS_triggered()
{
    m_userUI->hide();
    m_buyerMS->hide();
    m_sellerMS->hide();
    m_shoesMS->hide();
    m_storeMS->hide();
    m_shopCartMS->hide();
    m_orderMS->hide();
    m_shoesDetailsMS->hide();
    m_evaluationMS->hide();
    m_chatMS->show();
    m_photoMS->hide();
    ui->actionUserMS->setEnabled(true);
    ui->actionBuyerMS->setEnabled(true);
    ui->actionSellerMS->setEnabled(true);
    ui->actionShoesMS->setEnabled(true);
    ui->actionShoesDetailsMS->setEnabled(true);
    ui->actionStoreMS->setEnabled(true);
    ui->actionShopCart->setEnabled(true);
    ui->actionOrderMS->setEnabled(true);
    ui->actionEvaluationMS->setEnabled(true);
    ui->actionChatMS->setEnabled(false); ////
    ui->actionPhotoMS->setEnabled(true);////
}

void MainWindow::on_actionPhotoMS_triggered()
{
    m_userUI->hide();
    m_buyerMS->hide();
    m_sellerMS->hide();
    m_shoesMS->hide();
    m_storeMS->hide();
    m_shopCartMS->hide();
    m_orderMS->hide();
    m_shoesDetailsMS->hide();
    m_evaluationMS->hide();
    m_chatMS->hide();
    m_photoMS->show();
    ui->actionUserMS->setEnabled(true);
    ui->actionBuyerMS->setEnabled(true);
    ui->actionSellerMS->setEnabled(true);
    ui->actionShoesMS->setEnabled(true);
    ui->actionShoesDetailsMS->setEnabled(true);
    ui->actionStoreMS->setEnabled(true);
    ui->actionShopCart->setEnabled(true);
    ui->actionOrderMS->setEnabled(true);
    ui->actionEvaluationMS->setEnabled(true);
    ui->actionChatMS->setEnabled(true);
    ui->actionPhotoMS->setEnabled(false);////
}
void MainWindow::slotSendMsgToClient(QString id, QString msg)
{

    if(GlobalVars::m_socketMap.contains(id))
    {
        GlobalVars::m_socketMap[id]->slotSendMsg(msg);
    }


}
void MainWindow::slotSendPhotoToClient(QString id, bool isALL)
{
    if(GlobalVars::m_socketMap.contains(id))
    {
        GlobalVars::m_socketMap[id]->slotSendPhoto(isALL);
    }

}
