#ifndef CAMERAREADLEDDATA_RESPONSE_H
#define CAMERAREADLEDDATA_RESPONSE_H
#include <QVector>
#include "response.h"

class CameraReadLEDData_Command_Response : public Response
{
public:
    CameraReadLEDData_Command_Response();
    CameraReadLEDData_Command_Response(
            QVector<quint16>& grn1_gain, QVector<quint16>& grn1_power,
            QVector<quint16>& red1_gain, QVector<quint16>& red1_power,
            QVector<quint16>& grn2_gain, QVector<quint16>& grn2_power,
            QVector<quint16>& red2_gain, QVector<quint16>& red2_power,
            QVector<quint16>& grn3_gain, QVector<quint16>& grn3_power,
            QVector<quint16>& red3_gain, QVector<quint16>& red3_power,
            QVector<quint16>& grn4_gain, QVector<quint16>& grn4_power,
            QVector<quint16>& red4_gain, QVector<quint16>& red4_power);
public:
    inline const QVector<quint16>& grn1_gain()const{return _grn1_gain;}
    inline const QVector<quint16>& grn2_gain()const{return _grn2_gain;}
    inline const QVector<quint16>& grn3_gain()const{return _grn3_gain;}
    inline const QVector<quint16>& grn4_gain()const{return _grn4_gain;}
    inline const QVector<quint16>& red1_gain()const{return _red1_gain;}
    inline const QVector<quint16>& red2_gain()const{return _red2_gain;}
    inline const QVector<quint16>& red3_gain()const{return _red3_gain;}
    inline const QVector<quint16>& red4_gain()const{return _red4_gain;}
    inline const QVector<quint16>& grn1_power()const{return _grn1_power;}
    inline const QVector<quint16>& grn2_power()const{return _grn2_power;}
    inline const QVector<quint16>& grn3_power()const{return _grn3_power;}
    inline const QVector<quint16>& grn4_power()const{return _grn4_power;}
    inline const QVector<quint16>& red1_power()const{return _red1_power;}
    inline const QVector<quint16>& red2_power()const{return _red2_power;}
    inline const QVector<quint16>& red3_power()const{return _red3_power;}
    inline const QVector<quint16>& red4_power()const{return _red4_power;}
private:
    QVector<quint16> _grn1_gain, _grn1_power;
    QVector<quint16> _red1_gain, _red1_power;
    QVector<quint16> _grn2_gain, _grn2_power;
    QVector<quint16> _red2_gain, _red2_power;
    QVector<quint16> _grn3_gain, _grn3_power;
    QVector<quint16> _red3_gain, _red3_power;
    QVector<quint16> _grn4_gain, _grn4_power;
    QVector<quint16> _red4_gain, _red4_power;
};
Q_DECLARE_METATYPE(CameraReadLEDData_Command_Response)
#endif // CAMERAREADLEDDATA_RESPONSE_H
