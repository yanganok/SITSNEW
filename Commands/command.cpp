#include "command.h"
#include "instrumentoperator.h"
#include "Responses/audio_command_response.h"


int Command::_idCount = 0;
Command::Command():_msec(-1)
{
    Command::_idCount = (Command::_id == INT32_MAX ? 0:Command::_idCount+1);
    _id = _idCount;
    _typeName = classtype();
    //DebugOut(_typeName);
}

Command::Command(InstrumentOperator* operate,  Response *response, int msec, QString key, bool async, int delayMs)
    :_msec(msec), _async(async), _key(key),_delayMs(delayMs)
{
    Command::_idCount = (Command::_id == INT32_MAX ? 0:Command::_idCount+1);
    _id = _idCount;
    _typeName = classtype();
    if(operate != nullptr)
    {
        connect(this, &Command::translateResponseToOperator, operate, &InstrumentOperator::getResponse);
        _response = response;
//        DebugOut(QString("传入响应容器"));
    }
    else
    {
        //DebugOut(QString("仪器操作者为空"));
    }
    //getResponse = std::bind(&InstrucmentOperator::getResponse, *operate,std::placeholders::_1);
    //Response *response =
    //connect(this, &Command::translateResponseToOperator, operate, &InstrucmentOperator::getResponse);
}

QString Command::status() const
{
    switch (_cmdStatus) {
    case CommandStatus::READY_SEND:
        return "READY_SEND";
    case CommandStatus::COMMAND_FAULT:
        return "COMMAND_FAULT";
    case CommandStatus::RECEIVED:
        return "RECEIVED";
    case CommandStatus::SENDED:
        return "SENDED";
    default:
        return "UNKNOWN";
    }
}

void Command::sendCommand()
{
    DebugOut("Packging and Send");
    package(_package);
    _cmdStatus = CommandStatus::SENDED;
}

void Command::receiveResponse(QByteArray pkg)
{
#ifdef DEBUG
                QString s = BytesToAny::QByteArrayToHexString(pkg);
#endif
//    _recvPackage.resize(pkg.size());
//    memcpy(_recvPackage.data(), pkg.data(), pkg.size());
//    packageToResponse(_recvPackage);
}

bool Command::package(QByteArray& arr)
{
    _cmdStatus = CommandStatus::READY_SEND;
//    DebugOut(QString("命令Id:%1，状态为%2").arg(Command::_id).arg(status()));
//#ifdef DEBUG
//    QString s =  _typeName + " SendPackage:";
//    for(auto el : arr)
//    {
//        s += QString("%1 ").arg(el & 0xFF, 2, 16, QLatin1Char('0'));
//    }
//    DebugOut(s+ "|" + QString::number(arr.size()));
//#endif
    return true;
}


bool Command::packageToResponse(QByteArray& arr)
{
//    Response *response = new Audio_Command_Response();
//    emit translateResponseToOperator(QVariant::fromValue(*response));
    _cmdStatus = CommandStatus::RECEIVED;
    return true;
}

const QString Command::classtype() const
{
    return QString::fromStdString(typeid(*this).name()).mid(6);
}

QByteArray Command::toPackage(quint8 cmdType, quint8 devType, quint8 devId, quint8 ctrlWord, const QVector<qint32> &paras)
{
    QByteArray arr;
    quint8 header[]{0xEB, 0x90};
    quint8 tailer[]{0xDC, 0x97};
    quint8 ddcl[]{devType, devId, ctrlWord, (quint8)(paras.size() * sizeof(qint32))};
    quint8 lRC = 0;

    arr.append(reinterpret_cast<char *>(header), 2);
    arr.append((char)cmdType);
    int id1 = id();
    arr.append(reinterpret_cast<char *>(&id1), sizeof(int));
    arr.append(reinterpret_cast<char*>(ddcl), 4);
    arr.append((char *)(paras.data()), (quint8)(paras.size() * sizeof(qint32)));
    for(int i = 2; i < arr.size(); ++i)
    {
        lRC += arr.at(i);
    }
    arr.append((char)lRC);
    arr.append(reinterpret_cast<char *>(tailer), 2);
    return std::move(arr);
}

QByteArray Command::toPackage(quint8 cmdType, quint8 devType, quint8 devId, quint8 ctrlWord, const QVector<quint32> &paras)
{
    QByteArray arr;
    quint8 header[]{0xEB, 0x90};
    quint8 tailer[]{0xDC, 0x97};
    quint8 ddcl[]{devType, devId, ctrlWord, (quint8)(paras.size() * sizeof(quint32))};
    quint8 lRC = 0;

    arr.append(reinterpret_cast<char *>(header), 2);
    arr.append((char)cmdType);
    int id1 = id();
    arr.append(reinterpret_cast<char *>(&id1), sizeof(int));
    arr.append(reinterpret_cast<char*>(ddcl), 4);
    arr.append((char *)(paras.data()), (quint8)(paras.size() * sizeof(quint32)));
    for(int i = 2; i < arr.size(); ++i)
    {
        lRC += arr.at(i);
    }
    arr.append((char)lRC);
    arr.append(reinterpret_cast<char *>(tailer), 2);
    return std::move(arr);
}

QByteArray Command::toPackage(quint8 cmdType, quint8 devType, quint8 devId, quint8 ctrlWord, const QVector<quint16> &paras)
{
    QByteArray arr;
    quint8 header[]{0xEB, 0x90};
    quint8 tailer[]{0xDC, 0x97};
    quint8 ddcl[]{devType, devId, ctrlWord, (quint8)(paras.size() * sizeof(quint16))};
    quint8 lRC = 0;

    arr.append(reinterpret_cast<char *>(header), 2);
    arr.append((char)cmdType);
    int id1 = id();
    arr.append(reinterpret_cast<char *>(&id1), sizeof(int));
    arr.append(reinterpret_cast<char*>(ddcl), 4);
    arr.append((char *)(paras.data()), (quint8)(paras.size() * sizeof(quint16)));
    for(int i = 2; i < arr.size(); ++i)
    {
        lRC += arr.at(i);
    }
    arr.append((char)lRC);
    arr.append(reinterpret_cast<char *>(tailer), 2);
    return std::move(arr);
}


