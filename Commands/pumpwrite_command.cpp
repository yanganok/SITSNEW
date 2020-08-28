#include "pumpwrite_command.h"

PumpWrite_Command::PumpWrite_Command()
{

}

PumpWrite_Command::PumpWrite_Command(InstrumentOperator *operate,  Response *response, int msec, QVector<quint8> &data, quint32 num)
    :Command(operate, response, msec), _data(data), _num(num)
{

}

void PumpWrite_Command::receiveResponse(QByteArray pkg)
{
    packageToResponse(pkg);

}

bool PumpWrite_Command::package(QByteArray &arr)
{
    return true;
}

bool PumpWrite_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
