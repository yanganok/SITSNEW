#include "communicationcore.h"
#include "Commands/command.h"
#include "Commands/bubblemeasureflighttime_command.h"
#include "Responses/bubblemeasureflighttime_command_response.h"
#include "Core/serialportcore.h"
CommunicationCore *CommunicationCore::_core = nullptr;
CommunicationCore::CommunicationCore(QObject *parent) :
    QObject(parent),
    _isRead(false),
    _isEnd(false),
    _isLauched(false),
    _isResponse(false),
    _communicateStatus(CommunicateCoreUnderlying::CommunicateStatus::CLOSE),
    translateToResponse(nullptr)
{

}

//void CommunicationCore::onReadyRead()
//{
//    QByteArray bytes = _serialport->readAll();
//    _receiveBuffer.append(bytes);
////        _locker.lockForWrite();
//    _receiveBuffer.append(bytes);
//#ifdef DEBUG
//    QString s = QByteArrayToHexString(bytes);
//#endif
//    DebugOut(QStringLiteral("receive:%1").arg(s));
////    validateAndAnalysisPackage();
////    _locker.unlock();
//}

void CommunicationCore::insertCommandList(const QList<std::shared_ptr<Command>> &commands)
{
    _locker.lock();
    _commandList.clear();
    //_responseCommandList.clear();
    _commandList.append(commands);
    _locker.unlock();
}

void CommunicationCore::lauch()
{
    _thread = std::shared_ptr<QThread>(new QThread());
    this->moveToThread(_thread.get());
    QObject::connect(_thread.get(), &QThread::started, this, &CommunicationCore::doWork);
    _thread->start();
    _timer.setInterval(200);
    _timer.setTimerType(Qt::PreciseTimer);
//    _timer.moveToThread(this);
    connect(&_timer,
            &QTimer::timeout,
            this,
            [this](){
        if(_timeOutIndex>=TIMEOUTCOUNT)
        {
            _isRead = false;
            _timeOutIndex = 0;
        }
        else
        {
            ++_timeOutIndex;
        }
    });
    _isLauched = true;
}

void CommunicationCore::end()
{
//    if(!this->isFinished())
//    {
//        //todo
//    }
}

CommunicationCore *CommunicationCore::CreateInstance()
{
    if(_core ==nullptr)
        _core = new SerialPort_CommunicationCore();
    return _core;
}

void CommunicationCore::doWork()
{
    createCommunicateDevice();
    while(!_isEnd)
    {
        if(!reconnection())
            continue;
        if(!_isRead)
        {
            QByteArray writePkg;
            writePkg.clear();
            //_locker.lockForWrite();
            _locker.lock();
            if (!_commandList.isEmpty())
            {
                _commandList[0].get()->sendCommand();
                writePkg.resize(_commandList[0]->package().size());
                memcpy(writePkg.data(), _commandList[0]->package(), _commandList[0]->package().size());
                _isRead = true;
//#ifdef DEBUG
//                QString s = QByteArrayToHexString(writePkg);
//#endif
//                DebugOut(QStringLiteral("send:%1").arg(s));
//                _isResponse = false;
            }
            _locker.unlock();
            if(!writePkg.isEmpty())
            {
                writePackage(writePkg);
                if(_commandList[0]->async())
                {
//                    DebugOut(QString("is async command"));
                    std::shared_ptr<Command> ptr = _commandList[0];
                    int id = _commandList[0]->id();
                    _responseCommandList.insert(id, ptr);
                    if(_responseCommandList.size() > 1500)
                    {
                        for(int i = 1000; i <= 1100; ++i)
                        {
                            if(_responseCommandList.contains(id - i))
                            {
                                if(_responseCommandList[id - i]->cmdStatus() == CommunicateCoreUpper::CommandStatus::RECEIVED)
                                _responseCommandList.remove(id - i);
                            }
                        }
                    }
                    if(ptr->timeout() != -1)
                    {
                        startDog(ptr->timeout());
                    }
                    removeCommandById(id);
                    _isRead = false;
                    continue;
                }
#ifndef SIMPLIFY
                startDog(1000);
#else
                startDog(_commandList[0]->timeout());
#endif
            }
            else
            {
                QThread::msleep(10);
                continue;
            }
//            if(_isResponse)
//                _isRead = true;
        }
        else if(_isRead)
        {
            bool reading = readPackage();
            if(reading)
            {
                validateAndAnalysisPackage();
            }
        }
    }
}

void CommunicationCore::startDog(int msec)
{
    if(_timer.isActive())
        _timer.stop();
    _timeOutIndex = 0;
    if(msec != -1)
        _timer.start(msec);
}

void CommunicationCore::stopDog()
{
    if(_timer.isActive())
        _timer.stop();
}

void CommunicationCore::createCommunicateDevice()
{

}

bool CommunicationCore::reconnection()
{
    return true;
}

