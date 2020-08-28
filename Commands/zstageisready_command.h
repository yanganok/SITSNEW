#ifndef ZSTAGEISREADY_COMMAND_H
#define ZSTAGEISREADY_COMMAND_H
#include "command.h"

class ZStageIsReady_Command : public Command
{
    Q_OBJECT
public:
    ZStageIsReady_Command();
    ZStageIsReady_Command(InstrumentOperator* operate,  Response *response, int msec, int which);
public:
    inline int which()const{return _which;}
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
private:
    int _which;
};

#endif // ZSTAGEISREADY_COMMAND_H
