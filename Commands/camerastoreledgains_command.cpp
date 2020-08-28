#include "camerastoreledgains_command.h"

CameraStoreLEDGains_Command::CameraStoreLEDGains_Command()
{

}

CameraStoreLEDGains_Command::CameraStoreLEDGains_Command(InstrumentOperator *operate,  Response *response, int msec, QVector<quint8>& red_gains, QVector<quint8>& grn_gains)
    :Command(operate, response, msec), _red_gains(red_gains), _grn_gains(grn_gains)
{

}

bool CameraStoreLEDGains_Command::package(QByteArray &arr)
{
    return true;
}

bool CameraStoreLEDGains_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
