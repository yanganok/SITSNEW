#ifndef COMMNAD_H
#define COMMNAD_H
/**
* @projectName   SITS
* @brief         命令类，为各具体命令的父类
* @author        YangAn
* @date          2020-06-28
* @Email         yangan@AutoBio.com.cn
*/
#include "globals/globalSet.h"
#include <QObject>
#include <QVector>
#include <QVariant>
#include <utility>
#include <globals/enums.h>
#include <functional>
using namespace CommunicateCoreUpper;
class InstrumentOperator;
class Command:public QObject
{
    Q_OBJECT
public:
    Command();
    /**
     * @brief Command 所有命令的父类
     * @param operate 所依赖的通讯核心
     * @param response 所需返回的信息
     * @parm msec 等待响应毫秒数，-1代表不期望有应答
     */
    Command(InstrumentOperator* operate, Response *response, int msec = -1, QString key = "", bool async = false, int delayMs = 0);
public:
    /**
     * @brief id 获取命令id号
     * @return 命令id号
     */
    inline int id()const{return _id;}
//    /**
//     * @brief setId 设置命令id
//     * @param value 命令号
//     */
//    inline void setId(int value){ Command::_idCount = value;}
    /**
     * @brief response 获取应答信息
     * @return 应答信息
     */
    inline  Response * response() { return std::move(_response);}
    /**
     * @brief setResponse 设置应答信息
     * @param response 应答信息
     */
    inline void setResponse(Response *response){_response = response;}
    /**
     * @brief cmdStatus 获取命令状态
     * @return 命令状态
     */
    inline CommunicateCoreUpper::CommandStatus cmdStatus()const{return _cmdStatus;}
    inline void setCmdStatus(CommunicateCoreUpper::CommandStatus status){_cmdStatus = status;}
    inline const QByteArray& package()const{return _package;}
    inline int timeout()const{return _msec;}
    inline QString typeName()const{return _typeName;}
    inline bool async()const{return _async;}
    inline QString key()const{return  _key;}
    inline int delayMs()const{return _delayMs;}
    //inline Response *response()const {return _response;}
    QString status()const;
private:
    static int _idCount;
    CommunicateCoreUpper::CommandStatus _cmdStatus;
protected:
    int _msec;
    bool _async;
    QString _typeName;
    QByteArray _package;
    QByteArray _recvPackage;
    Response *_response;
    QString _key;
    int _delayMs;
    int _id;
public:
    /**
     * @brief setAsync 设置为异步非堵塞命令
     * @param value 是否异步非堵塞
     */
    void setAsync(bool value){_async = value;}
    /**
     * @brief SendCommand 发送命令
     */
    void sendCommand();
    /**
     * @brief receiveResponse 接收到回应
     * @param pkg
     */
    virtual void receiveResponse(QByteArray pkg);
protected:
    /**
     * @brief package 组包
     * @param arr     待组的包
     * @return        组包是否成功
     */
    virtual bool package(QByteArray& arr);
    /**
     * @brief packageToResponse 解包为应答信息
     * @param arr     待解的包
     * @return        解包是否成功
     */
    virtual bool packageToResponse(QByteArray& arr);
    /**
     * @brief classtype 返回类名
     * @return 类名字符串
     */
    virtual const QString classtype()const;
    QByteArray toPackage(quint8 cmdType, quint8 devType, quint8 devId, quint8 ctrlWord, const QVector<qint32> &paras);
    QByteArray toPackage(quint8 cmdType, quint8 devType, quint8 devId, quint8 ctrlWord, const QVector<quint32> &paras);
    QByteArray toPackage(quint8 cmdType, quint8 devType, quint8 devId, quint8 ctrlWord, const QVector<quint16> &paras);
signals:
    /**
     * @brief translateResponseToOperator 传送应答信息到测试模块
     * @param response 应答信息
     */
    void translateResponseToOperator(std::shared_ptr<Response> response);
};

//Q_DECLARE_METATYPE(Command)
#endif // COMMNAD_H
