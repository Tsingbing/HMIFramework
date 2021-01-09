import QtQuick 2.12
import QtQuick.Controls 2.4
import QtQuick.Dialogs  1.3
import QtQuick.Window 2.12
import QtQuick.Layouts  1.11

import HMI 1.0
import HMI.FactSystem 1.0
import HMI.ScreenTools 1.0
import HMI.Controls      1.0
import HMI.SettingsManager 1.0

ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Stack")

    footer: ToolBar {
        contentHeight: toolButton.implicitHeight

        ToolButton {
            id: toolButton
            text: stackView.depth > 1 ? "\u25C0" : "\u2630"
            font.pixelSize: Qt.application.font.pixelSize * 1.6
            onClicked: {
                if (stackView.depth > 1) {
                    stackView.pop()
                } else {
                    drawer.open()
                }
            }
        }

        Label {
            text: stackView.currentItem.title
            anchors.centerIn: parent
        }
    }

    Drawer {
        id: drawer

        height:         toolButton.height
        edge:           Qt.LeftEdge
        interactive:    true
        dragMargin:     0

        ColumnLayout {
            id:                 mainLayout
            //anchors.margins:    ScreenTools.defaultFontPixelWidth
            anchors.left:       parent.left
            anchors.bottom:     parent.bottom
            spacing:            10

            ItemDelegate {
                text: qsTr("Page 1")
                width: parent.width
                onClicked: {
                    stackView.push("Page1Form.ui.qml")
                    drawer.close()
                }
            }
            ItemDelegate {
                text: qsTr("Page 2")
                width: parent.width
                onClicked: {
                    stackView.push("Page2Form.ui.qml")
                    drawer.close()
                }
            }
        }
    }

    StackView {
        id: stackView
        initialItem: "HomeForm.ui.qml"
        anchors.fill: parent
    }
}


