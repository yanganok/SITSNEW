import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0

Window {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Loader{
        id:loader
        anchors.fill: parent
        source: "CheckPlatform.qml"
    }

    Connections{
        target: loader.item
        onQmlLoad:{
            console.log(qmlName);
            loader.source= qmlName;
        }
    }

}


/*##^##
Designer {
    D{i:1;anchors_y:32}D{i:2;anchors_height:364;anchors_width:596;anchors_x:21;anchors_y:88}
}
##^##*/
