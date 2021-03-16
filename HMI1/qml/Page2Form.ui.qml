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
        source: "qrc:/qmlimages/page2.jpg"

        Switch {
            id: element5
            x: 463
            y: 143
            height: 30
            width: 50
            checked: globals.frontLightFact ? globals.frontLightFact.value : false
            onClicked: globals.activeVehicle.sendFrontLightSwitch(checked)
        }

        Switch {
            id: element
            x: 450
            y: 190
            onClicked: globals.activeVehicle.sendBackLightSwitch(checked)
        }

        Switch {
            id: element1
            x: 450
            y: 244
            onClicked: globals.activeVehicle.sendAlarmSwitch(checked)
        }

        Switch {
            id: element2
            x: 451
            y: 294
            onClicked: globals.activeVehicle.sendPoChaiLockSwitch(checked)
        }

        Switch {
            id: element3
            x: 451
            y: 347
            onClicked: globals.activeVehicle.sendWajueLockSwitch(checked)
        }

        Switch {
            id: element4
            x: 451
            y: 401
            topPadding: 6
            onClicked: globals.activeVehicle.sendPoChaiQuickSwitch(checked)
        }
    }
}
