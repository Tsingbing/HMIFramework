/****************************************************************************
 *
 * (c) 2009-2019 HMI PROJECT <http://www.HMI.org>
 *
 * HMI is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 * @file
 *   @author Gus Grubba <gus@auterion.com>
 */

import QtQuick                      2.11
import QtQuick.Controls             2.4
import QtQuick.Layouts              1.11

import HMI.Controls      1.0
import HMI.Palette       1.0
import HMI.ScreenTools   1.0

ComboBox {
    id:         control
    padding:    ScreenTools.comboBoxPadding

    property string labelText:  qsTr("Options")

    signal itemClicked(int index)

    property var    _controlHMIPal: HMIPalette { colorGroupEnabled: enabled }
    property bool   _flashChecked
    property string _flashText
    property bool   _showFlash:     false

    Component.onCompleted: indicator.color = Qt.binding(function() { return _controlHMIPal.text })

    background: Rectangle {
        implicitWidth:                  ScreenTools.implicitComboBoxWidth
        implicitHeight:                 ScreenTools.implicitComboBoxHeight
        color:                          _controlHMIPal.window
        border.width:                   enabled ? 1 : 0
        border.color:                   "#999"
    }

    /*! Adding the Combobox list item to the theme.  */

    delegate: ItemDelegate {
        implicitHeight: modelData.visible ?
                            (Math.max(background ? background.implicitHeight : 0, Math.max(contentItem.implicitHeight, indicator ? indicator.implicitHeight : 0) + topPadding + bottomPadding)) :
                            0
        width:      control.width
        checkable:  true
        enabled:    modelData.enabled
        text:       modelData.text

        property var _checkedValue:     1
        property var _uncheckedValue:   0
        property var _itemHMIPal:       HMIPalette { colorGroupEnabled: enabled }
        property var _control:          control

        Binding on checked { value: modelData.fact ?
                                         (modelData.fact.typeIsBool ? (modelData.fact.value === false ? Qt.Unchecked : Qt.Checked) : (modelData.fact.value === 0 ? Qt.Unchecked : Qt.Checked)) :
                                         modelData.checked }

        contentItem: RowLayout {
            spacing: ScreenTools.defaultFontPixelWidth

            Rectangle {
                height:         ScreenTools.defaultFontPixelHeight
                width:          height
                border.color:   _itemHMIPal.buttonText
                border.width:   1
                color:          _itemHMIPal.button

                HMIColoredImage {
                    anchors.centerIn:   parent
                    width:              parent.width * 0.75
                    height:             width
                    source:             "/qmlimages/checkbox-check.svg"
                    color:              _itemHMIPal.buttonText
                    mipmap:             true
                    fillMode:           Image.PreserveAspectFit
                    sourceSize.height:  height
                    visible:            checked
                }
            }

            Text {
                text:   modelData.text
                color:  _itemHMIPal.buttonText
            }

        }

        background: Rectangle {
            color: _controlHMIPal.button
        }

        onClicked: {
            if (modelData.fact) {
                modelData.fact.value = (checked ? _checkedValue : _uncheckedValue)
            } else {
                itemClicked(index)
            }
            _control._flashChecked = checked
            _control._flashText = text
            _control._showFlash = true
            _control.popup.close()
        }
    }

    /*! This defines the label of the button.  */
    contentItem: Item {
        implicitWidth:                  _showFlash ? flash.implicitWidth : text.implicitWidth
        implicitHeight:                 _showFlash ? flash.implicitHeight : text.implicitHeight

        HMILabel {
            id:                         text
            anchors.verticalCenter:     parent.verticalCenter
            text:                       labelText
            color:                      _controlHMIPal.text
            visible:                    !_showFlash
        }

        RowLayout {
            id:                     flash
            anchors.verticalCenter: parent.verticalCenter
            spacing:                ScreenTools.defaultFontPixelWidth
            visible:                _showFlash

            onVisibleChanged: {
                if (visible) {
                    flashTimer.restart()
                }
            }

            Timer {
                id:             flashTimer
                interval:       1500
                repeat:         false
                running:        false
                onTriggered:    _showFlash = false
            }

            Rectangle {
                height:         ScreenTools.defaultFontPixelHeight
                width:          height
                border.color:   _controlHMIPal.buttonText
                border.width:   1
                color:          _controlHMIPal.window

                HMIColoredImage {
                    anchors.centerIn:   parent
                    width:              parent.width * 0.75
                    height:             width
                    source:             "/qmlimages/checkbox-check.svg"
                    color:              _controlHMIPal.text
                    mipmap:             true
                    fillMode:           Image.PreserveAspectFit
                    sourceSize.height:  height
                    visible:            _flashChecked
                }
            }

            Text {
                text:   _flashText
                color:  _controlHMIPal.buttonText
            }

        }
    }
}
