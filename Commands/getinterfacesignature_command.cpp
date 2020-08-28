#include "getinterfacesignature_command.h"

GetInterfaceSignature_Command::GetInterfaceSignature_Command()
{

}

GetInterfaceSignature_Command::GetInterfaceSignature_Command(InstrumentOperator *operate,  Response *response, int msec)
    :Command(operate, response, msec)
{

}

bool GetInterfaceSignature_Command::package(QByteArray &arr)
{
    return true;
}

bool GetInterfaceSignature_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
