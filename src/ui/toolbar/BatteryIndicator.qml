/****************************************************************************
 *
 * (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * HMI is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

import QtQuick          2.11
import QtQuick.Layouts  1.11

import HMI                       1.0
import HMI.Controls              1.0
//import HMI.MultiVehicleManager   1.0
import HMI.ScreenTools           1.0
import HMI.Palette               1.0

//-------------------------------------------------------------------------
//-- Battery Indicator
Item {
    id:             _root
    anchors.top:    parent.top
    anchors.bottom: parent.bottom
    width:          batteryIndicatorRow.width

    property bool showIndicator: true

    function getBatteryColor() {
        if(activeVehicle) {
            return hmiPal.text
//            if(activeVehicle.battery.percentRemaining.value > 75) {
//                return hmiPal.text
//            }
//            if(activeVehicle.battery.percentRemaining.value > 50) {
//                return hmiPal.colorOrange
//            }
//            if(activeVehicle.battery.percentRemaining.value > 0.1) {
//                return hmiPal.colorRed
//            }
        }
        return hmiPal.colorGrey
    }

    function getBatteryPercentageText() {
        if(activeVehicle) {
            return "100%"
//            if(activeVehicle.battery.percentRemaining.value > 98.9) {
//                return "100%"
//            }
//            if(activeVehicle.battery.percentRemaining.value > 0.1) {
//                return activeVehicle.battery.percentRemaining.valueString + activeVehicle.battery.percentRemaining.units
//            }
//            if(activeVehicle.battery.voltage.value >= 0) {
//                return activeVehicle.battery.voltage.valueString + activeVehicle.battery.voltage.units
//            }
        }
        return "N/A"
    }

    Component {
        id: batteryInfo

        Rectangle {
            width:  battCol.width   + ScreenTools.defaultFontPixelWidth  * 3
            height: battCol.height  + ScreenTools.defaultFontPixelHeight * 2
            radius: ScreenTools.defaultFontPixelHeight * 0.5
            color:  hmiPal.window
            border.color:   hmiPal.text

            Column {
                id:                 battCol
                spacing:            ScreenTools.defaultFontPixelHeight * 0.5
                width:              Math.max(battGrid.width, battLabel.width)
                anchors.margins:    ScreenTools.defaultFontPixelHeight
                anchors.centerIn:   parent

                HMILabel {
                    id:             battLabel
                    text:           qsTr("Battery Status")
                    font.family:    ScreenTools.demiboldFontFamily
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                GridLayout {
                    id:                 battGrid
                    anchors.margins:    ScreenTools.defaultFontPixelHeight
                    columnSpacing:      ScreenTools.defaultFontPixelWidth
                    columns:            2
                    anchors.horizontalCenter: parent.horizontalCenter

                    HMILabel { text: qsTr("Voltage:") }
                    //HMILabel { text: (activeVehicle && activeVehicle.battery.voltage.value !== -1) ? (activeVehicle.battery.voltage.valueString + " " + activeVehicle.battery.voltage.units) : "N/A" }
                    HMILabel { text: qsTr("Accumulated Consumption:") }
                   // HMILabel { text: (activeVehicle && activeVehicle.battery.mahConsumed.value !== -1) ? (activeVehicle.battery.mahConsumed.valueString + " " + activeVehicle.battery.mahConsumed.units) : "N/A" }
                }
            }
        }
    }

    Row {
        id:             batteryIndicatorRow
        anchors.top:    parent.top
        anchors.bottom: parent.bottom
        opacity:        /*(activeVehicle && activeVehicle.battery.voltage.value >= 0) ? 1 : */0.5
        HMIColoredImage {
            anchors.top:        parent.top
            anchors.bottom:     parent.bottom
            width:              height
            sourceSize.width:   width
            source:             "/qmlimages/Battery.svg"
            fillMode:           Image.PreserveAspectFit
            color:              hmiPal.text
        }
        HMILabel {
            text:                   getBatteryPercentageText()
            font.pointSize:         ScreenTools.smallFontPointSize
            color:                  getBatteryColor()
            anchors.verticalCenter: parent.verticalCenter
        }
    }
    MouseArea {
        anchors.fill:   parent
        onClicked: {
            mainWindow.showPopUp(_root, batteryInfo)
        }
    }
}
