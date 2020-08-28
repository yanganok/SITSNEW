#include "pumptestmodel.h"
#include <qdatetime.h>

PumpTestModel::PumpTestModel(QObject *parent):_isFirstRefresh(true)
{
    _timer.setInterval(1000);
    connect(&_timer, &QTimer::timeout, this, [this](){
        refresh();
    });
    _timer.start();
    refresh();
}

int PumpTestModel::rowCount(const QModelIndex &parent) const
{
    return _tableData.size();
}

int PumpTestModel::columnCount(const QModelIndex &parent) const
{
    if(_tableData.size() > 0)
    {
        return _tableData.at(0).size();
    }
    return 0;
}

QVariant PumpTestModel::data(const QModelIndex &index, int role) const
{
    //qDebug() << index.row() << index.column() << endl;
    if(_tableData.size() > 0)
    {
        switch (role) {
        case TableDataRole:
        {
            return  _tableData.at(index.row()).at(index.column());
        }
        case HeadingRole:
        {
            return index.row() == 0;
        }
        default:
            break;
        }
    }
    return QVariant();
}

bool PumpTestModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    return false;
}

QVariant PumpTestModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant();
}

QHash<int, QByteArray> PumpTestModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[TableDataRole] = "tableData";
    roles[HeadingRole] = "heading";
    return roles;
}

void PumpTestModel::refresh()
{
//    beginResetModel();
    if(_isFirstRefresh)
    {
        _tableData.push_back({QStringLiteral("设备号"), QStringLiteral("泵号"), QStringLiteral("状态")});
        _isFirstRefresh = false;
    }
    _tableData.push_back({QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz"), QStringLiteral("pumpId"), QStringLiteral("status")});
//    endResetModel();
}

QVariant PumpTestModel::getInitResult(const QModelIndex &index, int role)
{
//    if(index.column() == 0)
//    {
//        switch (role) {
//        case TableDataRole:
//        {
//            QString deviceId = "NONE";
//            switch (reinterpret_cast<PumpInit_Command_Response *>(_responseList.at(index.row()).get())->deviceId()) {
//            case CommunicateCoreUnderlying::SyringPumpId::ALL:
//                deviceId = "All";
//                break;
//            case CommunicateCoreUnderlying::SyringPumpId::SYRING1CS:
//                deviceId = "Syringe1";
//                break;
//            case CommunicateCoreUnderlying::SyringPumpId::SYRING2CS:
//                deviceId = "Syringe2";
//                break;
//            case CommunicateCoreUnderlying::SyringPumpId::NONE:
//                deviceId = "None";
//                break;
//            default:
//                deviceId = "Error";
//                break;
//            }
//            return deviceId;
//        }
//        case HeadingRole:
//        {
//            bool isHeading = (index.row() == 0);
//            return isHeading;
//        }
//        default:
//            break;
//        }
//        return QVariant();
//    }

//    if(index.column() == 1)
//    {
//        switch (role) {
//        case TableDataRole:
//        {
//            QString status = "NONE";
//            switch (reinterpret_cast<PumpInit_Command_Response *>(_responseList.at(index.row()).get())->status()) {
//            case CommunicateCoreUnderlying::SyringPumpStatusWord::stSY_FAILED_INIT:
//                status = "Failed init";
//                break;
//            case CommunicateCoreUnderlying::SyringPumpStatusWord::stSY_NO_ERR:
//                status = "Sucessed init";
//                break;
//            default:
//                status = "Error";
//                break;
//            }
//            return status;
//        }
//        case HeadingRole:
//            return index.row() == 0;
//        default:
//            break;
//        }
//    }

    return QVariant();
}

QVariant PumpTestModel::getAbsorbResult(const QModelIndex &index, int role)
{
//    if(index.column() == 0)
//    {
//        switch (role) {
//        case TableDataRole:
//        {
//            QString deviceId = "NONE";
//            switch (reinterpret_cast<PumpAbsorb_Command_Response *>(_responseList.at(index.row()).get())->deviceId()) {
//            case CommunicateCoreUnderlying::SyringPumpId::ALL:
//                deviceId = "All";
//                break;
//            case CommunicateCoreUnderlying::SyringPumpId::SYRING1CS:
//                deviceId = "Syringe1";
//                break;
//            case CommunicateCoreUnderlying::SyringPumpId::SYRING2CS:
//                deviceId = "Syringe2";
//                break;
//            case CommunicateCoreUnderlying::SyringPumpId::NONE:
//                deviceId = "None";
//                break;
//            default:
//                deviceId = "Error";
//                break;
//            }
//            return deviceId;
//        }
//        case HeadingRole:
//            return index.row() == 0;
//        default:
//            break;
//        }
//    }

//    if(index.column() == 1)
//    {
//        switch (role) {
//        case TableDataRole:
//        {
//            QString status = "NONE";
//            status = QString::number(reinterpret_cast<PumpAbsorb_Command_Response *>(_responseList.at(index.row()).get())->curPos());
//            return status;
//        }
//        case HeadingRole:
//            return index.row() == 0;
//        default:
//            break;
//        }
//    }

    return QVariant();
}

QVariant PumpTestModel::getDispenseResult(const QModelIndex &index, int role)
{
//    if(index.column() == 0)
//    {
//        switch (role) {
//        case TableDataRole:
//        {
//            QString deviceId = "NONE";
//            switch (reinterpret_cast<PumpDispense_Command_Response *>(_responseList.at(index.row()).get())->deviceId()) {
//            case CommunicateCoreUnderlying::SyringPumpId::ALL:
//                deviceId = "All";
//                break;
//            case CommunicateCoreUnderlying::SyringPumpId::SYRING1CS:
//                deviceId = "Syringe1";
//                break;
//            case CommunicateCoreUnderlying::SyringPumpId::SYRING2CS:
//                deviceId = "Syringe2";
//                break;
//            case CommunicateCoreUnderlying::SyringPumpId::NONE:
//                deviceId = "None";
//                break;
//            default:
//                deviceId = "Error";
//                break;
//            }
//            return deviceId;
//        }
//        case HeadingRole:
//            return index.row() == 0;
//        default:
//            break;
//        }
//    }

//    if(index.column() == 1)
//    {
//        switch (role) {
//        case TableDataRole:
//        {
//            QString status = "NONE";
//            status = QString::number(reinterpret_cast<PumpDispense_Command_Response *>(_responseList.at(index.row()).get())->curPos());
//            return status;
//        }
//        case HeadingRole:
//            return index.row() == 0;
//        default:
//            break;
//        }
//    }

    return QVariant();
}
