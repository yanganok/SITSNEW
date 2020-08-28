#include "rfidtaggetstatus_command.h"

RFIDTagGetStatus_Command::RFIDTagGetStatus_Command()
{

}

RFIDTagGetStatus_Command::RFIDTagGetStatus_Command(RFIDTagId tagId)
    :_tagId(tagId)
{

}

bool RFIDTagGetStatus_Command::package(QByteArray &arr)
{
    return true;
}

bool RFIDTagGetStatus_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
