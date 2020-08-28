#include "pressureinspection_instrumentoperator.h"
#include "Commands/pumpinit_command.h"
#include "Commands/pumpabsorb_command.h"
#include "Commands/pumpdispense_command.h"
#include "Commands/sensorread_command.h"
#include "Responses/pumpinit_command_response.h"
#include "Responses/pumpabsorb_command_response.h"
#include "Responses/pumpdispense_command_response.h"
#include "Responses/sensorread_command_response.h"
#include <QtConcurrent>
double PressureInspection_InstrumentOperator::func2(double el)
{
    return el - 100;
}

QString PressureInspection_InstrumentOperator::lineSerieTimeAt(int index)
{
    return index >= _serieLinePairs.size() ? "" :_serieLinePairs.at(index).dateTime();
}

int PressureInspection_InstrumentOperator::lineSerieIndexAt(int index)
{
    return index >= _serieLinePairs.size() ? 0 :_serieLinePairs.at(index).index();
}

double PressureInspection_InstrumentOperator::lineSerieValueAt(int index)
{
    return index >= _serieLinePairs.size() ? 0 :_serieLinePairs.at(index).mbar();
}

int PressureInspection_InstrumentOperator::lineSerieSize()
{
    return _serieLinePairs.size();
}

void sum(qint64& result, const qint64& param)
{
    result += param;
}

PressureInspection_InstrumentOperator::PressureInspection_InstrumentOperator()
    :_curPos(0), _curStep(StepType::NONE), _reachThresholdVolume(0), _psiPerul(0),
      _prePressureVolume(500), _absorbValve(0), _dispenseValve(0), _speed(0),
      _deviceId(CommunicateCoreUnderlying::SyringPumpId::SYRING1CS),
      _isTestReachVolume(false),
      _prepressurePsiCount(0),
      _prepressureinspectionCycle(0),
      _belowLeakRate(false),
      _pressureSampleIndex(0),
      _attemptIndex(1),
      _elpasedTime(0),
      _computeVolume(0),
      _mbarPerul(0),
      _isNegative(false)
{
    DebugOut(QStringLiteral("线程Id:%1").arg((qlonglong)QThread::currentThreadId()));
    _mbarPerul = IniFile::ReadIniFile(QString("PressureLeakRate"), QString("MBarPerUl"), QString("0"), IniFile::IniFileName).toDouble();
    _deviceId = static_cast<CommunicateCoreUnderlying::SyringPumpId>(IniFile::ReadIniFile(QString("PressureLeakRate"), QString("DeviceId"), QString("1"), IniFile::IniFileName).toInt());
    _dispenseValve = IniFile::ReadIniFile(QString("PressureLeakRate"), QString("DispenseValve"), QString("3"), IniFile::IniFileName).toInt();
    _absorbValve = IniFile::ReadIniFile(QString("PressureLeakRate"), QString("AbsorbValve"), QString("2"), IniFile::IniFileName).toInt();
    _speed = IniFile::ReadIniFile(QString("PressureLeakRate"), QString("Speed"), QString("7500"), IniFile::IniFileName).toInt();
    _computeVolume = IniFile::ReadIniFile(QString("PressureLeakRate"), QString("Volume"), QString("500"), IniFile::IniFileName).toInt();
    initDateTimeAxis();
//    emit(now.toString("yyyy-MM-dd HH:mm:ss:zzz"), now.addSecs(60 * 5));
}

