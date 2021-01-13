/****************************************************************************
 *
 * (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * HMI is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/


import QtQuick                  2.3
import QtQuick.Controls         1.2
import QtQuick.Controls.Styles  1.4
import QtQuick.Dialogs          1.2
import QtQuick.Layouts          1.2

import HMI                       1.0
import HMI.FactSystem            1.0
//import HMI.FactControls          1.0
import HMI.Controls              1.0
import HMI.ScreenTools           1.0
//import HMI.MultiVehicleManager   1.0
import HMI.Palette               1.0
//import HMI.Controllers           1.0
import HMI.SettingsManager       1.0

Rectangle {
    id:                 _root
    color:              hmiPal.window
    anchors.fill:       parent
    anchors.margins:    ScreenTools.defaultFontPixelWidth
    //visible: true
    property Fact _appFontPointSize:                    HMI.settingsManager.appSettings.appFontPointSize

    readonly property real _internalWidthRatio: 0.8

    HMILabel {
        id:         miscSectionLabel
        text:       qsTr("Miscellaneous")
        visible:    true
    }
    HMIFlickable {
        clip:               true
        anchors.fill:       parent

        contentHeight:      outerItem.height
        contentWidth:       outerItem.width
        visible:    true

        Item {
            id:     outerItem
            width:  Math.max(_root.width, settingsColumn.width)
            height: settingsColumn.height

            ColumnLayout {
                id:                         settingsColumn
                anchors.horizontalCenter:   parent.horizontalCenter

                HMILabel {
                    id:         miscSectionLabel2
                    text:       qsTr("Miscellaneous2")
                    visible:    true
                }

            } // settingsColumn
        }
    }
}
