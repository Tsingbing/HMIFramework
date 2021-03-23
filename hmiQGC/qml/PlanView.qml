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
    id:     settingsView
    color:  hmiPal.window
    z:      1//QGroundControl.zOrderTopMost

    readonly property real _defaultTextHeight:  ScreenTools.defaultFontPixelHeight
    readonly property real _defaultTextWidth:   ScreenTools.defaultFontPixelWidth
    readonly property real _horizontalMargin:   _defaultTextWidth / 2
    readonly property real _verticalMargin:     _defaultTextHeight / 2
    readonly property real _buttonHeight:       ScreenTools.isTinyScreen ? ScreenTools.defaultFontPixelHeight * 3 : ScreenTools.defaultFontPixelHeight * 2

    property bool _first: true

    HMIPalette { id: hmiPal }

    Component.onCompleted: {
        //-- Default Settings
        __rightPanel.source = "qrc:/qml/FlightDisplayViewUVC.qml"
    }

    HMIFlickable {
        id:                 buttonList
        width:              buttonColumn.width
        anchors.topMargin:  _verticalMargin
        anchors.top:        parent.top
        anchors.bottom:     parent.bottom
        anchors.leftMargin: _horizontalMargin
        anchors.left:       parent.left
        contentHeight:      buttonColumn.height + _verticalMargin
        flickableDirection: Flickable.VerticalFlick
        clip:               true

        ExclusiveGroup { id: panelActionGroup }

        ColumnLayout {
            id:         buttonColumn
            spacing:    _verticalMargin

            property real _maxButtonWidth: 0

            HMILabel {
                Layout.fillWidth:       true
                text:                   qsTr("PlanView")
                wrapMode:               Text.WordWrap
                horizontalAlignment:    Text.AlignHCenter
                visible:                true
            }

            Repeater {
                model: ListModel {
                    ListElement{title: qsTr("video"); url: "qrc:/qml/FlightDisplayViewUVC.qml"}
                    ListElement{title: qsTr("map"); url: "qrc:/qml/HMI/FlightMap/FlightMap.qml"}
                }
                HMIButton {
                    height:             _buttonHeight
                    text:               title
                    exclusiveGroup:     panelActionGroup
                    Layout.fillWidth:   true

                    onClicked: {
                        if (mainWindow.preventViewSwitch()) {
                            return
                        }
                        if (__rightPanel.source !== url) {
                            __rightPanel.source = url
                        }
                        checked = true
                    }

                    Component.onCompleted: {
                        if(_first) {
                            _first = false
                            checked = true
                        }
                    }
                }
            }
        }
    }

    Rectangle {
        id:                     divider
        anchors.topMargin:      _verticalMargin
        anchors.bottomMargin:   _verticalMargin
        anchors.leftMargin:     _horizontalMargin
        anchors.left:           buttonList.right
        anchors.top:            parent.top
        anchors.bottom:         parent.bottom
        width:                  1
        color:                  hmiPal.windowShade
    }

    //-- Panel Contents
    Loader {
        id:                     __rightPanel
        anchors.leftMargin:     _horizontalMargin
        anchors.rightMargin:    _horizontalMargin
        anchors.topMargin:      _verticalMargin
        anchors.bottomMargin:   _verticalMargin
        anchors.left:           divider.right
        anchors.right:          parent.right
        anchors.top:            parent.top
        anchors.bottom:         parent.bottom
    }

}

