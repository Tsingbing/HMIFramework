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
                onHelpClicked: {
                    globals.activeVehicle.sendReadControl(0) //关读
                }
            }

            FactTextField {
                id: textEdit2
                font.pixelSize: 14
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0
                fact: globals.activeVehicle.upperLimitLeftTrackLowSpeedFact
                onHelpClicked: {
                    globals.activeVehicle.sendReadControl(0) //关读
                }
            }

            FactTextField {
                id: textEdit3
                anchors.right: parent.right
                anchors.left: parent.left
                anchors.rightMargin: 0
                fact: globals.activeVehicle.upperLimitLeftTrackFrettingSpeedFact
                font.pixelSize: 14
                onHelpClicked: {
                    globals.activeVehicle.sendReadControl(0) //关读
                }
            }

            FactTextField {
                id: textEdit4
                font.pixelSize: 14
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0
                fact: globals.activeVehicle.lowerLimitLeftTrackSpeedFact
                onHelpClicked: {
                    globals.activeVehicle.sendReadControl(0) //关读
                }
            }

            FactTextField {
                id: textEdit5
                anchors.left: parent.left
                anchors.leftMargin: 0
                font.pixelSize: 14
                anchors.right: parent.right
                anchors.rightMargin: 0
                fact: globals.activeVehicle.upperLimitLeftTrackBackHighSpeedFact
                //fact: globals.activeVehicle.upperLimitRightTrackHighSpeedFact
                onHelpClicked: {
                    globals.activeVehicle.sendReadControl(0) //关读
                }
            }

            FactTextField {
                id: textEdit6
                anchors.left: parent.left
                anchors.leftMargin: 0
                font.pixelSize: 14
                anchors.right: parent.right
                anchors.rightMargin: 0
                fact: globals.activeVehicle.upperLimitLeftTrackBackLowSpeedFact
                //fact: globals.activeVehicle.upperLimitRightTrackLowSpeedFact
                onHelpClicked: {
                    globals.activeVehicle.sendReadControl(0) //关读
                }
            }

            //            FactTextField {
            //                id: textEdit7
            //                anchors.left: parent.left
            //                anchors.leftMargin: 0
            //                font.pixelSize: 14
            //                anchors.right: parent.right
            //                anchors.rightMargin: 0
            //                fact: globals.activeVehicle.upperLimitRightTrackFrettingSpeedFact
            //                onHelpClicked: {
            //                    globals.activeVehicle.sendReadControl(0) //关读
            //                }
            //            }
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
                fact: globals.activeVehicle.upperLimitRightTrackHighSpeedFact

                onHelpClicked: {
                    globals.activeVehicle.sendReadControl(0) //关读
                }
            }
            FactTextField {
                id: textEdit8
                font.pixelSize: 14
                anchors.right: parent.right
                anchors.leftMargin: 0
                anchors.rightMargin: 0
                anchors.left: parent.left
                fact: globals.activeVehicle.upperLimitRightTrackLowSpeedFact
                onHelpClicked: {
                    globals.activeVehicle.sendReadControl(0) //关读
                }
            }

            FactTextField {
                id: textEdit9
                font.pixelSize: 14
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.left: parent.left

                fact: globals.activeVehicle.upperLimitRightTrackFrettingSpeedFact

                onHelpClicked: {
                    globals.activeVehicle.sendReadControl(0) //关读
                }
            }

            FactTextField {
                id: textEdit10
                font.pixelSize: 14
                anchors.right: parent.right
                anchors.leftMargin: 0
                anchors.rightMargin: 0
                anchors.left: parent.left
                fact: globals.activeVehicle.lowerLimitRightTrackSpeedFact

                onHelpClicked: {
                    globals.activeVehicle.sendReadControl(0) //关读
                }
            }

            FactTextField {
                id: textEdit11
                font.pixelSize: 14
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.leftMargin: 0
                anchors.left: parent.left
                fact: globals.activeVehicle.upperLimitRightTrackBackHighSpeedFact
                onHelpClicked: {
                    globals.activeVehicle.sendReadControl(0) //关读
                }
            }

            FactTextField {
                id: textEdit12
                font.pixelSize: 14
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.leftMargin: 0
                anchors.left: parent.left
                fact: globals.activeVehicle.upperLimitRightTrackBackLowSpeedFact
                onHelpClicked: {
                    globals.activeVehicle.sendReadControl(0) //关读
                }
            }


            /*
            FactTextField {
                id: textEdit13
                font.pixelSize: 14
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.leftMargin: 0
                anchors.left: parent.left
            }
            */
            spacing: 13
        }

        Button {
            id: button
            x: 359
            y: 36
            width: 83
            height: 33
            text: "保存"
            font.weight: Font.Normal
            font.bold: true
            font.pointSize: 16
            checked: false
            onClicked: globals.activeVehicle.updateAllParams()
        }
    }
}
