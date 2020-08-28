#include "camerareadledgain_command_response.h"

CameraReadLEDGain_Command_Response::CameraReadLEDGain_Command_Response()
{
    _typeName = classtype();
}

CameraReadLEDGain_Command_Response::CameraReadLEDGain_Command_Response(QVector<quint16> red_gains, QVector<quint16> grn_gains)
    :_red_gains(red_gains), _grn_gains(grn_gains)
{
    _typeName = classtype();
}
