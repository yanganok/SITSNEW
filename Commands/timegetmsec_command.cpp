#include "timegetmsec_command.h"

TimeGetMSEC_Command::TimeGetMSEC_Command()
{

}

TimeGetMSEC_Command::TimeGetMSEC_Command(InstrumentOperator *operate,  Response *response, int msec)
    :Command(operate, response, msec)
{

}

bool TimeGetMSEC_Command::package(QByteArray &arr)
{
    return true;
}

bool TimeGetMSEC_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