void CommunicationCore::validateAndAnalysisPackage()
{
    bool isError = false;
    while (_receiveBuffer.size() >= 14)
    {
        while (_receiveBuffer.size() > 0)
        {
            if (_receiveBuffer.size() < 8)
            {
                break;
            }
            if(*(_receiveBuffer.data() + 0) != (char)0xEB)
            {
                _receiveBuffer.remove(0,1);
                continue;
            }
            else if(*(_receiveBuffer.data() + 1) != (char)0x90)
            {
                _receiveBuffer.remove(0, 1);
                continue;
            }
            if (*(_receiveBuffer.data() + 2) != (char)0x01
                && *(_receiveBuffer.data() + 2) != (char)0x02
                && *(_receiveBuffer.data() + 2) != (char)0x03)
            {
                _receiveBuffer.remove(0, 1);
                continue;
            }
            if(*(_receiveBuffer.data() + 7) < (char)0x01 || *(_receiveBuffer.data() + 7) > (char)0x23)
            {
                _receiveBuffer.remove(0, 1);
                continue;
            }
            break;
        }

        if (_receiveBuffer.size() >= 14)
        {
            int datalen = *(_receiveBuffer.data() + 10);
            if(datalen + 14> _receiveBuffer.size())
                break;
            else if(*(_receiveBuffer.data() + datalen + 12) !=(char)0xDC)
            {
                //char a = *(_receiveBuffer.data() + datalen + 12);
                //DebugOut(a);
                _receiveBuffer.remove(0, 1);
                break;
            }
            else if(*(_receiveBuffer.data() + datalen + 13) !=(char)0x97)
            {
                _receiveBuffer.remove(0, 1);
                break;
            }
            else
            {
                char sum = 0;
                for(int i = 2; i < datalen + 11; ++i)
                {
                    sum += _receiveBuffer[i];
                }
                if(sum != _receiveBuffer[datalen + 11])
                {
                    _receiveBuffer.remove(0, 1);
                    break;
                }
            }
            //以下是正常包处理
            std::shared_ptr<quint8> receivePackage = std::shared_ptr<quint8>(new quint8[datalen + 14], [](quint8 *arr){delete[] arr;});
            memcpy(receivePackage.get(), _receiveBuffer.data(), datalen + 14);
            dePackage(receivePackage, datalen + 14);

            //删除已处理的缓冲区
            _receiveBuffer.remove(0, datalen + 14);
        }
    }
}

CommunicationCore::Dispose::~Dispose()
{
    if(_core != nullptr)
    {
        delete _core;
        _core = nullptr;
    }
}


void CommunicationCore::dePackage(const std::shared_ptr<quint8> &package, int dataLen)
{
    int id = -1;
#ifndef SIMPLIFY
    if(*(package.get() + 2) == (char)0x01)
    {
        DebugOut("response:")
        _isResponse = true;
        id = BytesToAny::toInt(package.get() + 3);
        _locker.lock();
        setStatusById(id, CommunicateCoreUpper::CommandStatus::RESPONSE);
        std::shared_ptr<Command> ptr = findCommandById(id);
        _responseCommandList.insert(id, ptr);
        feedDog();
        if(ptr->timeout() != -1)
        {
            startDog(ptr->timeout());
        }
        removeCommandById(id);
        _locker.unlock();
        //气泡飞行时间终止测试，这里是响应命令，且无数据主动上传
        if(*(package.get() + 7) == (char)0x11 && *(package.get() + 9) == (char)0x02)
        {
            _isResponse = false;
            _isRead = false;
        }
    }

    else
#endif
    if(*(package.get() + 2) == (char)0x02)
    {
        feedDog();
        stopDog();
//        DebugOut("received:")
        id = BytesToAny::toInt(package.get() + 3);
        setStatusById(id, CommunicateCoreUpper::CommandStatus::RECEIVED);
        //BubbleMeasureFlightTime_Command *cmd = (BubbleMeasureFlightTime_Command *)(_responseCommandList[id].get());
        QByteArray recvPkg;
        recvPkg.resize(dataLen);
        memcpy(recvPkg.data(), package.get(), dataLen);
        _locker.lock();
#ifdef SIMPLIFY
        std::shared_ptr<Command> ptr = findCommandById(id);
        if(ptr)
        {
            _responseCommandList.insert(id, ptr);
        }

        if(_responseCommandList.size() > 1500)
        {
            for(int i = 1000; i <= 1100; ++i)
            {
                if(_responseCommandList.contains(id - i))
                {
                    if(_responseCommandList[id - i]->cmdStatus() == CommunicateCoreUpper::CommandStatus::RECEIVED)
                    _responseCommandList.remove(id - i);
                }
            }
        }
        if(_responseCommandList.contains(id) && _responseCommandList[id])
        {
            int delayMs = _responseCommandList[id]->delayMs();
            _responseCommandList[id]->receiveResponse(recvPkg);
            if(delayMs > 0)
            {
                DebugOut(QStringLiteral("等待%1毫秒").arg(delayMs));
                _condition.wait(&_locker, delayMs);
            }
        }

        removeCommandById(id);
#endif
        _locker.unlock();
        _isRead = false;
    }
    else
    if(*(package.get() + 2) == (char)0x03)
    {
//        DebugOut("received:")
        _isRead = false;
        id = BytesToAny::toInt(package.get() + 3);
        setStatusById(id, CommunicateCoreUpper::CommandStatus::RECEIVED);
        //BubbleMeasureFlightTime_Command *cmd = (BubbleMeasureFlightTime_Command *)(_responseCommandList[id].get());
        QByteArray recvPkg;
        recvPkg.resize(dataLen);
        memcpy(recvPkg.data(), package.get(), dataLen);
        _locker.lock();
//        if(_responseCommandList.contains(id) && _responseCommandList[id])
//            _responseCommandList[id]->receiveResponse(recvPkg);
        std::shared_ptr<Response> response = packageToResponse(recvPkg);
        if(response && translateToResponse)
            translateToResponse(response);
        _locker.unlock();
        //feedDog();
        //stopDog();
    }
}

