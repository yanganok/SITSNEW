#ifndef CAMERA_COMMAND_H
#define CAMERA_COMMAND_H
#include "command.h"
#include "globals/enums.h"
using namespace Camera_Module;
class Camera_Command : public Command
{
    Q_OBJECT
public:
    Camera_Command();
    Camera_Command(InstrumentOperator* operate,  Response *response, int msec, quint32 sensors, CameraChannelType chanelType, quint8 level, quint32 duration_msec);
public:
    inline CameraChannelType cameraChannelType()const {return _cameraChannelType;}
    inline quint8 level()const{return _level;}
    inline quint32 duration_msec()const{return _duration_msec;}
    inline quint32 sensor()const{return _sensors;}
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
private:
    CameraChannelType _cameraChannelType;
    quint8 _level;
    quint32 _sensors,_duration_msec;
};

#endif // CAMERA_COMMAND_H
