#include "xyenablerangecheck_command.h"

XYEnableRangeCheck_Command::XYEnableRangeCheck_Command()
{

}

XYEnableRangeCheck_Command::XYEnableRangeCheck_Command(InstrumentOperator *operate,  Response *response, int msec,  bool enable)
    :Command(operate, response, msec), _enable(enable)
{

}

bool XYEnableRangeCheck_Command::package(QByteArray &arr)
{
    return true;
}

bool XYEnableRangeCheck_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
