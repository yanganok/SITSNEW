#ifndef CAMERAPENALTY_COMMAND_H
#define CAMERAPENALTY_COMMAND_H
#include "command.h"
#include "globals/enums.h"

using namespace Camera_Module;
class CameraPenalty_Command : public Command
{
    Q_OBJECT
public:
    CameraPenalty_Command();
    CameraPenalty_Command(InstrumentOperator* operate,  Response *response, int msec, quint32 sensors, CameraChannelType type, quint32 penalty_msec);
public:
    inline quint32 sensors()const {return _sensors;}
    inline quint32 penalty_msec()const{return _penalty_msec;}
    inline CameraChannelType cameraChannelType()const{return _cameraChannelType;}
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr);
private:
    quint32 _sensors, _penalty_msec;
    CameraChannelType _cameraChannelType;
};

#endif // CAMERAPENALTY_COMMAND_H
