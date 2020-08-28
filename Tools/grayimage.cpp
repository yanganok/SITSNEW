#include "grayimage.h"
#include "normalexception.h"

GrayImage::GrayImage():_useStaticData(false)
{
    this->_width = 0;
    this->_height = 0;
    this->_date = QDateTime::currentDateTime();
}

GrayImage::GrayImage(quint32 width, quint32 height):_useStaticData(false)
{
    this->_date = QDateTime::currentDateTime();
   // GrayImage::GrayImage();
    this->resizeImageNoInit(width, height);
}

GrayImage::~GrayImage()
{
    _validRow.clear();
}

QImage* GrayImage::rotateImage(QImage &image, float rotationAngle, QImage::Format imageFormat)
{
    QTransform translateMatrix1(1, 0, 0, 1, static_cast<float>(image.width()) / -2, static_cast<float>(image.height()) / -2);
    QTransform rotationMatrix2(qCos(M_PI / 180 * rotationAngle), qSin(M_PI / 180 * rotationAngle), -qSin(M_PI / 180 * rotationAngle), qCos(M_PI / 180 * rotationAngle), 0, 0);
    QTransform resTrasnform = translateMatrix1 * rotationMatrix2;

    QVector<QPointF> pointfs{
                               QPointF(0, 0),
                               QPointF(image.width(), 0),
                               QPointF(0, image.height())
                           };

    for(int i = 0; i < pointfs.size(); ++i)
    {
        pointfs[i] = resTrasnform.map(pointfs[i]);
    }
    
    //image.save("D:\\TFS\\LaserSpotFilter_Expose\\1.0.0\\LaserSpotFilter_OpenCV\\AutoFocusError_QtOpencv\\testimageSource.tif", "tiff");
    image = image.transformed(resTrasnform);
    DebugOut(image.width());
    DebugOut(image.height());
    uchar* imgptr = image.bits();
    
    //image.save("D:\\TFS\\LaserSpotFilter_Expose\\1.0.0\\LaserSpotFilter_OpenCV\\AutoFocusError_QtOpencv\\testimage.tif", "tiff");
    QImage *dstImage = new QImage(image);

    //QRect rect = GrayImage::boundingBox(image, resTrasnform);
    //QPixmap* dstImage = new QPixmap(rect.width(), rect.height());
   // dstImage->
    //QImage image;

   // QTransform dstTransform;
    //dstTransform.translate(static_cast<float>(dstImage->width()) / 2, static_cast<float>(dstImage->height()) / 2);
    //dstImage->transformed(dstTransform);
    return  std::move(dstImage);
}

QRect GrayImage::boundingBox(QPixmap &image, const QTransform &transform)
{
    return QRect();
}

GrayImage *GrayImage::rotateImage(float rotationAngle)
{
    QImage image(this->width(), this->height(), QImage::Format_Grayscale16);
    memcpy(image.bits(), (quint8*)(this->data().get()), this->width() * this->height() * Image_Module::bytesPerPixel);
    std::shared_ptr<QImage> rotationImage = std::shared_ptr<QImage>(rotateImage(image, rotationAngle, image.format()));
   /* QImage image(this->width(), this->height(), QImage::Format_RGB888);
    int index = 0;
    for(int i = 0; i < image.height(); ++i)
    {
        quint8* dataPtr = image.scanLine(0) + (i * image.bytesPerLine());
        for(int j = 0; j < image.width(); ++j)
        {
            quint16 num = *(this->data().get() + index);
            ++index;
            *(dataPtr) = num & 0xff;
            *(dataPtr + 1) = (quint8)num >> 8;
            dataPtr += 3;
        }
    }
    std::shared_ptr<QImage> rotationImage = std::shared_ptr<QImage>(rotateImage(image, rotationAngle, image.format()));
    std::shared_ptr<quint16> data = std::shared_ptr<quint16>(new quint16[rotationImage.get()->width() * rotationImage.get()->height()], [](quint16 *arr){delete[] arr;});
    index = 0;
    for(int i = 0; i < rotationImage.get()->height(); ++i)
    {
        quint8* dataPtr = rotationImage.get()->scanLine(0) + (i * rotationImage.get()->bytesPerLine());
        for(int j = 0; j < rotationImage.get()->width(); ++j)
        {
            quint8 low = *(dataPtr);
            quint8 high = *(dataPtr + 1);
            *(data.get() + index) = high << 8 + low;
            ++index;
            dataPtr += 3;
        }
    }*/
    DebugOut(rotationImage.get()->width());
    DebugOut(rotationImage.get()->height());
    quint32 imageSize = rotationImage.get()->width() * rotationImage.get()->height();
    std::shared_ptr<quint32> data32 = std::shared_ptr<quint32>(new quint32[imageSize], [](quint32* arr) {delete[] arr; });
    memcpy(reinterpret_cast<char*>(data32.get()), rotationImage.get()->bits(), imageSize * sizeof(quint32));
    std::shared_ptr<quint16> data16 = std::shared_ptr<quint16>(new quint16[rotationImage.get()->width() * rotationImage.get()->height()], [](quint16* arr) {delete[] arr; });
    for (int i = 0; i < imageSize; ++i)
        *(data16.get() + i) = *(data32.get() + i);
    GrayImage *grayImage = new GrayImage();
    grayImage->setData(data16, rotationImage.get()->width(), rotationImage.get()->height());
    return std::move(grayImage);
}


