TEMPLATE = app

QT += gui qml quick sql webview
CONFIG += c++11

SOURCES += main.cpp \
    textdocumentformatter.cpp \
    notedatabase.cpp \
    Repository.cpp \
    ErrorHandler.cpp \
    TableOfContents.cpp

OTHER_FILES += main.qml \
    Note.qml
    ObjectDelegate.qml

RESOURCES += qml.qrc \
    Repository.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    textdocumentformatter.h \
    notedatabase.h \
    Repository.h \
    ErrorHandler.h \
    TableOfContents.h