void CommunicationCore::writePackage(const QByteArray &pkg)
{
    QString msg = "";
    switch (static_cast<CommunicateCoreUnderlying::DevicType>(pkg.at(7))) {
    case CommunicateCoreUnderlying::DevicType::DE_TP_LP:
        {
            msg += QStringLiteral("压力传感器->");
            switch (static_cast<CommunicateCoreUnderlying::PressureSensorDeviceID>(pkg.at(8))) {
            case CommunicateCoreUnderlying::PressureSensorDeviceID::PRESSURESENSORPAIRA:
                msg += QStringLiteral("LaneA压力传感器->");
                break;
            case CommunicateCoreUnderlying::PressureSensorDeviceID::PRESSURESENSORPAIRB:
                msg += QStringLiteral("LaneB压力传感器->");
                break;
            default:
                break;
            };
            switch (static_cast<CommunicateCoreUnderlying::PressureSensorControlWord>(pkg.at(9))) {
            case CommunicateCoreUnderlying::PressureSensorControlWord::CW_PV_GET:
                msg += QStringLiteral("获取压力值");
                break;
            default:
                break;
            };
        }
        break;
    case CommunicateCoreUnderlying::DevicType::DE_TP_SYRINGE:
        {
            msg += QStringLiteral("注射泵->");
            switch (static_cast<CommunicateCoreUnderlying::SyringPumpStatusWord>(pkg.at(8))) {
            case CommunicateCoreUnderlying::SyringPumpId::SYRING1CS:
                msg += QStringLiteral("LaneA注射泵->");
                break;
            case CommunicateCoreUnderlying::SyringPumpId::SYRING2CS:
                msg += QStringLiteral("LaneB注射泵->");
                break;
            default:
                break;
            };
            switch (static_cast<CommunicateCoreUnderlying::SyringPumpControlWord>(pkg.at(9))) {
            case CommunicateCoreUnderlying::SyringPumpControlWord::CW_SYRINGE_INIT:
                msg += QStringLiteral("初始化");
                break;
            case CommunicateCoreUnderlying::SyringPumpControlWord::CW_SYRINGE_MOVE:
                msg += QStringLiteral("移动->");
                msg += QStringLiteral("泵阀号:%1,速度:%2,绝对位置(距0点):%3").arg(BytesToAny::toQUint16(reinterpret_cast<const quint8 *>(pkg.data() + 11))).arg(BytesToAny::toQUint16(reinterpret_cast<const quint8 *>(pkg.data() + 13))).arg(BytesToAny::toQInt16(reinterpret_cast<const quint8 *>(pkg.data() + 15)));
                break;
            default:
                break;
            };
        }
        break;
    default:
        break;
    }
    DebugOut(msg);
}

bool CommunicationCore::readPackage()
{
    return true;
}

void CommunicationCore::setStatusById(int id, CommunicateCoreUpper::CommandStatus cmdStatus)
{
    for(auto it = _commandList.begin(); it != _commandList.end(); ++it)
    {
        if((*it).get()->id() == id)
        {
            (*it).get()->setCmdStatus(cmdStatus);
            break;
        }
    }
}

std::shared_ptr<Command> CommunicationCore::findCommandById(quint8 id)
{
    std::shared_ptr<Command> res = nullptr;
    for(auto it = _commandList.begin(); it != _commandList.end(); ++it)
    {
        if((*it).get()->id() == id)
        {
            res = (*it);
            break;
        }
    }
    return res;
}

bool CommunicationCore::removeCommandById(quint8 id)
{
    int index = -1;
    for(int i = 0; i < _commandList.size(); ++i)
    {
        if(_commandList[i].get()->id() == id)
        {
            index = i;
            break;
        }
    }
    if(index != -1)
    {
        _commandList.removeAt(index);
        return true;
    }
    else
    {
        return false;
    }
}

std::shared_ptr<Response> CommunicationCore::packageToResponse(const QByteArray &arr)
{
    return std::shared_ptr<Response>();
}
