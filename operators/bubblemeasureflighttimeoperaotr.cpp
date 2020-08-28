#include "bubblemeasureflighttimeoperaotr.h"
#include "Commands/bubblemeasureflighttime_command.h"
#include "Responses/bubblemeasureflighttime_command_response.h"
#include "Commands/bubblestopmeasureflighttime_command.h"
#include "communicationcore.h"

#include<QStringList>
using namespace GlobalPath;
BubbleMeasureFlightTime_InstrumentOperaotr::BubbleMeasureFlightTime_InstrumentOperaotr(QObject *parent)
    :InstrumentOperator(parent), _deviceId(CommunicateCoreUnderlying::BubbleDeviceId::LANEASENSOR)
{
    //_infos = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") + "\r\n";
    _timer.setInterval(1000);
    if(_isSimulation)
    {
        connect(&_timer, &QTimer::timeout, this, [this](){
            QString deviceId = "";
            switch (_deviceId) {
            case CommunicateCoreUnderlying::BubbleDeviceId::LANEASENSOR:
                deviceId = "LaneA";
                break;
            case CommunicateCoreUnderlying::BubbleDeviceId::LANEBSENSOR:
                deviceId = "LaneB";
                break;
            case CommunicateCoreUnderlying::BubbleDeviceId::LANEABSENSOR:
                deviceId = "LaneA and LaneB";
                break;
            case CommunicateCoreUnderlying::BubbleDeviceId::WASTE1SENSOR:
                deviceId = "Waste1";
                break;
            case CommunicateCoreUnderlying::BubbleDeviceId::LANEAWASTE1SENSOR :
                deviceId = "LaneA and Waste1";
                break;
            case CommunicateCoreUnderlying::BubbleDeviceId::LANEBWASTE1SENSOR :
                deviceId = "LaneB and Waste1";
                break;
            case CommunicateCoreUnderlying::BubbleDeviceId::LANEABWASTE1SENSOR :
                deviceId = "LaneA and LaneB and Waste1";
                break;
            case CommunicateCoreUnderlying::BubbleDeviceId::WASTE2SENSOR:
                deviceId = "Waste2";
                break;
            case CommunicateCoreUnderlying::BubbleDeviceId::LANEAWASTE2SENSOR :
                deviceId = "LaneA and Waste2";
                break;
            case CommunicateCoreUnderlying::BubbleDeviceId::LANEBWASTE2SENSOR :
                deviceId = "LaneB and Waste2";
                break;
            case CommunicateCoreUnderlying::BubbleDeviceId::LANEABWASTE2SENSOR :
                deviceId = "LaneA and LaneB and Waste2";
                break;
            case CommunicateCoreUnderlying::BubbleDeviceId::WASTE12SENSOR :
                deviceId = "Waste1 and Waste2";
                break;
            case CommunicateCoreUnderlying::BubbleDeviceId::LANEAWASTE12SENSOR :
                deviceId = "LaneA and Waste1 and Waste2";
                break;
            case CommunicateCoreUnderlying::BubbleDeviceId::LANEBWASTE12SENSOR :
                deviceId = "LaneB and Waste1 and Waste2";
                break;
            case CommunicateCoreUnderlying::BubbleDeviceId::LANEABWASTE12SENSOR :
                deviceId = "LandA and LaneB and Waste1 and Waste2";
                break;
            default:
                break;
            }
           this->_infos += QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") + ":" + deviceId + "\r\n";
            emit refreshInfoPosted(this->_infos);
            emit statusChanged("simulated");
        });
    }
    else
    {
        connect(&_timer, &QTimer::timeout, this, [this](){
            _infos = _displayInfos.join(QString());
            if(!_infos.isEmpty())
                emit refreshInfoPosted(_infos);

            switch (_core->communicateStatus()) {
            case CommunicateCoreUnderlying::CommunicateStatus::OPENED:
                emit statusChanged("Port is open");
                break;
            case CommunicateCoreUnderlying::CommunicateStatus::CLOSE:
                emit statusChanged("Port is close");
                break;
            case CommunicateCoreUnderlying::CommunicateStatus::OCCUPY:
                emit statusChanged("Port is occupy");
                break;
            case CommunicateCoreUnderlying::CommunicateStatus::ISNOTEXISTS:
                emit statusChanged("Port is not exists");
                break;
            default:
                break;
            }
        });
    }
}

