import QtQuick 2.0
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0

Item {
    signal qmlLoad(string qmlName)

    Label {
        id: label
        x: 305
        text: "外围设备模块"
        font.pointSize: 24
        anchors.top: parent.top
        anchors.topMargin: 32
        anchors.horizontalCenter: parent.horizontalCenter
    }
    Column {
        id: column
        x: 124
        y: 96
        width: 546
        height: 367
        Button {
            id: button
            text: qsTr("风扇")
            anchors.horizontalCenter: parent.horizontalCenter
            width: column.width / 3 -10
            height: column.height / 3 -10
            font.family: "Verdana"
            font.pointSize: 16
            font.strikeout: false
        }
        Item {
            id: placeholder
            width: column.width / 3 -10
            height: column.height / 3 -10
        }
        Button {
            id: button1
            text: qsTr("RFID")
            anchors.horizontalCenter: parent.horizontalCenter
            width: column.width / 3 -10
            height: column.height / 3 -10
            font.family: "Verdana"
            font.pointSize: 16
            font.strikeout: false
        }
    }

    Row {
        id: row
        x: 47
        y: 424
        width: 546
        height: 48
        spacing: 20
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        Button {
            text: qsTr("主页")
            anchors.verticalCenter: parent.verticalCenter
            onClicked: qmlLoad("CheckPlatform.qml")
        }
    }
}