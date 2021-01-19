import QtQuick 2.12
import QtQuick.Controls 2.4
import QtQuick.Dialogs  1.3
import QtQuick.Window 2.12
import QtQuick.VirtualKeyboard 2.4

import HMI 1.0
import HMI.Palette 1.0
import HMI.FactSystem 1.0
import HMI.ScreenTools 1.0
import HMI.Controls      1.0
import HMI.SettingsManager 1.0

ApplicationWindow {
    id:  mainWindow
    visible: true
    width: 800
    height: 600
    title: qsTr("HMI")

    //-------------------------------------------------------------------------
    //-- Global Scope Variables
    QtObject {
        id: globals

        readonly property var activeVehicle : HMI.vehicleManager.activeVehicle
        property Fact fact: activeVehicle.supplyVoltageFact
        property Fact fact1: activeVehicle.rotatingSpeedFact
        property Fact languageFact: HMI.settingsManager.appSettings.language
        property Fact _appFontPointSize: HMI.settingsManager.appSettings.appFontPointSize
        property bool se:  ScreenTools.isMobile
        property var se1:  HMI.vehicleManager.id
    }

    Component.onCompleted: {
        //console.info(globals._appFontPointSize.value)
        //console.info(globals.languageFact.enumStrings)
        //showMessage("message")
        // showMessage("message1")
    }

    property var                _rgPreventViewSwitch:       [ false ]
    property bool headerShow:  false
    readonly property real      _topBottomMargins:          ScreenTools.defaultFontPixelHeight * 0.5
    //readonly property string    _mainToolbar:               HMI.corePlugin.options.mainToolbarUrl
    //readonly property string    _planToolbar:               HMI.corePlugin.options.planToolbarUrl

    //-------------------------------------------------------------------------
    //-- Global Scope Variables

    /// Current active Vehicle
    property var                activeVehicle:              HMI.vehicleManager.activeVehicle
    /// Indicates communication with vehicle is list (no heartbeats)
    //property bool               communicationLost:          activeVehicle ? activeVehicle.connectionLost : false
    //property string             formatedMessage:            activeVehicle ? activeVehicle.formatedMessage : ""
    /// Indicates usable height between toolbar and footer
    property real               availableHeight:            mainWindow.height - mainWindow.footer.height

    property var                currentPlanMissionItem:     planMasterControllerPlan ? planMasterControllerPlan.missionController.currentPlanViewItem : null
    property var                planMasterControllerPlan:   null
    property var                planMasterControllerView:   null
    property var                flightDisplayMap:           null

    readonly property string    navButtonWidth:             ScreenTools.defaultFontPixelWidth * 24
    readonly property real      defaultTextHeight:          ScreenTools.defaultFontPixelHeight
    readonly property real      defaultTextWidth:           ScreenTools.defaultFontPixelWidth

    /// Default color palette used throughout the UI
    HMIPalette { id: hmiPal; colorGroupEnabled: true }

    //-------------------------------------------------------------------------
    //-- Global Scope Functions

    /// Prevent view switching
    function pushPreventViewSwitch() {
        _rgPreventViewSwitch.push(true)
    }

    /// Allow view switching
    function popPreventViewSwitch() {
        if (_rgPreventViewSwitch.length == 1) {
            console.warn("mainWindow.popPreventViewSwitch called when nothing pushed")
            return
        }
        _rgPreventViewSwitch.pop()
    }

    /// @return true: View switches are not currently allowed
    function preventViewSwitch() {
        return _rgPreventViewSwitch[_rgPreventViewSwitch.length - 1]
    }

    function viewSwitch() {
        settingsWindow.visible  = false
        setupWindow.visible     = false
        analyzeWindow.visible   = false
        flyView.visible  = false
        planView.visible  = false
    }

    function showFlyView() {
        viewSwitch()
        headerShow= true
        flyView.visible = true
    }

    function showPlanView() {
        viewSwitch()
        headerShow = false
        planView.visible = true
    }

    function showAnalyzeView() {
        viewSwitch()
        headerShow = false
        analyzeWindow.visible = true
    }

    function showSetupView() {
        viewSwitch()
        headerShow = false
        setupWindow.visible = true
    }

    function showSettingsView() {
        viewSwitch()
        headerShow = false
        settingsWindow.visible = true
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
        mainWindow.pushPreventViewSwitch()
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
            mainWindow.popPreventViewSwitch()
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

    //-------------------------------------------------------------------------
    /// Main, full window background
    background: Item {
        id:             rootBackground
        anchors.fill:   parent

        Rectangle {
            anchors.fill:   parent
            color: hmiPal.globalTheme === HMIPalette.Light ? "#FFFFFF" : "#212529"
        }
    }


    //-------------------------------------------------------------------------
    /// Toolbar

    header:ToolBar {
        id : indicatorBar
        width:          parent.width/2
        height:         ScreenTools.toolbarHeight
        anchors.right:  parent.right
        anchors.rightMargin: 15
        visible:        headerShow
        background:     Rectangle {
            color:"transparent" //hmiPal.globalTheme === HMIPalette.Light ? "#FFFFFF" : "#212529"
        }
        Loader {
            id:             indicators
            anchors.fill:   parent
            source:         "qrc:/toolbar/MainToolBarIndicators.qml"
        }
    }
    footer: ToolBar {
        x: 200
        width:          parent.width/2
        height:         ScreenTools.toolbarHeight * 1.2
        visible:        true
        background:     Rectangle {
            color:"transparent"// hmiPal.globalTheme === HMIPalette.Light ? "#FFFFFF" : "#212529"
        }
        Loader {
            id:             toolbar
            anchors.fill:   parent
            source:         "qrc:/toolbar/MainToolBar.qml"
        }
    }

    //-------------------------------------------------------------------------
    /// fly View
    Loader {
        id:             flyView
        //anchors.fill:   parent
        anchors.top:    header.top
        anchors.bottom: footer.bottom
        visible:        false
        source:         "FlyView.qml"
    }
    //-------------------------------------------------------------------------
    /// Plan View
    Loader {
        id:             planView
        anchors.fill:   parent
        visible:        false
        source:         "PlanView.qml"
    }
    //-------------------------------------------------------------------------
    /// Settings
    Loader {
        id:             settingsWindow
        anchors.fill:   parent
        visible:        false
        source:         "AppSettings.qml"
    }

    //-------------------------------------------------------------------------
    /// Setup
    Loader {
        id:             setupWindow
        anchors.fill:   parent
        visible:        false
        //source:         "SetupView.qml"
        source:         "AppSettings.qml"
    }

    //-------------------------------------------------------------------------
    /// Analyze
    Loader {
        id:             analyzeWindow
        //anchors.fill:   parent
        height:         mainWindow.height
        visible:        false
        source:         "AnalyzeView.qml"
    }


    //-------------------------------------------------------------------------
    //-- System Messages

    property var    _messageQueue:      []
    property string _systemMessage:     ""

    function showMessage(message) {
        //vehicleMessageArea.close()
        if(systemMessageArea.visible/* || QGroundControl.videoManager.fullScreen*/) {
            _messageQueue.push(message)
        } else {
            _systemMessage = message
            systemMessageArea.open()
        }
    }

//    function showMissingParameterOverlay(missingParamName) {
//        showError(qsTr("Parameters missing: %1").arg(missingParamName))
//    }

//    function showFactError(errorMsg) {
//        showError(qsTr("Fact error: %1").arg(errorMsg))
//    }

    Popup {
        id:                 systemMessageArea
        y:                  ScreenTools.defaultFontPixelHeight * 5
        x:                  Math.round((mainWindow.width - width) * 0.5)
        width:              mainWindow.width  * 0.55
        height:             ScreenTools.defaultFontPixelHeight * 6
        modal:              false
        focus:              true
        closePolicy:        Popup.CloseOnEscape

        background: Rectangle {
            anchors.fill:   parent
            color:          hmiPal.alertBackground
            radius:         ScreenTools.defaultFontPixelHeight * 0.5
            border.color:   hmiPal.alertBorder
            border.width:   2
        }

        onOpened: {
            systemMessageText.text = mainWindow._systemMessage
        }

        onClosed: {
            //-- Are there messages in the waiting queue?
            if(mainWindow._messageQueue.length) {
                mainWindow._systemMessage = ""
                //-- Show all messages in queue
                for (var i = 0; i < mainWindow._messageQueue.length; i++) {
                    var text = mainWindow._messageQueue[i]
                    if(i) mainWindow._systemMessage += "<br>"
                    mainWindow._systemMessage += text
                }
                //-- Clear it
                mainWindow._messageQueue = []
                systemMessageArea.open()
            } else {
                mainWindow._systemMessage = ""
            }
        }

        Flickable {
            id:                 systemMessageFlick
            anchors.margins:    ScreenTools.defaultFontPixelHeight * 0.5
            anchors.fill:       parent
            contentHeight:      systemMessageText.height
            contentWidth:       systemMessageText.width
            boundsBehavior:     Flickable.StopAtBounds
            pixelAligned:       true
            clip:               true
            TextEdit {
                id:             systemMessageText
                width:          systemMessageArea.width - systemMessageClose.width - (ScreenTools.defaultFontPixelHeight * 2)
                anchors.centerIn: parent
                readOnly:       true
                textFormat:     TextEdit.RichText
                font.pointSize: ScreenTools.defaultFontPointSize
                font.family:    ScreenTools.demiboldFontFamily
                wrapMode:       TextEdit.WordWrap
                color:          hmiPal.alertText
            }
        }

        //-- Dismiss Critical Message
        HMIColoredImage {
            id:                 systemMessageClose
            anchors.margins:    ScreenTools.defaultFontPixelHeight * 0.5
            anchors.top:        parent.top
            anchors.right:      parent.right
            width:              ScreenTools.isMobile ? ScreenTools.defaultFontPixelHeight * 1.5 : ScreenTools.defaultFontPixelHeight
            height:             width
            sourceSize.height:  width
            source:             "/res/XDelete.svg"
            fillMode:           Image.PreserveAspectFit
            color:              hmiPal.alertText
            MouseArea {
                anchors.fill:       parent
                anchors.margins:    -ScreenTools.defaultFontPixelHeight
                onClicked: {
                    systemMessageArea.close()
                }
            }
        }

        //-- More text below indicator
        HMIColoredImage {
            anchors.margins:    ScreenTools.defaultFontPixelHeight * 0.5
            anchors.bottom:     parent.bottom
            anchors.right:      parent.right
            width:              ScreenTools.isMobile ? ScreenTools.defaultFontPixelHeight * 1.5 : ScreenTools.defaultFontPixelHeight
            height:             width
            sourceSize.height:  width
            source:             "/res/ArrowDown.svg"
            fillMode:           Image.PreserveAspectFit
            visible:            systemMessageText.lineCount > 5
            color:              hmiPal.alertText
            MouseArea {
                anchors.fill:   parent
                onClicked: {
                    systemMessageFlick.flick(0,-500)
                }
            }
        }
    }

    //-------------------------------------------------------------------------
    //-- Indicator Popups

    function showPopUp(item, dropItem) {
        indicatorDropdown.currentIndicator = dropItem
        indicatorDropdown.currentItem = item
        indicatorDropdown.open()
    }

    function hidePopUp() {
        indicatorDropdown.close()
        indicatorDropdown.currentItem = null
        indicatorDropdown.currentIndicator = null
    }

    Popup {
        id:             indicatorDropdown
        y:              ScreenTools.defaultFontPixelHeight
        modal:          true
        focus:          true
        closePolicy:    Popup.CloseOnEscape | Popup.CloseOnPressOutside
        property var    currentItem:        null
        property var    currentIndicator:   null
        background: Rectangle {
            width:  loader.width
            height: loader.height
            color:  Qt.rgba(0,0,0,0)
        }
        Loader {
            id:             loader
            onLoaded: {
                var centerX = mainWindow.contentItem.mapFromItem(indicatorDropdown.currentItem, 0, 0).x - (loader.width * 0.5)
                if((centerX + indicatorDropdown.width) > (mainWindow.width - ScreenTools.defaultFontPixelWidth)) {
                    centerX = mainWindow.width - indicatorDropdown.width - ScreenTools.defaultFontPixelWidth
                }
                indicatorDropdown.x = centerX
            }
        }
        onOpened: {
            loader.sourceComponent = indicatorDropdown.currentIndicator
        }
        onClosed: {
            loader.sourceComponent = null
            indicatorDropdown.currentIndicator = null
        }
    }
//    InputPanel {
//        id: inputPanel
//        z: 99
//        x: (mainWindow.width-inputPanel.width)*0.5
//        y: mainWindow.height
//        width:mainWindow.width

//        states: State {
//            name: "visible"
//            when: inputPanel.active
//            PropertyChanges {
//                target: inputPanel
//                y: mainWindow.height - inputPanel.height
//            }
//        }
//        transitions: Transition {
//            from: ""
//            to: "visible"
//            reversible: true
//            //设置键盘弹出效果
//            ParallelAnimation {
//                NumberAnimation {
//                    properties: "y"
//                    //过渡时间
//                    duration: 100
//                    //弹出效果
//                    easing.type: Easing.InOutQuad
//                }
//            }
//        }
//    }
}



