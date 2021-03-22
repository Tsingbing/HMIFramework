HEADERS += \
    $$PWD/qml/AppMessages.h \
    $$PWD/qml/ScreenToolsController.h

SOURCES += \
    $$PWD/qml/AppMessages.cc \
    $$PWD/qml/ScreenToolsController.cc

FORMS    += \


RESOURCES += \
    $$PWD/hmiQGCqml.qrc \
    $$PWD/hmiQGCimages.qrc


INCLUDEPATH += $$PWD/qml

QML_IMPORT_PATH += $$PWD/qml
