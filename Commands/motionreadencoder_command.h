#ifndef MOTIONNOTIFY_H
#define MOTIONNOTIFY_H
#include "command.h"
#include "globals/enums.h"

using namespace MotionAixs_Module;
class MotionReadEncoder_Command:public Command
{
    Q_OBJECT
public:
    MotionReadEncoder_Command();
    MotionReadEncoder_Command(InstrumentOperator* operate,  Response *response, int msec,
                         Motion_Axis axis);
public:
    inline Motion_Axis axis()const{return _axis;}
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
private:
    Motion_Axis _axis;
};

#endif // MOTIONNOTIFY_H
