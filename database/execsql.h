#ifndef EXECSQL_H
#define EXECSQL_H
#include "userinfo.h"
#include "buyerinfo.h"
#include "shoesinfo.h"
#include "globalvars.h"
#include "storeinfo.h"
#include "shopcart.h"
#include "orderinfo.h"
#include "evaluationinfo.h"
#include "chatinfo.h"
#include "photoinfo.h"

class ExecSQL
{

public:

//////////////////////////  User    /////////////////////////////////
    static void selectAllUsers(void);
    static void updateUserInfoList(QString);
    static void selectUserInfoForId(QString);
    static void selectUserInfoForPswd(QString);
    static void selectUserInfoForRole(QString);
    static void selectUserInfoForDate(QString);

    static void modifyUserInfoPswd(QString id, QString pswd);
    static void modifyUserInfoRole(QString id, QString role);
    static void modifyUserInfoDate(QString id, QString date);

    static void insertUserInfo(UserInfo info);
    static void deleteUserInfo(QString id);

/////////////////////////////////////   Buyer   ////////////////////
    static void selectAllBuyers(void);
    static void updateBuyerInfoList(QString);

    static void selectBuyerInfoForID(QString);
    static void selectBuyerInfoForName(QString);
    static void selectBuyerInfoForTel(QString);
    static void selectBuyerInfoForAddress(QString);

    static void modifyBuyerInfoName(QString id, QString name);
    static void modifyBuyerInfoTel(QString id, QString telephone);
    static void modifyBuyerInfoAddress(QString id, QString address);

    static void insertBuyerInfo(BuyerInfo info);
    static void deleteBuyerInfo(QString id);
////////////////////////////// Seller //////////////////
    static void selectAllSellers(void);
    static void updateSellerInfoList(QString);

    static void selectSellerInfoForID(QString);
    static void selectSellerInfoForName(QString);
    static void selectSellerInfoForTel(QString);
    static void selectSellerInfoForAddress(QString);

    static void modifySellerInfoName(QString id, QString name);
    static void modifySellerInfoTel(QString id, QString telephone);
    static void modifySellerInfoAddress(QString id, QString address);

    static void insertSellerInfo(SellerInfo info);
    static void deleteSellerInfo(QString id);
/////////////////////////////   Shoes   //////////////////////////
    static void updateShoesInfoList(QString);
    static void selectAllShoes(void);
    static void selectShoesInfoForID(QString);
    static void selectShoesInfoForStoreID(QString);
    static void selectShoesInfoForShoesName(QString);
    static void selectShoesInfoForBottomPrice(QString);
    static void selectShoesInfoForFreight(QString);

    static void modifyShoesInfoStoreID(QString id, QString storeID);
    static void modifyShoesInfoShoesName(QString id, QString shoesName);

    static void modifyShoesInfoFreight(QString id, QString freight);

    static void insertShoesInfo(ShoesInfo info);
    static void deleteShoesInfo(QString id);
/////////////////////// Store    ////////////////////
    static void selectAllStores(void);
    static void updateStoreInfoList(QString);

    static void selectStoreInfoForID(QString);
    static void selectStoreInfoForSellerID(QString);
    static void selectStoreInfoForStoreName(QString);
    static void selectStoreInfoForBrand(QString);
    static void selectStoreInfoForDate(QString);
    static void selectStoreInfoForReputation(QString);

    static void modifyStoreInfoStoreSellerID(QString id, QString sellerID);
    static void modifyStoreInfoStoreName(QString id, QString storeName);
    static void modifyStoreInfoBrand(QString id, QString brand);
    static void modifyStoreInfoDate(QString id, QString date);
    static void modifyStoreInfoReputation(QString id, QString reputation);

    static void insertStoreInfo(StoreInfo info);
    static void deleteStoreInfo(QString id);

//////////////////////////////Shop Cart/////////////////////////////////////
    static void updateShopCartInfoList(QString sql);
    static void selectAllShopCart(void);

    static void selectShopCartInfoForID(QString id);
    static void selectShopCartInfoForDatailID(QString id);
    static void selectShopCartInfoForCount(QString count);

    static void modifyShopCartInfoDatailID(QString id, QString detailID);
    static void modifyShopCartInfoCount(QString id, QString detailID, QString count);

    static void insertShopCart(ShopCart info);
    static void deleteShopCart(QString id);
//////////////////////////  Order ////////////////////////
    static void updateOrderInfoList(QString sql);
    static void selectAllOrders(void);

    static void selectOrderInfoForID(QString id);
    static void selectOrderInfoForBuyerID(QString buyerID);
    static void selectOrderInfoForDetailID(QString detailID);
    static void selectOrderInfoForCount(QString count);
    static void selectOrderInfoForState(QString state);
    static void selectOrderInfoForCreateDate(QString createDate);
    static void selectOrderInfoForDeliveryDate(QString deliveryDate);
    static void selectOrderInfoForFinishDate(QString finishDate);

