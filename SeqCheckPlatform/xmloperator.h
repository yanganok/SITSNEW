#ifndef XMLOPERATOR_H
#define XMLOPERATOR_H

#include <QObject>
#include <QDomDocument>

class XmlOperator : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int test READ test WRITE setTest NOTIFY TestChanged)
public:
    explicit XmlOperator(QObject *parent = nullptr);

public:
    inline int test()const{return _test;}
    inline void setTest(int value){_test = value;}
signals:
    void TestChanged(int value);
public slots:
    void OnTestChanged(int value);
private:
    int _test;
};

#endif // XMLOPERATOR_H
