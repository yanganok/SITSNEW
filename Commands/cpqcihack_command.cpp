#include "cpqcihack_command.h"

CPQCIHack_Command::CPQCIHack_Command()
{

}

CPQCIHack_Command::CPQCIHack_Command(InstrumentOperator *operate,  Response *response, int msec)
    :Command(operate, response, msec)
{

}

bool CPQCIHack_Command::package(QByteArray &arr)
{
    return true;
}

bool CPQCIHack_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
