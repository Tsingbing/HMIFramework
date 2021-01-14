/****************************************************************************
 *
 * (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.HMI.org>
 *
 * HMI is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

import QtQuick          2.3
import QtQuick.Layouts  1.11

import HMI               1.0
import HMI.Controls      1.0
import HMI.Palette       1.0
import HMI.ScreenTools   1.0

Rectangle {
    color:          qgcPal.window
    anchors.fill:   parent

    readonly property real _margins: ScreenTools.defaultFontPixelHeight

    HMIPalette { id: qgcPal; colorGroupEnabled: true }

    HMIFlickable {
        anchors.margins:    _margins
        anchors.fill:       parent
        width:              grid.width
        contentWidth:       grid.width
        contentHeight:      grid.height
        clip:               true

        GridLayout {
            id:         grid
            columns:    2

            HMILabel { text: qsTr("HMI User Guide") }
            HMILabel {
                linkColor:          qgcPal.text
                text:               "<a href=\"https://docs.HMI.com\">https://docs.HMI.com</a>"
                onLinkActivated:    Qt.openUrlExternally(link)
            }

            HMILabel { text: qsTr("CAR Users Discussion Forum") }
            HMILabel {
                linkColor:          qgcPal.text
                text:               "<a href=\"http://discuss.px4.io/c/HMI\">http://discuss.px4.io/c/HMI</a>"
                onLinkActivated:    Qt.openUrlExternally(link)
            }

            HMILabel { text: qsTr("car Users Discussion Forum") }
            HMILabel {
                linkColor:          qgcPal.text
                text:               "<a href=\"https://discuss.HMI.org/c/HMI-software/HMI\">https://discuss.HMI.org/c/HMI-software/HMI</a>"
                onLinkActivated:    Qt.openUrlExternally(link)
            }
        }
    }
}
