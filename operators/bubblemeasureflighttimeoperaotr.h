#ifndef BUBBLEMEASUREFLIGHTTIMEOPERAOTR_H
#define BUBBLEMEASUREFLIGHTTIMEOPERAOTR_H
#include <QObject>
#include <QList>
#include <QTimer>
#include <QQmlListProperty>
#include "globals/globalSet.h"
#include "globals/enums.h"
#include "instrumentoperator.h"
#include "models/bubblemeasureflighttimemeasuremodel.h"
/**
* @projectName   SITS
* @brief         气泡飞行时间检测仪器
* @author        YangAn
* @date          2020-07-28
* @Email         yangan@AutoBio.com.cn
*/
using namespace GlobalPath;
class BubbleMeasureFlightTime_InstrumentOperaotr:public InstrumentOperator
{
    Q_OBJECT
//    Q_PROPERTY(BubbleMeasureFlightTimeMeasureModel * result READ result)
//    Q_PROPERTY(QQmlListProperty<BubbleMeasureFlightTimeMeasureModel> results READ results)
    Q_PROPERTY(QString infos READ infos)
    QML_ELEMENT
signals:
    /**
     * @brief refreshInfoPosted 刷新界面信息信号
     * @param info 响应信息
     */
    void refreshInfoPosted(const QString &info);
    /**
     * @brief statusChanged 通讯状态改变信号
     * @param status 通讯状态
     */
    void statusChanged(const QString &status);
public:
    explicit BubbleMeasureFlightTime_InstrumentOperaotr(QObject *parent = nullptr);
public:
    QString infos()const;

protected:
    int generateCommandList() override;
    void insertCommandList() override;
public slots:
    /**
     * @brief startTest 开始测试槽
     */
    void startTest();
    /**
     * @brief endTest 终止测试槽
     */
    void endTest();
    /**
     * @brief getResponse 接收响应信息槽
     * @param response
     */
    void getResponse(std::shared_ptr<Response> response) override;
    /**
     * @brief getSensorType 从对应的int类型识别传感器类型
     * @param id
     */
    void getSensorType(int id);
public:
    /**
     * @brief writeResultToCsv 产生结果csv
     */
    void writeResultToCsv();
    /**
     * @brief writeResultToCsv 追加信息
     * @param info
     */
    void writeResultToCsv(const QString &info);
//    static void appendResult(QQmlListProperty<BubbleMeasureFlightTimeMeasureModel>*, BubbleMeasureFlightTimeMeasureModel *);
//    static int resultCount(QQmlListProperty<BubbleMeasureFlightTimeMeasureModel>*) ;
//    static BubbleMeasureFlightTimeMeasureModel *get(QQmlListProperty<BubbleMeasureFlightTimeMeasureModel>*, int) ;
//    static void clearResults(QQmlListProperty<BubbleMeasureFlightTimeMeasureModel>*);
//    static void replaceResult(QQmlListProperty<BubbleMeasureFlightTimeMeasureModel>*, int, BubbleMeasureFlightTimeMeasureModel *);
//    static void removeLastResult(QQmlListProperty<BubbleMeasureFlightTimeMeasureModel>*);
private:
    QStringList _displayInfos;
    QString _infos;
    CommunicateCoreUnderlying::BubbleDeviceId _deviceId;
//    BubbleMeasureFlightTimeMeasureModel *_result;
//    QList<BubbleMeasureFlightTimeMeasureModel *> _results;
    QTimer _timer;
    QString _fileName;
};

#endif // BUBBLEMEASUREFLIGHTTIMEOPERAOTR_H
