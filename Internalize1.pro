TEMPLATE = app

QT += gui qml quick sql webview
CONFIG += c++11

SOURCES += main.cpp \
    textdocumentformatter.cpp \
    notedatabase.cpp

OTHER_FILES += main.qml \
    MainForm.ui.qml \
    Note.qml

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    textdocumentformatter.h \
    notedatabase.h
