import QtQuick 2.12
import QtQuick.Controls 2.4
import QtQuick.Dialogs  1.3
import QtQuick.Window 2.12

import HMI 1.0
import HMI.FactSystem 1.0
import HMI.ScreenTools 1.0

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
        console.info(globals.fact1.valueString)
        */
        console.log('ScreenTools: Screen.width: ' + Screen.width + ' Screen.height: ' + Screen.height + ' Screen.pixelDensity: ' + Screen.pixelDensity)

    }
    //-------------------------------------------------------------------------
    //-- Global Scope Variables
    QtObject {
        id: globals

        readonly property var activeVehicle : HMI.vehicleManager.activeVehicle
        property Fact fact: activeVehicle.supplyVoltageFact
        property Fact fact1: activeVehicle.rotatingSpeedFact
        property bool se:  ScreenTools.isMobile

    }

    Image {
        id: image
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



