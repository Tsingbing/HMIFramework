import QtQuick                  2.3
import QtQuick.Controls         1.2
import QtQuick.Controls.Styles  1.4
import QtQuick.Dialogs          1.2
import QtQuick.Layouts          1.2

import HMI                       1.0
import HMI.FactSystem            1.0
//import HMI.FactControls          1.0
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

                HMILabel {
                    id:         unitsSectionLabel
                    text:       qsTr("Units")
                    visible:    true
                }
                Rectangle {
                    Layout.preferredHeight: unitsGrid.height + (_margins * 2)
                    Layout.preferredWidth:  unitsGrid.width + (_margins * 2)
                    color:                  hmiPal.windowShade
                    visible:                true
                    Layout.fillWidth:       true

                    GridLayout {
                        id:                         unitsGrid
                        anchors.topMargin:          _margins
                        anchors.top:                parent.top
                        Layout.fillWidth:           false
                        anchors.horizontalCenter:   parent.horizontalCenter
                        flow:                       GridLayout.TopToBottom
                        rows:                       4

                        Repeater {
                            model: [ qsTr("Distance"), qsTr("Area"), qsTr("Speed"), qsTr("Temperature") ]
                            HMILabel { text: modelData }
                        }
                        //                        Repeater {
                        //                            model:  [ QGroundControl.settingsManager.unitsSettings.distanceUnits, QGroundControl.settingsManager.unitsSettings.areaUnits, QGroundControl.settingsManager.unitsSettings.speedUnits, QGroundControl.settingsManager.unitsSettings.temperatureUnits ]
                        //                            FactComboBox {
                        //                                Layout.preferredWidth:  _comboFieldWidth
                        //                                fact:                   modelData
                        //                                indexModel:             false
                        //                            }
                        //                        }
                    }
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

                        FactTextField {
                            //Width:  ScreenTools.defaultFontPixelWidth * 12
                            fact:                   HMI.settingsManager.appSettings.appFontPointSize
                            visible:                true
                        }
                        Text {

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
                            text:           qsTr("Indoor Imssssssssssssssssssssssssssssssssage")
                            visible:        true
                        }
                        //                        HMITextField {
                        //                            readOnly:           true
                        //                            Layout.fillWidth:   true
                        //                            text:               "_userBrandImageIndoor.valueString.replace"
                        //                        }
                        //                        HMIButton {
                        //                            text:       qsTr("Browse")
                        //                            onClicked:  userBrandImageIndoorBrowseDialog.openForLoad()

                        //                        }

                        //                        HMILabel {
                        //                            text:       qsTr("Outdoor Image")
                        //                            visible:    true
                        //                        }
                        //                        HMITextField {
                        //                            readOnly:           true
                        //                            Layout.fillWidth:   true
                        //                            text:               " _userBrandImageOutdoor.valueString.replace"
                        //                        }
                        //                        HMIButton {
                        //                            text:       qsTr("Browse")
                        //                            onClicked:  userBrandImageOutdoorBrowseDialog.openForLoad()

                        //                        }
                        //                        HMIButton {
                        //                            text:               qsTr("Reset Default Brand Image")
                        //                            Layout.columnSpan:  3
                        //                            Layout.alignment:   Qt.AlignHCenter
                        //                            onClicked:  {
                        //                                _userBrandImageIndoor.rawValue = ""
                        //                                _userBrandImageOutdoor.rawValue = ""
                        //                            }
                        //                        }
                    }
                }

                Item { width: 1; height: _margins }

                HMILabel {
                    text:               qsTr("%1 Version").arg(HMI.appName)
                    Layout.alignment:   Qt.AlignHCenter
                }
                HMILabel {
                    text:               "HMI.qgcVersion"
                    Layout.alignment:   Qt.AlignHCenter
                }
            } // settingsColumn
        }
    }
}
