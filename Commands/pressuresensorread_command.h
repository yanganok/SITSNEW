#ifndef PRESSURESENSORREAD_COMMAND_H
#define PRESSURESENSORREAD_COMMAND_H
#include "command.h"

class PressureSensorRead_Command : public Command
{
    Q_OBJECT
public:
    PressureSensorRead_Command();
    PressureSensorRead_Command(InstrumentOperator* operate,  Response *response, int msec, int sensor, quint8 readMsec);
public:
    inline int sensor()const{return _sensor;}
    inline quint8 readMsec()const{return _readMsec;}
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
private:
    int _sensor;
    quint8 _readMsec;
};

#endif // PRESSURESENSORREAD_COMMAND_H
