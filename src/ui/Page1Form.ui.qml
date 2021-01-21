import QtQuick 2.12
import QtQuick.Controls 2.5


import HMI 1.0
import HMI.FactSystem 1.0
import HMI.FactControls 1.0
import HMI.ScreenTools 1.0

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
        source: "qrc:/qmlimages/zcwjj3/page1.jpg"

        FactLabel {
            id: label
            x: 210
            y: 132
            width: 145
            height: 24
            fact: HMI.vehicleManager.activeVehicle.supplyVoltageFact
            //text: qsTr("Label")
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
            fact: HMI.vehicleManager.activeVehicle.rotatingSpeedFact
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
            fact: HMI.vehicleManager.activeVehicle.xDegreeFact
            //text: qsTr("Label")
        }

        FactLabel {
            id: yDegree
            x: 603
            y: 288
            width: 145
            height: 24
            fact: HMI.vehicleManager.activeVehicle.yDegreeFact
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
    }
}
