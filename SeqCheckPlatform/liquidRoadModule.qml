import QtQuick 2.0
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0

Item {
    signal qmlLoad(string qmlName)
    Label {
        id: label
        x: 305
        text: "液路模块"
        font.pointSize: 24
        anchors.top: parent.top
        anchors.topMargin: 32
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Grid {
        id: grid
        x: 20
        y: 90
        width: 599
        height: 341
        anchors.horizontalCenter: parent.horizontalCenter
        rows: 2
        columns: 3
        spacing: 15

        Button {
            id: button
            text: qsTr("泵阀响应")
            width: grid.width / 3 -10
            height: grid.height / 2 -10
            font.family: "Verdana"
            font.pointSize: 16
            font.strikeout: false
        }

        Button {
            id: button1
            text: qsTr("空气检测")
            width: grid.width / 3 -10
            height: grid.height / 2 -10
            font.pointSize: 16
            font.strikeout: false
        }

        Button {
            id: button3
            text: qsTr("流速检测")
            width: grid.width / 3 -10
            height: grid.height / 2 -10
            font.family: "Verdana"
            font.pointSize: 16
            font.strikeout: false
        }

        Button {
            id: button4
            text: qsTr("压力检测")
            width: grid.width / 3 -10
            height: grid.height / 2 -10
            font.family: "Verdana"
            font.pointSize: 16
            font.strikeout: false
        }

        Button {
            id: button5
            text: qsTr("阻抗检测")
            width: grid.width / 3 -10
            height: grid.height / 2 -10
            font.family: "Verdana"
            font.pointSize: 16
            font.strikeout: false
        }

        Button {
            id: button6
            text: qsTr("重量检测")
            width: grid.width / 3 -10
            height: grid.height / 2 -10
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
            onClicked:  qmlLoad("CheckPlatform.qml")
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
