/****************************************************************************
 *
 * (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/


import QtQuick          2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts  1.2

import HMI               1.0
import HMI.Palette       1.0
import HMI.Controls      1.0
import HMI.ScreenTools   1.0

Rectangle {
    id:     flyView
    color:  "#66B660"
    anchors.fill: parent
    z:      HMI.zOrderTopMost

    readonly property real _defaultTextHeight:  ScreenTools.defaultFontPixelHeight
    readonly property real _defaultTextWidth:   ScreenTools.defaultFontPixelWidth
    readonly property real _horizontalMargin:   _defaultTextWidth / 2
    readonly property real _verticalMargin:     _defaultTextHeight / 2
    readonly property real _buttonHeight:       ScreenTools.isTinyScreen ? ScreenTools.defaultFontPixelHeight * 3 : ScreenTools.defaultFontPixelHeight * 2

    property bool _first: true

    HMIPalette { id: hmiPal }

    Component.onCompleted: {
        //-- Default Settings
        //__rightPanel.source = QGroundControl.corePlugin.settingsPages[QGroundControl.corePlugin.defaultSettings].url
    }

    Rectangle {
        id:                     background
        anchors.left:           flyView.right
        anchors.top:            flyView.top
        anchors.bottom:         flyView.bottom
        //anchors.right:          flyView.right
        width:                  800

        color:                  hmiPal.windowShade
            Image {
                id: image
                z: 5
                anchors.fill:   parent
                source: "qrc:/qmlimages/main_set.jpg"
                fillMode: Image.PreserveAspectFit
            }
    }

//    HMIFlickable {
//        id:                 buttonList
//        width:              buttonColumn.width
//        anchors.topMargin:  _verticalMargin
//        anchors.top:        parent.top
//        anchors.bottom:     parent.bottom
//        anchors.leftMargin: _horizontalMargin
//        anchors.left:       parent.left
//        contentHeight:      buttonColumn.height + _verticalMargin
//        flickableDirection: Flickable.VerticalFlick
//        clip:               true

//        ExclusiveGroup { id: panelActionGroup }

//        ColumnLayout {
//            id:         buttonColumn
//            spacing:    _verticalMargin

//            property real _maxButtonWidth: 0

//            HMILabel {
//                Layout.fillWidth:       true
//                text:                   qsTr("FlyView.qml")
//                wrapMode:               Text.WordWrap
//                horizontalAlignment:    Text.AlignHCenter
//                visible:                true
//            }
//        }
//    }

}
