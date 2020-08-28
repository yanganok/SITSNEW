#ifndef SYSTEMLED_COMMAND_H
#define SYSTEMLED_COMMAND_H
#include "command.h"

class SystemLED_Command : public Command
{
    Q_OBJECT
public:
    SystemLED_Command();
    SystemLED_Command(InstrumentOperator* operate,  Response *response, int msec, quint8 r, quint8 g, quint8 b);
public:
    inline quint8 r()const{return _r;}
    inline quint8 g()const{return _g;}
    inline quint8 b()const{return _b;}
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
private:
    quint8 _r;
    quint8 _g;
    quint8 _b;
};

#endif // SYSTEMLED_COMMAND_H
