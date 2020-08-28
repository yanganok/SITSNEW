import QtQuick 2.0

Canvas{
    property var lineThickness : 1
    property var lineColor: "black"
    property var click: function(){}
    property var text:"textInputCell"
    property var color1: "gray"
    property var color2: "silver"
    property var itemWidth: 150
    property var itemHeight: 70
    anchors.horizontalCenter: parent.horizontalCenter
    width:itemWidth
    height:itemHeight
    TextInput{
        text:text
        width: parent.width - lineThickness * 2
        height: parent.height - lineThickness * 2
        x:lineThickness
        y:lineThickness
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }
    onPaint:  {
                var point = function(x, y) {
                    return {x:x, y:y};
                };

                var ctx = getContext("2d");
                function rectWH(x, y, w, h) {
                    return {x:x, y:y, width:w, height:h};
                }

                var rect = rectWH(0, 0, width, height);
                function drawRoundedRect(rect, r, ctx) {
                    ctx.clearRect(rect.x, rect.y, rect.width, rect.height);
                    var ptA = point(rect.x + r, rect.y);
                    var ptB = point(rect.x + rect.width - 2 * r, rect.y);
                    var ptC = point(rect.x + rect.width, rect.y + r);
                    var ptD = point(rect.x + rect.width, rect.y + rect.height - 2 * r);
                    var ptE = point(rect.x + rect.width, rect.y + rect.height);
                    var ptF = point(rect.x + rect.width - 2 * r, rect.y + rect.height);
                    var ptG = point(rect.x + r, rect.y + rect.height);
                    var ptH = point(rect.x, rect.y + rect.height);
                    var ptI = point(rect.x, rect.height - 2 * r)
                    var ptJ = point(rect.x, rect.y + r);
                    var ptK = point(rect.x, rect.y)
                    var ptL = point(rect.x + r, rect.y);

                    ctx.beginPath();
                    ctx.lineWidth = lineThickness;
                    ctx.strokeStyle = lineColor;
                    ctx.moveTo(ptA.x, ptA.y);
                    ctx.lineTo(ptB.x, ptB.y);
                    ctx.arcTo(ptC.x, ptB.y, ptC.x, ptC.y, r);
//                  ctx.lineTo(ptD.x, ptD.y);
//                  ctx.arcTo(ptF.x, ptF.y, ptE.x, ptE.y, r);
                    ctx.arcTo(ptE.x, ptE.y, ptF.x, ptF.y, r);
                    ctx.lineTo(ptG.x, ptG.y);
                    ctx.arcTo(ptH.x, ptH.y, ptI.x, ptI.y, r);
                    ctx.lineTo(ptJ.x, ptJ.y);
                    ctx.arcTo(ptK.x, ptK.y, ptL.x, ptL.y, r);
                    var lg=ctx.createLinearGradient(0,0,0,height);
                    lg.addColorStop(0,  color1);
                    lg.addColorStop(0.5,color2);
                    ctx.fillStyle = lg
                    ctx.fill();
                    ctx.stroke();
                }

                drawRoundedRect(rect, radius, ctx);
    }

    MouseArea{
        anchors.fill: parent
        hoverEnabled: true
        onEntered: {
            color1 = "white"
            parent.requestPaint();
        }
        onExited: {
            color1 = "white"
            parent.requestPaint();
        }
        onClicked: {
            click();
            color1 = "white"
            parent.requestPaint();
        }
    }
}
