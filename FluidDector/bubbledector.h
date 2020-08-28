#ifndef BUBBLEDECTOR_H
#define BUBBLEDECTOR_H

#include <QObject>
#include "ixmloperator.h"

class BubbleDector
        : public QObject, public IXMLOperator
{
    Q_OBJECT
public:
    explicit BubbleDector(QObject *parent = nullptr);
    ~BubbleDector() override;
public:
    void toXMLFile() override;
    void fromXMLFile() override;
signals:

public slots:
};

#endif // BUBBLEDECTOR_H
