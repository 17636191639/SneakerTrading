#include "execsql.h"
#include <QSqlQuery>    ///sql询问类，提供数据库的语句执行
#include <QDebug>
#include <QSqlRecord>


//////////////////////////////// user ///////////////////////
void ExecSQL::selectAllUsers(void)
{
    QString sql = QString("select * from user_info");
    updateUserInfoList(sql);
}
void ExecSQL::updateUserInfoList(QString sql)
{
    GlobalVars::g_userInfoList->clear();
    GlobalVars::g_userInfoMap.clear();
    QSqlQuery query;
    if(query.exec(sql))
    {
        int index_id = query.record().indexOf("id");
        int index_pswd = query.record().indexOf("pswd");
        int index_role = query.record().indexOf("role");
        int index_date = query.record().indexOf("date");

        //qDebug() << "data size" << query.size();

        while(query.next())
        {
            QString id = query.value(index_id).toString();
            QString pswd = query.value(index_pswd).toString();
            QString role = query.value(index_role).toString();
            QString date = query.value(index_date).toString();

            UserInfo info(id, pswd, role, date);
            GlobalVars::g_userInfoList->append(info);

        }

        for(UserInfoList::iterator it = GlobalVars::g_userInfoList->begin();
            it != GlobalVars::g_userInfoList->end(); it++)
        {
           GlobalVars::g_userInfoMap.insert(it->getID(), it);
        }

    }else
    {
        qDebug() << "执行语句失败";
    }

}
void ExecSQL::selectUserInfoForId(QString id)
{
    QString sql = QString("select * from user_info where id = '%1'");
    QString mysql = sql.arg(id);
    updateUserInfoList(mysql);
}
void ExecSQL::selectUserInfoForPswd(QString pswd)
{
    QString sql = QString("select * from user_info where pswd = '%1'");
    QString mysql = sql.arg(pswd);
    updateUserInfoList(mysql);
}
void ExecSQL::selectUserInfoForRole(QString role)
{
    QString sql = QString("select * from user_info where role = '%1'");
    QString mysql = sql.arg(role);
    updateUserInfoList(mysql);
}
void ExecSQL::selectUserInfoForDate(QString date)
{
    QString sql = QString("select * from user_info where date = '%1'");
    QString mysql = sql.arg(date);
    updateUserInfoList(mysql);
}
void ExecSQL::modifyUserInfoPswd(QString id, QString pswd)
{
    QString sql = QString("update user_info set pswd = '%1' where id = '%2';");
    QString exe_sql = sql.arg(pswd).arg(id);
    qDebug() << exe_sql;
    updateUserInfoList(exe_sql);

}
void ExecSQL::modifyUserInfoRole(QString id, QString role)
{
    QString sql = QString("update user_info set role = '%1' where id = '%2';");
    QString exe_sql = sql.arg(role).arg(id);
    updateUserInfoList(exe_sql);
}
void ExecSQL::modifyUserInfoDate(QString id, QString date)
{
    QString sql = QString("update user_info set date = '%1' where id = '%2';");
    QString exe_sql = sql.arg(date).arg(id);
    updateUserInfoList(exe_sql);
}
void ExecSQL::insertUserInfo(UserInfo info) //插入新数据需要注意主键
{

    QString UserInfoInsert = QString("insert into user_info values('%1','%2','%3','%4');");
    QString UserInfoInsertSql = UserInfoInsert.arg(info.getID()).arg(info.getPswd()).arg(info.getRole()).arg(info.getDate());

    updateUserInfoList(UserInfoInsertSql);
}
void ExecSQL::deleteUserInfo(QString id)
{
    QString sql = QString("delete from user_info where id = '%1';");
    QString exe_sql = sql.arg(id);
    updateUserInfoList(exe_sql);

}
/////////////////////////////////////////////////////////////Buyer/////////////////////////////////////////
void ExecSQL::selectAllBuyers(void)
{
    QString sql = QString("select * from buyer_info");
    updateBuyerInfoList(sql);
}
void ExecSQL::updateBuyerInfoList(QString sql)
{
    GlobalVars::g_buyerInfoList->clear();

    QSqlQuery query;
    if(query.exec(sql))
    {
        int index_id = query.record().indexOf("id");
        int index_name = query.record().indexOf("name");
        int index_tel = query.record().indexOf("telephone");
        int index_address = query.record().indexOf("address");

        //qDebug() << "data size" << query.size();

        while(query.next())
        {
            QString id = query.value(index_id).toString();
            QString name = query.value(index_name).toString();
            QString tel = query.value(index_tel).toString();
            QString address = query.value(index_address).toString();

            BuyerInfo info(id, name, tel, address);
            GlobalVars::g_buyerInfoList->append(info);
        }
    }else
    {
        qDebug() << "执行语句失败";
    }
}

void ExecSQL::selectBuyerInfoForID(QString id)
{
    QString sql = QString("select * from buyer_info where id = '%1'");
    QString mysql = sql.arg(id);
    updateBuyerInfoList(mysql);
}
void ExecSQL::selectBuyerInfoForName(QString name)
{
    QString sql = QString("select * from buyer_info where name = '%1'");
    QString mysql = sql.arg(name);
    updateBuyerInfoList(mysql);
}
void ExecSQL::selectBuyerInfoForTel(QString tel)
{
    QString sql = QString("select * from buyer_info where telephone = '%1'");
    QString mysql = sql.arg(tel);
    updateBuyerInfoList(mysql);
}
void ExecSQL::selectBuyerInfoForAddress(QString address)
{
    QString sql = QString("select * from buyer_info where address = '%1'");
    QString mysql = sql.arg(address);
    updateBuyerInfoList(mysql);
}

void ExecSQL::modifyBuyerInfoName(QString id, QString name)
{
    QString sql = QString("update buyer_info set name = '%1' where id = '%2';");
    QString mysql = sql.arg(name).arg(id);
    updateBuyerInfoList(mysql);
}
void ExecSQL::modifyBuyerInfoTel(QString id, QString telephone)
{
    QString sql = QString("update buyer_info set telephone = '%1' where id = '%2';");
    QString mysql = sql.arg(telephone).arg(id);
    updateBuyerInfoList(mysql);
}
void ExecSQL::modifyBuyerInfoAddress(QString id, QString address)
{
    QString sql = QString("update buyer_info set address = '%1' where id = '%2';");
    QString mysql = sql.arg(address).arg(id);
    updateBuyerInfoList(mysql);
}

