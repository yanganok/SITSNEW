#ifndef XYENABLERANGECHECK_COMMAND_H
#define XYENABLERANGECHECK_COMMAND_H
#include "command.h"

class XYEnableRangeCheck_Command : public Command
{
    Q_OBJECT
public:
    XYEnableRangeCheck_Command();
    XYEnableRangeCheck_Command(InstrumentOperator* operate,  Response *response, int msec, bool enable);
public:
    inline bool enable()const{return _enable;}
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
private:
    bool _enable;
};

#endif // XYENABLERANGECHECK_COMMAND_H
