/****************************************************************************
 *
 * (c) 2009-2020 HMI PROJECT <http://www.HMI.org>
 *
 * HMI is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

import QtQuick          2.3
import QtQuick.Controls 2.4

import HMI.Controls      1.0
import HMI.Palette       1.0
import HMI.ScreenTools   1.0

// Important Note: Toolbar buttons must manage their checked state manually in order to support
// view switch prevention. This means they can't be checkable or autoExclusive.

Button {
    id:                 button
    height:             ScreenTools.defaultFontPixelHeight * 3
    leftPadding:        _horizontalMargin
    rightPadding:       _horizontalMargin
    checkable:          false

    property bool logo: false

    property real _horizontalMargin: ScreenTools.defaultFontPixelWidth

    onCheckedChanged: checkable = false

    background: Rectangle {
        anchors.fill: parent
        color:  button.checked ? qgcPal.buttonHighlight : Qt.rgba(0,0,0,0)
    }

    contentItem: Row {
        spacing:                ScreenTools.defaultFontPixelWidth
        anchors.verticalCenter: button.verticalCenter
        HMIColoredImage {
            id:                     _icon
            height:                 ScreenTools.defaultFontPixelHeight * 2
            width:                  height
            sourceSize.height:      parent.height
            fillMode:               Image.PreserveAspectFit
            color:                  logo ? "transparent" : (button.checked ? qgcPal.buttonHighlightText : qgcPal.buttonText)
            source:                 button.icon.source
            anchors.verticalCenter: parent.verticalCenter
        }
        Label {
            id:                     _label
            visible:                text !== ""
            text:                   button.text
            color:                  button.checked ? qgcPal.buttonHighlightText : qgcPal.buttonText
            anchors.verticalCenter: parent.verticalCenter
        }
    }
}
