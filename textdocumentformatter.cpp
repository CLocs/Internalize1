#include "textdocumentformatter.h"
#include <QTextCharFormat>
#include <QTextCursor>

TextDocumentFormatter::TextDocumentFormatter()
    : m_textDocument(nullptr)
{

}

QQuickTextDocument *TextDocumentFormatter::getTextDocument() const
{
    return m_textDocument;
}

void TextDocumentFormatter::setTextDocument(QQuickTextDocument *value)
{
    m_textDocument = value;
    emit textDocumentChanged();
}

void TextDocumentFormatter::setBold(int start, int end)
{
    QTextCharFormat format;
    format.setFontWeight(QFont::Bold);
    QTextCursor cursor(m_textDocument->textDocument());
    cursor.setPosition(start,QTextCursor::MoveAnchor);
    cursor.setPosition(end,QTextCursor::KeepAnchor);
    cursor.mergeCharFormat(format);
}
