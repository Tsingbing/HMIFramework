/****************************************************************************
 *
 * (c) 2009-2020 HMI PROJECT <http://www.HMI.org>
 *
 * HMI is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

import QtQuick                  2.3
import QtQuick.Controls         1.2
import QtQuick.Controls.Styles  1.4

import HMI.Palette       1.0
import HMI.ScreenTools   1.0

Switch {
    id: _root
    HMIPalette { id:hmiPal; colorGroupEnabled: true }
    style: SwitchStyle {
        groove:     Rectangle {
            implicitWidth:  ScreenTools.defaultFontPixelWidth * 6
            implicitHeight: ScreenTools.defaultFontPixelHeight
            color:          (control.checked && control.enabled) ? hmiPal.colorGreen : hmiPal.colorGrey
            radius:         3
            border.color:   hmiPal.button
            border.width:   1
        }
    }
}
