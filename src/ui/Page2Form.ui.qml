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

    Component.onCompleted: {

        //mainWindow.showFullScreen()


        /* 测试代码
        globals.activeVehicle.forceArm();
        console.info(globals.activeVehicle.id)
        console.info(globals.activeVehicle.supplyVoltageFact.valueString)
        console.log('ScreenTools: Screen.width: ' + Screen.width + ' Screen.height: ' + Screen.height + ' Screen.pixelDensity: ' + Screen.pixelDensity)
        console.info(globals._appFontPointSize.value)*/
    }

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

        HMISwitch {
            id: element5
            x: 440
            y: 140
            checked: globals._fact ? globals._fact.value : false
            onClicked: globals._fact.value = checked ? 1 : 0
        }

        HMISwitch {
            id: element
            x: 440
            y: 189
        }

        HMISwitch {
            id: element1
            x: 440
            y: 241
        }

        HMISwitch {
            id: element2
            x: 440
            y: 293
        }

        HMISwitch {
            id: element3
            x: 440
            y: 347
        }

        HMISwitch {
            id: element4
            x: 440
            y: 399
        }
    }
}
