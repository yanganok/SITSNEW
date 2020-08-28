#ifndef CAMERAENABLEZSETTLING_COMMAND_H
#define CAMERAENABLEZSETTLING_COMMAND_H
#include "command.h"

class CameraEnableZSettling_Command : public Command
{
    Q_OBJECT
public:
    CameraEnableZSettling_Command();
    CameraEnableZSettling_Command(InstrumentOperator* operate,  Response *response, int msec, bool enable);
public:
    inline bool enable()const{return _enable;}
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr);
private:
    bool _enable;
};

#endif // CAMERAENABLEZSETTLING_COMMAND_H