void ExecSQL::insertBuyerInfo(BuyerInfo info)
{
    QString BuyerInfoInsert = QString("insert into buyer_info values('%1','%2','%3','%4');");
    QString BuyerInfoInsertSql = BuyerInfoInsert.arg(info.getID()).arg(info.getName()).arg(info.getTel()).arg(info.getAddress());

    updateBuyerInfoList(BuyerInfoInsertSql);
}
void ExecSQL::deleteBuyerInfo(QString id)
{

}



/////////////////////////////////////////////////////////    Seller  /////////////////////////////////////////////////
void ExecSQL::selectAllSellers(void)
{
    QString sql = QString("select * from seller_info");
    updateSellerInfoList(sql);
}
void ExecSQL::updateSellerInfoList(QString sql)
{
    GlobalVars::g_sellerInfoList->clear();

    QSqlQuery query;
    if(query.exec(sql))
    {
        int index_id = query.record().indexOf("id");
        int index_name = query.record().indexOf("name");
        int index_tel = query.record().indexOf("telephone");
        int index_address = query.record().indexOf("address");

        while(query.next())
        {
            QString id = query.value(index_id).toString();
            QString name = query.value(index_name).toString();
            QString tel = query.value(index_tel).toString();
            QString address = query.value(index_address).toString();

            SellerInfo info(id, name, tel, address);
            GlobalVars::g_sellerInfoList->append(info);
        }
    }else
    {
        qDebug() << "执行语句失败";
    }
}

void ExecSQL::selectSellerInfoForID(QString id)
{
    QString sql = QString("select * from seller_info where id = '%1'");
    QString mysql = sql.arg(id);
    updateSellerInfoList(mysql);
}
void ExecSQL::selectSellerInfoForName(QString name)
{
    QString sql = QString("select * from seller_info where name = '%1'");
    QString mysql = sql.arg(name);
    updateSellerInfoList(mysql);
}
void ExecSQL::selectSellerInfoForTel(QString tel)
{
    QString sql = QString("select * from seller_info where telephone = '%1'");
    QString mysql = sql.arg(tel);
    updateSellerInfoList(mysql);
}
void ExecSQL::selectSellerInfoForAddress(QString address)
{
    QString sql = QString("select * from seller_info where address = '%1'");
    QString mysql = sql.arg(address);
    updateSellerInfoList(mysql);
}

void ExecSQL::modifySellerInfoName(QString id, QString name)
{
    QString sql = QString("update seller_info set name = '%1' where id = '%2';");
    QString mysql = sql.arg(name).arg(id);
    updateSellerInfoList(mysql);
}
void ExecSQL::modifySellerInfoTel(QString id, QString telephone)
{
    QString sql = QString("update seller_info set telephone = '%1' where id = '%2';");
    QString mysql = sql.arg(telephone).arg(id);
    updateSellerInfoList(mysql);
}
void ExecSQL::modifySellerInfoAddress(QString id, QString address)
{
    QString sql = QString("update seller_info set address = '%1' where id = '%2';");
    QString mysql = sql.arg(address).arg(id);
    updateSellerInfoList(mysql);
}

void ExecSQL::insertSellerInfo(SellerInfo info)
{
    QString SellerInfoInsert = QString("insert into seller_info values('%1','%2','%3','%4');");
    QString SellerInfoInsertSql = SellerInfoInsert.arg(info.getID()).arg(info.getName()).arg(info.getTel()).arg(info.getAddress());

    updateSellerInfoList(SellerInfoInsertSql);
}
void ExecSQL::deleteSellerInfo(QString id)
{

}

////////////////////////////////////////////////    Shoes    /////////////////////////////////////////////////
void ExecSQL::selectAllShoes(void)
{
    QString sql = QString("select * from shoes_info");
    updateShoesInfoList(sql);
}
void ExecSQL::updateShoesInfoList(QString sql)
{
    GlobalVars::g_shoesInfoList->clear();

    QSqlQuery query;
    if(query.exec(sql))
    {
        int index_id = query.record().indexOf("id");
        int index_storeID = query.record().indexOf("store_id");
        int index_name = query.record().indexOf("name");
        int index_freight = query.record().indexOf("freight");

        while(query.next())
        {
            QString id = query.value(index_id).toString();
            QString storeID = query.value(index_storeID).toString();
            QString name = query.value(index_name).toString();
            QString freight = query.value(index_freight).toString();

            ShoesInfo info(id, storeID, name, freight);
            GlobalVars::g_shoesInfoList->append(info);

            //qDebug() << id << ", " << storeID << ", " << name << ", " << freight;
        }
    }else
    {
        qDebug() << "执行语句失败";
    }
}

void ExecSQL::selectShoesInfoForID(QString id)
{
    QString sql = QString("select * from shoes_info where id = '%1'");
    QString mysql = sql.arg(id);
    updateShoesInfoList(mysql);
}
void ExecSQL::selectShoesInfoForStoreID(QString store_id)
{
    QString sql = QString("select * from shoes_info where shore_id = '%1'");
    QString mysql = sql.arg(store_id);
    updateShoesInfoList(mysql);
}
void ExecSQL::selectShoesInfoForShoesName(QString name)
{
    QString sql = QString("select * from shoes_info where name = '%1'");
    QString mysql = sql.arg(name);
    updateShoesInfoList(mysql);
}

void ExecSQL::selectShoesInfoForFreight(QString freight)
{
    QString sql = QString("select * from shoes_info where freight = '%1'");
    QString mysql = sql.arg(freight);
    updateShoesInfoList(mysql);
}

void ExecSQL::modifyShoesInfoStoreID(QString id, QString storeID)
{
    QString sql = QString("update shoes_info set store_id = '%1' where id = '%2';");
    QString mysql = sql.arg(storeID).arg(id);
    updateShoesInfoList(mysql);
}
void ExecSQL::modifyShoesInfoShoesName(QString id, QString shoesName)
{
    QString sql = QString("update shoes_info set name = '%1' where id = '%2';");
    QString mysql = sql.arg(shoesName).arg(id);
    updateShoesInfoList(mysql);
}

