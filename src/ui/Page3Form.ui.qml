import QtQuick 2.12
import QtQuick.Controls 2.5

Page {
    width: 800
    height: 600

    title: qsTr("Page 3")

    Image {
        id: image
        x: 0
        y: 0
        width: 800
        height: 600
        fillMode: Image.PreserveAspectFit
        source: "qrc:/qmlimages/zcwjj3/page3.png"

        Label {
            x: 303
            y: 30
            color: "#1177dd"
            text: qsTr("You are on Page3.")
            font.pointSize: 18
        }
    }
}