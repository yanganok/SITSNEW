#include "xytargetsset_command.h"

XYTargetsSet_Command::XYTargetsSet_Command()
{

}

XYTargetsSet_Command::XYTargetsSet_Command(InstrumentOperator *operate,  Response *response, int msec, QVector<quint32> &index, QVector<int> &x_nm, QVector<int> &y_nm)
    :Command(operate, response, msec), _x_nm(x_nm), _y_nm(y_nm), _index(index)
{

}

bool XYTargetsSet_Command::package(QByteArray &arr)
{
    return true;
}

bool XYTargetsSet_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
