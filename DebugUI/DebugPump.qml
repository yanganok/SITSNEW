/**
* @projectName   SITS
* @brief         泵的测试
* @author        YangAn
* @date          2020-08-03
* @Email         yangan@AutoBio.com.cn
*/
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls 1.4
import QtGraphicalEffects 1.0
import cn.yangan.statusoperator 1.0
import cn.yangan.pumptestoperator 1.0
import cn.yangan.pumptestmodel 1.0

Item {
    id:container
    objectName: "bubblemeasureflighttime"
    property var startTest: "开始测试";
    property var autoTest: "自动化测试";
    property var endTest:   "终止测试";
    property var pumpInit:  "泵初始化";
    property var pumpAbsorb: "泵吸"
    property var pumpDispense: "泵推"
    property var btnColor: "gray"
    LinearGradient{
        anchors.fill: parent
        start: Qt.point(0, 0)
        end:Qt.point(parent.width, parent.height)
        gradient: Gradient{
            GradientStop{ position:0; color:"silver"}
            GradientStop{ position:1; color:"white"}
        }
    }
    Column{
        anchors.fill: parent
        Text {
              id: header
              font.pixelSize: 32
              text: "泵的测试"
              width:parent.width
              height: 40;
              horizontalAlignment: Text.AlignHCenter
              verticalAlignment: Text.AlignVCenter
              layer.enabled: true
              // This item should be used as the 'mask'
              layer.samplerName: "maskSource"
              layer.effect: ShaderEffect {
                  property var colorSource: gradientRect;
                  fragmentShader: "
                            uniform lowp sampler2D colorSource;
                            uniform lowp sampler2D maskSource;
                            uniform lowp float qt_Opacity;
                            varying highp vec2 qt_TexCoord0;
                            void main() {
                                gl_FragColor =
                                    texture2D(colorSource, qt_TexCoord0)
                                    * texture2D(maskSource, qt_TexCoord0).a
                                    * qt_Opacity;
                            }
                        "
              }
              Component.onCompleted: {StatusOperator.createInstance();}
          }
        Row{
            width: parent.width
            height: parent.height - header.height - tailer.height
            Column{
                id:tools
                width: 200
                height: parent.height
                Rectangle{
                    id: rectangle
                    width: parent.width
                    height: parent.height
                    border.width: 1
                    border.color: "#6f6666"
                    Column{
                        anchors.verticalCenter: parent.verticalCenter
                        width: parent.width
                        height: parent.height - 40
                        spacing: 20

                        YAButton{
                            width:150
                            height:50
                            lineThickness: 1
                            btnText:autoTest
                            radiusChanged: {setRadius(10);}
                            click: function(){
                                operator.autoTest(parseInt(txValveA.text), parseInt(txSpeedA.text), parseInt(txVolumnA.text));
                                //setRadius(5);
//                                if(rbInit.checked)
//                                {
//                                    operator.startTest(PumpTestOperator.INIT);
//                                    console.log(pumpInit)
//                                }
//                                else if(rbAbsorb.checked)
//                                {
//                                    operator.startTest(PumpTestOperator.ABSORB, parseInt(txValveA.text), parseInt(txSpeedA.text), parseInt(txVolumnA.text));
//                                    console.log(pumpAbsorb)
//                                }
//                                else if(rbDispense.checked)
//                                {
//                                    operator.startTest(PumpTestOperator.DISPENSE, parseInt(txValveD.text), parseInt(txSpeedD.text), parseInt(txVolumnD.text));
//                                    console.log(pumpDispense)
//                                }
                            }
                        }


                        YAButton{
                            width:150
                            height:50
                            lineThickness: 1
                            btnText:startTest
                            radiusChanged: {setRadius(10);}
                            click: function(){
                                //setRadius(5);
                                if(rbInit.checked)
                                {
                                    operator.startTest(PumpTestOperator.INIT);
                                    console.log(pumpInit)
                                }
                                else if(rbAbsorb.checked)
                                {
                                    operator.startTest(PumpTestOperator.ABSORB, parseInt(txValveA.text), parseInt(txSpeedA.text), parseInt(txVolumnA.text));
                                    console.log(pumpAbsorb)
                                }
                                else if(rbDispense.checked)
                                {
                                    operator.startTest(PumpTestOperator.DISPENSE, parseInt(txValveD.text), parseInt(txSpeedD.text), parseInt(txVolumnD.text));
                                    console.log(pumpDispense)
                                }
                            }
                        }

                        RadioButton{
                            id:rbInit
                            checked: true
                            text: pumpInit
                            onClicked: {
                                txValveA.enabled = txSpeedA.enabled = txVolumnA.enabled = false;
                                txValveD.enabled = txSpeedD.enabled = txVolumnD.enabled = false;
                            }
                        }
                        RadioButton{
                            id:rbAbsorb
                            text: pumpAbsorb
                            onClicked: {
                                txValveA.enabled = txSpeedA.enabled = txVolumnA.enabled = true;
                                txValveD.enabled = txSpeedD.enabled = txVolumnD.enabled = false;
                            }
                        }
                        Rectangle{
                            x:rectangle.border.width
                            width:parent.width - rectangle.border.width * 2
                            height: 100
                            border.width: 1
                            border.color: "black"
                            Column{
                                Row{
                                    //anchors.leftMargin: 15
                                    width: parent.width - 20
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    height: 30
                                    Text {
                                        anchors.verticalCenter: parent.verticalCenter
                                        id: titleValveA
                                        text: qsTr("阀号：")
                                        verticalAlignment: Text.AlignTop
                                        horizontalAlignment: Text.AlignLeft
                                    }
                                    Rectangle{
                                        y:titleValveA.y
                                        border.width: 1
                                        border.color: "black"
                                        width: 120
                                        height: 20
                                        TextInput{
                                            id:txValveA
                                            verticalAlignment: TextInput.AlignVCenter
                                            anchors.horizontalCenter: parent.horizontalCenter
                                            width:parent.width - 5
                                            height: parent.height
                                            validator: RegExpValidator{regExp: /[1-6]/}
                                            text: "1"
                                        }
                                    }
                                }
                                Row{
                                    //anchors.leftMargin: 15
                                    width: parent.width - 20
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    height: 30
                                    Text {
                                        anchors.verticalCenter: parent.verticalCenter
                                        id: titleSpeedA
                                        text: qsTr("速度：")
                                        verticalAlignment: Text.AlignTop
                                        horizontalAlignment: Text.AlignLeft
                                    }
                                    Rectangle{
                                        y:titleSpeedA.y
                                        border.width: 1
                                        border.color: "black"
                                        width: 110
                                        height: 20
                                        TextInput{
                                            id:txSpeedA
                                            verticalAlignment: TextInput.AlignVCenter
                                            anchors.horizontalCenter: parent.horizontalCenter
                                            width:parent.width - 5
                                            height: parent.height
                                            validator: RegExpValidator{regExp: /[1-6]/}
                                            text: "1"
                                        }
                                    }
                                    Text{
                                        anchors.verticalCenter: parent.verticalCenter
                                        text:"ul/min"
                                    }
                                }
                                Row{
                                    //anchors.leftMargin: 15
                                    width: parent.width - 20
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    height: 30
                                    Text {
                                        anchors.verticalCenter: parent.verticalCenter
                                        id: titleVolumnA
                                        text: qsTr("体积：")
                                        verticalAlignment: Text.AlignTop
                                        horizontalAlignment: Text.AlignLeft
                                    }
                                    Rectangle{
                                        y:titleSpeedA.y
                                        border.width: 1
                                        border.color: "black"
                                        width: 130
                                        height: 20
                                        TextInput{
                                            id:txVolumnA
                                            verticalAlignment: TextInput.AlignVCenter
                                            anchors.horizontalCenter: parent.horizontalCenter
                                            width:parent.width - 5
                                            height: parent.height
                                            validator: RegExpValidator{regExp: /[1-6]/}
                                            text: "1"
                                        }
                                    }
                                    Text{
                                        anchors.verticalCenter: parent.verticalCenter
                                        text:"ul"
                                    }
                                }
                            }
                        }
                        RadioButton{
                            id:rbDispense
                            text:pumpDispense
                            onClicked: {
                                txValveA.enabled = txSpeedA.enabled = txVolumnA.enabled = false;
                                txValveD.enabled = txSpeedD.enabled = txVolumnD.enabled = enabled;
                            }
                        }
                        Rectangle{
                            x:rectangle.border.width
                            width:parent.width - rectangle.border.width * 2
                            height: 100
                            border.width: 1
                            border.color: "black"
                            Column{
                                Row{
                                    width: parent.width - 20
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    height: 30
                                    Text {
                                        anchors.verticalCenter: parent.verticalCenter
                                        id: titleValveD
                                        text: qsTr("阀号：")
                                        verticalAlignment: Text.AlignTop
                                        horizontalAlignment: Text.AlignLeft
                                    }
                                    Rectangle{
                                        y:titleValveD.y
                                        border.width: 1
                                        border.color: "black"
                                        width: 150
                                        height: 20
                                        TextInput{
                                            id:txValveD
                                            verticalAlignment: TextInput.AlignVCenter
                                            anchors.horizontalCenter: parent.horizontalCenter
                                            width:parent.width - 5
                                            height: parent.height
                                            validator: RegExpValidator{regExp: /[1-6]/}
                                            text: "1"
                                        }
                                    }
                                }
                                Row{
                                    //anchors.leftMargin: 15
                                    width: parent.width - 20
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    height: 30
                                    Text {
                                        anchors.verticalCenter: parent.verticalCenter
                                        id: titleSpeedD
                                        text: qsTr("速度：")
                                        verticalAlignment: Text.AlignTop
                                        horizontalAlignment: Text.AlignLeft
                                    }
                                    Rectangle{
                                        y:titleSpeedD.y
                                        border.width: 1
                                        border.color: "black"
                                        width: 110
                                        height: 20
                                        TextInput{
                                            id:txSpeedD
                                            verticalAlignment: TextInput.AlignVCenter
                                            anchors.horizontalCenter: parent.horizontalCenter
                                            width:parent.width - 5
                                            height: parent.height
                                            validator: RegExpValidator{regExp: /[1-6]/}
                                            text: "1"
                                        }
                                    }
                                    Text{
                                        anchors.verticalCenter: parent.verticalCenter
                                        text:"ul/min"
                                    }
                                }
                                Row{
                                    //anchors.leftMargin: 15
                                    width: parent.width - 20
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    height: 30
                                    Text {
                                        anchors.verticalCenter: parent.verticalCenter
                                        id: titleVolumnD
                                        text: qsTr("体积：")
                                        verticalAlignment: Text.AlignTop
                                        horizontalAlignment: Text.AlignLeft
                                    }
                                    Rectangle{
                                        y:titleSpeedA.y
                                        border.width: 1
                                        border.color: "black"
                                        width: 130
                                        height: 20
                                        TextInput{
                                            id:txVolumnD
                                            verticalAlignment: TextInput.AlignVCenter
                                            anchors.horizontalCenter: parent.horizontalCenter
                                            width:parent.width - 5
                                            height: parent.height
                                            validator: RegExpValidator{regExp: /[1-6]/}
                                            text: "1"
                                        }
                                    }
                                    Text{
                                        anchors.verticalCenter: parent.verticalCenter
                                        text:"ul"
                                    }
                                }
                            }
                        }
                    }
                }
            }
            Column{
                id:debugContainer
                width:parent.width - tools.width
                height: parent.height
                Rectangle{
                    id:contentRect
                    property var borderThickness: 1
                    width: parent.width
                    height: parent.height
                    border.width: borderThickness
                    border.color: "#6f6666"
                    clip: true

                    TableView
                    {
                        id:tbView
                        width: parent.width - 2 * contentRect.borderThickness
                        height: parent.height - 2 * contentRect.borderThickness
                        TableViewColumn {
                             role: "title"
                             title: "Title"
                             width: 100
                         }
                         TableViewColumn {
                             role: "author"
                             title: "Author"
                             width: 200
                         }
                         model: listModel
                         headerDelegate: YATableCellItem{
                             implicitWidth:  200
                             implicitHeight:  30
                             text: styleData.value
                             isHeading: true
                             isText: false
                         }
                         rowDelegate: Rectangle{
                            height: 30
                         }
                         itemDelegate: YATableCellItem{
                             implicitWidth:  200
                             implicitHeight:   30
                             text: {
                                 var obj = listModel.get(styleData.row);
                                 if (obj && obj[styleData.role])
                                     return obj[styleData.role]
                                 return ""
                             }
                             isHeading: false
                             isText: true
                         }
                         Timer {
                             running: true
                             repeat: true
                             interval: 2000
                             onTriggered: {
 //                                tableView.forceLayout();
                                 listModel.append({"title":"hello world", "author":"yangan"})
                             }
                         }
                    }
//                    TableView{
//                        id:tableView
//                        width: parent.width - 2 * contentRect.borderThickness
//                        height: parent.height - 2 * contentRect.borderThickness
//                        TableViewColumn {
//                             role: "title"
//                             title: "Title"
//                             width: 100
//                         }
//                         TableViewColumn {
//                             role: "author"
//                             title: "Author"
//                             width: 200
//                         }
//                        model: listModel
//                        headerDelegate: YATableCellItem{
//                            implicitWidth:  200
//                            implicitHeight:  30
//                            text: styleData.value
//                            isHeading: true
//                            isText: false
//                        }
//                        itemDelegate: YATableCellItem{
//                            implicitWidth:  200
//                            height:  40
//                            text: {
//                                var obj = listModel.get(styleData.row);
//                                if (obj && obj[styleData.role])
//                                    return obj[styleData.role]
//                                return ""
//                            }
//                            isHeading: false
//                            isText: true
//                        }
//                        Timer {
//                            running: true
//                            repeat: true
//                            interval: 2000
//                            onTriggered: {
////                                tableView.forceLayout();
//                                listModel.append({"title":"hello world", "author":"yangan"})
//                            }
//                        }
//                    }
                }
            }
        }
        Row{
            id:tailer;
            width:parent.width
            height: 40;
            Text{
                id:txStatus
            }
        }
    }
    Rectangle {
      id: gradientRect;
      width: parent.width
      height: 40
      gradient:
        Gradient {
                 GradientStop { position: 0; color: "#058241" }
                 GradientStop { position: 0.75; color: "#1f74b6" }
                 GradientStop { position: 1; color: "#1f74b6" }
             }

      visible: false; // should not be visible on screen.
      layer.enabled: true;
      layer.smooth: true
    }
    Component.onCompleted: {
        txValveA.enabled = txSpeedA.enabled = txVolumnA.enabled = false;
        txValveD.enabled = txSpeedD.enabled = txVolumnD.enabled = false;
    }
    PumpTestOperator{
        id:operator
    }
    ListModel{
        id:listModel
//        ListElement{
//            title:"hello world"
//            author:"yangan"
//        }
    }
}



/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
