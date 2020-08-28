#ifndef IXMLOPERATOR_H
#define IXMLOPERATOR_H

#include<qdebug.h>
#include<qstring.h>
class IXMLOperator
{
public:
    IXMLOperator();
    virtual ~IXMLOperator();
public:
    virtual void toXMLFile()=0;
    virtual void fromXMLFile()=0;
};

#endif // IXMLOPERATOR_H
