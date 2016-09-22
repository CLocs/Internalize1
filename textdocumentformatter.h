#ifndef TEXTDOCUMENTFORMATTER_H
#define TEXTDOCUMENTFORMATTER_H

#include <QObject>
#include <QTextDocument>
#include <QQuickTextDocument>
#include <QTextCharFormat>

class TextDocumentFormatter : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQuickTextDocument *textDocument READ getTextDocument WRITE setTextDocument NOTIFY textDocumentChanged)
public:
    TextDocumentFormatter();

    QQuickTextDocument *getTextDocument() const;
    void setTextDocument(QQuickTextDocument *value);

signals:
    void textDocumentChanged();

public slots:
    void toggleBold(int start, int end);
    void setBold(int start, int end);
    void clearBold(int start, int end);
private:
    QQuickTextDocument *m_textDocument;
    QTextCursor makeCursor(int start, int end) const;
    static QVector<QTextCharFormat> charFormats(const QTextCursor &makeCursor);
};

#endif // TEXTDOCUMENTFORMATTER_H
