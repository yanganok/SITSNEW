import QtQuick 2.0
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.0
import cn.yangan.bubblemeasureflighttimeoperator 1.0
import cn.yangan.pressureinspectionoperator 1.0
import cn.yangan.statusoperator 1.0

Item {
    id:container
    objectName: "bubblemeasureflighttime"
    property var startTest: "开始测试";
    property var endTest:   "终止测试";
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
              text: "气泡飞行时间测试"
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
                        Rectangle{
                            width: 150
                            height: 40
                            anchors.horizontalCenter: parent.horizontalCenter
                            radius: 30
                            border.width: 2
                            border.color: "gray"
                            clip: true;
                            gradient:  Gradient{
                                GradientStop{position: 0; color:"Gray"}
                                GradientStop{position: 1; color:"white"}
                            }
//                            LinearGradient{

//                                              anchors.fill: parent
//                                              start: Qt.point(0, 0)
//                                              end:Qt.point(parent.width, parent.height)
//                                              gradient: Gradient{
//                                                  GradientStop{position: 0; color:"red"}
//                                                  GradientStop{position: 1; color:"white"}
//                                              }
//                                          }
                            Switch{
                                id:switchBtn
                                width: parent.width
                                height: parent.height
                                text: container.startTest
                                checked: false

                                onClicked:  {
                                    if(switchBtn.checked)
                                    {
                                        switchBtn.text = container.endTest

                                        if(ckLaneA.checked && !ckLaneB.checked && !ckWaste1.checked && !ckWaste2.checked)
                                        {
                                            operator.getSensorType(1);
                                        }
                                        else if(ckLaneB.checked && !ckLaneA.checked && !ckWaste1.checked && !ckWaste2.checked)
                                        {
                                            operator.getSensorType(2);
                                        }
                                        else if(ckLaneA.checked && ckLaneB.checked && !ckWaste1.checked && !ckWaste2.checked)
                                        {
                                            operator.getSensorType(3);
                                        }
                                        else if(ckWaste1.checked && !ckLaneA.checked && !ckLaneB.checked && !ckWaste2.checked)
                                        {
                                            operator.getSensorType(4);
                                        }
                                        else if(ckWaste1.checked && ckLaneA.checked && !ckWaste2.checked && !ckLaneB.checked)
                                        {
                                            operator.getSensorType(5);
                                        }
                                        else if(ckWaste1.checked && ckLaneB.checked && !ckWaste2.checked && !ckLaneA.checked)
                                        {
                                            operator.getSensorType(6);
                                        }
                                        else if(ckWaste1.checked && ckLaneA.checked && ckLaneB.checked && !ckWaste2.checked)
                                        {
                                            operator.getSensorType(7);
                                        }
                                        else if(ckWaste2.checked && !ckLaneA.checked && !ckLaneB.checked && !ckWaste1.checked)
                                        {
                                            operator.getSensorType(8);
                                        }
                                        else if(ckLaneA.checked && ckWaste2.checked && !ckLaneB.checked && !ckWaste1.checked)
                                        {
                                            operator.getSensorType(9);
                                        }
                                        else if(ckLaneB.checked && ckWaste2.checked && !ckLaneA.checked && !ckWaste1.checked)
                                        {
                                            operator.getSensorType(10);
                                        }
                                        else if(ckLaneA.checked && ckLaneB.checked && ckWaste2.checked && !ckWaste1.checked)
                                        {
                                            operator.getSensorType(11);
                                        }
                                        else if(ckWaste2.checked && ckWaste2.checked && !ckLaneA.checked && !ckLaneB.checked)
                                        {
                                            operator.getSensorType(12);
                                        }
                                        else if(ckLaneA.checked && ckWaste2.checked && ckWaste2.checked && !ckLaneB.checked)
                                        {
                                            operator.getSensorType(13);
                                        }
                                        else if(ckLaneB.checked && ckWaste2.checked && ckWaste2.checked && !ckLaneA.checked)
                                        {
                                            operator.getSensorType(14);
                                        }
                                        else if(ckLaneA.checked && ckLaneB.checked && ckWaste2.checked && ckWaste2.checked)
                                        {
                                            operator.getSensorType(15);
                                        }
                                        operator.startTest();
                                        ckLaneA.enabled = ckLaneB.enabled = ckWaste1.enabled = ckWaste2.enabled = false;
                                    }
                                    else
                                    {
                                        switchBtn.text = container.startTest
                                        operator.endTest();
                                        ckLaneA.enabled = ckLaneB.enabled = ckWaste1.enabled = ckWaste2.enabled = true;
                                    }
                                }
                            }

                        }
//                        Button{
//                            width: 150
//                            height: 40
//                            anchors.horizontalCenter: parent.horizontalCenter
//                            text:"保存结果"

//                            onClicked: operator.writeResultToCsv()
//                        }

                        RadioButton{
                            id:rbLane
                            checked: true
                            text: "Lane"
                            onClicked:
                            {
                                ckLaneA.checked = ckLaneB.checked = true;
                                ckLaneA.enabled = ckLaneB.enabled = true;
                                ckWaste1.enabled = ckWaste2.enabled = false;
                                ckWaste1.checked = ckWaste2.checked = false;
                            }
                        }
                        Rectangle
                        {
                            width: parent.width
                            height: 100
                            radius: 5
                            border.width: 1
                            border.color: "gray"
                            Column
                            {
                                width:parent.width
                                height: parent.height
                                CheckBox{
                                    id:ckLaneA
                                    checked: true
                                    text:"LANEA"
                                    //onClicked:  operator.getSensorType(1);
                                }
                                CheckBox{
                                    id:ckLaneB
                                    checked: true
                                    text:"LANEB"
                                    //onClicked:  operator.getSensorType(1);
                                }
                            }
                        }
                        RadioButton{
                            id:rbWaste
                            text: "Waste"
                            onClicked:
                            {
                                ckWaste1.checked = ckWaste2.checked = true;
                                ckWaste1.enabled = ckWaste2.enabled = true;
                                ckLaneA.enabled = ckLaneB.enabled = false;
                                ckLaneA.checked = ckLaneB.checked = false;
                            }
                        }
                        Rectangle
                        {
                            width: parent.width
                            height: 100
                            radius: 5
                            border.width: 1
                            border.color: "gray"
                            Column
                            {
                                CheckBox{
                                    id:ckWaste1
                                    checked: false
                                    text:"WASTE1"
                                    //onClicked:  operator.getSensorType(1);
                                }
                                CheckBox{
                                    id:ckWaste2
                                    checked: false
                                    text:"WASTE2"
                                    //onClicked:  operator.getSensorType(1);
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
                    width: parent.width
                    height: parent.height
                    border.width: 1
                    border.color: "#6f6666"
                    clip: true



                    TextEdit {
                                  id: infoEdt
                                  font.pointSize: 14
                                  height: contentHeight
                                  width: parent.width - vbar.width
                                  y: -vbar.position * infoEdt.height
                                  wrapMode: TextEdit.Wrap

                                  selectByMouse: true

                                  MouseArea{
                                      anchors.fill: parent
                                      onWheel: {
                                          if(infoEdt.contentHeight > debugContainer.height - infoEdt.height)
                                          {
                                              if (wheel.angleDelta.y > 0) {
                                                  vbar.decrease();
                                              }
                                              else {
                                                  vbar.increase();
                                              }
                                          }
                                      }
                                      onClicked: {
                                          textEdit.forceActiveFocus();
                                      }
                                  }
                              }

                      ScrollBar {
                          id: vbar
                          hoverEnabled: true
                          active: hovered || pressed
                          orientation: Qt.Vertical
                          size: parent.height / infoEdt.height
                          width: 20
                          anchors.top: parent.top
                          anchors.right: parent.right
                          anchors.bottom: parent.bottom
                      }
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
//      }
      visible: false; // should not be visible on screen.
      layer.enabled: true;
      layer.smooth: true
    }

    BubbleMeasureFlightTimeOperator{
        id:operator
        onRefreshInfoPosted:infoEdt.text = info;
        onStatusChanged:txStatus.text = status;
    }

    PressureInspectionOperator{
        id:operator1
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
