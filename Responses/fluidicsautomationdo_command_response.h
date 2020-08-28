#ifndef FLUIDICSAUTOMATIONDO_COMMAND_RESPONSE_H
#define FLUIDICSAUTOMATIONDO_COMMAND_RESPONSE_H
#include "response.h"

class FluidicsAutomationDo_Command_Response : public Response
{
public:
    FluidicsAutomationDo_Command_Response();
    FluidicsAutomationDo_Command_Response(quint32 ecode, QString english, QString fmtstr,
                                          quint32 msgnum, QString sensor, QString state,
                                          QString op, QString axis, QString axis2, QString exp,
                                          QString act);
public:
    quint32 ecode()const{return _ecode;}
    QString english()const{return _english;}
    QString fmtstr()const{return _fmtstr;}
    quint32 msgnum()const{return _msgnum;}
    QString sensor()const{return _sensor;}
    QString state()const{return _state;}
    QString op()const{return _op;}
    QString axis()const{return _axis;}
    QString axis2()const{return _axis2;}
    QString exp()const{return _exp;}
    QString act()const{return _act;}
private:
    quint32 _ecode; QString _english; QString _fmtstr;
    quint32 _msgnum; QString _sensor; QString _state;
    QString _op; QString _axis; QString _axis2; QString _exp;
    QString _act;
};
Q_DECLARE_METATYPE(FluidicsAutomationDo_Command_Response)
#endif // FLUIDICSAUTOMATIONDO_COMMAND_RESPONSE_H
