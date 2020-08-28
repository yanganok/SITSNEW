#include "camerareadleddata_command_response.h"

CameraReadLEDData_Command_Response::CameraReadLEDData_Command_Response()
{
    _typeName = classtype();
}

CameraReadLEDData_Command_Response::CameraReadLEDData_Command_Response(QVector<quint16> &grn1_gain, QVector<quint16> &grn1_power, QVector<quint16> &red1_gain, QVector<quint16> &red1_power, QVector<quint16> &grn2_gain, QVector<quint16> &grn2_power, QVector<quint16> &red2_gain, QVector<quint16> &red2_power, QVector<quint16> &grn3_gain, QVector<quint16> &grn3_power, QVector<quint16> &red3_gain, QVector<quint16> &red3_power, QVector<quint16> &grn4_gain, QVector<quint16> &grn4_power, QVector<quint16> &red4_gain, QVector<quint16> &red4_power)
    : _grn1_gain(grn1_gain), _grn1_power(grn1_power), _red1_gain(red1_gain), _red1_power(red1_power),
      _grn2_gain(grn2_gain), _grn2_power(grn2_power), _red2_gain(red2_gain), _red2_power(red2_power),
      _grn3_gain(grn3_gain), _grn3_power(grn3_power), _red3_gain(red3_gain), _red3_power(red3_power),
      _grn4_gain(grn4_gain), _grn4_power(grn4_power), _red4_gain(red4_gain), _red4_power(red4_power)
{
    _typeName = classtype();
}
