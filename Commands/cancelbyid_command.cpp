#include "cancelbyid_command.h"

CancelById_Command::CancelById_Command()
{

}

CancelById_Command::CancelById_Command(InstrumentOperator *operate,  Response *response, int msec, int id)
    :Command(operate, response, msec), _idCount(id)
{

}

bool CancelById_Command::package(QByteArray &arr)
{
    return true;
}

bool CancelById_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
