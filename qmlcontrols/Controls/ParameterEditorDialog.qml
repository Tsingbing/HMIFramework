/****************************************************************************
 *
 * (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * HMI is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

import QtQuick          2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts  1.2

import HMI               1.0
import HMI.Controls      1.0
import HMI.Palette       1.0
//import HMI.Controllers   1.0
import HMI.FactSystem    1.0
import HMI.FactControls  1.0
import HMI.ScreenTools   1.0

HMIViewDialog {
    id:     root
    focus:  true

    property Fact   fact
    property bool   showRCToParam:  false
    property bool   validate:       false
    property string validateValue
    property bool   setFocus:       true    ///< true: focus is set to text field on display, false: focus not set (works around strange virtual keyboard bug with FactValueSlider

    signal valueChanged

    property real   _editFieldWidth:            ScreenTools.defaultFontPixelWidth * 20
    property bool   _longDescriptionAvailable:  fact.longDescription != ""
    //property bool   _editingParameter:          fact.componentId != 0
    property bool   _allowForceSave:            false//HMI.corePlugin.showAdvancedUI || !_editingParameter
    property bool   _allowDefaultReset:         fact.defaultValueAvailable

    //ParameterEditorController { id: controller; }

    HMIPalette { id: hmiPal; colorGroupEnabled: true }

    function accept() {
/*        if (bitmaskColumn.visible && !manualEntry.checked) {
            fact.value = bitmaskValue();
            fact.valueChanged(fact.value)
            valueChanged()
            hideDialog();
        } else*/
        if (factCombo.visible && !manualEntry.checked) {
            fact.enumIndex = factCombo.currentIndex
            valueChanged()
            hideDialog()
        } else {
            var errorString = fact.validate(valueField.text, forceSave.checked)
            if (errorString === "") {
                fact.value = valueField.text
                fact.valueChanged(fact.value)
                valueChanged()
                hideDialog()
            } else {
                validationError.text = errorString
                if (_allowForceSave) {
                    forceSave.visible = true
                }
            }
        }
    }

    function reject() {
        fact.valueChanged(fact.value)
        hideDialog();
    }

    function bitmaskValue() {
        var value = 0;
        for (var i = 0; i < fact.bitmaskValues.length; ++i) {
            var checkbox = bitmaskRepeater.itemAt(i)
            if (checkbox.checked) {
                value |= fact.bitmaskValues[i];
            }
        }
        return value
    }

    Component.onCompleted: {
        if (validate) {
            validationError.text = fact.validate(validateValue, false /* convertOnly */)
            if (_allowForceSave) {
                forceSave.visible = true
            }
        }
    }

    HMIFlickable {
        id:                 flickable
        anchors.fill:       parent
        contentHeight:      _column.y + _column.height
        flickableDirection: Flickable.VerticalFlick

        Column {
            id:             _column
            spacing:        defaultTextHeight
            anchors.left:   parent.left
            anchors.right:  parent.right

            HMILabel {
                id:         validationError
                width:      parent.width
                wrapMode:   Text.WordWrap
                color:      hmiPal.warningText
            }

            RowLayout {
                spacing:        ScreenTools.defaultFontPixelWidth
                anchors.left:   parent.left
                anchors.right:  parent.right

                HMITextField {
                    id:                 valueField
                    text:               validate ? validateValue : fact.valueString
                    visible:            fact.enumStrings.length === 0 || validate || manualEntry.checked
                    unitsLabel:         fact.units
                    showUnits:          fact.units != ""
                    Layout.fillWidth:   true
                    focus:              setFocus
                    inputMethodHints:   Qt.ImhDigitsOnly  // Forces use of virtual numeric keyboard
                }

                HMIButton {
                    visible:    _allowDefaultReset
                    text:       qsTr("Reset to default")

                    onClicked: {
                        fact.value = fact.defaultValue
                        fact.valueChanged(fact.value)
                        hideDialog()
                    }
                }
            }

            HMIComboBox {
                id:             factCombo
                anchors.left:   parent.left
                anchors.right:  parent.right
                visible:        _showCombo
                model:          fact.enumStrings

                property bool _showCombo: fact.enumStrings.length !== 0 && fact.bitmaskStrings.length === 0 && !validate

                Component.onCompleted: {
                    // We can't bind directly to fact.enumIndex since that would add an unknown value
                    // if there are no enum strings.
                    if (_showCombo) {
                        currentIndex = fact.enumIndex
                    }
                }

                onCurrentIndexChanged: {
                    if (currentIndex >=0 && currentIndex < model.length) {
                        valueField.text = fact.enumValues[currentIndex]
                    }
                }
            }

//            Column {
//                id:         bitmaskColumn
//                spacing:    ScreenTools.defaultFontPixelHeight / 2
//                visible:    fact.bitmaskStrings.length > 0 ? true : false;

//                Repeater {
//                    id:     bitmaskRepeater
//                    model:  fact.bitmaskStrings

//                    delegate : HMICheckBox {
//                        text : modelData
//                        checked : fact.value & fact.bitmaskValues[index]

//                        onClicked: {
//                            valueField.text = bitmaskValue()
//                        }
//                    }
//                }
//            }

            HMILabel {
                width:      parent.width
                wrapMode:   Text.WordWrap
                visible:    !longDescriptionLabel.visible
                text:       fact.shortDescription
            }

            HMILabel {
                id:         longDescriptionLabel
                width:      parent.width
                wrapMode:   Text.WordWrap
                visible:    fact.longDescription != ""
                text:       fact.longDescription
            }

            Row {
                spacing: ScreenTools.defaultFontPixelWidth

                HMILabel {
                    id:         minValueDisplay
                    text:       qsTr("Min: ") + fact.minString
                    visible:    !fact.minIsDefaultForType
                }

                HMILabel {
                    text:       qsTr("Max: ") + fact.maxString
                    visible:    !fact.maxIsDefaultForType
                }

                HMILabel {
                    text:       qsTr("Default: ") + fact.defaultValueString
                    visible:    _allowDefaultReset
                }
            }

            HMILabel {
                text:       qsTr("Parameter name: ") + fact.name
                visible:    true // > 0 means it's a parameter fact
            }

//            HMILabel {
//                visible:    fact.vehicleRebootRequired
//                text:       "Vehicle reboot required after change"
//            }

//            HMILabel {
//                visible:    fact.qgcRebootRequired
//                text:       "Application restart required after change"
//            }

//            HMILabel {
//                width:      parent.width
//                wrapMode:   Text.WordWrap
//                text:       qsTr("Warning: Modifying values while vehicle is in flight can lead to vehicle instability and possible vehicle loss. ") +
//                            qsTr("Make sure you know what you are doing and double-check your values before Save!")
//                visible:    fact.componentId != -1
//            }

            HMICheckBox {
                id:         forceSave
                visible:    false
                text:       qsTr("Force save (dangerous!)")
            }

            Row {
                width:      parent.width
                spacing:    ScreenTools.defaultFontPixelWidth / 2
                visible:    false//showRCToParam || factCombo.visible || bitmaskColumn.visible

                Rectangle {
                    height: 1
                    width:  ScreenTools.defaultFontPixelWidth * 5
                    color:  hmiPal.text
                    anchors.verticalCenter: _advanced.verticalCenter
                }

                HMICheckBox {
                    id:     _advanced
                    text:   qsTr("Advanced settings")
                }

                Rectangle {
                    height: 1
                    width:  ScreenTools.defaultFontPixelWidth * 5
                    color:  hmiPal.text
                    anchors.verticalCenter: _advanced.verticalCenter
                }
            }

            // Checkbox to allow manual entry of enumerated or bitmask parameters
//            HMICheckBox {
//                id:         manualEntry
//                visible:    _advanced.checked && (factCombo.visible || bitmaskColumn.visible)
//                text:       qsTr("Manual Entry")

//                onClicked: {
//                    valueField.text = fact.valueString
//                }
//            }

//            HMIButton {
//                text:           qsTr("Set RC to Param...")
//                width:          _editFieldWidth
//                visible:        _advanced.checked && !validate && showRCToParam
//                onClicked:      controller.setRCToParam(fact.name)
//            }
        } // Column
    }
} // HMIViewDialog
