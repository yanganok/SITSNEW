#ifndef BUBBLEGETCOUNT_COMMAND_RESPONSE_H
#define BUBBLEGETCOUNT_COMMAND_RESPONSE_H
#include <QVariant>
#include "response.h"
class BubbleGetCount_Command_Response : public Response
{
public:
    BubbleGetCount_Command_Response();
    BubbleGetCount_Command_Response(quint32 count);
public:
    inline quint32 count()const{return _count;}
private:
    quint32 _count;
};
Q_DECLARE_METATYPE(BubbleGetCount_Command_Response)
#endif // BUBBLEGETCOUNT_COMMAND_RESPONSE_H
