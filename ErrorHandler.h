#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H

#include <QObject>
#include <QQmlError>
#include <QList>

class ErrorHandler : public QObject
{
    Q_OBJECT
public:
    explicit ErrorHandler(QObject *parent = 0);

    //for use with qInstallMessageHandler
    static void handleMessage(QtMsgType type, const QMessageLogContext &context, const QString &message);

public slots:
    // for use with QQmlEngine::warnings
    void handleWarnings(const QList<QQmlError> &warnings);
};

#endif // ERRORHANDLER_H
