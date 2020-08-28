import QtQuick 2.0
import QtQuick.Controls 2.1
import QtGraphicalEffects 1.0

Item {
    id: element
    signal qmlLoad(string qmlName)
    Label {
        id: label
        x: 305
        text: qsTr("成像模块")
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
        height: 371
        anchors.horizontalCenter: parent.horizontalCenter
        rows: 3
        columns: 3
        spacing: 15

        Button {
            id: button
            text: qsTr("LED测试")
            width: grid.width / 3 -10
            height: grid.height / 3 -10
            font.family: "Verdana"
            font.pointSize: 16
            font.strikeout: false
        }

        Button {
            id: button1
            text: qsTr("Laser测试")
            width: grid.width / 3 -10
            height: grid.height / 3 -10
            font.family: "Verdana"
            font.pointSize: 16
            font.strikeout: false
        }

        Button {
            id: button2
            text: qsTr("图像质量鉴定")
            width: grid.width / 3 -10
            height: grid.height / 3 -10
            font.family: "Verdana"
            font.pointSize: 16
            font.strikeout: false
        }

        Button {
            id: button3
            text: qsTr("LaserZ位置误差检测")
            width: grid.width / 3 -10
            height: grid.height / 3 -10
            font.pointSize: 16
            font.strikeout: false
        }

        Button {
            id: button4
            text: qsTr("自动对焦错误检测")
            width: grid.width / 3 -10
            height: grid.height / 3 -10
            font.family: "Verdana"
            font.pointSize: 16
            font.strikeout: false
        }

        Button {
            id: button5
            text: qsTr("焦矩模型一致性检测")
            width: grid.width / 3 -10
            height: grid.height / 3 -10
            font.family: "Verdana"
            font.pointSize: 16
            font.strikeout: false
        }

        Button {
            id: button6
            text: qsTr("穿透对焦过滤检测")
            width: grid.width / 3 -20
            height: grid.height / 3 -20
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

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
