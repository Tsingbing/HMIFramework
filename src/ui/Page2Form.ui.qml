import QtQuick 2.12
import QtQuick.Controls 2.5

Page {
    width: 800
    height: 600

    title: qsTr("Page 2")

    Image {
        id: image
        x: 0
        y: 0
        fillMode: Image.PreserveAspectFit
        source: "qrc:/qmlimages/zcwjj3/page2.png"

        Label {
            x: 305
            y: 32
            width: 205
            height: 27
            color: "#106ac4"
            text: qsTr("You are on Page 2.")
            font.pointSize: 18
        }
    }
}
