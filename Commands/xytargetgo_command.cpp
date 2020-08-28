#include "xytargetgo_command.h"

XYTargetGo_Command::XYTargetGo_Command()
{

}

XYTargetGo_Command::XYTargetGo_Command(InstrumentOperator *operate,  Response *response, int msec, quint32 index)
    :Command(operate, response, msec),_index(index)
{

}

bool XYTargetGo_Command::package(QByteArray &arr)
{
    return true;
}

bool XYTargetGo_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
