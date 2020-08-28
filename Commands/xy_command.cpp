#include "xy_command.h"
int XY_Command::_curPos = 0;
XY_Command::XY_Command()
{

}

XY_Command::XY_Command(InstrumentOperator *operate, Response *response, int msec)
    :Command(operate, response, msec)
{

}
