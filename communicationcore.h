#ifndef COMMUNICATIONCORE_H
#define COMMUNICATIONCORE_H

#include <QObject>
#include <QList>
#include <QMap>
#include <QtSerialPort/QSerialPort>
#include <QSerialPortInfo>
#include <QMutex>
#include <utility>
#include <QTimer>
#include <QThread>
#include <memory>
#include <QWaitCondition>
#include <functional>
#include "globals/enums.h"
#include "globals/globalSet.h"
class Command;

class CommunicationCore : public QObject
{
public:
    explicit CommunicationCore(QObject *parent = nullptr);
protected:
    static CommunicationCore* _core;
    /**
     * @brief 删除通讯核心
     */
    class Dispose{
        public:
            ~Dispose();
    };
    static Dispose dispose;
public slots:
    //void onReadyRead();
    /**
     * @brief run 线程运行过程
     */
    virtual void doWork() ;
public:
    /**
     * @brief insertCommandList 将命令序列加入到通讯核心中
     * @param commands 命令序列
     */
    void insertCommandList(const QList<std::shared_ptr<Command>> &commands);

    /**
     * @brief lauch 开始通讯线程
     */
    void lauch();

    /**
     * @brief end 结束通讯线程
     */
    void end();

    /**
     * @brief islauched 加载标志
     * @return
     */
    inline bool islauched()const{return _isLauched;}
    /**
     * @brief setRead 设置通讯状态是否读
     * @param value
     */
    inline void setRead(bool value){_isRead = value;}
    inline CommunicateCoreUnderlying::CommunicateStatus communicateStatus()const{return _communicateStatus;}

    /**
     * @brief CreateInstance 创建通讯核心单例
     * @return 通讯核心单例指针
     */
    static CommunicationCore* CreateInstance();
protected:
    QMutex _locker;
    QWaitCondition _condition;
    /**
     * @brief _commandList 命令序列
     */
    QList<std::shared_ptr<Command>> _commandList;
    QMap<int, std::shared_ptr<Command>> _responseCommandList;
    std::shared_ptr<QThread> _thread;
    /**
     * @brief _timer 超时定时器
     */
    QTimer _timer;
    const quint8 TIMEOUTCOUNT = 3;
    quint8 _timeOutIndex = 0;
    bool _isRead;
    bool _isEnd;
protected:
    void startDog(int msec = -1);
    inline void feedDog(){_timeOutIndex = 0;}
    void stopDog();
protected:
    virtual void createCommunicateDevice();
    virtual bool reconnection();
    virtual void validateAndAnalysisPackage();
    virtual void dePackage(const std::shared_ptr<quint8> &package, int dataLen);
    virtual void writePackage(const QByteArray &pkg);
    virtual bool readPackage();
    void setStatusById(int id,  CommunicateCoreUpper::CommandStatus cmdStatus);
    std::shared_ptr<Command> findCommandById(quint8 id);
    bool removeCommandById(quint8 id);
    QByteArray _receiveBuffer;
    bool _isResponse;
    bool _isLauched;
    CommunicateCoreUnderlying::CommunicateStatus _communicateStatus;
public:
    std::function<void(std::shared_ptr<Response>)> translateToResponse;
private:
    std::shared_ptr<Response> packageToResponse(const QByteArray &arr);
};

#endif // COMMUNICATIONCORE_H
