import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0
import Qt.labs.calendar 1.0

Window {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    Label{
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 40
        text: qsTr("液路检测")
        anchors.horizontalCenterOffset: 0
    }

    Grid {
        id: grid
        spacing: window.height / 10
        rows: 2
        columns: 2
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

        RoundButton {
            id: roundButton
            width: window.height / 4
            height: window.height / 4
            text: "气泡检测"
            background:
            Rectangle{
                id:rect
                width:roundButton.width
                height: roundButton.height
                radius: roundButton.width
                LinearGradient{
                    anchors.fill: rect
                    source:rect
                    start: Qt.point(0, 0)
                    end:Qt.point(0, rect.height)
                    gradient: Gradient{
                        GradientStop{position: 0.0; color: "#0ca5fb"}
                        GradientStop{position: 0.5;color:"#2c9bc2"}
                        GradientStop{position: 1;color: "#447699"}
                    }
                }
            }
        }

        RoundButton {
            id: roundButton1
            width: window.height / 4
            height: window.height / 4
            text: "空气检测"
        }

        RoundButton {
            id: roundButton2
            width: window.height / 4
            height: window.height / 4
            text: "阻抗检测"
        }

        RoundButton {
            id: roundButton3
            width: window.height / 4
            height: window.height / 4
            text: "压力检测"
        }
    }

    Component.onCompleted: {
    }
}
