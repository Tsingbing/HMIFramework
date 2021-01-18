/****************************************************************************
 *
 * (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * HMI is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

import QtQuick          2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts  1.11

import HMI                       1.0
import HMI.Controls              1.0
//import HMI.MultiVehicleManager   1.0
import HMI.ScreenTools           1.0
import HMI.Palette               1.0

//-------------------------------------------------------------------------
//-- Toolbar Indicators
Row {
    id:                 indicatorRow
    anchors.top:        parent.top
    anchors.bottom:     parent.bottom
    spacing:            ScreenTools.defaultFontPixelWidth * 1.5
    layoutDirection:    Qt.RightToLeft

    Repeater {
        model: ["qrc:/toolbar/BatteryIndicator.qml", "qrc:/toolbar/SignalStrength.qml"]

        Loader {
            id:                 indicatorLoader
            anchors.top:        parent.top
            anchors.bottom:     parent.bottom
            anchors.margins:    ScreenTools.defaultFontPixelHeight * 0.66
            source:             modelData
            visible:            true//item.showIndicator
        }
    }
}
