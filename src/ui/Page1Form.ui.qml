import QtQuick 2.12
import QtQuick.Controls 2.5

import HMI 1.0
import HMI.Controls 1.0
import HMI.FactSystem 1.0
import HMI.FactControls 1.0
import HMI.ScreenTools 1.0

Page {
    width: 800
    height: 600

    title: qsTr("Page 1")

    //property fact rotatingSpeed: HMI.ve.getFactGroup("engine")->getFact("rotatingSpeed")
    Image {
        id: image
        x: 0
        y: 0
        width: 800
        height: 600
        fillMode: Image.PreserveAspectFit
        source: "qrc:/qmlimages/zcwjj3/page1.jpg"

        //        HMIFlickable {
        //            anchors.fill: parent
        //            contentHeight: _column.height
        //            flickableDirection: Flickable.VerticalFlick
        //            clip: true

        //            Column {
        //                id: _column
        //                width: 800
        //                Repeater {
        //                    model: HMI.vehicleManager.activeVehicle.factNames

        //                    Loader {
        //                        sourceComponent: largeValue
        //                        property Fact fact: HMI.vehicleManager.activeVehicle.getFact(
        //                                                modelData)
        //                    }
        //                }

        //                Component {
        //                    id: largeValue

        //                    Column {
        //                        width: _column.width
        //                        HMILabel {
        //                            width: parent.width
        //                            horizontalAlignment: Text.AlignHCenter
        //                            wrapMode: Text.WordWrap
        //                            text: fact.shortDescription + fact.valueString
        //                                  + (fact.units ? " (" + fact.units + ")" : "")
        //                        }
        //                    }
        //                }
        //            }
        //        }
        FactLabel {
            id: label
            x: 210
            y: 132
            width: 145
            height: 24
            fact: HMI.vehicleManager.activeVehicle.batteryPowerFact
            //text: qsTr("Label")
        }

        Row {
            id: row
            x: 595
            y: 65
            width: 169
            height: 40

            Switch {
                id: element
                width: 111
                height: 35
                onClicked: {
                    globals.activeVehicle.sendJiesuo(checked)
                    if (checked) {
                        label2.text = "??????"
                        label2.color = "green"
                    } else {
                        label2.text = "?????????"
                        label2.color = "red"
                    }
                }
            }

            Label {
                id: label2
                height: 35
                color: "red"
                text: qsTr("?????????")
                verticalAlignment: Text.AlignTop
                font.pointSize: 16
            }
        }

        FactLabel {
            id: label1
            x: 210
            y: 184
            width: 145
            height: 24
            fact: HMI.vehicleManager.activeVehicle.supplyVoltageFact
            //text: qsTr("Label")
        }

        FactLabel {
            id: fuelLevel
            x: 210
            y: 238
            width: 145
            height: 24
            fact: HMI.vehicleManager.activeVehicle.fuelLevelFact
            //text: qsTr("Label")
        }

        FactLabel {
            id: rotatingSpeed
            x: 210
            y: 288
            width: 145
            height: 24
            //fact: HMI.vehicleManager.activeVehicle.rotatingSpeedFact
            fact: HMI.vehicleManager.activeVehicle.engineFactGroup.rotatingSpeedFact
            //text: qsTr("Label")
        }

        FactLabel {
            id: waterTemperature
            x: 210
            y: 344
            width: 145
            height: 24
            fact: HMI.vehicleManager.activeVehicle.waterTemperatureFact
            //text: qsTr("Label")
        }

        FactLabel {
            id: mainPumpPressure
            x: 210
            y: 399
            width: 145
            height: 24
            fact: HMI.vehicleManager.activeVehicle.mainPumpPressureFact
            //text: qsTr("Label")
        }

        FactLabel {
            id: oxygenConcentration
            x: 210
            y: 450
            width: 145
            height: 24
            fact: HMI.vehicleManager.activeVehicle.oxygenConcentrationFact
            //text: qsTr("Label")
        }

        FactLabel {
            id: combustibleGasConcentration
            x: 603
            y: 132
            width: 145
            height: 24
            fact: HMI.vehicleManager.activeVehicle.combustibleGasConcentrationFact
            //text: qsTr("Label")
        }

        FactLabel {
            id: ambientTemperaturen
            x: 603
            y: 184
            width: 145
            height: 24
            fact: HMI.vehicleManager.activeVehicle.ambientTemperaturenFact
            //text: qsTr("Label")
        }

        FactLabel {
            id: xDegree
            x: 603
            y: 238
            width: 145
            height: 24
            fact: HMI.vehicleManager.activeVehicle.engineFactGroup.xDegreeFact
            //text: qsTr("Label")
        }

        FactLabel {
            id: yDegree
            x: 603
            y: 288
            width: 145
            height: 24
            fact: HMI.vehicleManager.activeVehicle.engineFactGroup.yDegreeFact
            //text: qsTr("Label")
        }

        FactLabel {
            id: workHours
            x: 603
            y: 344
            width: 145
            height: 24
            fact: HMI.vehicleManager.activeVehicle.workHoursFact
            //text: qsTr("Label")
        }
        FactLabel {
            id: oilTemp
            x: 603
            y: 403
            width: 145
            height: 24
            fact: HMI.vehicleManager.activeVehicle.oilTemperatureFact
            //text: qsTr("Label")
        }
    }
}
