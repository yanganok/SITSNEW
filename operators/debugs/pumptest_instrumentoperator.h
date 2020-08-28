#ifndef PUMPTEST_INSTRUMENTOPERATOR_H
#define PUMPTEST_INSTRUMENTOPERATOR_H

#include <QObject>
#include <QQmlEngine>
#include <memory>
#include "globals/enums.h"
#include "globals/globalSet.h"
#include "instrumentoperator.h"

/**
* @projectName   SITS
* @brief         测试泵相关命令
* @author        YangAn
* @date          2020-08-04
* @Email         yangan@AutoBio.com.cn
*/
class PumpTest_InstrumentOperator : public InstrumentOperator
{
    Q_OBJECT
    Q_ENUMS(TestType)
    QML_ELEMENT
public:
    PumpTest_InstrumentOperator();
public:
    /**
     * @brief 测试命令类型
     */
    enum TestType{
        INIT,
        ABSORB,
        DISPENSE
    };
public slots:
    /**
      * @brief startTest 开始测试 暴露给qml
      * @param testType 测试命令类型
      */
     void startTest(TestType testType, int valveId = 0, int speed = 0, int volumn = 0);
     /**
      * @brief autoTest 自动化测试 暴露给qml
      */
     void autoTest(int valveId, int speed, int volumn);
protected:
    /**
     * @brief generateCommandList 产生命令序列
     * @return 命令条数
     */
    virtual int generateCommandList() override;
    /**
     * @brief insertCommandList 将测试模块命令序列插入到通讯核心命令序列
     */
    virtual void insertCommandList() override;
public slots:
    /**
    * @brief getResponse 槽函数：接收从Command返回的应答信息,应在子类中继承
    * @param response 应答信息必须注册为Qt元数据
    */
   virtual void getResponse(std::shared_ptr<Response> response) override;
public:
   virtual void getStatus(std::shared_ptr<Response> response) override;

};

#endif // PUMPTEST_INSTRUMENTOPERATOR_H
