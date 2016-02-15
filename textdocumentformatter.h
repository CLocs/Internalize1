#ifndef TEXTDOCUMENTFORMATTER_H
#define TEXTDOCUMENTFORMATTER_H

#include <QObject>
#include <QTextDocument>
#include <QQuickTextDocument>

class TextDocumentFormatter : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQuickTextDocument *textDocument READ getTextDocument WRITE setTextDocument NOTIFY textDocumentChanged)
public:
    TextDocumentFormatter();

    QQuickTextDocument *getTextDocument() const;
    void setTextDocument(QQuickTextDocument *value);

signals:
    textDocumentChanged();

public slots:
    void setBold(int start, int end);
private:
    QQuickTextDocument *m_textDocument;
};

#endif // TEXTDOCUMENTFORMATTER_H
