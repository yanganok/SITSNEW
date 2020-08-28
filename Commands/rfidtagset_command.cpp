#include "rfidtagset_command.h"

RFIDTagSet_Command::RFIDTagSet_Command()
{

}

RFIDTagSet_Command::RFIDTagSet_Command(InstrumentOperator *operate,  Response *response, int msec, RFIDTagId tagId, RFIDTag_Command_Response tag)
    :Command(operate, response, msec), _tagId(tagId), _tag(tag)
{

}

bool RFIDTagSet_Command::package(QByteArray &arr)
{
    return true;
}

bool RFIDTagSet_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
