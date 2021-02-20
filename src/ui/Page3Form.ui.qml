import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12

import HMI 1.0
import HMI.Controls 1.0
import HMI.FactSystem 1.0
import HMI.FactControls 1.0
import HMI.ScreenTools 1.0

Page {
    width: 800
    height: 600

    title: qsTr("Page 3")
    property Fact fact: HMI.vehicleManager.activeVehicle.alarmsFact
    Image {
        id: image
        x: 0
        y: 0
        width: 800
        height: 600
        fillMode: Image.PreserveAspectFit
        source: "qrc:/qmlimages/zcwjj3/page3.jpg"

        //        FactBitmask {
        //            id: armingCheckBitmask
        //            x: 60
        //            y: 120
        //            firstEntryIsAll: true
        //            fact: HMI.vehicleManager.activeVehicle.alarmsFact
        //        }
        Column {
            spacing: ScreenTools.defaultFontPixelWidth

            /// true: Checking the first entry will clear and disable all other entries
            property bool firstEntryIsAll: true

            x: 45
            y: 120
            width: 320
            height: 370

            Repeater {
                id: repeater
                model: fact ? fact.bitmaskStrings : []
                Item {
                    id: r
                    width: 300
                    height: 43
                    RowLayout {
                        id: layout
                        //width: 340
                        anchors.fill: parent
                        HMILabel {
                            id: checkbox
                            text: modelData
                        }

                        HMILabel {
                            id: label
                            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                            text: "正常"
                            states: [
                                State {
                                    name: "normal"
                                    PropertyChanges {
                                        target: label
                                        color: "green"
                                        text: "正常"
                                    }
                                },
                                State {
                                    name: "alarm"
                                    PropertyChanges {
                                        target: label
                                        text: "报警"
                                        color: "red"
                                    }
                                }
                            ]

                            Connections {
                                target: fact
                                onValueChanged: {
                                    if (fact.value & fact.bitmaskValues[index])
                                        label.state = "normal"
                                    else
                                        label.state = "alarm"
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
