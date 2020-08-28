#include "xysetsettlemsec_command.h"

XYSetSettleMsec_Command::XYSetSettleMsec_Command()
{

}

XYSetSettleMsec_Command::XYSetSettleMsec_Command(InstrumentOperator *operate,  Response *response, int msec, quint32 moveMsec)
    :Command(operate, response, msec), _moveMsec(moveMsec)
{

}

bool XYSetSettleMsec_Command::package(QByteArray &arr)
{
    return true;
}

bool XYSetSettleMsec_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
