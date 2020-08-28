#include "pumptest_instrumentoperator.h"
#include "Commands/pumpabsorb_command.h"
#include "Commands/pumpdispense_command.h"
#include "Commands/pumpinit_command.h"
#include "Responses/pumpabsorb_command_response.h"
#include "Responses/pumpdispense_command_response.h"
#include "Responses/pumpinit_command_response.h"

PumpTest_InstrumentOperator::PumpTest_InstrumentOperator()
{

}

void PumpTest_InstrumentOperator::startTest(TestType testType, int valveId, int speed, int volumn)
{
    switch (testType) {
    case INIT:
        _commandList.clear();
        //PumpInit_Command_Response *response = nullptr;
        _commandList.push_back(std::shared_ptr<PumpInit_Command>(new PumpInit_Command(this, nullptr)));
        DebugOut("start test pump init");
        break;
    case ABSORB:
    {
        _commandList.clear();
        //PumpInit_Command_Response *response = nullptr;
        _commandList.push_back(std::shared_ptr<PumpAbsorb_Command>(new PumpAbsorb_Command(this, nullptr, -1, CommunicateCoreUnderlying::SyringPumpId::ALL, valveId, speed, volumn)));
        DebugOut("start test pump absorb");
    }
    break;
    case DISPENSE:
        _commandList.clear();
        //PumpInit_Command_Response *response = nullptr;
        _commandList.push_back(std::shared_ptr<PumpDispense_Command>(new PumpDispense_Command(this, nullptr, -1, CommunicateCoreUnderlying::SyringPumpId::ALL, valveId, speed, volumn)));
        DebugOut("start test pump dispense");
        break;
    default:
        break;
    }
    generateCommandList();
    insertCommandList();
}

void PumpTest_InstrumentOperator::autoTest(int valveId, int speed, int volumn)
{
    _commandList.clear();
    //PumpInit_Command_Response *response = nullptr;
    _commandList.push_back(std::shared_ptr<PumpInit_Command>(new PumpInit_Command(this, nullptr)));
    _commandList.push_back(std::shared_ptr<PumpAbsorb_Command>(new PumpAbsorb_Command(this, nullptr, -1, CommunicateCoreUnderlying::SyringPumpId::ALL, valveId, speed, volumn)));
    _commandList.push_back(std::shared_ptr<PumpDispense_Command>(new PumpDispense_Command(this, nullptr, -1, CommunicateCoreUnderlying::SyringPumpId::ALL, valveId, speed, volumn)));
    generateCommandList();
    insertCommandList();
}

int PumpTest_InstrumentOperator::generateCommandList()
{
    return InstrumentOperator::generateCommandList();
}

void PumpTest_InstrumentOperator::insertCommandList()
{
    InstrumentOperator::insertCommandList();
}

void PumpTest_InstrumentOperator::getResponse(std::shared_ptr<Response> response)
{
    if(response->typeName() == "PumpInit_Command_Response")
    {
        PumpInit_Command_Response *rsp = reinterpret_cast<PumpInit_Command_Response *>(response.get());
        DebugOut(QString("%1, %2").arg((int)rsp->deviceId()).arg((int)rsp->status()));
    }

    if(response->typeName() == "PumpAbsorb_Command_Response")
    {
        PumpAbsorb_Command_Response *rsp = reinterpret_cast<PumpAbsorb_Command_Response *>(response.get());
        DebugOut(QString("%1, %2").arg((int)rsp->deviceId()).arg((int)rsp->curPos()));
    }

    if(response->typeName() == "PumpDispense_Command_Response")
    {
        PumpDispense_Command_Response *rsp = reinterpret_cast<PumpDispense_Command_Response *>(response.get());
        DebugOut(QString("%1, %2").arg((int)rsp->deviceId()).arg((int)rsp->curPos()));
    }
    InstrumentOperator::getResponse(response);
}

void PumpTest_InstrumentOperator::getStatus(std::shared_ptr<Response> response)
{

}
