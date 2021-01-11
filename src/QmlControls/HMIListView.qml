import QtQuick 2.3

import HMI.Palette 1.0

/// HMI version of ListVIew control that shows horizontal/vertial scroll indicators
ListView {
    id:             root
    boundsBehavior: Flickable.StopAtBounds

    property color indicatorColor: hmiPal.text

    HMIPalette { id: hmiPal; colorGroupEnabled: enabled }

    Component.onCompleted: {
        var indicatorComponent = Qt.createComponent("HMIFlickableVerticalIndicator.qml")
        indicatorComponent.createObject(root)
        indicatorComponent = Qt.createComponent("HMIFlickableHorizontalIndicator.qml")
        indicatorComponent.createObject(root)
    }
}
