#include "globalvars.h"

QQueue<QString> GlobalVars::g_msgQueue;

BuyerInfoList *GlobalVars::g_buyerInfoList = new BuyerInfoList;
UserInfoList *GlobalVars::g_userInfoList = new UserInfoList;
SellerInfoList *GlobalVars::g_sellerInfoList = new SellerInfoList;
ShoesInfoList *GlobalVars::g_shoesInfoList = new ShoesInfoList;
StoreInfoList *GlobalVars::g_storeInfoList = new StoreInfoList;
ShopCartList *GlobalVars::g_shopCartList = new ShopCartList;
OrderInfoList *GlobalVars::g_orderInfoList = new OrderInfoList;
ShoesDetailsList *GlobalVars::g_shoesDetailsList = new ShoesDetailsList;
EvaluationInfoList *GlobalVars::g_evaluationInfoList = new EvaluationInfoList;
ChatInfoList *GlobalVars::g_chatInfoList = new ChatInfoList;
PhotoInfoList *GlobalVars::g_photoInfoList = new PhotoInfoList;

UserInfoMap GlobalVars::g_userInfoMap;
