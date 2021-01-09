import QtQuick 2.12
import QtQuick.Controls 2.4
import QtQuick.Dialogs  1.3
import QtQuick.Window 2.12

import HMI 1.0
import HMI.FactSystem 1.0
import HMI.ScreenTools 1.0
import HMI.Controls      1.0
import HMI.SettingsManager 1.0

ApplicationWindow {
    id:  mainWindow
    visible: true
    width: 800
    height: 600
    title: qsTr("Hello World")

    Component.onCompleted: {
        //mainWindow.showFullScreen()

        /* 测试代码
        globals.activeVehicle.forceArm();
        console.info(globals.activeVehicle.id)
        console.info(globals.activeVehicle.supplyVoltageFact.valueString)
        console.log('ScreenTools: Screen.width: ' + Screen.width + ' Screen.height: ' + Screen.height + ' Screen.pixelDensity: ' + Screen.pixelDensity)
       */ console.info(globals._appFontPointSize.value)

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
        property var se1:  HMI.vehicleManager.id
    }

    //-------------------------------------------------------------------------
    /// Main, full window background (Fly View)
    background: Item {
        id:             rootBackground
        anchors.fill:   parent
    }

    //-------------------------------------------------------------------------
    /// Toolbar
     MainToolBar {
        id:         toolbar
        anchors.top:     parent.top
        //anchors.bottom:     parent.bottom
        anchors.left:       parent.left
        anchors.right:      parent.right
        z: 3
        height:     ScreenTools.toolbarHeight
        visible:    true
    }

//    footer: LogReplayStatusBar {
//        visible: QGroundControl.settingsManager.flyViewSettings.showLogReplayStatusBar.rawValue
//    }

    Image {
        id: image
        anchors.rightMargin: 0
        anchors.bottomMargin: 1
        anchors.leftMargin: 0
        anchors.topMargin: -1
        anchors.fill: parent
        source: "qrc:/qmlimages/main_set.jpg"
        fillMode: Image.PreserveAspectFit

        Switch {
            id: element
            x: 280
            y: 345
            text: qsTr("Switch")
        }

        Button {
            id: button
            x: 270
            y: 152
            text: qsTr(globals.fact.valueString)
            onClicked: {
                console.info("button pressed!")
                mainWindow.showAnalyzeTool()
            }
        }

        TextInput {
            id: textInput
            x: 280
            y: 225
            width: 80
            height: 20
            color: "#e9e7e7"
            text: qsTr("Text Input")
            clip: false
            font.pixelSize: 12
        }

        Button {
            id: button1
            x: 0
            y: 552
            text: qsTr("F1")
        }

        Button {
            id: button2
            x: 102
            y: 552
            text: qsTr("F2")
        }
    }

    function showAnalyzeTool(){
        console.info("showAnalyzeTool")
    }

    function showSetupTool(){
        console.info("showSetupTool")
    }

//    MessageDialog {
//        title: "Overwrite?"
//        icon: StandardIcon.Question
//        text: "file.txt already exists.  Replace?"
//        detailedText: "To replace a file means that its existing contents will be lost. " +
//                      "The file that you are copying now will be copied over it instead."
//        standardButtons: StandardButton.Yes | StandardButton.YesToAll |
//                         StandardButton.No | StandardButton.NoToAll | StandardButton.Abort
//        Component.onCompleted: visible = true
//        onYes: console.log("copied")
//        onNo: console.log("didn't copy")
//        onRejected: console.log("aborted")
//    }
}



