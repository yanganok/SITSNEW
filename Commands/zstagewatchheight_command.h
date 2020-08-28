#ifndef ZSTAGEWATCHHEIGHT_COMMAND_H
#define ZSTAGEWATCHHEIGHT_COMMAND_H
#include "command.h"

class ZStageWatchHeight_Command : public Command
{
    Q_OBJECT
public:
    ZStageWatchHeight_Command();
    ZStageWatchHeight_Command(InstrumentOperator* operate,  Response *response, int msec, quint32 sensors);
public:
    inline int sensors()const{return _sensors;}
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
private:
    quint32 _sensors;
};

#endif // ZSTAGEWATCHHEIGHT_COMMAND_H
