import QtQuick 2.12
import QtQuick.Controls 2.5
//import HMI.FactSystem 1.0
import HMI.FactControls 1.0

Page {
    id: page
    width: 800
    height: 600
    property alias button: button
    enabled: true

    title: qsTr("Page 4")

    Image {
        id: image
        x: 0
        y: 0
        fillMode: Image.PreserveAspectFit
        source: "qrc:/qmlimages/zcwjj3/page4.jpg"

        /*Fact*/
        Switch {
            id: readControl
            x: 654
            y: 62
            text: qsTr("读")
            onClicked: globals.activeVehicle.sendReadControl(checked)
        }

        Switch {
            id: writeControl
            x: 559
            y: 62
            text: qsTr("写")
            onClicked: globals.activeVehicle.sendWriteControl(checked)
        }

        Column {
            id: column
            x: 264
            y: 124
            width: 103
            height: 369
            spacing: 13

            FactTextField {
                id: textEdit
                font.pixelSize: 14
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0
                fact: globals.activeVehicle.upperLimitLeftTrackHighSpeedFact
            }

            FactTextField {
                id: textEdit2
                font.pixelSize: 14
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0
                fact: globals.activeVehicle.upperLimitLeftTrackLowSpeedFact
            }

            FactTextField {
                id: textEdit3
                anchors.right: parent.right
                anchors.left: parent.left
                anchors.rightMargin: 0
                fact: globals.activeVehicle.upperLimitLeftTrackFrettingSpeedFact
                font.pixelSize: 14
            }

            FactTextField {
                id: textEdit4
                font.pixelSize: 14
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0
                fact: globals.activeVehicle.lowerLimitLeftTrackSpeedFact
            }

            FactTextField {
                id: textEdit5
                anchors.left: parent.left
                anchors.leftMargin: 0
                font.pixelSize: 14
                anchors.right: parent.right
                anchors.rightMargin: 0
                fact: globals.activeVehicle.upperLimitRightTrackHighSpeedFact
            }

            FactTextField {
                id: textEdit6
                anchors.left: parent.left
                anchors.leftMargin: 0
                font.pixelSize: 14
                anchors.right: parent.right
                anchors.rightMargin: 0
                fact: globals.activeVehicle.upperLimitRightTrackLowSpeedFact
            }

            FactTextField {
                id: textEdit7
                anchors.left: parent.left
                anchors.leftMargin: 0
                font.pixelSize: 14
                anchors.right: parent.right
                anchors.rightMargin: 0
                fact: globals.activeVehicle.upperLimitRightTrackFrettingSpeedFact
            }
        }

        Column {
            id: column1
            x: 654
            y: 124
            width: 107
            height: 369
            FactTextField {
                id: textEdit1
                font.pixelSize: 14
                anchors.right: parent.right
                anchors.leftMargin: 0
                anchors.rightMargin: 0
                anchors.left: parent.left
                fact: globals.activeVehicle.lowerLimitRightTrackSpeedFact
            }

            FactTextField {
                id: textEdit8
                font.pixelSize: 14
                anchors.right: parent.right
                anchors.leftMargin: 0
                anchors.rightMargin: 0
                anchors.left: parent.left
            }

            FactTextField {
                id: textEdit9
                font.pixelSize: 14
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.left: parent.left
            }

            FactTextField {
                id: textEdit10
                font.pixelSize: 14
                anchors.right: parent.right
                anchors.leftMargin: 0
                anchors.rightMargin: 0
                anchors.left: parent.left
            }

            FactTextField {
                id: textEdit11
                font.pixelSize: 14
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.leftMargin: 0
                anchors.left: parent.left
            }

            FactTextField {
                id: textEdit12
                font.pixelSize: 14
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.leftMargin: 0
                anchors.left: parent.left
            }

            FactTextField {
                id: textEdit13
                font.pixelSize: 14
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.leftMargin: 0
                anchors.left: parent.left
            }
            spacing: 13
        }

        Button {
            id: button
            x: 107
            y: 77
            width: 83
            height: 25
            text: "设置"
            onClicked: globals.activeVehicle.updateAllParams()
        }
    }
}

/*##^##
Designer {
    D{i:4;anchors_height:400;anchors_width:200;anchors_x:263;anchors_y:125}D{i:12;anchors_height:400;anchors_width:200;anchors_x:263;anchors_y:125}
}
##^##*/