void ExecSQL::modifyShoesInfoFreight(QString id, QString freight)
{
    QString sql = QString("update shoes_info set freight = '%1' where id = '%2';");
    QString mysql = sql.arg(freight).arg(id);
    updateShoesInfoList(mysql);
}

void ExecSQL::insertShoesInfo(ShoesInfo info)
{
    QString ShoesInfoInsert = QString("insert into shoes_info values('%1','%2','%3','%4');");
    QString ShoesInfoInsertSql = ShoesInfoInsert.arg(info.getID()).arg(info.getStoreID()).arg(info.getShoesName()).arg(info.getFreight());

    updateShoesInfoList(ShoesInfoInsertSql);
}
void ExecSQL::deleteShoesInfo(QString id)
{

}
//////////////////////////////////////////////////////// Store ///////////////////////////////////////////////
void ExecSQL::updateStoreInfoList(QString sql)
{
    GlobalVars::g_storeInfoList->clear();

    QSqlQuery query;
    if(query.exec(sql))
    {
        int index_id = query.record().indexOf("id");
        int index_sellerID = query.record().indexOf("seller_id");
        int index_name = query.record().indexOf("name");
        int index_brand = query.record().indexOf("brand");
        int index_date = query.record().indexOf("date");
        int index_reputation = query.record().indexOf("reputation");

        while(query.next())
        {
            QString id = query.value(index_id).toString();
            QString sellerID = query.value(index_sellerID).toString();
            QString name = query.value(index_name).toString();
            QString brand = query.value(index_brand).toString();
            QString date = query.value(index_date).toString();
            QString reputation = query.value(index_reputation).toString();

            StoreInfo info(id, sellerID, name, brand, date, reputation);
            GlobalVars::g_storeInfoList->append(info);

            //qDebug() << id << ", " << storeID << ", " << name << ", " << freight;
        }
    }else
    {
        qDebug() << "执行语句失败";
    }
}
void ExecSQL::selectAllStores(void)
{
    QString sql = QString("select * from store_info");
    updateStoreInfoList(sql);
}
void ExecSQL::selectStoreInfoForID(QString id)
{
    QString sql = QString("select * from store_info where id = '%1'");
    QString mysql = sql.arg(id);
    updateStoreInfoList(mysql);
}
void ExecSQL::selectStoreInfoForSellerID(QString id)
{
    QString sql = QString("select * from store_info where seller_id = '%1'");
    QString mysql = sql.arg(id);
    updateStoreInfoList(mysql);
}
void ExecSQL::selectStoreInfoForStoreName(QString storeName)
{
    QString sql = QString("select * from store_info where name = '%1'");
    QString mysql = sql.arg(storeName);
    updateStoreInfoList(mysql);
}
void ExecSQL::selectStoreInfoForBrand(QString brand)
{
    QString sql = QString("select * from store_info where brand = '%1'");
    QString mysql = sql.arg(brand);
    updateStoreInfoList(mysql);
}
void ExecSQL::selectStoreInfoForDate(QString date)
{
    QString sql = QString("select * from store_info where date = '%1'");
    QString mysql = sql.arg(date);
    updateStoreInfoList(mysql);
}
void ExecSQL::selectStoreInfoForReputation(QString reputation)
{
    QString sql = QString("select * from store_info where reputation = '%1'");
    QString mysql = sql.arg(reputation);
    updateStoreInfoList(mysql);
}

void ExecSQL::modifyStoreInfoStoreSellerID(QString id, QString sellerID)
{
    QString sql = QString("update store_info set seller_id = '%1' where id = '%2';");
    QString mysql = sql.arg(sellerID).arg(id);
    updateStoreInfoList(mysql);
}
void ExecSQL::modifyStoreInfoStoreName(QString id, QString storeName)
{
    QString sql = QString("update store_info set name = '%1' where id = '%2';");
    QString mysql = sql.arg(storeName).arg(id);
    updateStoreInfoList(mysql);
}

void ExecSQL::modifyStoreInfoBrand(QString id, QString brand)
{
    QString sql = QString("update store_info set brand = '%1' where id = '%2';");
    QString mysql = sql.arg(brand).arg(id);
    updateStoreInfoList(mysql);
}
void ExecSQL::modifyStoreInfoDate(QString id, QString date)
{
    QString sql = QString("update store_info set date = '%1' where id = '%2';");
    QString mysql = sql.arg(date).arg(id);
    updateStoreInfoList(mysql);
}
void ExecSQL::modifyStoreInfoReputation(QString id, QString reputation)
{
    QString sql = QString("update store_info set reputation = '%1' where id = '%2';");
    QString mysql = sql.arg(reputation).arg(id);
    updateStoreInfoList(mysql);
}

void ExecSQL::insertStoreInfo(StoreInfo info)
{
    QString Insert = QString("insert into store_info values('%1','%2','%3','%4','%5','%6');");
    QString InsertSql = Insert.arg(info.getID()).arg(info.getSellerID()).arg(info.getStoreName()).
                        arg(info.getBrand()).arg(info.getDate()).arg(info.getReputation());

    updateShoesInfoList(InsertSql);
}
void ExecSQL::deleteStoreInfo(QString id)
{

}


/////////////////////////////////////////////////////////// Shop Cart ////////////////////////////////////////////
void ExecSQL::updateShopCartInfoList(QString sql)
{
    GlobalVars::g_shopCartList->clear();

    QSqlQuery query;
    if(query.exec(sql))
    {
        int index_id = query.record().indexOf("id");
        int index_detailID = query.record().indexOf("detail_id");
        int index_count = query.record().indexOf("count");

        while(query.next())
        {
            QString id = query.value(index_id).toString();
            QString detailID = query.value(index_detailID).toString();
            QString count = query.value(index_count).toString();


            ShopCart info(id, detailID, count);
            GlobalVars::g_shopCartList->append(info);
        }
    }else
    {
        qDebug() << "执行语句失败";
    }
}
void ExecSQL::selectAllShopCart(void)
{
    QString sql = QString("select * from shop_cart");
    updateShopCartInfoList(sql);
}

