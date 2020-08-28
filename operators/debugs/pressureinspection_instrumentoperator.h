#ifndef PRESSUREINSPECTION_INSTRUMENTOPERATOR_H
#define PRESSUREINSPECTION_INSTRUMENTOPERATOR_H

/**
* @projectName   SITS
* @brief         压力泄漏检测
* @author        YangAn
* @date          2020-08-18
* @Email         yangan@AutoBio.com.cn
*/
#include <QObject>
#include <QQmlEngine>
#include <QRunnable>
#include <memory>
#include <QMutex>
#include <QWaitCondition>
#include <QDateTime>
#include <functional>
#include <QTimer>
#include "globals/enums.h"
#include "globals/globalSet.h"
#include "instrumentoperator.h"
using namespace GlobalPath;
class PressureInspection_InstrumentOperator : public InstrumentOperator
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(InspectionResult inspectionResut READ inspectionResut)
    Q_PROPERTY(double reachThresholdVolume READ reachThresholdVolume)
    Q_PROPERTY(QString startDateTime READ startDateTime WRITE setStartDateTime)
    Q_PROPERTY(QString endDateTime READ endDateTime WRITE setEndDateTime)
public:
    PressureInspection_InstrumentOperator();
    double func2(double el);


    Q_INVOKABLE QString lineSerieTimeAt(int index);
    Q_INVOKABLE int lineSerieIndexAt(int index);
    Q_INVOKABLE double lineSerieValueAt(int index);
    Q_INVOKABLE int lineSerieSize();

public:
    enum InspectionResult{
      SUCCESS,
      FAILED,
      ERROR
    };
    Q_ENUM(InspectionResult)
    enum class StepType
    {
        NONE,
        INIT,
        COMPUTEPRESUREPERUL,
        PREPRESSURE,
        PRESSUREINSPECTION
    };
    /**
     * @brief The PressureSampleInfo class 压力检测信息
     */
    class PressureSampleInfo{
    public:
        PressureSampleInfo();
        PressureSampleInfo(const QDateTime& sampleDateTime, double samplePressure);
    public:
        inline QDateTime sampleDateTime()const{return _sampleDateTime;}
        inline double samplePressure()const{return _samplePressure;}
    private:
        QDateTime _sampleDateTime;
        double _samplePressure;
    };
    class SerieLinePairs{
    public:
        SerieLinePairs(const QDateTime &dateTime, double psi, int index);
    public:
        inline QString dateTime()const{return  _dateTime.toString("yyyy-MM-dd HH:mm:ss");}
        inline double mbar()const{return _mbar;}
        inline int index()const{return _index;}
    private:
        QDateTime _dateTime;
        double _mbar;
        int _index;
    };
signals:
    void reachThresholdVolumeChanged();
    void statusChanged(QString status);
    void dateTimeAxisLimitChanged();
    void serieValueChanged(QString date, double value);
public slots:
    /**
    * @brief autoTest 自动化测试 暴露给qml
    */
    void autoTest(int lanePair, int valveAbsorbId, int valveDispenseId, int speed, int volume);
    void computeMbarPerUl(int lanePair, int valveAbsorbId, int valveDispenseId, int speed, int volume);
protected:
    /**
     * @brief generateCommandList 产生命令序列
     * @return 命令条数
     */
    virtual int generateCommandList() override;
    /**
     * @brief insertCommandList 将测试模块命令序列插入到通讯核心命令序列
     */
    virtual void insertCommandList() override;
public slots:
    /**
    * @brief getResponse 槽函数：接收从Command返回的应答信息,应在子类中继承
    * @param response 应答信息必须注册为Qt元数据
    */
    virtual void getResponse(std::shared_ptr<Response> response) override;
