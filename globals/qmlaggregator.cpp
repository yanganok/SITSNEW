#include "qmlaggregator.h"
#include "instrumentoperator.h"
#include "operators/status_instrumentoperator.h"
#include "operators/bubblemeasureflighttimeoperaotr.h"
#include "operators/debugs/pumptest_instrumentoperator.h"
#include "operators/debugs/pressureinspection_instrumentoperator.h"
#include "models/debug/pumptestmodel.h"
void registerOperatorInQml()
{
    qmlRegisterType<InstrumentOperator>();
    qmlRegisterType<PumpTest_InstrumentOperator>("cn.yangan.pumptestoperator", 1, 0, "PumpTestOperator");
    qmlRegisterType<BubbleMeasureFlightTime_InstrumentOperaotr>("cn.yangan.bubblemeasureflighttimeoperator", 1, 0, "BubbleMeasureFlightTimeOperator");
    qmlRegisterType<PressureInspection_InstrumentOperator>("cn.yangan.pressureinspectionoperator", 1, 0, "PressureInspectionOperator");
    qmlRegisterSingletonType<Status_InstrumentOperator>("cn.yangan.statusoperator",1,0, "StatusOperator", [](QQmlEngine *engine, QJSEngine *jsEngine)->QObject *{
        Q_UNUSED(engine)
        Q_UNUSED(jsEngine)
        Status_InstrumentOperator *opera = new Status_InstrumentOperator(nullptr);
        return opera;
    });
    qmlRegisterType<PumpTestModel>("cn.yangan.pumptestmodel", 1, 0, "PumpTestModel");
}
