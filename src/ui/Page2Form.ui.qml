import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Window 2.12

import HMI 1.0
import HMI.Controls 1.0
import HMI.FactSystem 1.0

Page {
    id: page
    width: 800
    height: 600

    title: qsTr("Page 2")

    //-------------------------------------------------------------------------
    //-- Global Scope Variables
    QtObject {
        id: globals

        readonly property var activeVehicle: HMI.vehicleManager.activeVehicle
        property Fact _fact: activeVehicle.supplyVoltageFact
        property Fact fact1: activeVehicle.rotatingSpeedFact
        property Fact _appFontPointSize: HMI.settingsManager.appSettings.appFontPointSize
        property var se1: HMI.vehicleManager.id
    }
    Image {
        id: image
        x: 0
        y: 0
        fillMode: Image.PreserveAspectFit
        source: "qrc:/qmlimages/zcwjj3/page2.jpg"

        Switch {
            id: element5
            x: 463
            y: 143
            height: 30
            width: 50
            checked: globals._fact ? globals._fact.value : false
            onClicked: globals._fact.value = checked ? 1 : 0
        }

        Switch {
            id: element
            x: 450
            y: 190
        }

        Switch {
            id: element1
            x: 450
            y: 244
        }

        Switch {
            id: element2
            x: 451
            y: 294
        }

        Switch {
            id: element3
            x: 451
            y: 347
        }

        Switch {
            id: element4
            x: 451
            y: 401
            topPadding: 6
        }
    }
}
