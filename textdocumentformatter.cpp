#include "textdocumentformatter.h"
#include <QTextCharFormat>
#include <QTextCursor>
#include <QTextBlock>
#include <QTextLayout>

#include <iterator>
namespace {
    struct TextBlockInfo {
        QTextBlock block;
        int start;
        int end;
        int length() { return end - start; }
    };

    class TextBlockIteratorEnd { };

    class TextBlockIterator
      : public std::iterator<std::input_iterator_tag,TextBlockInfo>,
        private TextBlockInfo
    {
        int docStart;
        int docEnd;

        void init (const QTextBlock &block) {
            this->block = block;
            start = std::max(docStart - block.position(), 0);
            end = std::min(docEnd - block.position(),block.length());
        }
    public:
        TextBlockIterator(const QTextCursor &cursor)
          : docStart(cursor.selectionStart())
          , docEnd(cursor.selectionEnd()) {
            if(cursor.hasComplexSelection()) {
                abort(); // table cells and such, ?
            } else {
                init(cursor.document()->findBlock(docStart));
            }
        }

        TextBlockIterator &operator++() {
            init(block.next());
            return *this;
        }
        TextBlockIterator operator++(int) {
            TextBlockIterator r = *this;
            operator++();
            return r;
        }
        TextBlockInfo &operator *() { return *this; }
        TextBlockInfo *operator ->() { return this; }
        bool operator==(const TextBlockIterator&other) { return block == other.block; }
        template<typename T> bool operator !=(T && other) { return !(*this == other); }

        friend bool operator==(const TextBlockIterator &itr, const TextBlockIteratorEnd&) {
            return !itr.block.isValid() || itr.block.position() >= itr.docEnd;
        }
    };

    struct TextBlockRange {
        TextBlockIterator range;
        TextBlockIterator begin() { return range; }
        TextBlockIteratorEnd end() {return {}; }
    };
    TextBlockRange asTextBlocks(const QTextCursor &cursor) { return {cursor}; }
}

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
    QTextCharFormat highlightFormat;
    highlightFormat.setBackground(QColor(Qt::yellow));

    for(auto &&i: asTextBlocks(cursor)) {
        QTextLayout::FormatRange formatRange;
        formatRange.format = highlightFormat;
        formatRange.length = i.length();
        formatRange.start = i.start;
        i.block.layout()->setFormats({formatRange});
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
    if(cursor.hasSelection()) {
        QVector<QTextCharFormat> result;
        for(auto &&i: asTextBlocks(cursor)) {
            for(QTextLayout::FormatRange formatRange: i.block.textFormats()) {
                // ab[cd]ef
                //case 1: (a)b[cde]fg -> false (format before cursor)
                //case 2: a(b[c)de]fg -> true (format overlaps start of cursor
                //case 3: ab[c(d)e]fg -> true (format completely inside cursor)
                //case 4: ab[cd(e]f)g -> true (format overlaps end of cursor)
                //case 5: ab[cde]f(g) -> false (format after cursor)
                int formatRangeEnd = formatRange.start + formatRange.length;

                if( formatRange.start < i.end && formatRangeEnd > i.start) {
                    result.append(formatRange.format);
                }
            }
        }
        return result;
    } else {
        return { cursor.charFormat() };
    }
}
