import QtQuick                  2.12
import QtQuick.Controls         2.12

import HMI.Palette       1.0
import HMI.ScreenTools   1.0

Text {
    font.pointSize: ScreenTools.defaultFontPointSize
    font.family:    ScreenTools.normalFontFamily
    color:          hmiPal.text
    antialiasing:   true

    HMIPalette { id: hmiPal; colorGroupEnabled: enabled }
}
