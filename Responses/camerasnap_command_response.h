#ifndef CAMERASNAP_COMMAND_RESPONSE_H
#define CAMERASNAP_COMMAND_RESPONSE_H
#include "response.h"

class CameraSnap_Command_Response : public Response
{
public:
    CameraSnap_Command_Response();
    CameraSnap_Command_Response(quint32 cmdId, quint32 failed_sensors,
                                quint32 sensor_retries, quint32 xy_retries,
                                quint32 camboard_reboots, quint32 data_length_bytes,
                                QVector<quint32> &data_addr, int xy_tgt, int x_nm,
                                int y_nm, QVector<int> &z_nm, QVector<int> &z_nm_calc,
                                QVector<quint32> &chksum, QVector<quint8> &nstep_attempts);
public:

    inline quint32 cmdId()const {return _cmdId;}
    inline quint32 sensor_retries()const {return _sensor_retries;}
    inline quint32 failed_sensors()const {return _failed_sensors;}
    inline quint32 xy_retries()const {return _xy_retries;}
    inline quint32 camboard_reboots()const {return _camboard_reboots;}
    inline quint32 data_length_bytes()const {return _data_length_bytes;}
    inline int xy_tgt()const {return _xy_tgt;}
    inline int x_nm()const {return _x_nm;}
    inline int y_nm()const {return _y_nm;}
    inline const QVector<quint32> &data_addr()const{return _data_addr;}
    inline const QVector<int>  &z_nm()const{return _z_nm;}
    inline const QVector<int> &z_nm_calc()const{return _z_nm_calc;}
    inline const QVector<quint32> &chksum()const{return _chksum;}
    inline const QVector<quint8> &nstep_attempts()const{return _nstep_attempts;}
private:
    quint32 _cmdId; quint32 _failed_sensors;
    quint32 _sensor_retries; quint32 _xy_retries;
    quint32 _camboard_reboots; quint32 _data_length_bytes;
    QVector<quint32> _data_addr; int _xy_tgt; int _x_nm;
    int _y_nm; QVector<int> _z_nm; QVector<int> _z_nm_calc;
    QVector<quint32> _chksum; QVector<quint8> _nstep_attempts;
};
Q_DECLARE_METATYPE(CameraSnap_Command_Response)
#endif // CAMERASNAP_COMMAND_RESPONSE_H
