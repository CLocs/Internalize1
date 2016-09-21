import QtQuick 2.4
import QtQuick.Controls 1.3
import colin.das.Internalize 1.0

Item {
    id: item1
    width: 400
    height: titleArea.height + textArea.contentHeight + titleArea.anchors.topMargin + textArea.anchors.topMargin + textArea.anchors.bottomMargin + border.border.width * 2

    Rectangle {
        id: border
        color: "#ffffff"
        radius: 10
        anchors.fill: parent
        z: -1
        border.width: 2
    }

    TextInput {
        id: titleArea
        wrapMode: TextInput.Wrap
        text: qsTr("Text Input")
        anchors.right: parent.right
        anchors.rightMargin: 6
        anchors.left: parent.left
        anchors.leftMargin: 6
        anchors.top: parent.top
        anchors.topMargin: 6
        font.pixelSize: 12
    }
    property alias title: titleArea.text

    TextEdit {
        id: textArea
        wrapMode: TextEdit.Wrap
        selectByMouse: true
        text: ""
        anchors.top: titleArea.bottom
        anchors.topMargin: 6
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.rightMargin: 6
        anchors.leftMargin: 6
        anchors.bottomMargin: 6

        textFormat: TextEdit.RichText

        MouseArea {
            anchors.fill: parent
            acceptedButtons: Qt.RightButton
            onClicked: textAreaMenu.popup()
        }

        Menu {
            id: textAreaMenu
            MenuItem {
                action: boldAction
            }
        }

        Component.onDestruction: item1.save();
    }

    signal save()

    property alias content: textArea.text

    Action {
        id: boldAction
        text: "Bold"
        shortcut: "Ctrl+B"
        onTriggered: formatter.setBold(textArea.selectionStart,textArea.selectionEnd)
    }

    Action {
        id: saveAction
        text: "Save"
        shortcut: "Ctrl+S"
        onTriggered: item1.save()
    }

    TextDocumentFormatter {
        id: formatter
        textDocument: textArea.textDocument
    }
}
