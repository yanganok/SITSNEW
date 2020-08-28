#include "miscfwidstr_command.h"

MiscFWIdStr_Command::MiscFWIdStr_Command()
{

}

MiscFWIdStr_Command::MiscFWIdStr_Command(InstrumentOperator *operate,  Response *response, int msec, QString fwId)
    :Command(operate, response, msec), _fwId(fwId)
{
}

bool MiscFWIdStr_Command::package(QByteArray &arr)
{
    return true;
}

bool MiscFWIdStr_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
