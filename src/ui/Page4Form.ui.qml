import QtQuick 2.12
import QtQuick.Controls 2.5

Page {
    width: 800
    height: 600

    title: qsTr("Page 4")

    Image {
        id: image
        x: 0
        y: 0
        fillMode: Image.PreserveAspectFit
        source: "qrc:/qmlimages/zcwjj3/page4.png"

        Label {
            x: 271
            y: 41
            width: 241
            color: "#1477da"
            text: qsTr("You are on Page4.")
            styleColor: "#11a1e1"
            font.pointSize: 21
        }
    }
}