void ExecSQL::selectShopCartInfoForID(QString id)
{
    QString sql = QString("select * from shop_cart where id = '%1'");
    QString mysql = sql.arg(id);
    updateShopCartInfoList(mysql);

}
void ExecSQL::selectShopCartInfoForDatailID(QString id)
{
    QString sql = QString("select * from shop_cart where detail_id = '%1'");
    QString mysql = sql.arg(id);
    updateShopCartInfoList(mysql);
}
void ExecSQL::selectShopCartInfoForCount(QString count)
{
    QString sql = QString("select * from shop_cart where count = '%1'");
    QString mysql = sql.arg(count);
    updateShopCartInfoList(mysql);
}

void ExecSQL::modifyShopCartInfoDatailID(QString id, QString detailID)
{
    QString sql = QString("update shop_cart set detail_id = '%1' where id = '%2';");
    QString mysql = sql.arg(detailID).arg(id);
    updateShopCartInfoList(mysql);
}
void ExecSQL::modifyShopCartInfoCount(QString id, QString detailID,QString count)
{
    QString sql = QString("update shop_cart set count = '%1' where id = '%2' and detail_id = '%3';");
    QString mysql = sql.arg(count).arg(id).arg(detailID);
    updateShopCartInfoList(mysql);
}

void ExecSQL::insertShopCart(ShopCart info)
{
    QString Insert = QString("insert into shop_cart values('%1','%2','%3');");
    QString InsertSql = Insert.arg(info.getID()).arg(info.getDetailID()).arg(info.getCount());

    updateShopCartInfoList(InsertSql);

}
void ExecSQL::deleteShopCart(QString id)
{
    QString Delete = QString("delete from shop_cart where id = '%1';");
    QString DeleteSQL = Delete.arg(id);
    updateShopCartInfoList(DeleteSQL);
}
//////////////////////////////////////// Order ////////////////////////////////////////////////////////////////
void ExecSQL::updateOrderInfoList(QString sql)
{
    GlobalVars::g_orderInfoList->clear();

    QSqlQuery query;
    if(query.exec(sql))
    {
        int index_id = query.record().indexOf("id");
        int index_buyerID = query.record().indexOf("buyer_id");
        int index_detailID = query.record().indexOf("detail_id");
        int index_count = query.record().indexOf("count");
        int index_state = query.record().indexOf("state");
        int index_createDate = query.record().indexOf("create_date");
        int index_deliveryDate = query.record().indexOf("delivery_date");
        int index_finishDate = query.record().indexOf("finish_date");

        while(query.next())
        {
            QString id = query.value(index_id).toString();
            QString buyerID = query.value(index_buyerID).toString();
            QString detailID = query.value(index_detailID).toString();
            QString count = query.value(index_count).toString();
            QString state = query.value(index_state).toString();
            QString createDate = query.value(index_createDate).toString();
            QString deliveryDate = query.value(index_deliveryDate).toString();
            QString finishDate = query.value(index_finishDate).toString();


            OrderInfo info(id, buyerID, detailID, count, state, createDate, deliveryDate, finishDate);
            GlobalVars::g_orderInfoList->append(info);
        }
    }else
    {
        qDebug() << "执行语句失败";
    }
}
void ExecSQL::selectAllOrders(void)
{
    QString sql = QString("select * from order_info");

    updateOrderInfoList(sql);
}

void ExecSQL::selectOrderInfoForID(QString id)
{
    QString sql = QString("select * from order_info where id = '%1'");
    QString mysql = sql.arg(id);
    updateOrderInfoList(mysql);
}
void ExecSQL::selectOrderInfoForBuyerID(QString buyerID)
{
    QString sql = QString("select * from order_info where buyer_id = '%1'");
    QString mysql = sql.arg(buyerID);
    updateOrderInfoList(mysql);
}
void ExecSQL::selectOrderInfoForDetailID(QString detailID)
{
    QString sql = QString("select * from order_info where detail_id = '%1'");
    QString mysql = sql.arg(detailID);
    updateOrderInfoList(mysql);
}
void ExecSQL::selectOrderInfoForCount(QString count)
{
    QString sql = QString("select * from order_info where count = '%1'");
    QString mysql = sql.arg(count);
    updateOrderInfoList(mysql);
}
void ExecSQL::selectOrderInfoForState(QString state)
{
    QString sql = QString("select * from order_info where state = '%1'");
    QString mysql = sql.arg(state);
    updateOrderInfoList(mysql);
}
void ExecSQL::selectOrderInfoForCreateDate(QString createDate)
{
    QString sql = QString("select * from order_info where create_date = '%1'");
    QString mysql = sql.arg(createDate);
    updateOrderInfoList(mysql);
}
void ExecSQL::selectOrderInfoForDeliveryDate(QString deliveryDate)
{
    QString sql = QString("select * from order_info where delivery_date = '%1'");
    QString mysql = sql.arg(deliveryDate);
    updateOrderInfoList(mysql);
}
void ExecSQL::selectOrderInfoForFinishDate(QString finishDate)
{
    QString sql = QString("select * from order_info where finish_date = '%1'");
    QString mysql = sql.arg(finishDate);
    updateOrderInfoList(mysql);
}

