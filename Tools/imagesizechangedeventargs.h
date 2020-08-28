#ifndef IMAGESIZECHANGEDEVENTARGS_H
#define IMAGESIZECHANGEDEVENTARGS_H
#include <qglobal.h>

class ImageSizeChangedEventArgs
{
public:
    ImageSizeChangedEventArgs()=delete;
    ImageSizeChangedEventArgs(quint32 rows, quint32 cols);
public:
    inline quint32 rows()const{return _rows;}
    inline quint32 cols()const{return _cols;}
private:
    quint32 _rows;
    quint32 _cols;
};

#endif // IMAGESIZECHANGEDEVENTARGS_H
