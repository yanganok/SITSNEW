#ifndef CAMERASETAF_COMMAND_H
#define CAMERASETAF_COMMAND_H
#include "command.h"

class CameraSetAF_Command : public Command
{
    Q_OBJECT
public:
    CameraSetAF_Command();
    CameraSetAF_Command(InstrumentOperator* operate,  Response *response, int msec,
                        quint8 sensor, quint8 af_parameter_set, quint16 origin_x,
                        quint16 origin_y, quint16 width_x, quint16 height_y,
                        int x_per_64k, QVector<quint32>& bg_image, int bg_threshold,
                        int y0_millirows, int gain, bool prefer_top_peak, int max_range_nm,
                        int min_range_nm);
public:
    inline quint8 sensor()const {return _sensor;}
    inline quint8 af_parameter_set()const {return _af_parameter_set;}
    inline quint16 origin_x()const {return _origin_x;}
    inline quint16 origin_y()const {return _origin_y;}
    inline quint16 width_x()const {return _width_x;}
    inline quint16 height_y()const {return _height_y;}
    inline int x_per_64k()const {return _x_per_64k;}
    inline int max_range_nm()const {return _max_range_nm;}
    inline int min_range_nm()const {return _min_range_nm;}
    inline int bg_threshold()const {return _bg_threshold;}
    inline int y0_millirows()const {return _y0_millirows;}
    inline int gain()const {return _gain;}
    inline const QVector<quint32>& bg_image()const {return _bg_image;}
    inline bool prefer_top_peak()const {return _prefer_top_peak;}
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr);
private:
    quint8 _sensor, _af_parameter_set;
    quint16 _origin_x, _origin_y, _width_x, _height_y;
    int _x_per_64k;
    int _max_range_nm, _min_range_nm;
    int _bg_threshold, _y0_millirows, _gain;
    QVector<quint32> _bg_image;
    bool _prefer_top_peak;
};

#endif // CAMERASETAF_COMMAND_H
