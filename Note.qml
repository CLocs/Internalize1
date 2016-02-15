import QtQuick 2.4
import QtQuick.Controls 1.3
import colin.das.Internalize 1.0

NoteForm {
    property string content: textArea.text
    property string title: titleArea.text

    onContentChanged: { textArea.text = content; content = Qt.binding(function() { return textArea.text} ) }
    onTitleChanged: { titleArea.text = title; title = Qt.binding(function() { return titleArea.text}) }

    Action {
        id: boldAction
        text: "Bold"
        shortcut: "Ctrl+B"
        onTriggered: formatter.setBold(textArea.selectionStart,textArea.selectionEnd)
    }

    textArea.textFormat: TextEdit.RichText
    textArea.menu: Menu {
        MenuItem {
            action: boldAction
        }
    }

    TextDocumentFormatter {
        id: formatter
        textDocument: textArea.textDocument
    }
}
