#ifndef CAMERAREADLEDGAINS_COMMAND_H
#define CAMERAREADLEDGAINS_COMMAND_H
#include "command.h"

class CameraReadLEDGains_Command : public Command
{
    Q_OBJECT
public:
    CameraReadLEDGains_Command();
    CameraReadLEDGains_Command(InstrumentOperator* operate,  Response *response, int msec);
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr);
};
#endif // CAMERAREADLEDGAINS_COMMAND_H
