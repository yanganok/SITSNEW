#ifndef CAMERAREADLEDDATA_COMMAND_H
#define CAMERAREADLEDDATA_COMMAND_H
#include "command.h"

class CameraReadLEDData_Command : public Command
{
    Q_OBJECT
public:
    CameraReadLEDData_Command();
    CameraReadLEDData_Command(InstrumentOperator* operate,  Response *response, int msec);
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr);
};

#endif // CAMERAREADLEDDATA_COMMAND_H