QString BubbleMeasureFlightTime_InstrumentOperaotr::infos() const
{
    return _infos;
}


int BubbleMeasureFlightTime_InstrumentOperaotr::generateCommandList()
{
    BubbleMeasureFlightTime_Command_Response *response = nullptr;
    _commandList.append(std::shared_ptr<BubbleMeasureFlightTime_Command>(new BubbleMeasureFlightTime_Command(this, response, -1, _deviceId)));
    return InstrumentOperator::generateCommandList();
}

void BubbleMeasureFlightTime_InstrumentOperaotr::insertCommandList()
{
    InstrumentOperator::insertCommandList();
}

void BubbleMeasureFlightTime_InstrumentOperaotr::startTest()
{
    if(_isSimulation)
    {
        _timer.start();
        return;
    }
    QString deviceId;
    switch (_deviceId) {
    case CommunicateCoreUnderlying::BubbleDeviceId::LANEASENSOR:
        deviceId = "LaneA";
        break;
    case CommunicateCoreUnderlying::BubbleDeviceId::LANEBSENSOR:
        deviceId = "LaneB";
        break;
    case CommunicateCoreUnderlying::BubbleDeviceId::LANEABSENSOR:
        deviceId = "LaneA and LaneB";
        break;
    case CommunicateCoreUnderlying::BubbleDeviceId::WASTE1SENSOR:
        deviceId = "Waste1";
        break;
    case CommunicateCoreUnderlying::BubbleDeviceId::LANEAWASTE1SENSOR :
        deviceId = "LaneA and Waste1";
        break;
    case CommunicateCoreUnderlying::BubbleDeviceId::LANEBWASTE1SENSOR :
        deviceId = "LaneB and Waste1";
        break;
    case CommunicateCoreUnderlying::BubbleDeviceId::LANEABWASTE1SENSOR :
        deviceId = "LaneA and LaneB and Waste1";
        break;
    case CommunicateCoreUnderlying::BubbleDeviceId::WASTE2SENSOR:
        deviceId = "Waste2";
        break;
    case CommunicateCoreUnderlying::BubbleDeviceId::LANEAWASTE2SENSOR :
        deviceId = "LaneA and Waste2";
        break;
    case CommunicateCoreUnderlying::BubbleDeviceId::LANEBWASTE2SENSOR :
        deviceId = "LaneB and Waste2";
        break;
    case CommunicateCoreUnderlying::BubbleDeviceId::LANEABWASTE2SENSOR :
        deviceId = "LaneA and LaneB and Waste2";
        break;
    case CommunicateCoreUnderlying::BubbleDeviceId::WASTE12SENSOR :
        deviceId = "Waste1 and Waste2";
        break;
    case CommunicateCoreUnderlying::BubbleDeviceId::LANEAWASTE12SENSOR :
        deviceId = "LaneA and Waste1 and Waste2";
        break;
    case CommunicateCoreUnderlying::BubbleDeviceId::LANEBWASTE12SENSOR :
        deviceId = "LaneB and Waste1 and Waste2";
        break;
    case CommunicateCoreUnderlying::BubbleDeviceId::LANEABWASTE12SENSOR :
        deviceId = "LandA and LaneB and Waste1 and Waste2";
        break;
    default:
        break;
    }
    _fileName = deviceId + "_" + QDateTime::currentDateTime().toString("yyyyMMddHHmmss")+ ".csv";
    writeResultToCsv();
    _timer.start();
    _displayInfos.clear();
    _commandList.clear();
    _responseList.clear();

//    _commandList.clear();
//    _commandList.append(std::shared_ptr<BubbleStopMeasureFlightTime_Command>(new BubbleStopMeasureFlightTime_Command(this, nullptr, -1, _deviceId)));
    generateCommandList();
    insertCommandList();
}

void BubbleMeasureFlightTime_InstrumentOperaotr::endTest()
{
    if(_isSimulation)
    {
        _timer.stop();
    }
    _timer.stop();
    _commandList.clear();
    _commandList.append(std::shared_ptr<BubbleStopMeasureFlightTime_Command>(new BubbleStopMeasureFlightTime_Command(this, nullptr, -1, _deviceId)));


    generateCommandList();
    insertCommandList();
    _core->setRead(false);
}

