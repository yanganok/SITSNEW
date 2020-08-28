#include "instrumentoperator.h"
#include "commands/command.h"
#include "communicationcore.h"
#include <functional>

InstrumentOperator::InstrumentOperator(QObject *parnet) : _core(nullptr)
{
    _core = CommunicationCore::CreateInstance();
    if(!_core->islauched())
        _core->lauch();
}

int InstrumentOperator::generateCommandList()
{
    //to do generate command list
    for(auto el : _commandList)
    {
        disconnect(el.get(), &Command::translateResponseToOperator, this, &InstrumentOperator::getResponse);
        connect(el.get(), &Command::translateResponseToOperator, this, &InstrumentOperator::getResponse, Qt::BlockingQueuedConnection);
    }
//    DebugOut(QString("Command Count:%1").arg(_commandList.size()))
    return _commandList.size();
}

void InstrumentOperator::insertCommandList()
{
//    DebugOut(QString("Command Count:%1").arg(_commandList.size()))
    _core->insertCommandList(_commandList);
}

void InstrumentOperator::getResponse(std::shared_ptr<Response> response)
{
    _responseList.append(response);
}

void InstrumentOperator::getStatus(std::shared_ptr<Response> response)
{
    _statusList.append(response);
}