void ExecSQL::modifyOrderInfoBuyerID(QString id, QString buyerID)
{
    QString sql = QString("update order_info set buyer_id = '%1' where id = '%2';");
    QString mysql = sql.arg(buyerID).arg(id);
    updateOrderInfoList(mysql);
}
void ExecSQL::modifyOrderInfoDetailID(QString id, QString detailID)
{
    QString sql = QString("update order_info set detail_id = '%1' where id = '%2';");
    QString mysql = sql.arg(detailID).arg(id);
    updateOrderInfoList(mysql);
}
void ExecSQL::modifyOrderInfoCount(QString id, QString detailID, QString buyerID, QString count)
{
    QString sql = QString("update order_info set count = '%1' where id = '%2' and detail_id = '%3' and buyer_id = '%4';");
    QString mysql = sql.arg(count).arg(id).arg(detailID).arg(buyerID);
    updateOrderInfoList(mysql);
}
void ExecSQL::modifyOrderInfoState(QString id, QString detailID, QString buyerID, QString state)
{
    QString sql = QString("update order_info set state = '%1' where id = '%2' and detail_id = '%3' and buyer_id = '%4';");
    QString mysql = sql.arg(state).arg(id).arg(detailID).arg(buyerID);
    updateOrderInfoList(mysql);
}
void ExecSQL::modifyOrderInfoCreateDate(QString id, QString detailID, QString buyerID, QString createDate)
{
    QString sql = QString("update order_info set create_date = '%1' where id = '%2' and detail_id = '%3' and buyer_id = '%4';");
    QString mysql = sql.arg(createDate).arg(id).arg(detailID).arg(buyerID);
    updateOrderInfoList(mysql);
}
void ExecSQL::modifyOrderInfoDeliveryDate(QString id, QString detailID, QString buyerID, QString DeliveryDate)
{
    QString sql = QString("update order_info set delivery_date = '%1' where id = '%2' and detail_id = '%3' and buyer_id = '%4';");
    QString mysql = sql.arg(DeliveryDate).arg(id).arg(detailID).arg(buyerID);
    updateOrderInfoList(mysql);
}
void ExecSQL::modifyOrderInfoFinishDate(QString id, QString detailID, QString buyerID, QString FinishDate)
{
    QString sql = QString("update order_info set finish_date = '%1' where id = '%2' and detail_id = '%3' and buyer_id = '%4';");
    QString mysql = sql.arg(FinishDate).arg(id).arg(detailID).arg(buyerID);
    updateOrderInfoList(mysql);
}

void ExecSQL::insertOrderInfo(OrderInfo info)
{
    QString insert = QString("insert into order_info values('%1','%2','%3','%4','%5','%6','%7','%8')");
    QString insertSQL = insert.arg(info.getID()).arg(info.getBuyID()).arg(info.getDetailID()).arg(info.getCount())
            .arg(info.getState()).arg(info.getCreateDate()).arg(info.getDeliveryDate()).arg(info.getFinishDate());
    updateOrderInfoList(insertSQL);
}
void ExecSQL::deleteOrderInfo(QString id)
{
    QString Delete = QString("delete from order_info where id = '%1';");
    QString DeleteSQL = Delete.arg(id);
    updateShopCartInfoList(DeleteSQL);
}


/////////////////////////////////////////////////////Shoes Details//////////////////////////////////////////////
void ExecSQL::updateShoesDetailsList(QString sql)
{
    GlobalVars::g_shoesDetailsList->clear();

    QSqlQuery query;
    if(query.exec(sql))
    {
        int index_id = query.record().indexOf("id");
        int index_shoesID = query.record().indexOf("shoes_id");
        int index_photoID = query.record().indexOf("photo_id");
        int index_size = query.record().indexOf("size");
        int index_color = query.record().indexOf("color");
        int index_price = query.record().indexOf("price");
//        int index_photoCount = query.record().indexOf("photo_count");
//        int index_photoPath = query.record().indexOf("photo_path");
        int index_stock = query.record().indexOf("stock");

        while(query.next())
        {
            QString id = query.value(index_id).toString();
            QString shoesID = query.value(index_shoesID).toString();
            QString photoID = query.value(index_photoID).toString();
            QString size = query.value(index_size).toString();
            QString color = query.value(index_color).toString();
            QString price = query.value(index_price).toString();
//            QString photoCount = query.value(index_photoCount).toString();
//            QString photoPath = query.value(index_photoPath).toString();
            QString stock = query.value(index_stock).toString();


            ShoesDetails info(id, shoesID, photoID, size, color, price, stock);
            GlobalVars::g_shoesDetailsList->append(info);
        }
    }else
    {
        qDebug() << "执行语句失败";
    }
}
void ExecSQL::selectAllShoesDetails(void)
{
    QString sql = QString("select * from shoes_details");
    updateShoesDetailsList(sql);
}

void ExecSQL::selectShoesDetailsForID(QString id)
{
    QString sql = QString("select * from shoes_details where id = '%1'");
    QString mysql = sql.arg(id);
    updateShoesDetailsList(mysql);
}
void ExecSQL::selectShoesDetailsForShoesID(QString id)
{
    QString sql = QString("select * from shoes_details where shoes_id = '%1'");
    QString mysql = sql.arg(id);
    updateShoesDetailsList(mysql);
}
void ExecSQL::selectShoesDetailsForPhotoID(QString id)
{
    QString sql = QString("select * from shoes_details where photo_id = '%1'");
    QString mysql = sql.arg(id);
    updateShoesDetailsList(mysql);
}
void ExecSQL::selectShoesDetailsForSize(QString size)
{
    QString sql = QString("select * from shoes_details where size = '%1'");
    QString mysql = sql.arg(size);
    updateShoesDetailsList(mysql);
}
void ExecSQL::selectShoesDetailsForColor(QString color)
{
    QString sql = QString("select * from shoes_details where color = '%1'");
    QString mysql = sql.arg(color);
    updateShoesDetailsList(mysql);
}
void ExecSQL::selectShoesDetailsForPrice(QString price)
{
    QString sql = QString("select * from shoes_details where price = '%1'");
    QString mysql = sql.arg(price);
    updateShoesDetailsList(mysql);
}
//void ExecSQL::selectShoesDetailsForPhotoCount(QString photoCount)
//{
//    QString sql = QString("select * from shoes_details where photo_count = '%1'");
//    QString mysql = sql.arg(photoCount);
//    updateShoesDetailsList(mysql);
//}
//void ExecSQL::selectShoesDetailsForPhotoPath(QString photoPath)
//{
//    QString sql = QString("select * from shoes_details where photo_path = '%1'");
//    QString mysql = sql.arg(photoPath);
//    updateShoesDetailsList(mysql);
//}

void ExecSQL::selectShoesDetailsForStock(QString stock)
{
    QString sql = QString("select * from shoes_details where stock = '%1'");
    QString mysql = sql.arg(stock);
    updateShoesDetailsList(mysql);
}


