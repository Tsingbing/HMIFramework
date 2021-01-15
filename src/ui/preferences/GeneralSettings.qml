import QtQuick                  2.3
import QtQuick.Controls         1.2
import QtQuick.Controls.Styles  1.4
import QtQuick.Dialogs          1.2
import QtQuick.Layouts          1.2

import HMI                       1.0
import HMI.FactSystem            1.0
import HMI.Controls              1.0
import HMI.ScreenTools           1.0
//import HMI.MultiVehicleManager   1.0
import HMI.Palette               1.0
//import HMI.Controllers           1.0
import HMI.SettingsManager       1.0
import HMI.FactControls          1.0

Rectangle {
    id:                 _root
    color:              hmiPal.window
    anchors.fill:       parent
    anchors.margins:    ScreenTools.defaultFontPixelWidth

    property Fact _appFontPointSize: HMI.settingsManager.appSettings.appFontPointSize
    property real _margins: ScreenTools.defaultFontPixelWidth
    property real _comboFieldWidth:  ScreenTools.defaultFontPixelWidth * 30
    readonly property real _internalWidthRatio: 0.8

    HMIFlickable {
        clip:               true
        anchors.fill:       parent
        contentHeight:      outerItem.height
        contentWidth:       outerItem.width
        ExclusiveGroup { id: panelActionGroup }

        Item {
            id:     outerItem
            width:  Math.max(_root.width, settingsColumn.width)
            height: settingsColumn.height

            ColumnLayout {
                id:                         settingsColumn
                anchors.horizontalCenter:   parent.horizontalCenter

                Item { width: 1; height: _margins }

                HMILabel {
                    id:         miscSectionLabel
                    text:       qsTr("Miscellaneous")
                    visible:    true
                }
                Rectangle {
                    Layout.preferredWidth:  Math.max(comboGrid.width, miscCol.width) + (_margins * 2)
                    Layout.preferredHeight: (pathRow.visible ? pathRow.y + pathRow.height : miscColItem.y + miscColItem.height)  + (_margins * 2)
                    Layout.fillWidth:       true
                    color:                  hmiPal.windowShade
                    visible:                miscSectionLabel.visible

                    Item {
                        id:                 comboGridItem
                        anchors.margins:    _margins
                        anchors.top:        parent.top
                        anchors.left:       parent.left
                        anchors.right:      parent.right
                        height:             comboGrid.height

                        GridLayout {
                            id:                         comboGrid
                            anchors.horizontalCenter:   parent.horizontalCenter
                            columns:                    2

                            HMILabel {
                                text:           qsTr("Language")
                                visible: true
                            }
                            FactComboBox {
                                Layout.preferredWidth:  _comboFieldWidth
                                fact:                   HMI.settingsManager.appSettings.language
                                indexModel:             false
                                visible:                true
                            }

                            HMILabel {
                                text:           qsTr("Color Scheme")
                                visible: true
                            }
                            FactComboBox {
                                Layout.preferredWidth:  _comboFieldWidth
                                fact:                   HMI.settingsManager.appSettings.indoorPalette
                                indexModel:             false
                                visible:                true
                            }

                            HMILabel {
                                text:                           qsTr("UI Scaling")
                                visible:                        true
                                Layout.alignment:               Qt.AlignVCenter
                            }
                            Item {
                                width:                          _comboFieldWidth
                                height:                         baseFontEdit.height * 1.5
                                visible:                        true
                                Layout.alignment:               Qt.AlignVCenter
                                Row {
                                    spacing:                    ScreenTools.defaultFontPixelWidth
                                    anchors.verticalCenter:     parent.verticalCenter
                                    HMIButton {
                                        width:                  height
                                        height:                 baseFontEdit.height * 1.5
                                        text:                   "-"
                                        anchors.verticalCenter: parent.verticalCenter
                                        onClicked: {
                                            if (_appFontPointSize.value > _appFontPointSize.min) {
                                                _appFontPointSize.value = _appFontPointSize.value - 1
                                                _appFontPointSize.valueChanged(_appFontPointSize.value)
                                            }
                                        }
                                    }
                                    HMILabel {
                                        id:                     baseFontEdit
                                        width:                  ScreenTools.defaultFontPixelWidth * 6
                                        text:                   (HMI.settingsManager.appSettings.appFontPointSize.value / ScreenTools.platformFontPointSize * 100).toFixed(0) + "%"
                                        horizontalAlignment:    Text.AlignHCenter
                                        anchors.verticalCenter: parent.verticalCenter
                                    }

                                    HMIButton {
                                        width:                  height
                                        height:                 baseFontEdit.height * 1.5
                                        text:                   "+"
                                        anchors.verticalCenter: parent.verticalCenter
                                        onClicked: {
                                            if (_appFontPointSize.value < _appFontPointSize.max) {
                                                _appFontPointSize.value = _appFontPointSize.value + 1
                                                _appFontPointSize.valueChanged(_appFontPointSize.value)
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }



                    Item {
                        id:                 miscColItem
                        anchors.margins:    _margins
                        anchors.left:       parent.left
                        anchors.right:      parent.right
                        anchors.top:        comboGridItem.bottom
                        anchors.topMargin:  ScreenTools.defaultFontPixelHeight
                        height:             miscCol.height

                        ColumnLayout {
                            id:                         miscCol
                            anchors.horizontalCenter:   parent.horizontalCenter
                            spacing:                    _margins

                            RowLayout {
                                visible: true//HMI.settingsManager.appSettings.batteryPercentRemainingAnnounce.visible

                                HMICheckBox {
                                    id:         announcePercentCheckbox
                                    text:       qsTr("Announce battery lower than")
                                    //checked:    _percentRemainingAnnounce.value !== 0
                                    onClicked: {
                                        if (checked) {
                                            _percentRemainingAnnounce.value = _percentRemainingAnnounce.defaultValueString
                                        } else {
                                            _percentRemainingAnnounce.value = 0
                                        }
                                    }
                                }
                                //                                FactTextField {
                                //                                    fact:                   _percentRemainingAnnounce
                                //                                    Layout.preferredWidth:  _valueFieldWidth
                                //                                    enabled:                announcePercentCheckbox.checked
                                //                                }
                            }
                        }
                    }

                    //-----------------------------------------------------------------
                    //-- Save path
                    RowLayout {
                        id:                 pathRow
                        anchors.margins:    _margins
                        anchors.left:       parent.left
                        //anchors.right:      parent.right
                        anchors.top:        miscColItem.bottom
                        visible:            true

                        HMILabel { text: qsTr("Load/Save Path") }
                        HMITextField {
                            //Layout.fillWidth:   true
                            readOnly:           true
                            text:               "_savePath.rawValue"
                        }
                        HMIButton {
                            text:       qsTr("Browse")
                            onClicked:  savePathBrowseDialog.openForLoad()
                            //                            HMIFileDialog {
                            //                                id:             savePathBrowseDialog
                            //                                title:          qsTr("Choose the location to save/load files")
                            //                                folder:         _savePath.rawValue
                            //                                selectExisting: true
                            //                                selectFolder:   true
                            //                                onAcceptedForLoad: _savePath.rawValue = file
                            //                            }
                        }
                    }
                }

                Item { width: 1; height: _margins }
                Rectangle {
                    Layout.preferredWidth:  brandImageGrid.width + (_margins * 2)
                    Layout.preferredHeight: brandImageGrid.height + (_margins * 2)
                    color:                  hmiPal.windowShade
                    Layout.fillWidth:       true
                    visible:                true

                    GridLayout {
                        id:                 brandImageGrid
                        //                        anchors.margins:    _margins
                        //                        anchors.top:        parent.top
                        //                        anchors.left:       parent.left
                        //                        anchors.right:      parent.right
                        columns:            3

                        anchors.topMargin:          _margins
                        anchors.top:                parent.top
                        Layout.fillWidth:           false
                        anchors.horizontalCenter:   parent.horizontalCenter

                        HMILabel {
                            text:           qsTr("一人我饮酒醉醉醉醉醉醉醉醉醉醉把那乐乐成双对")
                            visible:        true
                        }
                    }
                }

                Item { width: 1; height: _margins }

                FactTextField {
                    //Width:  ScreenTools.defaultFontPixelWidth * 12
                    fact:                   HMI.settingsManager.appSettings.appFontPointSize
                    Layout.alignment:   Qt.AlignHCenter
                    visible:                true
                }

                Item { width: 1; height: _margins * 6 }

                HMILabel {
                    text:               qsTr("%1 Version").arg(HMI.appName)
                    Layout.alignment:   Qt.AlignHCenter
                }
                HMILabel {
                    text:               HMI.hmiVersion
                    Layout.alignment:   Qt.AlignHCenter
                }
            } // settingsColumn
        }
    }
}
