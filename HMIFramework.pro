# -------------------------------------------------
# HMI
# Maintainer: xueqingbing
# -------------------------------------------------

CONFIG -= debug_and_release

CONFIG(debug, debug|release) {
    message(Debug flavor)
    CONFIG += DebugBuild
} else:CONFIG(release, debug|release) {
    message(Release flavor)
    CONFIG += ReleaseBuild
} else {
    error(Unsupported build flavor)
}

DebugBuild {
    DESTDIR  = $${OUT_PWD}/debug
} else {
    DESTDIR  = $${OUT_PWD}/release
}

win32 {
    contains(QMAKE_TARGET.arch, x86_64) {
        message("Windows build")
        CONFIG += WindowsBuild
        CONFIG += WarningsAsErrorsOn
        DEFINES+=_CRT_SECURE_NO_WARNINGS
        DEFINES += __STDC_LIMIT_MACROS
    } else {
        #error("Unsupported Windows toolchain, only Visual Studio 2017 64 bit is supported")
    }
}

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

#
# 品牌
#

DEFINES += APPLICATION_NAME=\"\\\"HMIFramework\\\"\"
DEFINES += ORG_NAME=\"\\\"umltech.org\\\"\"
DEFINES += GIT_VERSION=\"\\\"$$GIT_VERSION\\\"\"

TARGET   = HMI
TEMPLATE = app
HMIROOT  = $$PWD

DebugBuild {
    CONFIG -= qtquickcompiler
} else {
    CONFIG += qtquickcompiler
}


QT += core gui concurrent
QT += serialbus
QT += quick
QT += qml

# Multimedia only used if QVC is enabled
#!contains (DEFINES, QGC_DISABLE_UVC) {
    QT += \
        multimedia
#}

static {
    QT += svg
    QTPLUGIN += qtvirtualkeyboardplugin
}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += .

INCLUDEPATH += \
    src \
    src/vehicles \
    src/settings \
    src/links \
    src/QmlControls

SOURCES += \
    src/HMILoggingCategory.cc \
    src/HMIPalette.cc \
    src/HMIQmlGlobal.cpp \
    src/Tool.cpp \
    src/Toolbox.cpp \
    src/XApplication.cpp \
    src/links/CanLink.cpp \
    src/links/CanLinkProtocol.cpp \
    src/links/LinkManager.cpp \
    src/main.cpp \
    src/settings/AppSettings.cpp \
    src/settings/SettingsGroup.cpp \
    src/settings/SettingsManager.cpp \
    src/vehicles/Vehicle.cpp \
    src/vehicles/VehicleManager.cpp

HEADERS += \
    src/HMILoggingCategory.h \
    src/HMIPalette.h \
    src/HMIQmlGlobal.h \
    src/Tool.h \
    src/Toolbox.h \
    src/XApplication.h \
    src/links/CanLink.h \
    src/links/CanLinkProtocol.h \
    src/links/LinkManager.h \
    src/settings/AppSettings.h \
    src/settings/SettingsGroup.h \
    src/settings/SettingsManager.h \
    src/vehicles/Vehicle.h \
    src/vehicles/VehicleManager.h

#
#TARGET = run
# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /home/root/client
#!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    HMIFramework.qrc
#    hmiresources.qrc \
#    hmiimages.qrc \


QML_IMPORT_PATH += $$PWD/src/QmlControls

#-------------------------------------------------------------------------------------
#
# Localization
#

TRANSLATIONS += $$files($$PWD/localization/qgc_*.ts)
CONFIG+=lrelease embed_translations

include($$PWD/inputnew/inputnew.pri)
include($$PWD/factsystem/factsystem.pri)
include($$PWD/qmlcontrols/qmlcontrols.pri)
include($$PWD/toolbar/toolbar.pri)
include($$PWD/HMI1/HMI1.pri)
include($$PWD/hmiQGC/hmiQGC.pri)
include($$PWD/video/video.pri)
include($$PWD/map/map.pri)
