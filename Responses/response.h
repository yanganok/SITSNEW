#ifndef RESPONSE_H
#define RESPONSE_H
#include "globals/enums.h"
#include <QVariant>
#include <typeinfo>
#include <QDateTime>
/**
* @projectName   SITS
* @brief         响应类
* @author        YangAn
* @date          2020-06-29
* @Email         yangan@AutoBio.com.cn
*/

class Response
{
public:
    Response();
    Response(int cmdId, QString key = "");
protected:
    virtual const QString classtype()const;
public:
    inline int cmdId()const{ return _cmdId;}
    inline void setCmdId(int value){_cmdId = value;}
    inline const QString &typeName(){return _typeName;}
    inline const QString &message()const{return  _msg;}
    inline void setMessage(QString msg){_msg = msg;}
    inline void setRecDate(){_recDate = QDateTime::currentDateTime();}
    inline const QDateTime &recDate() const{ return _recDate;}
    inline QString key()const{return  _key;}
protected:
    int _cmdId;
    QString _msg;
    QString _typeName;
    QDateTime _recDate;
    QString _key;
};
Q_DECLARE_METATYPE(Response)

#endif // RESPONSE_H