void BubbleMeasureFlightTime_InstrumentOperaotr::getResponse(std::shared_ptr<Response> response)
{

    QString deviceId;
    QStringList strs;
    if(response->typeName() == "BubbleMeasureFlightTime_Command_Response")
    {
        BubbleMeasureFlightTime_Command_Response *el = reinterpret_cast<BubbleMeasureFlightTime_Command_Response *>(response.get());
        switch (el->deviceId()) {
        case CommunicateCoreUnderlying::BubbleDeviceId::LANEASENSOR:
            deviceId = "LaneA";
            break;
        case CommunicateCoreUnderlying::BubbleDeviceId::LANEBSENSOR:
            deviceId = "LaneB";
            break;
        case CommunicateCoreUnderlying::BubbleDeviceId::LANEABSENSOR:
            deviceId = "LaneA and LaneB";
            break;
        case CommunicateCoreUnderlying::BubbleDeviceId::WASTE1SENSOR:
            deviceId = "Waste1";
            break;
        case CommunicateCoreUnderlying::BubbleDeviceId::LANEAWASTE1SENSOR :
            deviceId = "LaneA and Waste1";
            break;
        case CommunicateCoreUnderlying::BubbleDeviceId::LANEBWASTE1SENSOR :
            deviceId = "LaneB and Waste1";
            break;
        case CommunicateCoreUnderlying::BubbleDeviceId::LANEABWASTE1SENSOR :
            deviceId = "LaneA and LaneB and Waste1";
            break;
        case CommunicateCoreUnderlying::BubbleDeviceId::WASTE2SENSOR:
            deviceId = "Waste2";
            break;
        case CommunicateCoreUnderlying::BubbleDeviceId::LANEAWASTE2SENSOR :
            deviceId = "LaneA and Waste2";
            break;
        case CommunicateCoreUnderlying::BubbleDeviceId::LANEBWASTE2SENSOR :
            deviceId = "LaneB and Waste2";
            break;
        case CommunicateCoreUnderlying::BubbleDeviceId::LANEABWASTE2SENSOR :
            deviceId = "LaneA and LaneB and Waste2";
            break;
        case CommunicateCoreUnderlying::BubbleDeviceId::WASTE12SENSOR :
            deviceId = "Waste1 and Waste2";
            break;
        case CommunicateCoreUnderlying::BubbleDeviceId::LANEAWASTE12SENSOR :
            deviceId = "LaneA and Waste1 and Waste2";
            break;
        case CommunicateCoreUnderlying::BubbleDeviceId::LANEBWASTE12SENSOR :
            deviceId = "LaneB and Waste1 and Waste2";
            break;
        case CommunicateCoreUnderlying::BubbleDeviceId::LANEABWASTE12SENSOR :
            deviceId = "LandA and LaneB and Waste1 and Waste2";
            break;
        default:
            break;
        }
        strs.append(el->recDateTime());
        strs.append(",");
        strs.append(deviceId);
        strs.append(",");
        strs.append(QString::number(el->code()));
        strs.append(",");
        strs.append(QString::number(el->usec()));
    }
    writeResultToCsv(strs.join(QString()));
    strs.append("\r\n");
    if(_displayInfos.size() < 200)
    {
        _displayInfos.append(strs.join(QString()));
    }
    else
    {
        _displayInfos.removeAt(0);
        _displayInfos.append(strs.join(QString()));
    }
    //this->_infos += strs.join(QString());
    InstrumentOperator::getResponse(response);
}

void BubbleMeasureFlightTime_InstrumentOperaotr::getSensorType(int id)
{
    _deviceId = static_cast<CommunicateCoreUnderlying::BubbleDeviceId>(id);
}

void BubbleMeasureFlightTime_InstrumentOperaotr::writeResultToCsv()
{
    QStringList strs;
    strs.append(QStringLiteral("记录时间"));
    strs.append(",");
    strs.append(QStringLiteral("设备名称"));
    strs.append(",");
    strs.append(QStringLiteral("气泡个数"));
    strs.append(",");
    strs.append(QStringLiteral("间隔时间"));
    strs.append("\r\n");
    QString content = strs.join(QString());
    if(!QDir(localFilePath + "/BubbleMeasureTimeResults/").exists())
    {
        QDir dir;
        dir.mkdir(localFilePath + "/BubbleMeasureTimeResults/");
    }
    QFile file(localFilePath + "/BubbleMeasureTimeResults/" + _fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        return;
    }
    QTextStream txtOutput(&file);
    txtOutput << content << endl;
    file.close();
}

