import QtQuick 2.3

import HMI.Palette 1.0

/// HMI version of Flickable control that shows horizontal/vertial scroll indicators
Flickable {
    id:             root
    boundsBehavior: Flickable.StopAtBounds
    clip:           true

    property color indicatorColor: qgcPal.text

    Component.onCompleted: {
        var indicatorComponent = Qt.createComponent("HMIFlickableVerticalIndicator.qml")
        indicatorComponent.createObject(root)
        indicatorComponent = Qt.createComponent("HMIFlickableHorizontalIndicator.qml")
        indicatorComponent.createObject(root)
    }
}
