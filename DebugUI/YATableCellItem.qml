import QtQuick 2.0

Rectangle{
    id:cellItem
    property var isHeading:false
    property var isText:true
    property var isTextInput:false
    property var borderThickness:0
    property var borderColor: "black"
    property var text:""

    property var component:null
    property var sprite:null

    border.width: borderThickness
    border.color: borderColor
    onWidthChanged: {
        if(sprite != null)
        {
            sprite.itemWidth = width - 2 * borderThickness;
//            console.log("width change:" + sprite.itemWidth)
//            console.log("width change:" + sprite.itemHeight)
        }
    }
    onHeightChanged: {
        if(sprite != null)
        {
            sprite.itemHeight = height - 2 * borderThickness;
        }
    }
    Component.onCompleted: {
        if(isHeading)
        {
//            console.log("Is heading " + width);
            if(sprite == null && component == null)
            {
                component = Qt.createComponent("TableHeaderItem.qml");
                if(component.status === Component.Ready)
                {
                    sprite = component.createObject(cellItem, {"x":borderThickness, "y":borderThickness, "title":text, "itemWidth":width - 2 * borderThickness, "itemHeight":height - 2 * borderThickness})
                }
//                if(sprite == null)
//                    console.log("failed create sprite");

            }
            else
            {
                sprite.title = text;
            }
        }
        else
        {
//            console.log("Is not heading");
        }

        if(isText)
        {
//            console.log("Is text");
//            if(sprite != null)
//                sprite.destroy();
//            if(component != null)
//                component.destroy();
            if(sprite == null && component == null)
            {
                component = Qt.createComponent("TableCellTextItem.qml");
                if(component.status === Component.Ready)
                    sprite = component.createObject(cellItem, {"x":borderThickness, "y":borderThickness, "text":text, "itemWidth":width - 2 * borderThickness, "itemHeight":height - 2 * borderThickness})
//                if(sprite == null)
//                    console.log("failed create sprite");
//                console.log(sprite.itemWidth)
//                console.log(height - 2 * borderThickness);
            }
            else
            {
                sprite.text = text;
            }
        }
        else
        {
//            console.log("Is not text")
        }


        if(isTextInput)
        {
//            console.log("Is textinput");
//            if(sprite != null)
//                sprite.destroy();
//            if(component != null)
//                component.destroy();
            if(sprite == null && component == null)
            {
                component = Qt.createComponent("TableCellTextInputItem.qml");
                if(component.status === Component.Ready)
                    sprite = component.createObject(cellItem, {"x":borderThickness + 10, "y":borderThickness, "text":text, "itemWidth":width - 2 * borderThickness, "itemHeight":height - 2 * borderThickness})
//                if(sprite == null)
//                    console.log("failed create sprite");
            }
            else
            {
                sprite.text = text;
            }
        }
        else
        {
//            console.log("Is not textinput");
        }
    }

    onIsHeadingChanged: {
    }
    onIsTextChanged: {
    }
    onIsTextInputChanged: {
    }
}
