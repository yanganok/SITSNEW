#include "loggetlist_command.h"

LogGetList_Command::LogGetList_Command()
{

}

LogGetList_Command::LogGetList_Command(InstrumentOperator *operate,  Response *response, int msec)
    :Command(operate, response, msec)
{

}

bool LogGetList_Command::package(QByteArray &arr)
{
    return true;
}

bool LogGetList_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
