#include "camerasnap_command.h"

CameraSnap_Command::CameraSnap_Command()
{

}

CameraSnap_Command::CameraSnap_Command(InstrumentOperator *operate,  Response *response, int msec,
                                       quint32 id, int xy_tgt, QVector<int> &z_nm, CameraZAlgorithm z_algo,
                                       quint32 avg_frames, quint32 sensors, quint32 bitdepth, quint16 origin_x,
                                       quint16 origin_y, quint16 limit_x, quint16 limit_y,
                                       CameraChannelType channelType, CameraDataType dataType,
                                       QVector<quint32> &exposure_usec, QVector<quint16> &sensor_gain,
                                       QVector<quint8> &dac_setting, quint8 af_parameter_set,
                                       bool af_outlier_correction, quint8 af_nstep_attempts,
                                       quint32 af_nstep_range_nm)
    : Command(operate, response, msec), _idCount(id), _xy_tgt(xy_tgt), _z_nm(z_nm), _z_algo(z_algo),_avg_frames(avg_frames),
      _sensors(sensors), _bitdepth(bitdepth), _origin_x(origin_x), _origin_y(origin_y), _limit_x(limit_x),
      _limit_y(limit_y), _channelType(channelType), _dataType(dataType), _exposure_usec(exposure_usec),
      _sensor_gain(sensor_gain), _dac_setting(dac_setting), _af_parameter_set(af_parameter_set),
      _af_outlier_correction(af_outlier_correction), _af_nstep_attempts(af_nstep_attempts),
      _af_nstep_range_nm(af_nstep_range_nm)
{

}

bool CameraSnap_Command::package(QByteArray &arr)
{
    return true;
}

bool CameraSnap_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
