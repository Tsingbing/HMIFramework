import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import HMI.Palette 1.0

TabBar {
    property alias myModel: myModel
    property int lastIndex: 0
    HMIPalette { id:hmiPal; colorGroupEnabled: true }
    id: bar
    currentIndex: 0

    Component.onCompleted: {
        console.info(hmiPal.brandingBlue)
    }

    ListModel {
        id: myModel
    }

    Repeater {
        id: repeater
        model: myModel

        TabButton {
            //property alias imageSource: image.source
            property alias textColor: text.color

            height: bar.height *2
            contentItem:Text{
                id: text
                text: modelText
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignBottom
                color: (model.index === bar.currentIndex) ? modelColorG : modelColor
            }
            background: Rectangle
            {
                color : "transparent"	//transparent:透明
            }
            //            background:Image{
            //                id: image
            //                width: 24
            //                height: 24
            //                anchors.horizontalCenter: parent.horizontalCenter
            //                source: (model.index === bar.currentIndex) ? modelSrcG : modelSrc
            //            }
            onHoveredChanged: {
                if (model.index !== bar.currentIndex){
                    hovered ? text.color = modelColorG : text.color = modelColor
                    //hovered ? image.source = modelSrcG : image.source = modelSrc
                }
            }
            onClicked: {
                //repeater.itemAt(bar.lastIndex).imageSource = myModel.get(bar.lastIndex).modelSrc;
                repeater.itemAt(bar.lastIndex).textColor = modelColor;

                //image.source = modelSrcG;
                text.color = modelColorG;
                bar.lastIndex = model.index;
            }
        }
    }
}
