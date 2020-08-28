#include "xyreinitialize_command.h"

XYReinitialize_Command::XYReinitialize_Command()
{

}

XYReinitialize_Command::XYReinitialize_Command(InstrumentOperator *operate,  Response *response, int msec)
    :Command(operate, response, msec)
{

}

bool XYReinitialize_Command::package(QByteArray &arr)
{
    return true;
}

bool XYReinitialize_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