void GrayImage::resizeImageNoInit(quint32 width, quint32 height)
{
    bool resized = false;
    //_locker.lockForWrite();
    if(width != this->width() || height != this->height())
    {
        if(!this->_useStaticData)
        {
            this->allocateData(width, height);
        }
        resized = true;
    }
    if(resized)
    {
        emit evImageSizeChanged(this, std::move(ImageSizeChangedEventArgs(width, height)));
    }
    //_locker.unlock();
}

void GrayImage::resizeImage(quint32 width, quint32 height)
{
    this->resizeImageNoInit(width, height);
    this->Erase();
}

void GrayImage::loadedImage(const QString& path)
{
    //_locker.lockForWrite();
    QFileInfo info(path);
    QString suffix = info.suffix();
    if (suffix == QString("jpg"))
    {
        Image_Module::LoadCompressedImage(path, this);
    }
    else if (suffix == QString("png"))
    {
        Image_Module::LoadFromPngFile(path, this);
    }
    else if (suffix == QString("tif"))
    {
        Image_Module::LoadFromTiffFile( this, path);
    }
   // _locker.unlock();
}

void GrayImage::saveImage(const QString& path)
{
    saveImage(path, Image_Module::ImageFormat::TIFF);
}

void GrayImage::saveImage(const QString& path, Image_Module::ImageFormat imageFormat)
{
    switch (imageFormat)
    {
    case Image_Module::ImageFormat::JPEG:
        break;
    case Image_Module::ImageFormat::PNG:        
        break;
    case Image_Module::ImageFormat::TIFF:
        Image_Module::SaveAsTiffFile(this, path, Image_Module::OverwriteHandling::BACKUPCURRENTFILEFIRST);
        _path = path;
        break;
    }
    _path = path;
}

void GrayImage::saveImage(const QString& path, Image_Module::ImageFormat imageFormat, int compression)
{

}

quint32 GrayImage::width()
{
    //DebugOut("GrayImage::width");
    quint32 width = 0;
    //_locker.lockForRead();
    width = _width;
    //_locker.unlock();
    return width;
}

quint32 GrayImage::height()
{
    quint32 height = 0;
    //_locker.lockForRead();
    height = _height;
    //_locker.unlock();
    return height;
}

std::shared_ptr<quint16> GrayImage::data()
{
    std::shared_ptr<quint16> data;
//    _locker.lockForRead();
    data = _data;
//    _locker.unlock();
    return std::move(data);
}

void GrayImage::Erase()
{
    this->Erase(Image_Module::BlankColor);
}

void GrayImage::Erase(quint16 color)
{
    this->InvalidateAllRows();
    FillImage(this, color);
}

void GrayImage::InvalidateAllRows()
{
    this->validateAllRows(false);
}

void GrayImage::setData(const std::shared_ptr<quint16> &data, quint32 width, quint32 height)
{
    try{
//       _locker.lockForWrite();
       this->resizeImageNoInit(width, height);
       if(data)
       {
           if(!_data)
           {
               throw NullException(QString("File %1 Line %2:cannot copy data to null data").arg(__FILE__).arg(__LINE__));
           }
           if(_width * _height < width * height)
           {
               throw IndexOutOfRangeException(QString("File %1 Line %2:cannot copy data to an array that has lesser length than original").arg(__FILE__).arg(__LINE__));
           }
       }
       memcpy(_data.get(), data.get(), width * height * 2);
//       _locker.unlock();
    }
    catch(QException &ex)
    {
    }
    emit evImageChanged(this, ImageChangedEventArgs());
}

void GrayImage::setData(const QVector<QVector<quint16> > &data)
{
    quint32 height = data.size();
    quint32 width = data.at(0).size();
    allocateData(width, height);
    for(int i = 0; i < height; ++i)
        for(int j = 0; j < width; ++j)
        {
            memcpy(reinterpret_cast<char *>(_data.get()) + i * width* 2, reinterpret_cast<const char *>(data[i].data()), width * 2);
        }
}

void GrayImage::setData(ImageBase &image)
{
    try
    {
//        _locker.lockForWrite();
//        image.locker().lockForWrite();
        resizeImageNoInit(image.width(), image.height());
        if(image.data())
        {
            memcpy(_data.get(), image.data().get(), image.width() * image.height() * 2);
        }
        //if(image)
//        image.locker().unlock();
//        _locker.unlock();
    }
    catch(...)
    {
        emit evImageChanged(this, ImageChangedEventArgs());
    }
}

