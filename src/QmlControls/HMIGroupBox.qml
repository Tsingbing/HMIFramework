/****************************************************************************
 *
 * (c) 2009-2020 HMI PROJECT <http://www.HMI.org>
 *
 * HMI is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

import QtQuick          2.3
import QtQuick.Controls 2.0

import HMI.Palette       1.0
import HMI.ScreenTools   1.0

GroupBox {
    id: control

    HMIPalette { id: hmiPal; colorGroupEnabled: enabled }

    background: Rectangle {
        y:      control.topPadding - control.padding
        width:  parent.width
        height: parent.height - control.topPadding + control.padding
        color:  hmiPal.windowShade
    }

    label: HMILabel {
        width:  control.availableWidth
        text:   control.title
    }
}
