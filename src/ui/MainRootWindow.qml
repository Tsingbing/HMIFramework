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


ApplicationWindow {
    id: mainWindow
    visible: true
    width: 800
    height: 600
    title: qsTr("Stack")

    Component.onCompleted: {
        //mainWindow.showFullScreen()

        /* 测试代码
        globals.activeVehicle.forceArm();
        console.info(globals.activeVehicle.id)
        console.info(globals.activeVehicle.supplyVoltageFact.valueString)
        console.log('ScreenTools: Screen.width: ' + Screen.width + ' Screen.height: ' + Screen.height + ' Screen.pixelDensity: ' + Screen.pixelDensity)
        console.info(globals._appFontPointSize.value)
        */
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
    }

    SwipeView {
        id: view
        anchors.fill: parent
        currentIndex: bar.currentIndex

        Component.onCompleted:{
            contentItem.highlightMoveDuration = 100
        }

        Page1Form {

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
        height: 98
        width: parent.width
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


    InputPanel {
        id: inputPanel
        z: 99
        x: (mainWindow.width-inputPanel.width)*0.5
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