void ExecSQL::modifyShoesDetailsShoesID(QString id, QString shoesID)
{
    QString sql = QString("update shoes_details set shoes_id = '%1' where id = '%2';");
    QString mysql = sql.arg(shoesID).arg(id);
    updateShoesDetailsList(mysql);
}

void ExecSQL::modifyShoesDetailsPhotoID(QString id, QString photoID)
{
    QString sql = QString("update shoes_details set photo_id = '%1' where id = '%2';");
    QString mysql = sql.arg(photoID).arg(id);
    updateShoesDetailsList(mysql);
}
void ExecSQL::modifyShoesDetailsSize(QString id, QString size)
{
    QString sql = QString("update shoes_details set size = '%1' where id = '%2';");
    QString mysql = sql.arg(size).arg(id);
    updateShoesDetailsList(mysql);
}
void ExecSQL::modifyShoesDetailsColor(QString id, QString color)
{
    QString sql = QString("update shoes_details set color = '%1' where id = '%2';");
    QString mysql = sql.arg(color).arg(id);
    updateShoesDetailsList(mysql);
}
void ExecSQL::modifyShoesDetailsPrice(QString id, QString price)
{
    QString sql = QString("update shoes_details set price = '%1' where id = '%2';");
    QString mysql = sql.arg(price).arg(id);
    updateShoesDetailsList(mysql);
}
//void ExecSQL::modifyShoesDetailsPhotoCount(QString id, QString photoCount)
//{
//    QString sql = QString("update shoes_details set photo_count = '%1' where id = '%2';");
//    QString mysql = sql.arg(photoCount).arg(id);
//    updateShoesDetailsList(mysql);
//}
//void ExecSQL::modifyShoesDetailsPhotoPath(QString id, QString photoPath)
//{
//    QString sql = QString("update shoes_details set photo_path = '%1' where id = '%2';");
//    QString mysql = sql.arg(photoPath).arg(id);
//    updateShoesDetailsList(mysql);
//}
void ExecSQL::modifyShoesDetailsStock(QString id, QString stock)
{
    QString sql = QString("update shoes_details set stock = '%1' where id = '%2';");
    QString mysql = sql.arg(stock).arg(id);
    updateShoesDetailsList(mysql);
}
void ExecSQL::insertShoesDetails(ShoesDetails info)
{
    QString insert = QString("insert into shoes_details values('%1','%2','%3','%4','%5','%6','%7','%8');");
    QString insertSQL = insert.arg(info.getID()).arg(info.getShoesID()).arg(info.getPhotoID()).arg(info.getSize()).arg(info.getColor())
            .arg(info.getPrice()).arg(info.getStock());
    updateShoesDetailsList(insertSQL);
}
void ExecSQL::deleteShoesDetails(QString id)
{
    QString Delete = QString("delete from shoes_details where id = '%1';");
    QString DeleteSQL = Delete.arg(id);
    updateShoesDetailsList(DeleteSQL);
}

////////////////////////////////////////////////////////// Evaluation /////////////////////////////////////////////////////
void ExecSQL::updateEvaluationInfoList(QString sql)
{
    GlobalVars::g_evaluationInfoList->clear();

    QSqlQuery query;
    if(query.exec(sql))
    {
        int index_id = query.record().indexOf("id");
        int index_shoesID = query.record().indexOf("shoes_id");
        int index_buyerID = query.record().indexOf("buyer_id");
        int index_photoID = query.record().indexOf("photo_id");
        int index_grade = query.record().indexOf("grade");
        int index_content = query.record().indexOf("content");
//        int index_photoCount = query.record().indexOf("photo_count");
//        int index_photoPath = query.record().indexOf("photo_path");
        int index_date = query.record().indexOf("date");

        while(query.next())
        {
            QString id = query.value(index_id).toString();
            QString shoesID = query.value(index_shoesID).toString();
            QString buyerID = query.value(index_buyerID).toString();
            QString photoID = query.value(index_photoID).toString();
            QString grade = query.value(index_grade).toString();
            QString content = query.value(index_content).toString();

            //QString photoPath = query.value(index_photoPath).toString();
            QString date = query.value(index_date).toString();


            EvaluationInfo info(id, shoesID, buyerID, photoID,  grade, content, date);
            GlobalVars::g_evaluationInfoList->append(info);
        }
    }else
    {
        qDebug() << "执行语句失败";
    }
}
void ExecSQL::selectAllEvaluations(void)
{
    QString sql = QString("select * from evaluation_info");
    updateEvaluationInfoList(sql);
}

void ExecSQL::selectEvaluationInfoForID(QString id)
{
    QString sql = QString("select * from evaluation_info where id = '%1'");
    QString mysql = sql.arg(id);
    updateEvaluationInfoList(mysql);
}
void ExecSQL::selectEvaluationInfoForShoesID(QString ShoesID)
{
    QString sql = QString("select * from evaluation_info where shoes_id = '%1'");
    QString mysql = sql.arg(ShoesID);
    updateEvaluationInfoList(mysql);
}
void ExecSQL::selectEvaluationInfoForBuyerID(QString BuyerID)
{
    QString sql = QString("select * from evaluation_info where buyer_id = '%1'");
    QString mysql = sql.arg(BuyerID);
    updateEvaluationInfoList(mysql);
}
void ExecSQL::selectEvaluationInfoForPhotoID(QString PhotoID)
{
    QString sql = QString("select * from evaluation_info where photo_id = '%1'");
    QString mysql = sql.arg(PhotoID);
    updateEvaluationInfoList(mysql);
}
void ExecSQL::selectEvaluationInfoForGrade(QString Grade)
{
    QString sql = QString("select * from evaluation_info where grade = '%1'");
    QString mysql = sql.arg(Grade);
    updateEvaluationInfoList(mysql);
}
void ExecSQL::selectEvaluationInfoForContent(QString Content)
{
    QString sql = QString("select * from evaluation_info where grade = '%1'");
    QString mysql = sql.arg(Content);
    updateEvaluationInfoList(mysql);
}
//void ExecSQL::selectEvaluationInfoForPhotoCount(QString PhotoCount)
//{
//    QString sql = QString("select * from evaluation_info where photo_count = '%1'");
//    QString mysql = sql.arg(PhotoCount);
//    updateEvaluationInfoList(mysql);
//}
//void ExecSQL::selectEvaluationInfoForPhotoPath(QString PhotoPath)
//{
//    QString sql = QString("select * from evaluation_info where photo_path = '%1'");
//    QString mysql = sql.arg(PhotoPath);
//    updateEvaluationInfoList(mysql);
//}
void ExecSQL::selectEvaluationInfoForDate(QString Date)
{
    QString sql = QString("select * from evaluation_info where date = '%1'");
    QString mysql = sql.arg(Date);
    updateEvaluationInfoList(mysql);
}

