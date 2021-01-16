QT += core gui concurrent
QT += serialbus
QT += quick
QT += qml
QT += svg
QTPLUGIN += qtvirtualkeyboardplugin

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

#
# 品牌
#

DEFINES += APPLICATION_NAME=\"\\\"HMIFramework\\\"\"
DEFINES += ORG_NAME=\"\\\"umltech.org\\\"\"

# 设置构建目录
DESTDIR = $${OUT_PWD}/bin
OBJECTS_DIR  = $${OUT_PWD}/build/obj
MOC_DIR      = $${OUT_PWD}/build/moc
UI_DIR       = $${OUT_PWD}/build/ui
RCC_DIR      = $${OUT_PWD}/build/rcc
QMLCACHE_DIR = $${OUT_PWD}/build/qmlcache

# 设置版本号（从git获取）
exists ($$PWD/.git) {
    GIT_DESCRIBE = $$system(git --git-dir $$PWD/.git --work-tree $$PWD describe --always --tags)
    GIT_BRANCH   = $$system(git --git-dir $$PWD/.git --work-tree $$PWD rev-parse --abbrev-ref HEAD)
    GIT_HASH     = $$system(git --git-dir $$PWD/.git --work-tree $$PWD rev-parse --short HEAD)
    GIT_TIME     = $$system(git --git-dir $$PWD/.git --work-tree $$PWD show --oneline --format=\"%ci\" -s HEAD)

    # 设置设备标号

    contains(GIT_DESCRIBE, v[0-9]+.[0-9]+.[0-9]+) {
        # 发布版本 "vX.Y.Z"
        GIT_VERSION = $${GIT_DESCRIBE}
        VERSION      = $$replace(GIT_DESCRIBE, "v", "")
        VERSION      = $$replace(VERSION, "-", ".")
        VERSION      = $$section(VERSION, ".", 0, 3)
    } else {
        # 开发版本 "Development branch:sha date"
        GIT_VERSION = "Development $${GIT_BRANCH}:$${GIT_HASH} $${GIT_TIME}"
        VERSION         = 0.0.0
    }
    message(HMI $${GIT_VERSION})

} else {
    GIT_VERSION     = None
    VERSION         = 0.0.0   # Marker to indicate out-of-tree build
    MAC_VERSION     = 0.0.0
    MAC_BUILD       = 0
}

DEFINES += GIT_VERSION=\"\\\"$$GIT_VERSION\\\"\"

INCLUDEPATH += .

INCLUDEPATH += \
    src \
    src/factsystem \
    src/vehicles \
    src/settings \
    src/links \
    src/QmlControls \
    src/ui

SOURCES += \
    src/HMILoggingCategory.cc \
    src/HMIPalette.cc \
    src/HMIQmlGlobal.cpp \
    src/QmlControls/AppMessages.cc \
    src/QmlControls/ScreenToolsController.cc \
    src/Tool.cpp \
    src/Toolbox.cpp \
    src/XApplication.cpp \
    src/factsystem/Fact.cpp \
    src/factsystem/FactGroup.cpp \
    src/factsystem/FactMetaData.cpp \
    src/factsystem/FactSystem.cc \
    src/factsystem/JsonHelper.cc \
    src/factsystem/SettingsFact.cpp \
    src/links/CanLink.cpp \
    src/links/CanLinkProtocol.cpp \
    src/links/LinkManager.cpp \
    src/main.cpp \
    src/settings/AppSettings.cpp \
    src/settings/SettingsGroup.cpp \
    src/settings/SettingsManager.cpp \
    src/ui/Dialog2.cpp \
    src/ui/MessageDialog.cpp \
    src/ui/numkeyboard.cpp \
    src/ui/softkeylineedit.cpp \
    src/vehicles/Vehicle.cpp \
    src/vehicles/VehicleManager.cpp

HEADERS += \
    src/HMILoggingCategory.h \
    src/HMIPalette.h \
    src/HMIQmlGlobal.h \
    src/QmlControls/AppMessages.h \
    src/QmlControls/ScreenToolsController.h \
    src/Tool.h \
    src/Toolbox.h \
    src/XApplication.h \
    src/factsystem/Fact.h \
    src/factsystem/FactGroup.h \
    src/factsystem/FactMetaData.h \
    src/factsystem/FactSystem.h \
    src/factsystem/JsonHelper.h \
    src/factsystem/SettingsFact.h \
    src/links/CanLink.h \
    src/links/CanLinkProtocol.h \
    src/links/LinkManager.h \
    src/settings/AppSettings.h \
    src/settings/SettingsGroup.h \
    src/settings/SettingsManager.h \
    src/ui/Dialog2.h \
    src/ui/MessageDialog.h \
    src/ui/numkeyboard.h \
    src/ui/softkeylineedit.h \
    src/vehicles/Vehicle.h \
    src/vehicles/VehicleManager.h

FORMS += \
    src/ui/Dialog2.ui \
    src/ui/MessageDialog.ui \
    src/ui/numkeyboard.ui
#
TARGET = run
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /home/root/client
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    HMIFramework.qrc \
    hmiimages.qrc

QML_IMPORT_PATH += $$PWD/src/QmlControls


DISTFILES += \
    src/QmlControls/HMI/Specific/qmldir
