#ifndef GETINTERFACESIGNATURE_COMMAND_H
#define GETINTERFACESIGNATURE_COMMAND_H
#include "command.h"

class GetInterfaceSignature_Command : public Command
{
    Q_OBJECT
public:
    GetInterfaceSignature_Command();
    GetInterfaceSignature_Command(InstrumentOperator* operate,  Response *response, int msec);
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
private:
};

#endif // GETINTERFACESIGNATURE_COMMAND_H
