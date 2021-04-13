import QtQuick 2.12
import QtQuick.Controls 2.4
import QtQuick.Dialogs  1.3
import QtQuick.Window 2.12
import QtQuick.Layouts  1.11
import QtQuick.VirtualKeyboard 2.4

import HMI 1.0
import HMI.FactSystem 1.0
import HMI.ScreenTools 1.0
import HMI.Controls      1.0
import HMI.SettingsManager 1.0
import HMI.Palette 1.0

ApplicationWindow {
    id: mainWindow
    visible: true
    width: 800
    height: 600
    title: qsTr("Stack")
    readonly property real      defaultTextHeight:          ScreenTools.defaultFontPixelHeight
    /// Default color palette used throughout the UI
    HMIPalette { id: hmiPal; colorGroupEnabled: true }

    Component.onCompleted: {
        //mainWindow.showFullScreen()

        /* 测试代码
        globals.activeVehicle.forceArm();
        console.info(globals.activeVehicle.id)
        console.info(globals.activeVehicle.supplyVoltageFact.valueString)
        console.log('ScreenTools: Screen.width: ' + Screen.width + ' Screen.height: ' + Screen.height + ' Screen.pixelDensity: ' + Screen.pixelDensity)
        console.info(globals._appFontPointSize.value)
        */

        //mainWindow.showMessageDialog(qsTr("Log Replay"), qsTr("xxxxx"))
    }

    //-------------------------------------------------------------------------
    //-- Global Scope Variables
    QtObject {
        id: globals

        readonly property var activeVehicle : HMI.vehicleManager.activeVehicle
        property Fact fact: activeVehicle.supplyVoltageFact
        property Fact fact1: activeVehicle.rotatingSpeedFact
        property Fact _appFontPointSize: HMI.settingsManager.appSettings.appFontPointSize
        property bool se:  ScreenTools.isMobile
        //property var se1:  HMI.vehicleManager.id
        property string se1:  "HMI.vehicleManager.id"
        property bool showMainUI: false
    }

    UserInput {
        id: _user
        anchors.fill: parent
    }

    SwipeView {
        id: view
        anchors.fill: parent
        currentIndex: bar.currentIndex
        visible: globals.showMainUI
        Component.onCompleted:{
            contentItem.highlightMoveDuration = 100
        }

        Page11Form {
        }
        Page2Form {
        }
        Page3Form {
        }
        Page4Form {
        }

    }

    footer: HMITabBar{
        id: bar
        //x: 200
        height: 60
        width: parent.width
        visible: globals.showMainUI
        background: Rectangle
        {
            color : "transparent"	//transparent:透明
        }
        Component.onCompleted: {
            myModel.append({ "modelText": " ", "modelColor": "#FFFFFF", "modelColorG": "#148014", "modelSrc": "qrc:/images/Chat_MsgRecord.svg", "modelSrcG": "qrc:/images/Chat_MsgRecordG.svg"})
            myModel.append({ "modelText": " ", "modelColor": "#FFFFFF", "modelColorG": "#148014", "modelSrc": "qrc:/images/Chat_FriendManager.svg", "modelSrcG": "qrc:/images/Chat_FriendManagerG.svg"})
            myModel.append({ "modelText": " ", "modelColor": "#FFFFFF", "modelColorG": "#148014", "modelSrc": "qrc:/images/Mobile_Find.svg", "modelSrcG": "qrc:/images/Mobile_FindG.svg"})
            myModel.append({ "modelText": " ", "modelColor": "#FFFFFF", "modelColorG": "#148014", "modelSrc": "qrc:/images/Main_P2PChat.svg", "modelSrcG": "qrc:/images/Main_P2PChatG.svg"})
        }
    }

    //-------------------------------------------------------------------------
       //-- Global simple message dialog

       function showMessageDialog(title, text) {
           if(simpleMessageDialog.visible) {
               simpleMessageDialog.close()
           }
           simpleMessageDialog.title = title
           simpleMessageDialog.text  = text
           simpleMessageDialog.open()

       }

       /// Saves main window position and size
       MainWindowSavedState {
           window: mainWindow
       }

       MessageDialog {
           id:                 simpleMessageDialog
           standardButtons:    StandardButton.Ok
           modality:           Qt.ApplicationModal
           visible:            false
       }


    //-------------------------------------------------------------------------
    //-- Global complex dialog

    /// Shows a HMIViewDialogContainer based dialog
    ///     @param component The dialog contents
    ///     @param title Title for dialog
    ///     @param charWidth Width of dialog in characters
    ///     @param buttons Buttons to show in dialog using StandardButton enum

    readonly property int showDialogFullWidth:      -1  ///< Use for full width dialog
    readonly property int showDialogDefaultWidth:   40  ///< Use for default dialog width

    function showComponentDialog(component, title, charWidth, buttons) {
        if (mainWindowDialog.visible) {
            console.warn(("showComponentDialog called while dialog is already visible"))
            return
        }
        var dialogWidth = charWidth === showDialogFullWidth ? mainWindow.width : ScreenTools.defaultFontPixelWidth * charWidth
        mainWindowDialog.width = dialogWidth
        mainWindowDialog.dialogComponent = component
        mainWindowDialog.dialogTitle = title
        mainWindowDialog.dialogButtons = buttons
        //mainWindow.pushPreventViewSwitch()
        mainWindowDialog.open()
        if (buttons & StandardButton.Cancel || buttons & StandardButton.Close || buttons & StandardButton.Discard || buttons & StandardButton.Abort || buttons & StandardButton.Ignore) {
            mainWindowDialog.closePolicy = Popup.NoAutoClose;
            mainWindowDialog.interactive = false;
        } else {
            mainWindowDialog.closePolicy = Popup.CloseOnEscape | Popup.CloseOnPressOutside;
            mainWindowDialog.interactive = true;
        }
    }

    Drawer {
        id:             mainWindowDialog
        y:              0
        height:         mainWindow.height /*- mainWindow.header.height*/
        edge:           Qt.RightEdge
        interactive:    false

        background: Rectangle {
            color:  hmiPal.windowShadeDark
        }
        property var    dialogComponent: null
        property var    dialogButtons: null
        property string dialogTitle: ""
        Loader {
            id:             dlgLoader
            anchors.fill:   parent
            onLoaded: {
                item.setupDialogButtons()
            }
        }
        onOpened: {
            dlgLoader.source = "HMI/Controls/HMIViewDialogContainer.qml"
        }
        onClosed: {
            //console.log("View switch ok")
            //mainWindow.popPreventViewSwitch()
            dlgLoader.source = ""
        }

        InputPanel {
            id: inputPanel
            z: 99
            x: parent.width - mainWindow.width
            y: mainWindow.height
            width:mainWindow.width

            states: State {
                name: "visible"
                when: inputPanel.active
                PropertyChanges {
                    target: inputPanel
                    y: mainWindow.height - inputPanel.height
                }
            }
            transitions: Transition {
                from: ""
                to: "visible"
                reversible: true
                //设置键盘弹出效果
                ParallelAnimation {
                    NumberAnimation {
                        properties: "y"
                        //过渡时间
                        duration: 100
                        //弹出效果
                        easing.type: Easing.InOutQuad
                    }
                }
            }
        }
    }
}


