#include "xysetminmovemsec_command.h"

XYSetMinMoveMsec_Command::XYSetMinMoveMsec_Command()
{

}

XYSetMinMoveMsec_Command::XYSetMinMoveMsec_Command(InstrumentOperator *operate,  Response *response, int msec, quint32 moveMsec)
    :Command(operate, response, msec), _moveMsec(moveMsec)
{

}

bool XYSetMinMoveMsec_Command::package(QByteArray &arr)
{
    return true;
}

bool XYSetMinMoveMsec_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
