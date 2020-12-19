#ifndef SHOESINFO_H
#define SHOESINFO_H

#include <QString>

class ShoesInfo
{
public:
    ShoesInfo();
    ShoesInfo(const QString &m_id, const QString &m_storeID, const QString &m_shoesName,
                                 const QString &m_freight);

    void setID(const QString &m_id);
    void setStoreID(const QString &m_storeID);
    void setShoesName(const QString &m_shoesName);
    //void setBottomPrice(const QString &m_bottomPrice);
    void setFreight(const QString &m_freight);

    const QString &getID(void) const;
    const QString &getStoreID(void) const;
    const QString &getShoesName(void) const;
    //const QString &getBottomPrice(void) const;
    const QString &getFreight(void) const;
private:
    QString m_id;
    QString m_storeID;
    QString m_shoesName;
    //QString m_bottomPrice;
    QString m_freight;
};

typedef QList<ShoesInfo> ShoesInfoList;

#endif // SHOESINFO_H
