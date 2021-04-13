import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Window 2.12

import HMI 1.0
import HMI.Controls 1.0
import HMI.FactSystem 1.0
import HMI.FactControls 1.0

Page {
    id: page
    width: 800
    height: 600

    title: qsTr("Page 2")
    property Fact pochaiIsLockFact: HMI.vehicleManager.activeVehicle.engineFactGroup.pochaiIsLockFact
    property Fact wajueIsLockFact: HMI.vehicleManager.activeVehicle.engineFactGroup.wajueIsLockFact
    property bool wajueIsLock: HMI.vehicleManager.activeVehicle.engineFactGroup.wajueIsLockFact.rawValue
    property bool pochaiIsLock: HMI.vehicleManager.activeVehicle.engineFactGroup.pochaiIsLockFact.rawValue
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
    }

    FactLabel {
        id: la
        x: 200
        y: 307
        width: 74
        height: 31
        color: "white"
        //text: HMI.vehicleManager.activeVehicle.engineFactGroup.pochaiIsLockFact.rawValue
        //      === 1 ? qsTr("锁定") : qsTr("未锁定")
        fact: HMI.vehicleManager.activeVehicle.engineFactGroup.pochaiIsLockFact
        //fact: HMI.vehicleManager.activeVehicle.engineFactGroup.yDegreeFact
        text: "未锁定"
        Connections {
            target: pochaiIsLockFact
            onValueChanged: {
                if (HMI.vehicleManager.activeVehicle.engineFactGroup.pochaiIsLockFact.value) {
                    la.text = qsTr("锁定")
                    la.color = "red"
                } else {
                    la.text = qsTr("未锁定")
                    la.color = "white"
                }
            }
        }
    }

    FactLabel {
        id: la1
        x: 200
        y: 360
        width: 74
        height: 31
        color: "white"
        //text: wajueIsLockFact.valueString === "true" ? qsTr("锁定") : qsTr("未锁定")
        //text: wajueIsLockFact.valueString
        text: "未锁定"
        fact: HMI.vehicleManager.activeVehicle.engineFactGroup.wajueIsLockFact
        Connections {
            target: HMI.vehicleManager.activeVehicle.engineFactGroup.wajueIsLockFact
            onValueChanged: {
                if (HMI.vehicleManager.activeVehicle.engineFactGroup.wajueIsLockFact.value) {
                    la1.text = qsTr("锁定")
                    la1.color = "red"
                } else {
                    la1.text = qsTr("未锁定")
                    la1.color = "white"
                }
            }
        }
    }
    Button {
        id: button
        x: 441
        y: 298
        width: 74
        height: 31
        text: qsTr("开")
        onPressed: {
            globals.activeVehicle.sendPoChaiLockSwitch(1)
            //button.text = "1"
        }
        onReleased: {
            globals.activeVehicle.sendPoChaiLockSwitch(0)
            //button.text = "0"
        }
    }

    Button {
        id: button1
        x: 536
        y: 298
        width: 78
        height: 31
        text: qsTr("锁")
        onPressed: {
            globals.activeVehicle.sendPoChaiLockSwitch(2)
        }
        onReleased: {
            globals.activeVehicle.sendPoChaiLockSwitch(0)
        }
    }

    Button {
        id: button2
        x: 441
        y: 351
        width: 74
        height: 31
        text: qsTr("开")
        onPressed: {
            globals.activeVehicle.sendWajueLockSwitch(1)
        }
        onReleased: {
            globals.activeVehicle.sendWajueLockSwitch(0)
        }
    }

    Button {
        id: button3
        x: 538
        y: 351
        width: 74
        height: 31
        text: qsTr("锁")
        onPressed: {
            globals.activeVehicle.sendWajueLockSwitch(2)
        }
        onReleased: {
            globals.activeVehicle.sendWajueLockSwitch(0)
        }
    }

    Button {
        id: button4
        x: 441
        y: 403
        width: 74
        height: 31
        text: qsTr("开")
        onPressed: {
            globals.activeVehicle.sendPoChaiQuickSwitch(1)
        }
        onReleased: {
            globals.activeVehicle.sendPoChaiQuickSwitch(0)
        }
    }

    Button {
        id: button5
        x: 538
        y: 403
        width: 74
        height: 31
        text: qsTr("锁")
        onPressed: {
            globals.activeVehicle.sendPoChaiQuickSwitch(2)
        }
        onReleased: {
            globals.activeVehicle.sendPoChaiQuickSwitch(0)
        }
    }
}
