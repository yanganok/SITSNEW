#include "valvewrite_command.h"

ValveWrite_Command::ValveWrite_Command()
{

}

ValveWrite_Command::ValveWrite_Command(InstrumentOperator *operate,  Response *response, int msec, int valve, QVector<quint8> &data, quint32 num)
    :Command(operate, response, msec), _valve(valve), _data(data), _num(num)
{

}

bool ValveWrite_Command::package(QByteArray &arr)
{
    return true;
}

bool ValveWrite_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