void ExecSQL::modifyEvaluationInfoShoesID(QString id, QString shoesID)
{
    QString sql = QString("update evaluation_info set shoes_id = '%1' where id = '%2';");
    QString mysql = sql.arg(shoesID).arg(id);
    updateEvaluationInfoList(mysql);
}
void ExecSQL::modifyEvaluationInfoBuyerID(QString id, QString BuyerID)
{
    QString sql = QString("update evaluation_info set buyer_id = '%1' where id = '%2';");
    QString mysql = sql.arg(BuyerID).arg(id);
    updateEvaluationInfoList(mysql);
}
void ExecSQL::modifyEvaluationInfoPhotoID(QString id, QString PhotoID)
{
    QString sql = QString("update evaluation_info set photo_id = '%1' where id = '%2';");
    QString mysql = sql.arg(PhotoID).arg(id);
    updateEvaluationInfoList(mysql);
}
void ExecSQL::modifyEvaluationInfoGrade(QString id, QString Grade)
{
    QString sql = QString("update evaluation_info set grade = '%1' where id = '%2';");
    QString mysql = sql.arg(Grade).arg(id);
    updateEvaluationInfoList(mysql);
}
void ExecSQL::modifyEvaluationInfoContent(QString id, QString Content)
{
    QString sql = QString("update evaluation_info set content = '%1' where id = '%2';");
    QString mysql = sql.arg(Content).arg(id);
    updateEvaluationInfoList(mysql);
}
//void ExecSQL::modifyEvaluationInfoPhotoCount(QString id, QString PhotoCount)
//{
//    QString sql = QString("update evaluation_info set photo_count = '%1' where id = '%2';");
//    QString mysql = sql.arg(PhotoCount).arg(id);
//    updateEvaluationInfoList(mysql);
//}
//void ExecSQL::modifyEvaluationInfoPhotoPath(QString id, QString PhotoPath)
//{
//    QString sql = QString("update evaluation_info set photo_path = '%1' where id = '%2';");
//    QString mysql = sql.arg(PhotoPath).arg(id);
//    updateEvaluationInfoList(mysql);
//}
void ExecSQL::modifyEvaluationInfoDate(QString id, QString Date)
{
    QString sql = QString("update evaluation_info set date = '%1' where id = '%2';");
    QString mysql = sql.arg(Date).arg(id);
    updateEvaluationInfoList(mysql);
}

void ExecSQL::insertEvaluationInfo(EvaluationInfo info)
{
    QString insert = QString("insert into evaluation_info values('%1','%2','%3','%4','%5','%6','%7');");
    QString insertSQL = insert.arg(info.getID()).arg(info.getShoesID()).arg(info.getBuyerID()).arg(info.getPhotoID()).
            arg(info.getGrade()).arg(info.getContent()).arg(info.getDate());

    updateEvaluationInfoList(insertSQL);
}
void ExecSQL::deleteEvaluationInfo(QString id)
{
    QString Delete = QString("delete from evaluation_info where id = '%1';");
    QString DeleteSQL = Delete.arg(id);
    updateEvaluationInfoList(DeleteSQL);
}
//////////////////////////////////////////////  Chat //////////////////////////

void ExecSQL::updateChatInfoList(QString sql)
{
    GlobalVars::g_chatInfoList->clear();

    QSqlQuery query;
    if(query.exec(sql))
    {
        int index_id = query.record().indexOf("id");
        int index_buyerID = query.record().indexOf("buyer_id");
        int index_sellerID = query.record().indexOf("seller_id");
        int index_photoID = query.record().indexOf("photo_id");
        int index_content = query.record().indexOf("content");
//        int index_photoCount = query.record().indexOf("photo_count");
//        int index_photoPath = query.record().indexOf("photo_path");
        int index_date = query.record().indexOf("date");

        while(query.next())
        {
            QString id = query.value(index_id).toString();
            QString buyerID = query.value(index_buyerID).toString();
            QString sellerID = query.value(index_sellerID).toString();
            QString photoID = query.value(index_photoID).toString();
            QString content = query.value(index_content).toString();
//            QString photoCount = query.value(index_photoCount).toString();
//            QString photoPath = query.value(index_photoPath).toString();
            QString date = query.value(index_date).toString();


            ChatInfo info(id, buyerID, sellerID, photoID, content, date);
            GlobalVars::g_chatInfoList->append(info);
        }
    }else
    {
        qDebug() << "执行语句失败";
    }
}
void ExecSQL::selectAllChats(void)
{
    QString sql = QString("select * from chat_info");
    updateChatInfoList(sql);
}

void ExecSQL::selectChatInfoForID(QString id)
{
    QString sql = QString("select * from chat_info where id = '%1'");
    QString mysql = sql.arg(id);
    updateChatInfoList(mysql);
}
void ExecSQL::selectChatInfoForBuyerID(QString BuyerID)
{
    QString sql = QString("select * from chat_info where buyer_id = '%1'");
    QString mysql = sql.arg(BuyerID);
    updateChatInfoList(mysql);

}
void ExecSQL::selectChatInfoForSellerID(QString SellerID)
{
    QString sql = QString("select * from chat_info where seller_id = '%1'");
    QString mysql = sql.arg(SellerID);
    updateChatInfoList(mysql);
}
void ExecSQL::selectChatInfoForPhotoID(QString photoID)
{
    QString sql = QString("select * from chat_info where photo_id = '%1'");
    QString mysql = sql.arg(photoID);
    updateChatInfoList(mysql);
}
void ExecSQL::selectChatInfoForContent(QString Content)
{
    QString sql = QString("select * from chat_info where content = '%1'");
    QString mysql = sql.arg(Content);
    updateChatInfoList(mysql);
}
//void ExecSQL::selectChatInfoForPhotoCount(QString photoCount)
//{
//    QString sql = QString("select * from chat_info where photo_count = '%1'");
//    QString mysql = sql.arg(photoCount);
//    updateChatInfoList(mysql);
//}
//void ExecSQL::selectChatInfoForPhotoPath(QString PhotoPath)
//{
//    QString sql = QString("select * from chat_info where photo_path = '%1'");
//    QString mysql = sql.arg(PhotoPath);
//    updateChatInfoList(mysql);
//}
void ExecSQL::selectChatInfoForDate(QString Date)
{
    QString sql = QString("select * from chat_info where date = '%1'");
    QString mysql = sql.arg(Date);
    updateChatInfoList(mysql);
}

