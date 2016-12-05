#include "ErrorHandler.h"

ErrorHandler::ErrorHandler(QObject *parent) : QObject(parent)
{

}

void ErrorHandler::handleMessage(QtMsgType type, const QMessageLogContext &context, const QString &message) {
    QByteArray localMsg = message.toLocal8Bit();
    switch (type) {
    case QtDebugMsg:
        fprintf(stderr, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtInfoMsg:
        fprintf(stderr, "Info: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtWarningMsg:
        fprintf(stderr, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtCriticalMsg:
        fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtFatalMsg:
        fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        abort();
    }
}

void ErrorHandler::handleWarnings(const QList<QQmlError> &warnings) {
    for(auto error:warnings) {
        QByteArray localMsg = error.description().toLocal8Bit();
        fprintf(stderr, "QML: %s (%s:%u:%u)\n", localMsg.constData(), error.url().toEncoded().constData(), error.line(), error.column());
    }
}
