#ifndef CAMERASNAP_COMMAND_H
#define CAMERASNAP_COMMAND_H
#include <QVector>
#include "command.h"
#include "globals/enums.h"

using namespace Camera_Module;
class CameraSnap_Command : public Command
{
    Q_OBJECT
public:
    CameraSnap_Command();
    CameraSnap_Command(InstrumentOperator* operate,  Response *response, int msec,
                        quint32 id, int xy_tgt, QVector<int>& z_nm,
                        CameraZAlgorithm z_algo, quint32 avg_frames, quint32 sensors,
                        quint32 bitdepth, quint16 origin_x, quint16 origin_y,
                        quint16 limit_x, quint16 limit_y, CameraChannelType channelType, CameraDataType dataType,
                        QVector<quint32>& exposure_usec, QVector<quint16>& sensor_gain,
                        QVector<quint8>& dac_setting, quint8 af_parameter_set, bool af_outlier_correction,
                        quint8 af_nstep_attempts, quint32 af_nstep_range_nm);
public:
    inline quint32 id()const {return _idCount;}
    inline quint32 avg_frames()const {return _avg_frames;}
    inline quint32 sensors()const {return _sensors;}
    inline quint32 bitdepth()const {return _bitdepth;}
    inline CameraZAlgorithm z_algo()const {return _z_algo;}
    inline quint16 origin_x()const {return _origin_x;}
    inline quint16 origin_y()const {return _origin_y;}
    inline quint16 limit_x()const {return _limit_x;}
    inline quint16 limit_y()const {return _limit_y;}
    inline CameraChannelType channelType()const {return _channelType;}
    inline CameraDataType dataType()const {return _dataType;}
    inline const QVector<quint32> &exposure_usec()const{return _exposure_usec;}
    inline const QVector<quint16> &sensor_gain()const{return _sensor_gain;}
    inline const QVector<quint8> &dac_setting()const{return _dac_setting;}
    inline quint8 af_parameter_set()const {return _af_parameter_set;}
    inline bool af_outlier_correction()const {return _af_outlier_correction;}
    inline quint8 af_nstep_attempts()const {return _af_nstep_attempts;}
    inline quint32 af_nstep_range_nm()const {return _af_nstep_range_nm;}
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr);
private:
    quint32 _idCount; int _xy_tgt; QVector<int> _z_nm;
    CameraZAlgorithm _z_algo; quint32 _avg_frames; quint32 _sensors;
    quint32 _bitdepth; quint16 _origin_x; quint16 _origin_y;
    quint16 _limit_x; quint16 _limit_y; CameraChannelType _channelType; CameraDataType _dataType;
    QVector<quint32> _exposure_usec; QVector<quint16> _sensor_gain;
    QVector<quint8> _dac_setting; quint8 _af_parameter_set; bool _af_outlier_correction;
    quint8 _af_nstep_attempts; quint32 _af_nstep_range_nm;
};

#endif // CAMERASNAP_COMMAND_H
