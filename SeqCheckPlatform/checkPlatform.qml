import QtQuick 2.0
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0

Item {
    signal qmlLoad(string qmlName)

    Label {
        id: label
        x: 305
        text: qsTr("测序平台测试软件")
        font.pointSize: 24
        anchors.top: parent.top
        anchors.topMargin: 32
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Grid {
        id: grid
        x: 22
        y: 88
        width: 578
        height: 344
        transformOrigin: Item.Center
        rowSpacing: 20
        columnSpacing: 15
        anchors.verticalCenterOffset: 40
        anchors.horizontalCenterOffset: 0
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        rows: 2
        columns: 3

        Button {
            id: button
            width: grid.width / 3 -10
            height: grid.height / 2 -10
            font.family: "Verdana"
            font.pointSize: 16
            font.strikeout: false
            text: qsTr("运动平台")
            onClicked: {
                qmlLoad("MotionPlatform.qml")
            }
        }
        Button {
            id: button1
            width: grid.width / 3 -10
            height: grid.height / 2 -10
            font.family: "Verdana"
            font.pointSize: 16
            text: qsTr("液路模块")
            onClicked: {
                qmlLoad("LiquidRoadModule.qml")
            }
        }
        Button {
            id: button2
            width: grid.width / 3 -10
            height: grid.height / 2 -10
            font.pointSize: 16
            font.family: "Verdana"
            text: qsTr("成像模块")
            onClicked: {
                qmlLoad("ImageModule.qml")
            }
        }

        Button {
            id: button3
            width: grid.width / 3 -10
            height: grid.height / 2 -10
            font.pointSize: 16
            text: qsTr("FC模块")
            onClicked: {
                qmlLoad("FlowCellModule.qml")
            }
        }

        Button {
            id: button4
            width: grid.width / 3 - 10
            height: grid.height / 2 -10
            font.pointSize: 16
            text: qsTr("传感器模块")
            onClicked: {
                qmlLoad("SensorModule.qml")
            }
        }

        Button {
            id: button5
            width: grid.width / 3 -10
            height: grid.height / 2 -10
            font.pointSize: 16
            text: qsTr("外围设备模块")
            onClicked: {
                qmlLoad("PeripheralEquipment.qml")
            }
        }
    }

}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