void PressureInspection_InstrumentOperator::autoTest(int lanePair, int valveAbsorbId, int valveDispenseId, int speed, int volume)
{
    DebugOut(QStringLiteral("压力泄漏->开始测试"));
    _speed = speed;
    _prepressureinspectionCycle = 0;
    _deviceId = static_cast<CommunicateCoreUnderlying::SyringPumpId>(lanePair);
    _absorbValve = valveAbsorbId;
    _dispenseValve = valveDispenseId;
    _prePressureVolume = volume;
    _attemptIndex = 1;
    _pressureSampleIndex = 0;
    _elpasedTime = 0;
    _prepressureMbars.clear();
    _serieLinePairs.clear();
    _pressureSampleInfos.clear();
    _prepressureSampleInfos.clear();

    IniFile::WriteIniFile(QString("PressureLeakRate"), QString("DeviceId"), QString("%1").arg((int)_deviceId), IniFile::IniFileName);
    IniFile::WriteIniFile(QString("PressureLeakRate"), QString("DispenseValve"), QString("%1").arg(_dispenseValve), IniFile::IniFileName);
    IniFile::WriteIniFile(QString("PressureLeakRate"), QString("AbsorbValve"), QString("%1").arg(_absorbValve), IniFile::IniFileName);
    IniFile::WriteIniFile(QString("PressureLeakRate"), QString("Speed"), QString("%1").arg(_speed), IniFile::IniFileName);
    IniFile::WriteIniFile(QString("PressureLeakRate"), QString("Volume"), QString("%1").arg(_computeVolume), IniFile::IniFileName);

    QString deviceId;
    switch (_deviceId) {
    case CommunicateCoreUnderlying::SyringPumpId::SYRING1CS:
        deviceId = "LaneA";
        break;
    case CommunicateCoreUnderlying::SyringPumpId::SYRING2CS:
        deviceId = "LaneB";
        break;
    case CommunicateCoreUnderlying::SyringPumpId::ALL:
        deviceId = "LaneA and LaneB";
        break;
    default:
        break;
    }
    _fileName = deviceId + "_" + QDateTime::currentDateTime().toString("yyyyMMddHHmmss")+ ".csv";
    writeResultToCsv();
    //开始预加压
    initDateTimeAxis();
    emit dateTimeAxisLimitChanged();
    prePressure(true);
    emit statusChanged(QStringLiteral("开始测试，正在预加压"));
}

void PressureInspection_InstrumentOperator::computeMbarPerUl(int lanePair, int valveAbsorbId, int valveDispenseId, int speed, int volume)
{
    _speed = speed;
    _prepressureinspectionCycle = 0;
    _deviceId = static_cast<CommunicateCoreUnderlying::SyringPumpId>(lanePair);
    _absorbValve = valveAbsorbId;
    _dispenseValve = valveDispenseId;
    _prePressureVolume = volume;
    _attemptIndex = 1;
    _pressureSampleIndex = 0;
    _elpasedTime = 0;

    IniFile::WriteIniFile(QString("PressureLeakRate"), QString("DeviceId"), QString("%1").arg((int)_deviceId), IniFile::IniFileName);
    IniFile::WriteIniFile(QString("PressureLeakRate"), QString("DispenseValve"), QString("%1").arg(_dispenseValve), IniFile::IniFileName);
    IniFile::WriteIniFile(QString("PressureLeakRate"), QString("AbsorbValve"), QString("%1").arg(_absorbValve), IniFile::IniFileName);
    IniFile::WriteIniFile(QString("PressureLeakRate"), QString("Speed"), QString("%1").arg(_speed), IniFile::IniFileName);
    IniFile::WriteIniFile(QString("PressureLeakRate"), QString("Volume"), QString("%1").arg(_computeVolume), IniFile::IniFileName);

    emit statusChanged(QStringLiteral("开始计算mbar/ul"));
    computePressurePerUl(static_cast<CommunicateCoreUnderlying::SyringPumpId>(lanePair),  speed, volume, valveAbsorbId, valveDispenseId);
}

int PressureInspection_InstrumentOperator::generateCommandList()
{
    return InstrumentOperator::generateCommandList();
}

void PressureInspection_InstrumentOperator::insertCommandList()
{
    InstrumentOperator::insertCommandList();
}

