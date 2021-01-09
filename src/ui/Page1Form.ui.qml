import QtQuick 2.12
import QtQuick.Controls 2.5
import HMI.ScreenTools 1.0

Page {
    width: 800
    height: 600

    title: qsTr("Page 1")

    Image {
        id: image
        x: 0
        y: 0
        width: 800
        height: 600
        fillMode: Image.PreserveAspectFit
        source: "qrc:/qmlimages/zcwjj3/page1.png"

        Label {
            id: label
            x: 340
            y: 17
            width: 120
            height: 51
            color: "#1c75ce"
            text: qsTr("主参数")
            font.pointSize: ScreenTools.defaultFontPointSize
        }

        Switch {
            id: element
            x: 673
            y: 552
            text: qsTr("Switch")
        }
    }
}
