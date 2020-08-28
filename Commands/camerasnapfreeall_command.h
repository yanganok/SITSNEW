#ifndef CAMERASNAPFREEALL_COMMAND_H
#define CAMERASNAPFREEALL_COMMAND_H
#include "command.h"

class CameraSnapFreeAll_Command:Command
{
    Q_OBJECT
public:
    CameraSnapFreeAll_Command();
    CameraSnapFreeAll_Command(InstrumentOperator* operate,  Response *response, int msec);
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr);
};

#endif // CAMERASNAPFREEALL_COMMAND_H
