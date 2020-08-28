#ifndef INSTRUMENTOPERATOR_H
#define INSTRUMENTOPERATOR_H

#include <QObject>
#include <QList>
#include <QMap>
#include <memory>
#include <QJsonObject>
#include <QJsonArray>
#include "Responses/response.h"
/**
* @projectName   SITS
* @brief         抽象类，所有测试模块的子类
* @author        YangAn
* @date          2020-06-30
* @Email         yangan@AutoBio.com.cn
*/
class Command;
class CommunicationCore;
class InstrumentOperator : public QObject
{
    Q_OBJECT
public:
    explicit InstrumentOperator(QObject *parent = nullptr);
protected:
    /**
     * @brief _commandList 命令序列
     */
    QList<std::shared_ptr<Command>>_commandList;
    /**
     * @brief _responseList 响应序列
     */
    QList<std::shared_ptr<Response>> _responseList;
    QList<std::shared_ptr<Response>> _statusList;
    /**
     * @brief _core 通讯核心指针
     */
    CommunicationCore *_core;
    /**
     * @brief _isSimulation 虚拟模式
     */
    const bool _isSimulation = false;
protected:
    /**
     * @brief generateCommandList 产生命令序列
     * @return 命令条数
     */
    virtual int generateCommandList();
    /**
     * @brief insertCommandList 将测试模块命令序列插入到通讯核心命令序列
     */
    virtual void insertCommandList();
public slots:
    /**
    * @brief getResponse 槽函数：接收从Command返回的应答信息,应在子类中继承
    * @param response 应答信息必须注册为Qt元数据
    */
   virtual void getResponse(std::shared_ptr<Response> response);
public:
   virtual void getStatus(std::shared_ptr<Response> response);
signals:

};

#endif // INSTRUMENTOPERATOR_H
