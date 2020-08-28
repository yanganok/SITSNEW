#include "pump_command.h"
int Pump_Command::_curPos = 0;
/**
 * @brief Pump_Command::Pump_Command 发送为ul, 接收为步
 */
Pump_Command::Pump_Command()
{

}

Pump_Command::Pump_Command(InstrumentOperator *operate, Response *response, int msec, QString key, bool async, int delayMs)
    :Command(operate, response, msec, key, async, delayMs)
{

}

