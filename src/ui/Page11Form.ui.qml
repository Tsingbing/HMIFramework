import QtQuick 2.12
import QtQuick.Controls 2.5

import HMI 1.0
import HMI.Controls 1.0
import HMI.FactSystem 1.0
import HMI.FactControls 1.0
import HMI.ScreenTools 1.0

Page {
    id: page
    width: 800
    height: 600
    visible: true

    title: qsTr("Page 1")
    property var textVar: HMI.vehicleManager.activeVehicle.warningsStrings
    property var textIndex: 0
    Image {
        id: image
        x: 0
        y: 0
        width: 800
        height: 600
        fillMode: Image.PreserveAspectFit
        //source: "toolbar/images/ZCWJJ3/page11.jpg"
        source: "qrc:/qmlimages/zcwjj3/Page11.jpg"
        FactLabel {
            id: label
            x: 67
            y: 147 + 7
            width: 83
            height: 24
            horizontalAlignment: Text.AlignHCenter
            fact: HMI.vehicleManager.activeVehicle.batteryPowerFact
            font.pointSize: 11
        }

        Row {
            id: row
            x: 623
            y: 3
            width: 169
            height: 36

            Switch {
                id: element
                width: 111
                height: 35
                onClicked: {
                    globals.activeVehicle.sendJiesuo(checked)
                    globals.activeVehicle.sendReadControl(1) //发送读参数命令
                    if (checked) {
                        label2.text = "解锁"
                        label2.color = "green"
                    } else {
                        label2.text = "未解锁"
                        label2.color = "red"
                    }
                }
            }

            Label {
                id: label2
                height: 35
                color: "red"
                text: qsTr("未解锁")
                verticalAlignment: Text.AlignTop
                font.pointSize: 16
            }
        }

        FactLabel {
            id: label1
            x: 67
            y: 190 + 7
            width: 83
            height: 24
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 11
            fact: HMI.vehicleManager.activeVehicle.supplyVoltageFact
        }

        FactLabel {
            id: fuelLevel
            x: 67
            y: 231 + 7
            width: 83
            height: 24
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 11
            fact: HMI.vehicleManager.activeVehicle.fuelLevelFact
        }

        FactLabel {
            id: rotatingSpeed
            x: 336
            y: 5
            width: 138
            height: 28
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 19
            fact: HMI.vehicleManager.activeVehicle.engineFactGroup.rotatingSpeedFact
        }

        FactLabel {
            id: waterTemperature
            x: 659
            y: 146 + 7
            width: 74
            height: 24
            font.pointSize: 11
            horizontalAlignment: Text.AlignHCenter
            fact: HMI.vehicleManager.activeVehicle.waterTemperatureFact
        }

        FactLabel {
            id: mainPumpPressure
            x: 363
            y: 421
            width: 74
            height: 24
            horizontalAlignment: Text.AlignHCenter
            fact: HMI.vehicleManager.activeVehicle.mainPumpPressureFact
        }

        FactLabel {
            id: oxygenConcentration
            x: 223
            y: 421
            width: 88
            height: 24
            horizontalAlignment: Text.AlignHCenter
            fact: HMI.vehicleManager.activeVehicle.oxygenConcentrationFact
        }

        FactLabel {
            id: combustibleGasConcentration
            x: 486
            y: 421
            width: 73
            height: 24
            horizontalAlignment: Text.AlignHCenter
            fact: HMI.vehicleManager.activeVehicle.combustibleGasConcentrationFact
        }

        FactLabel {
            id: ambientTemperaturen
            x: 108
            y: 421
            width: 82
            height: 24
            horizontalAlignment: Text.AlignHCenter
            fact: HMI.vehicleManager.activeVehicle.ambientTemperaturenFact
        }

        FactLabel {
            id: xDegree
            x: 635
            y: 406 + 4
            width: 57
            height: 24
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 11
            fact: HMI.vehicleManager.activeVehicle.engineFactGroup.xDegreeFact
        }

        FactLabel {
            id: yDegree
            x: 635
            y: 431 + 4
            width: 57
            height: 24
            font.pointSize: 11
            horizontalAlignment: Text.AlignHCenter
            fact: HMI.vehicleManager.activeVehicle.engineFactGroup.yDegreeFact
        }

        FactLabel {
            id: workHours
            x: 660
            y: 190 + 7
            width: 70
            height: 24
            font.pointSize: 11
            horizontalAlignment: Text.AlignHCenter
            fact: HMI.vehicleManager.activeVehicle.workHoursFact
        }
        FactLabel {
            id: oilTemp
            x: 660
            y: 231 + 7
            width: 70
            height: 24
            font.pointSize: 11
            horizontalAlignment: Text.AlignHCenter
            fact: HMI.vehicleManager.activeVehicle.oilTemperatureFact
        }

        Label {
            id: warnings
            x: 250
            y: 350
            height: 40
            width: 300
            color: "red"
            font.pointSize: 20
            horizontalAlignment: Text.AlignHCenter
            text: "报警列表"
        }
        Timer {
            id: textTimer
            interval: 1000
            running: true
            repeat: true
            onTriggered: {
                if (textIndex >= textVar.length) {
                    warnings.text = ""
                    textIndex = 0
                    return
                }
                warnings.text = textVar[textIndex]
                textIndex++
            }
        }
    }
}