public:
    virtual void getStatus(std::shared_ptr<Response> response) override;
    /**
     * @brief inspectionResut 检测结果
     * @return
     */
    inline InspectionResult inspectionResut()const{return _inspectionResult;}
    /**
     * @brief decayRatePsiPerSecond 每秒衰减率
     * @return
     */
    inline double decayRatePsiPerSecond()const{return _decayRatePsiPerSecond;}
    /**
     * @brief reachThresholdVolume 达到预加压阈值所需要的体积
     * @return
     */
    inline double reachThresholdVolume()const{return _mbarPerul;}
    inline QString startDateTime()const{return _startDateTime;}
    inline void setStartDateTime(QString value){_startDateTime = value;}
    inline QString endDateTime()const{return _endDateTime;}
    inline void setEndDateTime(QString value){_endDateTime = value;}
    /**
     * @brief writeResultToCsv 产生结果csv
     */
    void writeResultToCsv();
    /**
     * @brief writeResultToCsv 追加信息
     * @param info
     */
    void writeResultToCsv(const QString &info);
private:
    /**
     * @brief computePressurePerUl  计算psi每ul
     * @param deviceId              泵序号
     * @param speed                 速度
     * @param volume                体积
     * @param absorbValve           吸入的阀
     * @param dispenseValve         排出的阀
     */
    void computePressurePerUl(CommunicateCoreUnderlying::SyringPumpId deviceId, int speed, int volume, int absorbValve, int dispenseValve);
    /**
     * @brief prePressure 根据_reachThresholdVolume预加压
     */
    void prePressure(bool needInit = false);
    /**
     * @brief samplePsiList 保压后采样psi到列表中
     */
    void samplePsiList(bool isDelay = true);
    /**
     * @brief computeDurationFromStartSecond 计算采样信息列表中某元素到开始时间的时间段
     * @param index 采样信息列表某元素
     */
    qint64 computeSampleDurationFromStartSecond(PressureSampleInfo &sampleInfo);
    /**
     * @brief computeLeakRate 计算每秒泄漏率,判断是否测试成功
     */
    void computeLeakRate();
    void initPump();
    double computeTestParrela(double el);
    inline int attemptIndex()const{return _attemptIndex;}
private:
    void initDateTimeAxis();
private:
    const int _delayMs = 500;
    const int _pressureTolerance = 1 * 1000 / 14.5;
//    const int _pressureTolerance = 20;
    const double _leakRateUncertainty = 0.345;
//    const int _leakLimitRate = 0.02;
    const double _leakLimitRate = 1.379;
//    const int pressureMaintainingThreshold = 18;
    const int pressureMaintainingThreshold = 1300;
    const int pressureMaintainingInspectionCycleLimit = 15;
    const int _attemptCount = 1;
    const int _stabilizationMs = 5000;
    const int _measurementDurationMs = 30000;

private:
    int _pressureStandards;
    int _curPos;
    int _computeVolume;
    double _psiPerul;
    double _mbarPerul;
    int _speed;
    int _reachThresholdVolume;
    CommunicateCoreUnderlying::SyringPumpId _deviceId;
    int _absorbValve;
    int _dispenseValve;
private:
    int _prePressureVolume;
    QList<int> _cpResults;
    bool _isNegative;

    int _attemptIndex;
    int _pressureSampleIndex;
    int _elpasedTime;
    QList<PressureSampleInfo> _pressureSampleInfos;
    QList<PressureSampleInfo> _prepressureSampleInfos;

    double _decayRatePsiPerSecond;

    StepType _curStep;
    bool _isTestReachVolume;

    QMutex _waitmtx;
    QWaitCondition _waitEvent;
    int _prepressurePsiCount;
    QList<double> _prepressureMbars;
    int _prepressureinspectionCycle;
    InspectionResult _inspectionResult;
    bool _belowLeakRate;


private:
    QList<SerieLinePairs> _serieLinePairs;
    QString _info;
    QString _fileName;
    QString _startDateTime;
    QString _endDateTime;
};

#endif // PRESSUREINSPECTION_INSTRUMENTOPERATOR_H
