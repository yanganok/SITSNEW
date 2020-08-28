#ifndef ZSTAGEGETHEIGHT_COMMAND_H
#define ZSTAGEGETHEIGHT_COMMAND_H
#include "command.h"

class ZStageGetHeight_Command : public Command
{
    Q_OBJECT
public:
    ZStageGetHeight_Command();
    ZStageGetHeight_Command(InstrumentOperator* operate,  Response *response, int msec, int sensors);
public:
    inline int sensors()const{return _sensors;}
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
private:
    int _sensors;
};

#endif // ZSTAGEGETHEIGHT_COMMAND_H
