import QtQuick 2.12
import QtQuick.Controls 2.5
//import HMI.FactSystem 1.0
import HMI.FactControls 1.0

Page {
    width: 800
    height: 600
    enabled: true

    title: qsTr("Page 4")

    Image {
        id: image
        x: 0
        y: 0
        fillMode: Image.PreserveAspectFit
        source: "qrc:/qmlimages/zcwjj3/page4.jpg"

        FactTextField {
            id: textEdit
            fact: globals.fact
            x: 222
            y: 162
            width: 118
            height: 21
            font.pixelSize: 12
        }

        Switch {
            id: readControl
            x: 654
            y: 62
            text: qsTr("读")
            onClicked: globals.activeVehicle.sendReadControl(checked)
        }

        Switch {
            id: writeControl
            x: 559
            y: 62
            text: qsTr("写")
            onClicked: globals.activeVehicle.sendWriteControl(checked)
        }
    }
}
