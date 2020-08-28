#ifndef ZSTAGEINITIALIZE_COMMAND_H
#define ZSTAGEINITIALIZE_COMMAND_H
#include "command.h"

class ZStageInitialize_Command:public Command
{
    Q_OBJECT
public:
    ZStageInitialize_Command();
    ZStageInitialize_Command(InstrumentOperator* operate,  Response *response, int msec, int which);
public:
    inline int which()const{return _which;}
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
private:
    int _which;
};

#endif // ZSTAGEINITIALIZE_COMMAND_H
