#include "xytargetset_command.h"

XYTargetSet_Command::XYTargetSet_Command()
{

}

XYTargetSet_Command::XYTargetSet_Command(InstrumentOperator *operate,  Response *response, int msec, quint32 index, int x_nm, int y_nm)
    :Command(operate, response, msec), _index(index), _x_nm(x_nm), _y_nm(y_nm)
{

}

bool XYTargetSet_Command::package(QByteArray &arr)
{
    return true;
}

bool XYTargetSet_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