    static void modifyOrderInfoBuyerID(QString id, QString buyerID);
    static void modifyOrderInfoDetailID(QString id, QString detailID);
    static void modifyOrderInfoCount(QString id, QString detailID, QString buyerID, QString count);
    static void modifyOrderInfoState(QString id, QString detailID, QString buyerID, QString state);
    static void modifyOrderInfoCreateDate(QString id, QString detailID, QString buyerID, QString createDate);
    static void modifyOrderInfoDeliveryDate(QString id, QString detailID, QString buyerID, QString DeliveryDate);
    static void modifyOrderInfoFinishDate(QString id, QString detailID, QString buyerID, QString FinishDate);

    static void insertOrderInfo(OrderInfo info);
    static void deleteOrderInfo(QString id);

/////////////////////////// Shoes Details /////////////////////////////
    static void updateShoesDetailsList(QString sql);
    static void selectAllShoesDetails(void);

    static void selectShoesDetailsForID(QString id);
    static void selectShoesDetailsForShoesID(QString id);
    static void selectShoesDetailsForPhotoID(QString id);
    static void selectShoesDetailsForSize(QString size);
    static void selectShoesDetailsForColor(QString color);
    static void selectShoesDetailsForPrice(QString price);
//    static void selectShoesDetailsForPhotoCount(QString photoCount);
//    static void selectShoesDetailsForPhotoPath(QString photoPath);
    static void selectShoesDetailsForStock(QString stock);


    static void modifyShoesDetailsShoesID(QString id, QString shoesID);
    static void modifyShoesDetailsPhotoID(QString id, QString shoesID);
    static void modifyShoesDetailsSize(QString id, QString size);
    static void modifyShoesDetailsColor(QString id, QString color);
    static void modifyShoesDetailsPrice(QString id, QString price);
//    static void modifyShoesDetailsPhotoCount(QString id, QString photoCount);
//    static void modifyShoesDetailsPhotoPath(QString id, QString photoPath);
    static void modifyShoesDetailsStock(QString id, QString stock);

    static void insertShoesDetails(ShoesDetails info);
    static void deleteShoesDetails(QString id);

//////////////////////////////  Evaluation ////////////////////
    static void updateEvaluationInfoList(QString sql);
    static void selectAllEvaluations(void);

    static void selectEvaluationInfoForID(QString id);
    static void selectEvaluationInfoForShoesID(QString ShoesID);
    static void selectEvaluationInfoForBuyerID(QString BuyerID);
    static void selectEvaluationInfoForPhotoID(QString PhotoID);
    static void selectEvaluationInfoForGrade(QString Grade);
    static void selectEvaluationInfoForContent(QString Content);
//    static void selectEvaluationInfoForPhotoCount(QString PhotoCount);
//    static void selectEvaluationInfoForPhotoPath(QString PhotoPath);
    static void selectEvaluationInfoForDate(QString Date);

    static void modifyEvaluationInfoShoesID(QString id, QString shoesID);
    static void modifyEvaluationInfoBuyerID(QString id, QString BuyerID);
    static void modifyEvaluationInfoPhotoID(QString id, QString PhotoID);
    static void modifyEvaluationInfoGrade(QString id, QString Grade);
    static void modifyEvaluationInfoContent(QString id, QString Content);
//    static void modifyEvaluationInfoPhotoCount(QString id, QString PhotoCount);
//    static void modifyEvaluationInfoPhotoPath(QString id, QString PhotoPath);
    static void modifyEvaluationInfoDate(QString id, QString Date);

    static void insertEvaluationInfo(EvaluationInfo info);
    static void deleteEvaluationInfo(QString id);

    //////////////////////////////// Chat ////////////////////////////////////////////////
    static void updateChatInfoList(QString sql);
    static void selectAllChats(void);

    static void selectChatInfoForID(QString id);
    static void selectChatInfoForBuyerID(QString BuyerID);
    static void selectChatInfoForSellerID(QString SellerID);
    static void selectChatInfoForPhotoID(QString photoID);
    static void selectChatInfoForContent(QString Content);
//    static void selectChatInfoForPhotoCount(QString photoCount);
//    static void selectChatInfoForPhotoPath(QString PhotoPath);
    static void selectChatInfoForDate(QString Date);

    static void modifyChatInfoBuyerID(QString id, QString BuyerID);
    static void modifyChatInfoSellerID(QString id, QString SellerID);
    static void modifyChatInfoPhotoID(QString id, QString photoID);
    static void modifyChatInfoContent(QString id, QString Content);
//    static void modifyChatInfoPhotoCount(QString id, QString PhotoCount);
//    static void modifyChatInfoPhotoPath(QString id, QString PhotoPath);
    static void modifyChatInfoDate(QString id, QString Date);

    static void insertChatInfo(ChatInfo info);
    static void deleteChatInfo(QString id);

/////////////////////////////////////// Photo ////////////////////////////////////////////////
    static void updatePhotoInfoList(QString sql);
    static void selectAllPhotos(void);

    static void selectPhotoInfoForID(QString id);
    static void selectPhotoInfoForPhotoCount(QString photoCount);
    static void selectPhotoInfoForPhotoPath(QString photoPath);
    static void modifyPhotoInfoPhotoCount(QString id, QString photoCount);
    static void modifyPhotoInfoPhotoPath(QString id, QString photoPath);

    static void insertPhotoInfo(PhotoInfo info);
    static void deletePhotoInfo(QString id);
};

#endif // EXECSQL_H