void BubbleMeasureFlightTime_InstrumentOperaotr::writeResultToCsv(const QString &info)
{
    QString content = info;
    if(!QDir(localFilePath + "/BubbleMeasureTimeResults/").exists())
    {
        QDir dir;
        dir.mkdir(localFilePath + "/BubbleMeasureTimeResults/");
    }
    QFile file(localFilePath + "/BubbleMeasureTimeResults/" + _fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        return;
    }
    QTextStream txtOutput(&file);
    txtOutput << content << endl;
    file.close();
}


//BubbleMeasureFlightTimeMeasureModel *BubbleMeasureFlightTimeOperaotr::result() const
//{
//    return _result;
//}

//QQmlListProperty<BubbleMeasureFlightTimeMeasureModel> BubbleMeasureFlightTimeOperaotr::results()
//{
//    return QQmlListProperty<BubbleMeasureFlightTimeMeasureModel>(this, &(this->_results));
//}

//void BubbleMeasureFlightTimeOperaotr::appendResult(BubbleMeasureFlightTimeMeasureModel *res)
//{
//    _results.append(res);
//}

//int BubbleMeasureFlightTimeOperaotr::resultCount() const
//{
//    return _results.count();
//}

//BubbleMeasureFlightTimeMeasureModel *BubbleMeasureFlightTimeOperaotr::get(int index) const
//{
//    return _results.at(index);
//}

//void BubbleMeasureFlightTimeOperaotr::clearResults()
//{
//    _results.clear();
//}

//void BubbleMeasureFlightTimeOperaotr::replaceResult(int index, BubbleMeasureFlightTimeMeasureModel *m)
//{
//    _results[index] = m;
//}

//void BubbleMeasureFlightTimeOperaotr::removeLastResult()
//{
//    _results.removeLast();
//}

//void BubbleMeasureFlightTimeOperaotr::getResponse(Response *response, const QString &typeName)
//{

//    InstrumentOperator::getResponse(response, typeName);
//}

//void BubbleMeasureFlightTimeOperaotr::appendResult(QQmlListProperty<BubbleMeasureFlightTimeMeasureModel> *list, BubbleMeasureFlightTimeMeasureModel *m)
//{
//    reinterpret_cast<BubbleMeasureFlightTimeOperaotr *>(list->data)->appendResult(m);
//}

//int BubbleMeasureFlightTimeOperaotr::resultCount(QQmlListProperty<BubbleMeasureFlightTimeMeasureModel> *list)
//{
//    return reinterpret_cast<BubbleMeasureFlightTimeOperaotr *>(list->data)->resultCount();
//}

//BubbleMeasureFlightTimeMeasureModel *BubbleMeasureFlightTimeOperaotr::get(QQmlListProperty<BubbleMeasureFlightTimeMeasureModel> *list, int index)
//{
//    return reinterpret_cast<BubbleMeasureFlightTimeOperaotr *>(list->data)->get(index);
//}

//void BubbleMeasureFlightTimeOperaotr::clearResults(QQmlListProperty<BubbleMeasureFlightTimeMeasureModel> *list)
//{
//    reinterpret_cast<BubbleMeasureFlightTimeOperaotr *>(list->data)->clearResults();
//}

//void BubbleMeasureFlightTimeOperaotr::replaceResult(QQmlListProperty<BubbleMeasureFlightTimeMeasureModel> *list, int index, BubbleMeasureFlightTimeMeasureModel *m)
//{
//    reinterpret_cast<BubbleMeasureFlightTimeOperaotr *>(list->data)->replaceResult(index, m);
//}

//void BubbleMeasureFlightTimeOperaotr::removeLastResult(QQmlListProperty<BubbleMeasureFlightTimeMeasureModel> *list)
//{
//    reinterpret_cast<BubbleMeasureFlightTimeOperaotr *>(list->data)->removeLastResult();
//}
