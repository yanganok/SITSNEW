#ifndef XYTARGETGO_COMMAND_H
#define XYTARGETGO_COMMAND_H
#include "command.h"

class XYTargetGo_Command : public Command
{
    Q_OBJECT
public:
    XYTargetGo_Command();
    XYTargetGo_Command(InstrumentOperator* operate,  Response *response, int msec, quint32 index);
public:
    inline quint32 index()const{return _index;}
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
private:
    quint32 _index;
};

#endif // XYTARGETGO_COMMAND_H
