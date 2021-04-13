

/****************************************************************************
 *
 * (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/
import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.2
import QtQuick.VirtualKeyboard 2.4

Rectangle {
    id: user
    width: 800
    height: 600
    color: "#404be9"

    Image {
        id: image
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
        source: "qrc:/qmlimages/zcwjj3/userPage.jpg"
    }

    Button {
        id: button
        x: 442
        y: 280
        width: 95
        height: 41
        text: qsTr("确定")
        onClicked: {
            if ("2021" === textField.text) {
                globals.showMainUI = true
                element1.visible = true
            } else
                element1.visible = true
        }
    }

    InputPanel {
        id: inputPanel
        z: 99
        x: parent.width - mainWindow.width
        y: mainWindow.height
        width: mainWindow.width

        states: State {
            name: "visible"
            when: inputPanel.active
            PropertyChanges {
                target: inputPanel
                y: mainWindow.height - inputPanel.height - 30
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

    Text {
        id: element1
        x: 285
        y: 201
        width: 233
        height: 55
        color: "#e41005"
        visible: false
        text: "密码错误！"
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 42
    }

    TextField {
        id: textField
        x: 230
        y: 281
        width: 171
        height: 40
        font.pointSize: 12
        readOnly: false
        inputMethodHints: Qt.ImhDigitsOnly // Forces use of virtual numeric keyboard
        placeholderText: qsTr("请输入密码")
        onEditingFinished: {
            if ("2021" === textField.text) {
                globals.showMainUI = true
                element1.visible = true
            } else
                element1.visible = true
        }
    }
}
