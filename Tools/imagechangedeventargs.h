#ifndef IMAGECHANGEDEVENTARGS_H
#define IMAGECHANGEDEVENTARGS_H
#include <qglobal.h>
#include <globals/enums.h>

class ImageChangedEventArgs
{
public:
    ImageChangedEventArgs();
    ImageChangedEventArgs(quint32 firstLine, quint32 numLines);
public:
    inline quint32 firstLine()const{return _firstLine;}
    inline quint32 numLine()const{return _numLine;}
    inline Image_Module::ChangeType changeType()const{return _type;}
    inline void setChangeType(Image_Module::ChangeType value){ _type = value; }
    inline bool IsWholeImage()const {return this->_firstLine == 0 && this->_numLine == 0;}
public:
    const quint32 ALL_LINES = UINT32_MAX;
private:
    quint32 _firstLine;
    quint32 _numLine;
    Image_Module::ChangeType _type;
};

#endif // IMAGECHANGEDEVENTARGS_H
