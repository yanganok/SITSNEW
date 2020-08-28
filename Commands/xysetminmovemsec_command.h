#ifndef XYSETMINMOVEMSEC_COMMAND_H
#define XYSETMINMOVEMSEC_COMMAND_H
#include "command.h"

class XYSetMinMoveMsec_Command : public Command
{
    Q_OBJECT
public:
    XYSetMinMoveMsec_Command();
    XYSetMinMoveMsec_Command(InstrumentOperator* operate,  Response *response, int msec, quint32 moveMsec);
public:
    inline quint32 moveMsec()const{return  _moveMsec;}
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
private:
    quint32 _moveMsec;
};

#endif // XYSETMINMOVEMSEC_COMMAND_H
