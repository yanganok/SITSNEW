#ifndef HUMIDITYREAD_COMMAND_H
#define HUMIDITYREAD_COMMAND_H
#include "command.h"

class HumidityRead_Command : public Command
{
    Q_OBJECT
public:
    HumidityRead_Command();
    HumidityRead_Command(InstrumentOperator* operate,  Response *response, int msec, int millic);
public:
    inline int millic()const{return _millic;}
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
private:
    int _millic;
};

#endif // HUMIDITYREAD_COMMAND_H
