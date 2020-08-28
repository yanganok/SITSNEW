#ifndef XYREINITIALIZE_COMMAND_H
#define XYREINITIALIZE_COMMAND_H
#include "command.h"

class XYReinitialize_Command : public Command
{
    Q_OBJECT
public:
    XYReinitialize_Command();
    XYReinitialize_Command(InstrumentOperator* operate,  Response *response, int msec);
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
};

#endif // XYREINITIALIZE_COMMAND_H
