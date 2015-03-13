TEMPLATE = app

QT += qml quick widgets axcontainer

SOURCES += main.cpp \
    reader.cpp \
    speech_thread.cpp
lupdate_only{
    SOURCES += *.qml
}

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    reader.h \
    speech_thread.h
TRANSLATIONS = zh_CN.ts
RC_FILE += speak_reader.rc
DISTFILES +=
