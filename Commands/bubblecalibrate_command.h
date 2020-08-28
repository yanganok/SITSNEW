#ifndef BUBBLE_CALIBRATE_H
#define BUBBLE_CALIBRATE_H
#include "command.h"
/**
* @projectName   SITS
* @brief         气泡校准命令
* @author        YangAn
* @date          2020-06-29
* @Email         yangan@AutoBio.com.cn
*/

class BubbleCalibrate_Command : public Command
{
    Q_OBJECT
public:
    BubbleCalibrate_Command();
    BubbleCalibrate_Command(InstrumentOperator* operate,  Response *response, int msec);
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
};

#endif // BUBBLE_CALIBRATE_H
