import QtQuick 2.12
import QtQuick.Controls 2.5

import HMI 1.0
import HMI.ScreenTools 1.0
import HMI.Controls 1.0
import HMI.FactSystem 1.0
import HMI.FactControls 1.0

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
            y: 47
            width: 120
            height: 51
            color: "#1c75ce"
            text: qsTr("主参数")
            font.pointSize: ScreenTools.largeFontPointSize
        }

        Switch {
            id: element
            x: 673
            y: 552
            text: qsTr("Switch")
        }

        FactTextField {
            id: textEdit
            fact: HMI.settingsManager.appSettings.appFontPointSize
            x: 222
            y: 162
            width: 118
            height: 21
            font.pixelSize: 12
        }
    }
}
