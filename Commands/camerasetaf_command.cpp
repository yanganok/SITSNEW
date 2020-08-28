#include "camerasetaf_command.h"

CameraSetAF_Command::CameraSetAF_Command()
{

}

CameraSetAF_Command::CameraSetAF_Command(InstrumentOperator *operate,  Response *response, int msec,
                                         quint8 sensor, quint8 af_parameter_set, quint16 origin_x,
                                         quint16 origin_y, quint16 width_x, quint16 height_y,
                                         int x_per_64k, QVector<quint32> &bg_image, int bg_threshold,
                                         int y0_millirows, int gain, bool prefer_top_peak, int max_range_nm,
                                         int min_range_nm)
    : Command(operate, response, msec), _sensor(sensor), _af_parameter_set(af_parameter_set),
      _origin_x(origin_x), _origin_y(origin_y), _width_x(width_x), _height_y(height_y),
      _x_per_64k(x_per_64k), _bg_image(bg_image), _bg_threshold(bg_threshold), _y0_millirows(y0_millirows),
      _prefer_top_peak(prefer_top_peak), _max_range_nm(max_range_nm), _min_range_nm(min_range_nm)
{

}

bool CameraSetAF_Command::package(QByteArray &arr)
{
    return true;
}

bool CameraSetAF_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
