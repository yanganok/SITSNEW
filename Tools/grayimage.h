#ifndef GRAYIMAGE_H
#define GRAYIMAGE_H
#include <QMap>
#include <QRect>
#include <QTransform>
//#include <math.h>
#include <qmath.h>
#include <QImage>
#include <QPixmap>
#include <QPainterPath>
#include <QException>
#include <qmatrix.h>
#include "globals/enums.h"
#include "imagebase.h"
#include "imagechangedeventargs.h"
#include "imagesizechangedeventargs.h"
#include "applicationexception.h"
#include "nullexception.h"
#include "indexoutofrangeexception.h"
/**
* @projectName   SITS
* @brief         灰度图类
* @author        YangAn
* @date          2020-07-10
* @Email         yangan@AutoBio.com.cn
*/

class GrayImage:public ImageBase
{
    Q_OBJECT
public:
    GrayImage();
    GrayImage(quint32 width, quint32 height);
    ~GrayImage();
public:
    /**
     * @brief rotateImage   旋转图片
     * @param image         图像
     * @param rotationAngle 旋转角度
     * @param imageFormat   图片格式
     * @return              返回新的图片指针
     */
    static QImage* rotateImage(QImage& image, float rotationAngle, QImage::Format imageFormat);
    static QRect boundingBox(QPixmap& image, const QTransform &transform);
    /**
     * @brief rotateImage   旋转图片
     * @param rotationAngle 旋转角度
     * @return              返回新的图片指针
     */
    GrayImage *rotateImage(float rotationAngle);
    /**
     * @brief resizeImageNoInit 改变图片大小
     * @param width             宽度
     * @param height            高度
     */
    void resizeImageNoInit(quint32 width, quint32 height) override;
    /**
     * @brief resizeImage       改变图片大小，并以1024初始化图片数据
     * @param width             宽度
     * @param height            高度
     */
    void resizeImage(quint32 width, quint32 height) override;
    /**
     * @brief loadedImage       加载图片
     * @param path              路径
     */
    void loadedImage(const QString &path);
    /**
     * @brief saveImage         保存图片
     * @param path              路径
     */
    void saveImage(const QString &path) override;
    void saveImage(const QString& path, Image_Module::ImageFormat imageFormat);
    void saveImage(const QString& path, Image_Module::ImageFormat imageFormat, int compression);
    /**
     * @brief width     图片宽度
     * @return
     */
    quint32 width() override ;
    /**
     * @brief height    图片高度
     * @return
     */
    quint32 height() ;
    /**
     * @brief data  获取图像数据
     * @return      返回数据缓冲区指针
     */
    std::shared_ptr<quint16> data();
    /**
     * @brief Erase 以1024清空图片
     */
    void Erase();
    /**
     * @brief Erase 以指定数据清空图片
     * @param color 数据
     */
    void Erase(quint16 color);
    void InvalidateAllRows();
    /**
     * @brief setData   写入图片缓冲区
     * @param data      待写入数据
     * @param width     缓冲区宽度
     * @param height    缓冲区高度
     */
    void setData(const std::shared_ptr<quint16> &data, quint32 width, quint32 height);
    /**
     * @brief setData   写入图片缓冲区
     * @param data      待写入数据
     */
    void setData(const QVector<QVector<quint16>>&data);
    void setData(ImageBase& image);
    void setStaticData(const std::shared_ptr<quint16> &data, quint32 width, quint32 height, bool staticFlagSetting = true);
    void setTestImage(int val = 0);
    Image_Module::ImageStruct &imageStruct() override;
    inline bool visible()const{return _visible;}
    void setVisible(bool value);
    inline const QMap<QString, QObject> &tags()const{return _tags;}
    inline const QString& path()const { return _path; }
    std::shared_ptr<QObject> Clone();

    static void FillImage(ImageBase *image, quint16 pixVal);
    static void FillImage(ImageBase *image, const QRect &partialRect, quint16 pixVal);
    static void FillImage(const Image_Module::ImageStruct &image, const QRect &partialRect, quint16 pixVal);
private:
    void createValidRowArray();
    void allocateData(quint32 width, quint32 height);
    void validateAllRows(bool valid);
private:
    bool _useStaticData;
    quint32 _dataLength;
    QMap<QString, QObject> _tags;
    QString _path;
};

#endif // GRAYIMAGE_H
