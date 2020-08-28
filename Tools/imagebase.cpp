#include "imagebase.h"

ImageBase::ImageBase():_width(0), _height(0), _date(QDateTime::currentDateTime())
{

}

ImageBase::~ImageBase()
{
    
}

//ImageBase::ImageBase(ImageBase &image)
//    :_width(image.width()), _height(image.height()), _visible(image.visible()), _date(image.date())
//{
//    _data = std::shared_ptr<quint16>(new quint16[_width * _height], [](quint16 *p){delete[] p;});
//    memcpy(_data.get(), image.data().get(), _width * _height * sizeof(quint16));
//    for(int i = 0; i < _height; ++i)
//    {
//        *(_validRow.get() + i) = *(image.validRow().get() + i);
//    }
//}

void ImageBase::resizeImageNoInit(quint32 width, quint32 height)
{

}

void ImageBase::resizeImage(quint32 width, quint32 height)
{

}

void ImageBase::saveImage(const QString& path)
{

}

quint32 ImageBase::width()
{
    DebugOut("ImageBase::width");
    return _width;
}

quint32 ImageBase::height() const
{
    return _height;
}

bool ImageBase::visible() const
{
    return _visible;
}

std::shared_ptr<QObject> ImageBase::Clone()
{
//    ImageBase imageBase = new ImageBase();
//    std::shared_ptr<quint16>(new quint16[_width * _height], [](quint16 *p){delete[] p;});
//    memcpy(_data.get(), image.data().get(), _width * _height * sizeof(quint16));
//        for(int i = 0; i < _height; ++i)
//        {
//            *(_validRow.get() + i) = *(image.validRow().get() + i);
//        }
    return std::shared_ptr<QObject>(nullptr);
}

Image_Module::ImageStruct &ImageBase::imageStruct()
{
    return _imageStruct;
}

