#include <QApplication>
#include <QQmlApplicationEngine>
#include "textdocumentformatter.h"
#include "notedatabase.h"
#include <QtQml>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("Internalize");
    QQmlApplicationEngine engine;

    qmlRegisterType<TextDocumentFormatter>("colin.das.Internalize", 1, 0, "TextDocumentFormatter");
    qmlRegisterSingletonType<NoteDatabase>("colin.das.Internalize", 1, 0, "NoteDatabase", &NoteDatabase::singletontype_provider);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
