import QtQuick 2.0
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.0

Item {
    id:cp1
    Loader{
        anchors.leftMargin: 24
        anchors.topMargin: 34
        anchors.rightMargin: 396
        anchors.bottomMargin: 365
        anchors.fill: parent;
        sourceComponent: cp
    }
    Component{
        id:cp
        Rectangle{
            anchors.fill: parent
            color: "red"
        MouseArea{
            anchors.fill: parent
            onPressed: {

            }
        }
        }
    }

    Loader {
        anchors.bottomMargin: 238
        anchors.topMargin: 161
        anchors.rightMargin: 255
        anchors.leftMargin: 165
        anchors.fill: parent
        sourceComponent: cp
    }
}


/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
