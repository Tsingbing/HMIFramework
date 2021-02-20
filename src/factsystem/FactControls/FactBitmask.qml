import QtQuick          2.3
import QtQuick.Controls 1.2

import HMI.FactSystem    1.0
import HMI.Palette       1.0
import HMI.Controls      1.0
import HMI.ScreenTools   1.0

Column {
    spacing: ScreenTools.defaultFontPixelWidth

    /// true: Checking the first entry will clear and disable all other entries
    property bool firstEntryIsAll: true

    property Fact fact: Fact { }

    Component.onCompleted: {
        if (firstEntryIsAll && repeater.itemAt(0).checked) {
            for (var i=1; i<repeater.count; i++) {
                var otherCheckbox = repeater.itemAt(i)
                otherCheckbox.enabled = false
            }
        }
    }

    Repeater {
        id:     repeater
        model:  fact ? fact.bitmaskStrings : []

        Row{
            HMILabel {
                id: label
                text: "正常"
                states: [
                    State {
                        name: "normal"
                        PropertyChanges {
                            target: label
                            text: "正常"
                        }
                    },
                    State {
                        name: "alarm"
                        PropertyChanges {
                            target: label
                            text :"报警"
                            color: "red"
                        }
                    }
                ]
            }

            HMICheckBox {
                id:         checkbox
                text:       modelData
                checked:    fact.value & fact.bitmaskValues[index]

                onCheckedChanged: {
                    if (checked)
                        label.state = "normal";
                    else
                        label.state = "alarm";
                }

    //            onClicked: {
    //                var i;
    //                var otherCheckbox;
    //                if (checked) {
    ////                    if (firstEntryIsAll && index == 0) {
    ////                        for (i = 1; i < repeater.count; i++) {
    ////                            otherCheckbox = repeater.itemAt(i)
    ////                            fact.value &= ~fact.bitmaskValues[i]
    ////                            otherCheckbox.checked = false
    ////                            otherCheckbox.enabled = false
    ////                        }
    ////                    }
    //                    fact.value |= fact.bitmaskValues[index]
    //                } else {
    ////                    if (firstEntryIsAll && index == 0) {
    ////                        for (i = 1; i < repeater.count; i++) {
    ////                            otherCheckbox = repeater.itemAt(i)
    ////                            otherCheckbox.enabled = true
    ////                        }
    ////                    }
    //                    fact.value &= ~fact.bitmaskValues[index]
    //                }

    //                console.info(fact.value)
    //            }
            }
        }


    }
}
