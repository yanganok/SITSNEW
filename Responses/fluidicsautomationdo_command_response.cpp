#include "fluidicsautomationdo_command_response.h"

FluidicsAutomationDo_Command_Response::FluidicsAutomationDo_Command_Response()
{
    _typeName = classtype();
}

FluidicsAutomationDo_Command_Response::FluidicsAutomationDo_Command_Response(
        quint32 ecode, QString english, QString fmtstr, quint32 msgnum, QString sensor,
        QString state, QString op, QString axis, QString axis2, QString exp, QString act)
    : _ecode(ecode), _english(english), _fmtstr(fmtstr), _msgnum(msgnum), _sensor(sensor),
      _state(state), _op(op), _axis(axis), _axis2(axis2), _exp(exp), _act(act)
{
    _typeName = classtype();
}
