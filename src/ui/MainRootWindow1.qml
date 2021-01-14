import QtQuick 2.12
import QtQuick.Controls 2.4
import QtQuick.Dialogs  1.3
import QtQuick.Window 2.12

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

    Component.onCompleted: {
        //console.info(globals._appFontPointSize.value)
    }


    property var                _rgPreventViewSwitch:       [ false ]
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
    }

    function showFlyView() {
        viewSwitch()
        flyView.visible = true
    }

    function showAnalyzeView() {
        viewSwitch()
        analyzeWindow.visible = true
    }

    function showSetupView() {
        viewSwitch()
        setupWindow.visible = true
    }

    function showSettingsView() {
        viewSwitch()
        settingsWindow.visible = true
    }

    //-------------------------------------------------------------------------
    //-- Global complex dialog

    /// Shows a QGCViewDialogContainer based dialog
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
    /// Main, full window background
    //    background: Item {
    //        id:             rootBackground
    //        anchors.fill:   parent

    //        Image {
    //            id: image
    //            anchors.rightMargin: 0
    //            anchors.bottomMargin: 1
    //            anchors.leftMargin: 0
    //            anchors.topMargin: -1
    //            anchors.fill: parent
    //            source: "qrc:/qmlimages/main_set.jpg"
    //            fillMode: Image.PreserveAspectFit
    //        }
    //    }

    //-------------------------------------------------------------------------
    /// Main, full window background (Fly View)
    background: Item {
        id:             rootBackground
        anchors.fill:   parent

        Rectangle {
            anchors.fill:   parent
            color:          "#222222"
        }
    }


    //-------------------------------------------------------------------------
    /// Toolbar
    footer: ToolBar {
        x: 200
        width:          parent.width/2
        height:         ScreenTools.toolbarHeight * 2
        visible:        true
        background:     Rectangle {
            color:  "transparent"	//transparent:透明  // qgcPal.globalTheme === HMIPalette.Light ? HMI.corePlugin.options.toolbarBackgroundLight : HMI.corePlugin.options.toolbarBackgroundDark
        }
        Loader {
            id:             toolbar
            anchors.fill:   parent
            source:         "qrc:/toolbar/MainToolBar.qml"
        }
    }

    //    footer: LogReplayStatusBar {
    //        visible: HMI.settingsManager.flyViewSettings.showLogReplayStatusBar.rawValue
    //    }


    //-------------------------------------------------------------------------
    /// Plan View
    Loader {
        id:             flyView
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
        anchors.fill:   parent
        //height:         mainWindow.height
        visible:        false
        source:         "AnalyzeView.qml"
    }
}



