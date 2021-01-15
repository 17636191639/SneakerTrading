#ifndef GLOBALVARS_H
#define GLOBALVARS_H

#include "userinfo.h"
#include "buyerinfo.h"
#include "sellerinfo.h"
#include "shoesinfo.h"
#include "storeinfo.h"
#include "shopcart.h"
#include "orderinfo.h"
#include "shoesdetails.h"
#include "evaluationinfo.h"
#include "chatinfo.h"
#include "photoinfo.h"
#include <QQueue>
#include "mysocket.h"

enum RESPONSE{
    RES_Success = '!',
    RES_Fail = '?'
};

enum COMMAND{
    ///通用请求命令
    CMD_UserLogin_L = 'L',          //用户登录
    CMD_UserInfo_I = 'I',           //获取个人信息
    CMD_ChangePswd_H = 'H',         //修改密码
    CMD_UserExit_X = 'X',           //用户退出
    ///买家请求命令
    CMD_GetShoes_T = 'T',    //商品信息
    CMD_GetOrder_O = 'O',      //订单信息
    CMD_ViewShopCart_P = 'P',     //购物车信息
    CMD_ViewEvaluation_W = 'W',         //评价信息
    CMD_UploadEvaluation_U = 'U',         //上传评价
    CMD_GetShoesPhoto_A = 'A',
    CMD_GetShoesDetails_F = 'F',
    CMD_GetShoesDetailFromDetailsID_f = 'f', //通过商品详情ID获取商品详情
    CMD_GetShoesDetailByOrder_o = 'o',//通过订单信息获取商品详情
    CMD_CommitOrderInfo_c = 'c',  //客户端提交订单
    CMD_AddToShopCart_p = 'p',   //添加购物车
    CMD_GetBuyerInfo_B = 'B', //获取买家个人信息
    ///卖家请求命令
    CMD_GetShoesInfo_G = 'G',    //商品信息
    CMD_NewShoes_N = 'N',        //上架商品
    CMD_ChangeShoes_C = 'C',         //修改商品
    CMD_DeleteShoes_D = 'D',           //下架商品
    CMD_ShowOrders_S = 'S',         //订单信息
    CMD_ModifyOrder_M = 'M' ,          //订单状态修改

    CMD_ViewEvaluations_V = 'V',     //查看评价信息
    CMD_ReceiveEvaluation_E = 'E'    //回复评价
};
class GlobalVars
{
public:
    static SocketMap m_socketMap;
    static QQueue<QString> g_msgQueue; //消息队列

    static ShoesInfoList *g_shoesInfoList;
    static BuyerInfoList *g_buyerInfoList;
    static UserInfoList *g_userInfoList;
    static SellerInfoList *g_sellerInfoList;
    static StoreInfoList *g_storeInfoList;
    static ShopCartList *g_shopCartList;
    static OrderInfoList *g_orderInfoList;
    static ShoesDetailsList *g_shoesDetailsList;
    static EvaluationInfoList *g_evaluationInfoList;
    static ChatInfoList *g_chatInfoList;
    static PhotoInfoList *g_photoInfoList;

    static UserInfoMap g_userInfoMap;
};

#endif // GLOBALVARS_H
