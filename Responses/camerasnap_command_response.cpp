#include "camerasnap_command_response.h"

CameraSnap_Command_Response::CameraSnap_Command_Response()
{
    _typeName = classtype();
}

CameraSnap_Command_Response::CameraSnap_Command_Response(quint32 id, quint32 failed_sensors,
                                                         quint32 sensor_retries, quint32 xy_retries,
                                                         quint32 camboard_reboots, quint32 data_length_bytes,
                                                         QVector<quint32> &data_addr, int xy_tgt, int x_nm,
                                                         int y_nm, QVector<int> &z_nm, QVector<int> &z_nm_calc,
                                                         QVector<quint32> &chksum,
                                                         QVector<quint8> &nstep_attempts)
    :_cmdId(id), _failed_sensors(failed_sensors), _sensor_retries(sensor_retries), _xy_retries(xy_retries),
      _camboard_reboots(camboard_reboots), _data_length_bytes(data_length_bytes), _data_addr(data_addr),
      _xy_tgt(xy_tgt), _x_nm(x_nm), _y_nm(y_nm), _z_nm(z_nm), _z_nm_calc(z_nm_calc), _chksum(chksum),
      _nstep_attempts(nstep_attempts)
{
    _typeName = classtype();
}
