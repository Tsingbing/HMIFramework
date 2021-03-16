HEADERS += \    
    $$PWD/Fact.h \
    $$PWD/FactGroup.h \
    $$PWD/FactMetaData.h \
    $$PWD/FactSystem.h \
    $$PWD/JsonHelper.h \
    $$PWD/SettingsFact.h
           
SOURCES += \    
    $$PWD/Fact.cpp \
    $$PWD/FactGroup.cpp \
    $$PWD/FactMetaData.cpp \
    $$PWD/FactSystem.cc \
    $$PWD/JsonHelper.cc \
    $$PWD/SettingsFact.cpp

FORMS    += \


RESOURCES += \
    $$PWD/factsystem.qrc

INCLUDEPATH += $$PWD

QML_IMPORT_PATH += $$PWD
