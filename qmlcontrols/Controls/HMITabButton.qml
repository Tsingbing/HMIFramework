/****************************************************************************
 *
 * (c) 2009-2020 HMI PROJECT <http://www.HMI.org>
 *
 * HMI is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

import QtQuick                  2.12
import QtQuick.Controls         2.12
import QtQuick.Controls.impl    2.12
import QtQuick.Templates        2.12 as T

import HMI.ScreenTools   1.0
import HMI.Palette       1.0

T.TabButton {
    id: control

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                            implicitContentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
                             implicitContentHeight + topPadding + bottomPadding)

    HMIPalette { id: hmiPal; colorGroupEnabled: enabled }

    font.pointSize: ScreenTools.defaultFontPointSize
    font.family:    ScreenTools.normalFontFamily

    padding: 6
    spacing: 6

    //icon.width: 24
    icon.height: ScreenTools.defaultFontPixelHeight
    icon.color: checked ? hmiPal.buttonHighlightText : hmiPal.buttonText


    contentItem: IconLabel {
        spacing: control.spacing
        mirrored: control.mirrored
        display: control.display

        icon: control.icon
        text: control.text
        font: control.font
        color: checked ? hmiPal.buttonHighlightText : hmiPal.buttonText
    }

    background: Rectangle {
        implicitHeight: 40
        color: checked ? hmiPal.buttonHighlight : hmiPal.button
        /*color: Color.blend(control.checked ? control.palette.window : control.palette.dark,
                                             control.palette.mid, control.down ? 0.5 : 0.0)*/
    }
}
