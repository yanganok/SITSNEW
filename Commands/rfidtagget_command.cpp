#include "rfidtagget_command.h"

RFIDTagGet_Command::RFIDTagGet_Command()
{

}

RFIDTagGet_Command::RFIDTagGet_Command(InstrumentOperator *operate,  Response *response, int msec, int rfid)
    :Command(operate, response, msec), _rfid(rfid)
{

}

bool RFIDTagGet_Command::package(QByteArray &arr)
{
    return true;
}

bool RFIDTagGet_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
