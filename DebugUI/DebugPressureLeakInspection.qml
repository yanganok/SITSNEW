/**
* @projectName   SITS
* @brief         压力泄漏测试
* @author        YangAn
* @date          2020-08-03
* @Email         yangan@AutoBio.com.cn
*/
import QtQuick 2.15
import QtCharts 2.15
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.15 as QtControlHighLevel
import QtQuick.Controls 1.4
import QtGraphicalEffects 1.0
import cn.yangan.statusoperator 1.0
import cn.yangan.pressureinspectionoperator 1.0

Item {
    id:container
    objectName: "bubblemeasureflighttime"
    property var startTest: "开始测试";
    property var autoTest: "自动化测试";
    property var computeMBarPerUl: "计算mbar/ul"
    property var endTest:   "终止测试";
    property var pumpInit:  "泵初始化";
    property var pumpAbsorb: "泵吸"
    property var pumpDispense: "泵推"
    property var btnColor: "gray"
    property var laneNo: 1
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
              text: "压力泄漏测试"
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
                                chart.series(0).clear();
                                operator.autoTest(laneNo, parseInt(txValveA.text), parseInt(txValveD.text), parseInt(txSpeedA.text), parseInt(txVolumnA.text));
                            }
                        }


                        YAButton{
                            width:150
                            height:50
                            lineThickness: 1
                            btnText:computeMBarPerUl
                            radiusChanged: {setRadius(10);}
                            click: function(){
                                //setRadius(5);
                                operator.computeMbarPerUl(laneNo, parseInt(txValveA.text), parseInt(txValveD.text), parseInt(txSpeedA.text), parseInt(txVolumnA.text));
                            }
                        }
                        Row{
                            Text{
                                text:"计算的mbar/ul:"
                            }
                            Text{
                                id:txReachThresholdVolume
                                text:operator.reachThresholdVolume
                            }
                        }
                        Column{
                            width: parent.width
                            QtControlHighLevel.RadioButton{
                                id:rbLanePairA
                                checked: true
                                text: "泵1"
                                onClicked: {
                                    laneNo = 1;
                                }
                            }
                            QtControlHighLevel.RadioButton{
                                id:rbLanePairB
                                checked: false
                                text: "泵2"
                                onClicked: {
                                    laneNo = 2;
                                }
                            }
                            spacing: 10
                        }
                        Rectangle{
                            x:rectangle.border.width
                            width:parent.width - rectangle.border.width * 2
                            height: 150
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
                                        text: qsTr("吸入阀号：")
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
                                            text: "2"
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
                                        id: titleValveD
                                        text: qsTr("排出阀号：")
                                        verticalAlignment: Text.AlignTop
                                        horizontalAlignment: Text.AlignLeft
                                    }
                                    Rectangle{
                                        y:titleValveD.y
                                        border.width: 1
                                        border.color: "black"
                                        width: 120
                                        height: 20
                                        TextInput{
                                            id:txValveD
                                            verticalAlignment: TextInput.AlignVCenter
                                            anchors.horizontalCenter: parent.horizontalCenter
                                            width:parent.width - 5
                                            height: parent.height
                                            validator: RegExpValidator{regExp: /[1-6]/}
                                            text: "3"
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
                                            validator: RegExpValidator{regExp: /\d{1,4}/}
                                            text: "7500"
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
                                            validator: RegExpValidator{regExp: /[0-4]\d{2}|[5][0][0]/}
                                            text: "500"
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
//                Rectangle{
//                    id:contentRect
//                    property var borderThickness: 1
//                    width: parent.width
//                    height: parent.height / 2
//                    border.width: borderThickness
//                    border.color: "#6f6666"
//                    clip: true

//                    TableView
//                    {
//                        id:tbView
//                        width: parent.width - 2 * contentRect.borderThickness
//                        height: (parent.height - 2 * contentRect.borderThickness)
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
//                         model: listModel
//                         headerDelegate: YATableCellItem{
//                             implicitWidth:  200
//                             implicitHeight:  30
//                             text: styleData.value
//                             isHeading: true
//                             isText: false
//                         }
//                         rowDelegate: Rectangle{
//                            height: 30
//                         }
//                         itemDelegate: YATableCellItem{
//                             implicitWidth:  200
//                             implicitHeight:   30
//                             text: {
//                                 var obj = listModel.get(styleData.row);
//                                 if (obj && obj[styleData.role])
//                                     return obj[styleData.role]
//                                 return ""
//                             }
//                             isHeading: false
//                             isText: true
//                         }
////                         Timer {
////                             running: true
////                             repeat: true
////                             interval: 2000
////                             onTriggered: {
//// //                                tableView.forceLayout();
////                                 listModel.append({"title":"hello world", "author":"yangan"})
////                             }
////                         }
//                    }
//                }

                ChartView{
                    id:chart
                    title: "压力泄漏测试曲线"
                    antialiasing: true
                    width: parent.width
//                    height: (parent.height) / 2
                    height: (parent.height - 20)


                    // Define x-axis to be used with the series instead of default one
                    ValueAxis {
                        id: valueAxis
                        min: 0
                        max: 1500
                        tickCount: 16
                        labelFormat: "%.0f"
                    }

                    DateTimeAxis{
                        id: xAxis
                        tickCount: 3
                        min:Date.fromLocaleString(Qt.locale(), operator.startDateTime, "yyyy-MM-dd hh:mm:ss:zzz")
                        max:Date.fromLocaleString(Qt.locale(), operator.endDateTime, "yyyy-MM-dd hh:mm:ss:zzz")
                        format: "yyyy-MM-dd HH:mm:ss:zzz"
                    }
//                    AreaSeries {
//                        name: "Russian"
//                        axisX: valueAxis
                        LineSeries {
                            name: "压差"
                            axisX: xAxis
                            axisY: valueAxis;
//                            XYPoint { x: 2000; y: 1 }
//                            XYPoint { x: 2001; y: 1 }
//                            XYPoint { x: 2002; y: 1 }
//                            XYPoint { x: 2003; y: 1 }
//                            XYPoint { x: 2004; y: 1 }
//                            XYPoint { x: 2005; y: 0 }
//                            XYPoint { x: 2006; y: 1 }
//                            XYPoint { x: 2007; y: 1 }
//                            XYPoint { x: 2008; y: 4 }
//                            XYPoint { x: 2009; y: 3 }
//                            XYPoint { x: 2010; y: 2 }
//                            XYPoint { x: 2011; y: 1 }
                        }
//                    }
                }
                Component.onCompleted: {
                    console.log("completed")
                    xAxis.min = Date.fromLocaleString(Qt.locale(), operator.startDateTime, "yyyy-MM-dd hh:mm:ss:zzz");
                    xAxis.max = Date.fromLocaleString(Qt.locale(), operator.endDateTime, "yyyy-MM-dd hh:mm:ss:zzz");
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
//        txValveA.enabled = txSpeedA.enabled = txVolumnA.enabled = false;
//        txValveD.enabled = txSpeedD.enabled = txVolumnD.enabled = false;
    }
    PressureInspectionOperator{
        id:operator
        onReachThresholdVolumeChanged: {
            txReachThresholdVolume.text = reachThresholdVolume;
        }
        onDateTimeAxisLimitChanged: {
            xAxis.min = Date.fromLocaleString(Qt.locale(), operator.startDateTime, "yyyy-MM-dd hh:mm:ss:zzz");
            xAxis.max = Date.fromLocaleString(Qt.locale(), operator.endDateTime, "yyyy-MM-dd hh:mm:ss:zzz");
        }
        onSerieValueChanged: {
            chart.series(0).append(Date.fromLocaleString(Qt.locale(), date, "yyyy-MM-dd hh:mm:ss:zzz"), value);
        }
        onStatusChanged:{
            txStatus.text = status;
        }
    }
    ListModel{
        id:listModel
    }
}



/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
