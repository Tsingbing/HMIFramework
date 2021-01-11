import QtQuick 2.12
import QtQuick.Controls 2.4
import QtQuick.Dialogs  1.3
import QtQuick.Window 2.12
import QtQuick.Layouts  1.11

import HMI 1.0
import HMI.FactSystem 1.0
import HMI.ScreenTools 1.0
import HMI.Controls      1.0
import HMI.SettingsManager 1.0

ApplicationWindow {
    id: window
    visible: true
    width: 800
    height: 600
    title: qsTr("Stack")
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

    HMILabel {
        font.pointSize:ScreenTools.largeFontPointSize
        text: "hello"
    }

    footer: HMITabBar{
        id: bar
        x: 200
        height: 98
        width: parent.width/2
        background: Rectangle
        {
            color : "transparent"	//transparent:透明
        }
        Component.onCompleted: {
            myModel.append({ "modelText": "消息", "modelColor": "#FFFFFF", "modelColorG": "#148014", "modelSrc": "qrc:/images/Chat_MsgRecord.svg", "modelSrcG": "qrc:/images/Chat_MsgRecordG.svg"})
            myModel.append({ "modelText": "联系人", "modelColor": "#FFFFFF", "modelColorG": "#148014", "modelSrc": "qrc:/images/Chat_FriendManager.svg", "modelSrcG": "qrc:/images/Chat_FriendManagerG.svg"})
            myModel.append({ "modelText": "发现", "modelColor": "#FFFFFF", "modelColorG": "#148014", "modelSrc": "qrc:/images/Mobile_Find.svg", "modelSrcG": "qrc:/images/Mobile_FindG.svg"})
            myModel.append({ "modelText": "我", "modelColor": "#FFFFFF", "modelColorG": "#148014", "modelSrc": "qrc:/images/Main_P2PChat.svg", "modelSrcG": "qrc:/images/Main_P2PChatG.svg"})
        }
    }
}


