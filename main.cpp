#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "textdocumentformatter.h"
#include "notedatabase.h"
#include "Repository.h"
#include "ErrorHandler.h"
#include <QtQml>
#include <QtWebView>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QtWebView::initialize();
    app.setApplicationName("Internalize");

    QQmlApplicationEngine engine;
    ErrorHandler handler;
    qInstallMessageHandler(ErrorHandler::handleMessage);
    QObject::connect(&engine,&QQmlApplicationEngine::warnings,&handler,&ErrorHandler::handleWarnings);

    qmlRegisterType<TextDocumentFormatter>("colin.das.Internalize", 1, 0, "TextDocumentFormatter");
    qmlRegisterSingletonType<NoteDatabase>("colin.das.Internalize", 1, 0, "NoteDatabase", &NoteDatabase::singletontype_provider);
    qmlRegisterSingletonType<Repository>("colin.das.Internalize", 1, 0, "Repository", &Repository::singletontype_provider);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