void GrayImage::setStaticData(const std::shared_ptr<quint16> &data, quint32 width, quint32 height, bool staticFlagSetting)
{
    try{
//        _locker.lockForWrite();
        _width = width;
        _height = height;
        createValidRowArray();
        int size = width * height;
        _dataLength = size;
        if(data)
        {
            this->_data = data;
            this->_useStaticData = staticFlagSetting;
        }
//        _locker.unlock();
    }
    catch(QException &ex)
    {

    }
    emit evImageChanged(this, ImageChangedEventArgs());
}

void GrayImage::setTestImage(int val)
{
    try{
        this->resizeImageNoInit(2000u, 2000u);
//        _locker.lockForWrite();
        int pos = 0;
        if(val == 0)
        {
            for(int y = 0; y < this->_height; ++y)
            {
                for(int x = 0; x < this->_width; ++x)
                {
                    double px = (double)(x - this->_width / 2);
                    double py = (double)(y - this->_height / 2);
                    double r = sqrt(px * px + py + py);
                    *((_data.get()) + pos) = static_cast<quint16>(1600 - r);
                }
            }
        }
        else
        {
            for(int y2 = 0; y2 < this->_height; ++y2)
            {
                for(int x2 = 0; x2 < this->_width; ++x2)
                {
                    *((_data.get()) + pos) = (ushort)((val == 1) ? x2 : y2);
                }
            }
        }
//        _locker.unlock();
    }
    catch(...)
    {

    }
    emit evImageChanged(this, ImageChangedEventArgs());
}

Image_Module::ImageStruct &GrayImage::imageStruct()
{
    //Image_Module::ImageStruct result;
    //_locker.lockForWrite();
    _imageStruct.data = _data;
    _imageStruct.width = _width;
    _imageStruct.height = _height;
    //_locker.unlock();
    return _imageStruct;
}

void GrayImage::setVisible(bool value)
{
    if(value == _visible)
        return;
    _visible = value;
    emit evVisibilityChanged(this);
}

std::shared_ptr<QObject> GrayImage::Clone()
{
    std::shared_ptr<QObject> result;
//    _locker.lockForRead();
    GrayImage *newImage = new GrayImage();
    newImage->allocateData(this->width(), this->height());
    result = std::shared_ptr<QObject>(newImage);
//    _locker.unlock();
    return result;
}

void GrayImage::FillImage(ImageBase *image, quint16 pixVal)
{
    int width, height;
    //image->locker().lockForWrite();
    width = image->width();
    height = image->height();
    //image->locker().unlock();
    GrayImage::FillImage(image, QRect(0, 0, width, height), pixVal);
}

void GrayImage::FillImage(ImageBase *image, const QRect &partialRect, quint16 pixVal)
{
    //image->locker().lockForWrite();
    FillImage(image->imageStruct(), partialRect, pixVal);
    //image->locker().unlock();
    emit (image)->evImageChanged(image, ImageChangedEventArgs());
}

void GrayImage::FillImage(const Image_Module::ImageStruct &image, const QRect &partialRect, quint16 pixVal)
{
    QRect imageRect(0, 0, image.width, image.height);
    if(!imageRect.contains(partialRect))
    {
        throw NormalException("parital rect can't bigger than image rect");
    }
    quint16 *data = image.data.get();
    for(int row = 0; row < partialRect.height(); ++row)
    {
        ushort* startPixel = data + partialRect.left();
        for(int col = 0; col < partialRect.width(); ++col)
            *(startPixel++) = pixVal;
        data += imageRect.width();
    }
}

void GrayImage::createValidRowArray()
{
    //_locker.lockForWrite();
    this->_validRow.resize(_height);
    for(int i = 0; i < _height; ++i)
    {
        _validRow[i] = true;
    }
    //_locker.unlock();
}

void GrayImage::allocateData(quint32 width, quint32 height)
{
    //_locker.lockForWrite();
    quint32 size = 0;
    try{
        _width = width;
        _height = height;
        this->createValidRowArray();
        size = (quint32)(width * height);
        this->_dataLength = size;
        if(!this->_dataLength == 0)
           this->_data = std::shared_ptr<quint16>(new quint16[size],[](quint16 *p){
            delete[] p;
               });
    }
    catch(QException& ex)
    {
        this->_dataLength = 0;
        throw ApplicationException(QString("File %1 Line %2:failed to allocate image buffer of %3 bytes").arg(__FILE__).arg(__LINE__).arg(size * 2));
    }
    //_locker.unlock();
}

void GrayImage::validateAllRows(bool valid)
{
    bool sthChanged = false;
    //_locker.lockForWrite();
    for(quint32 i = 0; i < _height; ++i)
    {
        if(_validRow[i] != valid)
        {
            _validRow[i] = valid;
            sthChanged = true;
        }
    }
    //_locker.unlock();
    if(sthChanged)
    {
        emit evImageChanged(this, ImageChangedEventArgs());
    }
}
