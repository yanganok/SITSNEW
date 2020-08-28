import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.0

import cn.yangan.statusoperator 1.0

Window {
    objectName: "window"
    visible: true
    visibility: "Maximized"
//    width: 640
//    height: 480
    title: qsTr("检测软件")



    Loader{
        id:loader
        anchors.fill: parent;
//        source:"BubbleMeasureFlightTimeInterface.qml"
       source: "DebugUI/DebugPressureLeakInspection.qml"
//        source: "DebugUI/RadioButtonTest.qml"
        Component.onCompleted: {
            StatusOperator.createInstance();
        }
    }
}
