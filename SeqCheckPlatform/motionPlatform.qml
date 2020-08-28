import QtQuick 2.0
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0

Item {
    signal qmlLoad(string qmlName)
    Label {
        id: label
        x: 305
        text: "运动平台测试"
        font.pointSize: 24
        anchors.top: parent.top
        anchors.topMargin: 32
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Grid {
        id: grid
        x: 22
        y: 88
        width: 596
        height: 276
        transformOrigin: Item.Center
        spacing: 40
        anchors.verticalCenterOffset: 40
        anchors.horizontalCenterOffset: 0
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        rows: 2
        columns: 2


        Button {
            id: button
            text: qsTr("光学运动平台")
            width: grid.width / 2 -20
            height: grid.height / 2 -20
            font.family: "Verdana"
            font.pointSize: 16
            font.strikeout: false
        }

        Button {
            id: button1
            text: qsTr("FC运动平台")
            width: grid.width / 2 -20
            height: grid.height / 2 -20
            font.family: "Verdana"
            font.pointSize: 16
            font.strikeout: false
        }

        Button {
            id: button2
            text: qsTr("试剂盒运动平台")
            width: grid.width / 2 -20
            height: grid.height / 2 -20
            font.family: "Verdana"
            font.pointSize: 16
            font.strikeout: false
        }

        Button {
            id: button3
            text: qsTr("缓冲液和废液盒运动平台")
            width: grid.width / 2 -20
            height: grid.height / 2 -20
            font.family: "Verdana"
            font.pointSize: 16
            font.strikeout: false
        }
    }

    Row {
        id: row
        x: 22
        y: 424
        width: 596
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

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
