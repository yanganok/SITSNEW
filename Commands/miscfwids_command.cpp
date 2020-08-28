#include "miscfwids_command.h"

MiscFWIds_Command::MiscFWIds_Command()
{

}

MiscFWIds_Command::MiscFWIds_Command(InstrumentOperator *operate,  Response *response, int msec)
    :Command(operate, response, msec)
{

}

bool MiscFWIds_Command::package(QByteArray &arr)
{
    return true;
}

bool MiscFWIds_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
