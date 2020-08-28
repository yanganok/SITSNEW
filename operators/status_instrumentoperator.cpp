#include "status_instrumentoperator.h"
#include "communicationcore.h"

Status_InstrumentOperator::Status_InstrumentOperator(QObject *parent):InstrumentOperator(parent)
{
    _core->translateToResponse = std::bind(&InstrumentOperator::getResponse, this, std::placeholders::_1);
}

void Status_InstrumentOperator::createInstance()
{
    DebugOut("CreateInstance");
}

void Status_InstrumentOperator::getResponse(std::shared_ptr<Response> response)
{

}