void PressureInspection_InstrumentOperator::getResponse(std::shared_ptr<Response> response)
{
    if(response->typeName() == "PumpInit_Command_Response")
    {
        PumpInit_Command_Response *rsp = reinterpret_cast<PumpInit_Command_Response *>(response.get());
        DebugOut(QStringLiteral("压力泄漏->泵初始化->泵Id号:%1, 泵状态:%2, 泵当前位置:%3步").arg((int)rsp->deviceId()).arg((int)rsp->status()).arg((int)rsp->curPos()));
    }

    if(response->typeName() == "PumpAbsorb_Command_Response")
    {
        PumpAbsorb_Command_Response *rsp = reinterpret_cast<PumpAbsorb_Command_Response *>(response.get());
        if(rsp->key() == "prePressure_Absorb")
        {
            DebugOut(QStringLiteral("压力泄漏->预压加泵吸入->泵Id号:%1, 泵当前位置%2步").arg((int)rsp->deviceId()).arg((int)rsp->curPos()));
            QtConcurrent::run([this](){
                    _waitmtx.lock();
                    _commandList.clear();
                    if(_isNegative)
                    {
                        _commandList.append(std::make_shared<PumpDispense_Command>(this, nullptr, -1, _deviceId, _absorbValve, _speed, _prePressureVolume, "prePressure_Dispense", true));
                    }
                    else
                    {
                        _commandList.append(std::make_shared<PumpDispense_Command>(this, nullptr, -1, _deviceId, _dispenseValve, _speed, _prePressureVolume, "prePressure_Dispense", true));
                    }
                    _commandList.append(std::make_shared<SensorRead_Command>(this, nullptr, -1, SensorType::LIQUIDROADPRESSURE, static_cast<CommunicateCoreUnderlying::PressureSensorDeviceID>(_deviceId), QString("prepressure_sensorread_%1").arg(_prepressurePsiCount)));
                    generateCommandList();
                    insertCommandList();
                    ++_prepressurePsiCount;
//                    _waitEvent.wait(&_waitmtx, _delayMs);
                    _waitmtx.unlock();
            });
        }
    }

    if(response->typeName() == "PumpDispense_Command_Response")
    {
        PumpDispense_Command_Response *rsp = reinterpret_cast<PumpDispense_Command_Response *>(response.get());
        if(rsp->key() == "prePressure_Dispense")
        {
            DebugOut(QStringLiteral("压力泄漏->预加压泵排出->泵Id号:%1, 泵当前位置%2步").arg((int)rsp->deviceId()).arg((int)rsp->curPos()));
            _isTestReachVolume = true;
        }
    }

    if(response->typeName() == "SensorRead_Command_Response")
    {
        SensorRead_Command_Response *rsp = reinterpret_cast<SensorRead_Command_Response *>(response.get());

        if(rsp->key() == "pressureReadStart")
        {
            _pressureStandards = pressureToMBar(rsp->curPressure());
            DebugOut(QStringLiteral("标准值:%1mbar,原始值:%2").arg(Sensor_Module::pressureToMBar(_pressureStandards)).arg(_pressureStandards));

        }
        else if(rsp->key() == "compute_sensorread1")
        {
            _cpResults.clear();
            int pressureValue = rsp->curPressure();
//            DebugOut(pressureValue);
            _cpResults.append(pressureValue);
        }
        else if(rsp->key() == "compute_sensorread2")
        {
            int pressureValue = rsp->curPressure();
//            DebugOut(pressureValue);
            _cpResults.append(pressureValue);
//            double res = Sensor_Module::pressureToPsi(_cpResults[1]) - Sensor_Module::pressureToPsi(_cpResults[0]);
//            _psiPerul = res / _computeVolume;
            double res = Sensor_Module::pressureToMBar(_cpResults[1]) - Sensor_Module::pressureToMBar(_cpResults[0]);
            DebugOut(QStringLiteral("压力泄漏->计算mbar/ul->吸入%1ul时的值:%2,排出%3ul的值:%4,压力差为%5mbar.").arg(_computeVolume).arg(_cpResults[0]).arg(_computeVolume).arg(_cpResults[1]).arg(res));
            _mbarPerul = res / _computeVolume;
            DebugOut(QString("压力泄漏->计算mbar/ul->mbar/ul:%1.").arg(_mbarPerul));
            _reachThresholdVolume = qRound(pressureMaintainingThreshold / _mbarPerul);
            DebugOut(QStringLiteral("压力泄漏->mbar/ul->达到预加压阈值时的容积:%1，开始预加压").arg(_reachThresholdVolume));
            emit reachThresholdVolumeChanged();
            emit statusChanged(QStringLiteral("计算完成，请泄压"));
//            QtConcurrent::run([this](){prePressure();});
        }
        if(rsp->key().indexOf("prepressure_sensorread") > -1)
        {
            double mbar = Sensor_Module::pressureToMBar(rsp->curPressure()) - _pressureStandards ;
            _prepressureMbars.append(mbar);
            _prepressureSampleInfos.append(PressureSampleInfo(QDateTime::currentDateTime(), mbar));
            emit serieValueChanged(_prepressureSampleInfos.last().sampleDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz"), _prepressureSampleInfos.last().samplePressure());
            DebugOut(QStringLiteral("压力泄漏->预加压->读取到psi%1,原始值%2,标准值%3,标准差值%4").arg(Sensor_Module::pressureToMBar(rsp->curPressure())).arg(rsp->curPressure()).arg(_pressureStandards).arg(mbar));
            //如果达到推送的容量，则开始测试是否达到psi阈值（18psi）
            if(_isTestReachVolume)
            {
                QtConcurrent::run([this](){
//                    while(_prepressurePsiCount != _prepressureMbars.size())
//                    {
//                        _waitmtx.lock();
//                        _waitEvent.wait(&_waitmtx, _delayMs);
//                        _waitmtx.unlock();
//                    };
                    double val = _prepressureMbars.last();
                    _serieLinePairs.append(std::move(SerieLinePairs(QDateTime::currentDateTime(), val, _serieLinePairs.size())));
                    if(qAbs(val  - pressureMaintainingThreshold) < _pressureTolerance)//如果小于公差(1psi)
                    {
                        DebugOut(QStringLiteral("压力泄漏->预加压->已小于公差%1mbar").arg(_pressureTolerance));
                        //todo inspection pressureLeakRate
                        //保压
                        _waitmtx.lock();
                        _waitEvent.wait(&_waitmtx, _stabilizationMs);
                        _waitmtx.unlock();
                        DebugOut(QStringLiteral("压力泄漏->采样->稳定延时%1").arg(_stabilizationMs));
                        samplePsiList(false);
                        emit statusChanged(QStringLiteral("开始保压并采样，请等待"));
                        DebugOut(QStringLiteral("压力泄漏->采样->无延时:"));
                    }
                    else if(pressureMaintainingInspectionCycleLimit > _prepressureinspectionCycle)//如果没有到预加压次数(15)
                    {
                        DebugOut(QString("pressureMaintainingThresold:%1, _prepressureMBars last element:%2").arg(pressureMaintainingThreshold).arg(_prepressureMbars.last()))
                        if(pressureMaintainingThreshold > val)
                        {
                            double volume = val - pressureMaintainingThreshold > 0 ? val - pressureMaintainingThreshold :-(val - pressureMaintainingThreshold);
                            volume /= _mbarPerul;
//                            double volume = qAbs(val - pressureMaintainingThreshold) / _psiPerul;
                            DebugOut(QStringLiteral("第%1次,距与容量差距%2").arg(_prepressureinspectionCycle).arg(volume));
                            if(volume > Fluidics_Module::fullScaleVolume)
                               _prePressureVolume = Fluidics_Module::fullScaleVolume;
                            else
                               _prePressureVolume = volume;
//                            _reachThresholdVolume += qAbs(_prepressurePsis.last() - pressureMaintainingThreshold) / _psiPerul;
//                            DebugOut(QStringLiteral("压力泄漏->预加压->增益,吸排体积更新为:").arg(_prePressureVolume));
                            _isNegative = false;
                        }
                        else
                        {
                            double volume = val - pressureMaintainingThreshold > 0 ? val - pressureMaintainingThreshold :-(val - pressureMaintainingThreshold);
                            DebugOut(QStringLiteral("第%1次,距与容量差距%2").arg(_prepressureinspectionCycle).arg(-volume));;
//                            double volume = qAbs(val - pressureMaintainingThreshold) / _psiPerul;
//                            DebugOut(volume);
                            if(volume > Fluidics_Module::fullScaleVolume)
                               _prePressureVolume = Fluidics_Module::fullScaleVolume;
                            else
                               _prePressureVolume = volume;
                            _isNegative = true;
//                            DebugOut(QStringLiteral("压力泄漏->预加压->减益,体积阈值更新为:").arg(_prePressureVolume));
                        }
                        //预加压
                        _isTestReachVolume = false;
                        prePressure();
                    }
                    else//如果达到预加压次数
                    {
                        _inspectionResult = ERROR;
                        DebugOut(QStringLiteral("压力泄漏->预加压->无法接近psi阈值"));
                        emit statusChanged(QStringLiteral("测试异常：预加压无法达到开始测试阈值，请泄压后重新测试"));
                    }
                });
            }
            else
            {
                QtConcurrent::run([this](){
                    _waitmtx.lock();
                    _waitEvent.wait(&_waitmtx, _delayMs);
                    _commandList.clear();
                    _commandList.append(std::make_shared<SensorRead_Command>(this, nullptr, -1, SensorType::LIQUIDROADPRESSURE, static_cast<CommunicateCoreUnderlying::PressureSensorDeviceID>(_deviceId), QString("prepressure_sensorread_%1").arg(_prepressurePsiCount)));
                    generateCommandList();
                    insertCommandList();
                    ++_prepressurePsiCount;
                    _waitmtx.unlock();
                });
            }
        }
        //如果得到的结果是psi采样值
        else if(rsp->key().indexOf("psileakrate_sensorread") > -1)
        {
            double mbar = Sensor_Module::pressureToMBar(rsp->curPressure()) - _pressureStandards;
            QDateTime time = QDateTime::currentDateTime();
            _pressureSampleInfos.append(PressureSampleInfo(time, mbar));
            emit serieValueChanged(_pressureSampleInfos.last().sampleDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz"), _pressureSampleInfos.last().samplePressure());
            _serieLinePairs.append(std::move(SerieLinePairs(_pressureSampleInfos.last().sampleDateTime(), _pressureSampleInfos.last().samplePressure(), _serieLinePairs.size())));
            DebugOut(QString("压力泄漏%1").arg(_pressureSampleInfos.last().samplePressure()));
            //尚未到测试时间，则继续采样
            _info += QStringLiteral("%1,%2,%3\r\n").arg(time.toString("yyyy-MM-dd HH:mm:ss:zzz")).arg(_pressureStandards).arg(mbar);
            if(_elpasedTime < _measurementDurationMs)
            {
                //因为有延时放到线程中进行
                QtConcurrent::run([this](){
                    samplePsiList();
                    DebugOut(QStringLiteral("压力泄漏->采样->延时%1ms:").arg(_delayMs));
                });
            }
            else
            {
                writeResultToCsv(_info);
                computeLeakRate();
            }
        }
    }
    InstrumentOperator::getResponse(response);
}

void PressureInspection_InstrumentOperator::getStatus(std::shared_ptr<Response> response)
{

}

void PressureInspection_InstrumentOperator::writeResultToCsv()
{
    QStringList strs;
    strs.append(QStringLiteral("记录时间"));
    strs.append(",");
    strs.append(QStringLiteral("标准值"));
    strs.append(",");
    strs.append(QStringLiteral("压差"));
    QString content = strs.join(QString());
    if(!QDir(localFilePath + "/PressureLeakRateInspection/").exists())
    {
        QDir dir;
        dir.mkdir(localFilePath + "/PressureLeakRateInspection/");
    }
    QFile file(localFilePath + "/PressureLeakRateInspection/" + _fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        return;
    }
    QTextStream txtOutput(&file);
    txtOutput << content << endl;
    file.close();
}

void PressureInspection_InstrumentOperator::writeResultToCsv(const QString &info)
{
    QString content = info;
    if(!QDir(localFilePath + "/PressureLeakRateInspection/").exists())
    {
        QDir dir;
        dir.mkdir(localFilePath + "/PressureLeakRateInspection/");
    }
    QFile file(localFilePath + "/PressureLeakRateInspection/" + _fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        return;
    }
    QTextStream txtOutput(&file);
    txtOutput << content << endl;
    file.close();
}

void PressureInspection_InstrumentOperator::computePressurePerUl(CommunicateCoreUnderlying::SyringPumpId deviceId, int speed, int volume, int absorbValve, int dispenseValve)
{
    _curStep = StepType::COMPUTEPRESUREPERUL;
    _computeVolume = volume;
    _commandList.clear();
    _commandList.append(std::make_shared<PumpInit_Command>(this, nullptr, -1, deviceId));
//    for(int i = 0; i < 6; ++i)
    {
        _commandList.append(std::make_shared<PumpAbsorb_Command>(this, nullptr, -1, deviceId, absorbValve, speed, volume));
        //read pressure to do
        std::shared_ptr<SensorRead_Command> sensorRead_command1 = std::shared_ptr<SensorRead_Command>(new SensorRead_Command(this, nullptr, -1, SensorType::LIQUIDROADPRESSURE, static_cast<CommunicateCoreUnderlying::PressureSensorDeviceID>(deviceId), "compute_sensorread1"));

        _commandList.append(sensorRead_command1);
        _commandList.append(std::make_shared<PumpDispense_Command>(this, nullptr, -1, deviceId, dispenseValve, speed, volume));
        //read pressure to do
        std::shared_ptr<SensorRead_Command> sensorRead_command2 = std::shared_ptr<SensorRead_Command>(new SensorRead_Command(this, nullptr, -1, SensorType::LIQUIDROADPRESSURE, static_cast<CommunicateCoreUnderlying::PressureSensorDeviceID>(deviceId), "compute_sensorread2"));
        _commandList.append(sensorRead_command2);
    }
    generateCommandList();
    insertCommandList();
    return;
}

void PressureInspection_InstrumentOperator::prePressure(bool needInit)
{
    DebugOut(QString("PressureInspection_InstrumentOperator->prePressure线程Id:%1").arg((qlonglong)QThread::currentThreadId()));
    _curStep = StepType::PREPRESSURE;
    _prepressureinspectionCycle++;
    _prepressurePsiCount = 0;
    _commandList.clear();
    if(needInit)
    {
        _commandList.append(std::make_shared<SensorRead_Command>(this, nullptr, -1, SensorType::LIQUIDROADPRESSURE,static_cast<CommunicateCoreUnderlying::PressureSensorDeviceID>(_deviceId), "pressureReadStart"));
        _commandList.append(std::make_shared<PumpInit_Command>(this, nullptr, -1, _deviceId));
//        _commandList.append(std::make_shared<SensorRead_Command>(this, nullptr, -1, SensorType::LIQUIDROADPRESSURE, static_cast<CommunicateCoreUnderlying::PressureSensorDeviceID>(_deviceId), QString("prepressure_sensorread_%1").arg(_prepressurePsiCount)));
    }
    if(_isNegative)
    {
        _commandList.append(std::make_shared<PumpAbsorb_Command>(this, nullptr, -1, _deviceId, _dispenseValve, _speed, _prePressureVolume, "prePressure_Absorb"));
    }
    else
    {
        _commandList.append(std::make_shared<PumpAbsorb_Command>(this, nullptr, -1, _deviceId, _absorbValve, _speed, _prePressureVolume, "prePressure_Absorb"));
    }
    generateCommandList();
    insertCommandList();
//    while(true)
//    {
//        _waitmtx.lock();
//        _commandList.clear();
//        _commandList.append(std::make_shared<SensorRead_Command>(this, nullptr, -1, SensorType::LIQUIDROADPRESSURE, static_cast<CommunicateCoreUnderlying::PressureSensorDeviceID>(_deviceId), QString("prepressure_sensorread_%1").arg(_prepressurePsiCount)));
//        generateCommandList();
//        insertCommandList();
//        ++_prepressurePsiCount;
//        _waitEvent.wait(&_waitmtx, _delayMs);
//        _waitmtx.unlock();

//        if(_isReachVolume)
//        {
//            _commandList.clear();
//            _commandList.append(std::make_shared<SensorRead_Command>(this, nullptr, -1, SensorType::LIQUIDROADPRESSURE, static_cast<CommunicateCoreUnderlying::PressureSensorDeviceID>(_deviceId), QString("prepressure_sensorread_%1").arg(_prepressurePsiCount)));
//            generateCommandList();
//            insertCommandList();
//            ++_prepressurePsiCount;
//        }
//    }
    return;
}

void PressureInspection_InstrumentOperator::samplePsiList(bool isDelay)
{
    if(isDelay)
    {
        _waitmtx.lock();
        _waitEvent.wait(&_waitmtx, _delayMs);
        _waitmtx.unlock();
    }
    _commandList.clear();
    _commandList.append(
                std::shared_ptr<SensorRead_Command>(
                    new SensorRead_Command(
                        this,
                        nullptr,
                        -1,
                        SensorType::LIQUIDROADPRESSURE,
                        static_cast<CommunicateCoreUnderlying::PressureSensorDeviceID>(_deviceId),
                        QString("psileakrate_sensorread_%1").arg(_pressureSampleIndex))));
    generateCommandList();
    insertCommandList();
    ++_pressureSampleIndex;
    _elpasedTime += 500;
}

double PressureInspection_InstrumentOperator::computeTestParrela(double el)
{
    return el + 1;
}

void PressureInspection_InstrumentOperator::initDateTimeAxis()
{
    QDateTime now = QDateTime::currentDateTime();
    setStartDateTime(now.toString("yyyy-MM-dd HH:mm:ss:zzz"));
    setEndDateTime(now.addSecs(60 * 3).toString("yyyy-MM-dd HH:mm:ss:zzz"));
}

qint64 PressureInspection_InstrumentOperator::computeSampleDurationFromStartSecond(PressureSampleInfo &sampleInfo)
{
    return sampleInfo.sampleDateTime().toSecsSinceEpoch() - _pressureSampleInfos[0].sampleDateTime().toSecsSinceEpoch();
}

void PressureInspection_InstrumentOperator::computeLeakRate()
{
    //已到采样时间，则根据采样列表计算汇漏率
    _attemptIndex = 1;
    do
    {
        double averageSampleDruation = 0;
        double averageSamplePressure = 0;
        double averageSampleDurationSquare = 0;
        double averageSampleDurationPressure = 0;

        std::function<qint64(const PressureSampleInfo&)> func1 = [this](const PressureSampleInfo& info){
            if(_pressureSampleInfos.size() == 0)
                return 0;
            int duration = info.sampleDateTime().toSecsSinceEpoch() - _pressureSampleInfos.at(0).sampleDateTime().toSecsSinceEpoch();
            return duration;
        };
        QFuture<qint64> future = QtConcurrent::mapped(_pressureSampleInfos, func1);
        future.waitForFinished();
        for(int i = 0; i < _pressureSampleInfos.size(); ++i)
            averageSampleDruation += (double)future.resultAt(i);
        averageSampleDruation /= _pressureSampleInfos.size();

        for(int i = 0; i < _pressureSampleInfos.size(); ++i)
            averageSamplePressure += _pressureSampleInfos.at(i).samplePressure();
        averageSamplePressure /= _pressureSampleInfos.size();

        std::function<qint64(const qint64&)> func2 = [this](const qint64& duration){
            return duration * duration;
        };
        QFuture<qint64> futureDurationSquare = QtConcurrent::mappedReduced(future.results(), func2, sum);
        futureDurationSquare.waitForFinished();
        averageSampleDurationSquare = futureDurationSquare.result() / _pressureSampleInfos.size();

        for(int i = 0; i < _pressureSampleInfos.size(); ++i)
        {
            averageSampleDurationPressure += future.resultAt(i) * _pressureSampleInfos.at(i).samplePressure();
        }
        averageSampleDurationPressure /= _pressureSampleInfos.size();

        double pressueDecay = -1 * (averageSampleDurationPressure - averageSampleDruation * averageSamplePressure)
                / (averageSampleDurationSquare - averageSampleDruation * averageSampleDruation);
        _decayRatePsiPerSecond = (_decayRatePsiPerSecond * (_attemptIndex - 1) + pressueDecay)/_attemptIndex;
        DebugOut(QString("averageSampleDurationPressure:%1").arg(averageSampleDurationPressure));
        DebugOut(QString("averageSampleDurationSquare:%1").arg(averageSampleDurationSquare));
        DebugOut(QString("averageSampleDruation:%1").arg(averageSampleDruation));
        DebugOut(QString("averageSamplePressure:%1").arg(averageSamplePressure));
        DebugOut(QString("pressueDecay:%1").arg(pressueDecay));
        DebugOut(QString("decayRatePsiPerSecond:%1").arg(_decayRatePsiPerSecond));
        double limitWithUncertainty = _leakLimitRate - _leakRateUncertainty;
        DebugOut(QString("limitWithUncertainty:%1").arg(limitWithUncertainty))
        if(_attemptIndex >= _attemptCount)
        {
            limitWithUncertainty = _leakLimitRate + _leakRateUncertainty;
        }
        if(_decayRatePsiPerSecond < limitWithUncertainty)
        {
            emit statusChanged(QStringLiteral("测试值:%1,小于阈值%2,通过测试").arg(_decayRatePsiPerSecond).arg(limitWithUncertainty));
            writeResultToCsv(QStringLiteral("测试值:%1,小于阈值%2,通过测试").arg(_decayRatePsiPerSecond).arg(limitWithUncertainty));
            _attemptIndex = _attemptCount;
            _inspectionResult = SUCCESS;
            return;
        }
        limitWithUncertainty = _leakLimitRate + _leakRateUncertainty;

        if(_decayRatePsiPerSecond > limitWithUncertainty)
        {
            emit statusChanged(QStringLiteral("测试值:%1,大于阈值%2,再次迭代").arg(_decayRatePsiPerSecond).arg(limitWithUncertainty));
            writeResultToCsv(QStringLiteral("测试值:%1,大于阈值%2,再次迭代").arg(_decayRatePsiPerSecond).arg(limitWithUncertainty));
            _belowLeakRate = false;
            _attemptIndex = _attemptCount;
        }
        ++_attemptIndex;
        _elpasedTime = 0;
    }while(_attemptIndex <= _attemptCount && !_belowLeakRate);
    emit statusChanged(QStringLiteral("已达到测试次数，未通过测试"));
    writeResultToCsv(QStringLiteral("已达到测试次数，未通过测试"));
    _belowLeakRate = true;
    _inspectionResult = FAILED;
}

void PressureInspection_InstrumentOperator::initPump()
{
}

PressureInspection_InstrumentOperator::PressureSampleInfo::PressureSampleInfo()
{

}

PressureInspection_InstrumentOperator::PressureSampleInfo::PressureSampleInfo(const QDateTime &sampleDateTime, double samplePressure)
{
    _sampleDateTime = sampleDateTime;
    _samplePressure = samplePressure;
}

PressureInspection_InstrumentOperator::SerieLinePairs::SerieLinePairs(const QDateTime &dateTime, double psi, int index)
{
    _dateTime = dateTime;
    _mbar = psi;
    _index = index;
}