void ExecSQL::modifyChatInfoBuyerID(QString id, QString BuyerID)
{
    QString sql = QString("update chat_info set buyer_id = '%1' where id = '%2';");
    QString mysql = sql.arg(BuyerID).arg(id);
    updateChatInfoList(mysql);
}
void ExecSQL::modifyChatInfoSellerID(QString id, QString SellerID)
{
    QString sql = QString("update chat_info set seller_id = '%1' where id = '%2';");
    QString mysql = sql.arg(SellerID).arg(id);
    updateChatInfoList(mysql);
}
void ExecSQL::modifyChatInfoPhotoID(QString id, QString PhotoID)
{
    QString sql = QString("update chat_info set photo_id = '%1' where id = '%2';");
    QString mysql = sql.arg(PhotoID).arg(id);
    updateChatInfoList(mysql);
}
void ExecSQL::modifyChatInfoContent(QString id, QString Content)
{
    QString sql = QString("update chat_info set content = '%1' where id = '%2';");
    QString mysql = sql.arg(Content).arg(id);
    updateChatInfoList(mysql);
}
//void ExecSQL::modifyChatInfoPhotoCount(QString id, QString PhotoCount)
//{
//    QString sql = QString("update chat_info set photo_count = '%1' where id = '%2';");
//    QString mysql = sql.arg(PhotoCount).arg(id);
//    updateChatInfoList(mysql);
//}
//void ExecSQL::modifyChatInfoPhotoPath(QString id, QString PhotoPath)
//{
//    QString sql = QString("update chat_info set photo_path = '%1' where id = '%2';");
//    QString mysql = sql.arg(PhotoPath).arg(id);
//    updateChatInfoList(mysql);
//}
void ExecSQL::modifyChatInfoDate(QString id, QString Date)
{
    QString sql = QString("update chat_info set date = '%1' where id = '%2';");
    QString mysql = sql.arg(Date).arg(id);
    updateChatInfoList(mysql);
}

void ExecSQL::insertChatInfo(ChatInfo info)
{
    QString insert = QString("insert into chat_info values('%1','%2','%3','%4','%5','%6');");
    QString insertSQL = insert.arg(info.getID()).arg(info.getBuyerID()).arg(info.getSellerID()).arg(info.getPhotoID())
            .arg(info.getContent()).arg(info.getDate());

    updateChatInfoList(insertSQL);
}
void ExecSQL::deleteChatInfo(QString id)
{
    QString Delete = QString("delete from chat_info where id = '%1';");
    QString DeleteSQL = Delete.arg(id);
    updateChatInfoList(DeleteSQL);
}
//////////////////////////////////// Photo  /////////////////////////////
void ExecSQL::updatePhotoInfoList(QString sql)
{
    GlobalVars::g_photoInfoList->clear();

    QSqlQuery query;
    if(query.exec(sql))
    {
        int index_id = query.record().indexOf("id");
        int index_photoCount = query.record().indexOf("count");
        int index_photoPath = query.record().indexOf("path");

        while(query.next())
        {
            QString id = query.value(index_id).toString();
            QString photoCount = query.value(index_photoCount).toString();
            QString photoPath = query.value(index_photoPath).toString();

            PhotoInfo info(id, photoCount, photoPath);
            GlobalVars::g_photoInfoList->append(info);
        }
    }else
    {
        qDebug() << "执行语句失败";
    }
}
void ExecSQL::selectAllPhotos(void)
{
    QString sql = QString("select * from photo_info");
    updatePhotoInfoList(sql);
}

void ExecSQL::selectPhotoInfoForID(QString id)
{
    QString sql = QString("select * from photo_info where id = '%1'");
    QString mysql = sql.arg(id);
    updatePhotoInfoList(mysql);
}
void ExecSQL::selectPhotoInfoForPhotoCount(QString photoCount)
{
    QString sql = QString("select * from photo_info where count = '%1'");
    QString mysql = sql.arg(photoCount);
    updatePhotoInfoList(mysql);
}
void ExecSQL::selectPhotoInfoForPhotoPath(QString photoPath)
{
    QString sql = QString("select * from photo_info where path = '%1'");
    QString mysql = sql.arg(photoPath);
    updatePhotoInfoList(mysql);
}
void ExecSQL::modifyPhotoInfoPhotoCount(QString id, QString photoCount)
{
    QString sql = QString("update photo_info set count = '%1' where id = '%2';");
    QString mysql = sql.arg(photoCount).arg(id);
    updatePhotoInfoList(mysql);
}
void ExecSQL::modifyPhotoInfoPhotoPath(QString id, QString photoPath)
{
    QString sql = QString("update photo_info set path = '%1' where id = '%2';");
    QString mysql = sql.arg(photoPath).arg(id);
    updatePhotoInfoList(mysql);
}

void ExecSQL::insertPhotoInfo(PhotoInfo info)
{
    QString insert = QString("insert into photo_info values('%1','%2','%3');");
    QString insertSQL = insert.arg(info.getID()).arg(info.getPhotoCount()).arg(info.getPhotoPath());

    updatePhotoInfoList(insertSQL);
}
void ExecSQL::deletePhotoInfo(QString id)
{
    QString Delete = QString("delete from photo_info where id = '%1';");
    QString DeleteSQL = Delete.arg(id);
    updatePhotoInfoList(DeleteSQL);
}
