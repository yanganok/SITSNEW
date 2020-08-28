#ifndef IMAGEBASE_H
#define IMAGEBASE_H
#include <exception>
#include <memory>
#include <QVector>
#include <QDateTime>
#include <QReadWriteLock>
#include <QObject>

#include "globals/globalSet.h"
#include "Tools/imagechangedeventargs.h"
#include "Tools/imagesizechangedeventargs.h"

class ImageBase:public QObject
{
    Q_OBJECT
signals:
    /**
     * @brief evImageSizeChanged 图像大小改变事件
     * @param sender
     * @param args
     */
    void evImageSizeChanged(QObject *sender, const ImageSizeChangedEventArgs& args);

    /**
     * @brief evVisibilityChanged 是否可见事件
     * @param sender
     */
    void evVisibilityChanged(QObject *sender);

    /**
     * @brief evImageChanged
     * @param sender
     */
    void evImageChanged(QObject *sender, const ImageChangedEventArgs);
public:
    ImageBase();
//    ImageBase(ImageBase &image);
    ~ImageBase();
protected:
//    QReadWriteLock _locker;
    quint32 _width, _height;
    std::shared_ptr<quint16> _data;
    QVector<bool> _validRow;
    bool _visible;
    QDateTime _date;
    Image_Module::ImageStruct _imageStruct;
public:
    virtual void resizeImageNoInit(quint32 width, quint32 height);
    virtual void resizeImage(quint32 width, quint32 height);
    virtual void saveImage(const QString& path);
    virtual quint32 width();
    virtual quint32 height()const;
    virtual bool visible()const;
    std::shared_ptr<QObject> Clone();
    virtual const std::shared_ptr<quint16> &data()const{return _data;}
    inline QVector<bool> &validRow() {return _validRow;}
    inline const QDateTime& date()const{return _date;}
    virtual Image_Module::ImageStruct &imageStruct();
//    inline QReadWriteLock& locker(){return  _locker;}
};

#endif // IMAGEBASE_H
