#include "textdocumentformatter.h"
#include <QTextCharFormat>
#include <QTextCursor>
#include <QTextBlock>
#include <QTextLayout>

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

void TextDocumentFormatter::toggleBold(int start, int end)
{
    QTextCursor cursor = makeCursor(start,end);

    bool isAllBold = false;
    for(const QTextCharFormat &format: charFormats(cursor)) {
        if(format.fontWeight() > QFont::Normal) {
            isAllBold = true;
        } else {
            isAllBold = false;
            break; // if *anything* is not bold, the result is "not bold"
        }
    }
    if(isAllBold) {
        clearBold(start,end);
    } else {
        setBold(start,end);
    }
}

void TextDocumentFormatter::setBold(int start, int end)
{
    QTextCharFormat format;
    format.setFontWeight(QFont::Bold);
    makeCursor(start,end).mergeCharFormat(format);
}

void TextDocumentFormatter::clearBold(int start, int end)
{
    QTextCharFormat format;
    format.setFontWeight(QFont::Normal);
    makeCursor(start,end).mergeCharFormat(format);
}

void TextDocumentFormatter::highlightSelection(int start, int end)
{
    QTextCursor cursor = makeCursor(start,end);
    cursor.beginEditBlock();
    QTextBlock block = m_textDocument->textDocument()->findBlock(start);
    QTextCharFormat highlightFormat;
    highlightFormat.setBackground(QColor(Qt::yellow));

    while(block.isValid() && (block.position() < end)) {
        QVector<QTextLayout::FormatRange> formats;
        QTextLayout::FormatRange formatRange;
        formatRange.format = highlightFormat;
        // start = beginning of block or inside
        formatRange.start = std::max(start - block.position(), 0);
        // end = inside or end of block
        formatRange.length = std::min(end - block.position(),block.length()) - formatRange.start;
        formats.append(formatRange);
        block.layout()->setFormats(formats);
        block = block.next();
    }

    cursor.endEditBlock();
}

QTextCursor TextDocumentFormatter::makeCursor(int start, int end) const
{
    QTextCursor cursor(m_textDocument->textDocument());
    cursor.setPosition(start,QTextCursor::MoveAnchor);
    cursor.setPosition(end,QTextCursor::KeepAnchor);
    return cursor;
}

QVector<QTextCharFormat> TextDocumentFormatter::charFormats(const QTextCursor &cursor)
{
    if(cursor.hasComplexSelection()) {
        abort(); // table cells and such, ?
    } else if(cursor.hasSelection()) {
        QVector<QTextCharFormat> result;
        const QTextBlock &block = cursor.block();
        for(QTextLayout::FormatRange formatRange: block.textFormats()) {
            // ab[cd]ef
            //case 1: (a)b[cde]fg -> false (format before cursor)
            //case 2: a(b[c)de]fg -> true (format overlaps start of cursor
            //case 3: ab[c(d)e]fg -> true (format completely inside cursor)
            //case 4: ab[cd(e]f)g -> true (format overlaps end of cursor)
            //case 5: ab[cde]f(g) -> false (format after cursor)
            int formatRangeEnd = formatRange.start + formatRange.length;

            if( formatRange.start < (cursor.selectionEnd() - block.position())
              && formatRangeEnd > (cursor.selectionStart() - block.position())
) {
                result.append(formatRange.format);
            }
        }
        return result;
    } else {
        return { cursor.charFormat() };
    }
}
