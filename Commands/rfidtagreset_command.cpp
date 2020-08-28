#include "rfidtagreset_command.h"

RFIDTagReset_Command::RFIDTagReset_Command()
{

}

RFIDTagReset_Command::RFIDTagReset_Command(InstrumentOperator *operate,  Response *response, int msec, RFIDTagId rfid)
    :Command(operate, response, msec), _rfid(rfid)
{

}

bool RFIDTagReset_Command::package(QByteArray &arr)
{
    return true;
}

bool RFIDTagReset_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
