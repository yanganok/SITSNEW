#ifndef MOTIONMOVE_COMMAND_H
#define MOTIONMOVE_COMMAND_H
#include "command.h"
#include "globals/enums.h"
using namespace MotionAixs_Module;
class MotionMove_Command : public Command
{
    Q_OBJECT
public:
    MotionMove_Command();
    MotionMove_Command(InstrumentOperator* operate,  Response *response, int msec, Motion_Axis axis, int distance);
public:
    inline Motion_Axis axis()const{return _axis;}
    inline int distance()const{return _distance;}
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
private:
    Motion_Axis _axis;
    int _distance;
};

#endif // MOTIONMOVE_COMMAND_H
