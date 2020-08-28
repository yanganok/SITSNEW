#include "sensorread_command.h"
#include "Responses/sensorread_command_response.h"

SensorRead_Command::SensorRead_Command()
{
    _typeName = classtype();
}

SensorRead_Command::SensorRead_Command(InstrumentOperator *operate,  Response *response, int msec, SensorType type, CommunicateCoreUnderlying::PressureSensorDeviceID deviceId, QString key, bool async, int delayMs)
    :Command(operate, response, msec, key, async, delayMs), _type(type), _deviceId(deviceId)
{
    _typeName = classtype();
}

bool SensorRead_Command::package(QByteArray &arr)
{
    switch (_type) {
    case SensorType::LIQUIDROADPRESSURE:
        arr = Command::toPackage(static_cast<quint8>(CommunicateCoreUnderlying::CommandType::SEND),
                    static_cast<quint8>(CommunicateCoreUnderlying::DevicType::DE_TP_LP),
                    static_cast<quint8>(_deviceId),
                    static_cast<quint8>(CommunicateCoreUnderlying::PressureSensorControlWord::CW_PV_GET),
                    QVector<quint32>{}
                    );
        Command::package(arr);
        break;
    default:
        break;
    }
    return true;
}

bool SensorRead_Command::packageToResponse(QByteArray &arr)
{
    int code;
    code = BytesToAny::toInt((quint8 *)arr.data() + 3);
    if(*(arr.data() + 9) == (quint8)CommunicateCoreUnderlying::PressureSensorControlWord::CW_PV_GET)
    {
        int pressure = BytesToAny::toInt((quint8 *)arr.data() + 11);
        SensorType sensortype = static_cast<SensorType>(*((quint8 *)arr.data() + 7));
        CommunicateCoreUnderlying::PressureSensorDeviceID deviceId = static_cast<CommunicateCoreUnderlying::PressureSensorDeviceID>(*((quint8 *)arr.data() + 8));
        std::shared_ptr<SensorRead_Command_Response> response(new SensorRead_Command_Response(code, sensortype, deviceId, pressure, _key));
        emit translateResponseToOperator(response);
        Command::packageToResponse(arr);
    }
    return true;
}

void SensorRead_Command::receiveResponse(QByteArray pkg)
{
    packageToResponse(pkg);
}
