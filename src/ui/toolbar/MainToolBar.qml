/****************************************************************************
 *
 * (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

import QtQuick          2.12
import QtQuick.Controls 2.4
import QtQuick.Layouts  1.11
import QtQuick.Dialogs  1.3

import HMI                       1.0
import HMI.ScreenTools           1.0

Rectangle {
    id:     _root
    //color:  Qt.red
    opacity: 0.5

    property int currentToolbar: flyViewToolbar

    readonly property int flyViewToolbar:   0
    readonly property int planViewToolbar:  1
    readonly property int simpleToolbar:    2

    property var    _activeVehicle:     HMI.vehicleManager.activeVehicle

    RowLayout {
        id:                     viewButtonRow
        anchors.bottomMargin:   1
        anchors.top:            parent.top
        anchors.bottom:         parent.bottom
        spacing:                ScreenTools.defaultFontPixelWidth / 2

        Button {
            id:                 disconnectButton
            opacity: 1
            text:               qsTr("Disconnect")
            //onClicked:          _activeVehicle.closeVehicle()
            visible:           true
        }
    }

}
