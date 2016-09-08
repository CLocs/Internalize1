import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.2
import colin.das.Internalize 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("&Open")
                onTriggered: console.log("Open action triggered");
            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    SplitView {
        anchors.fill: parent

        ColumnLayout {
            CheckBox {
                id: showContentCheck
                text: "Show Content"
                checked: true
            }

            ListView {
                Layout.fillHeight: true
                model: NoteDatabase.model
                delegate: Text { text: model.title }
            }

            Button {
                text: "Add Note"
                onClicked: NoteDatabase.addNote();
            }
        }

        ListView {
            model: NoteDatabase.model
            delegate: Note {
                title: model.title
                content: model.content

                showContent: showContentCheck.checked

                onTitleChanged:  NoteDatabase.model.setTitle(index, title)
                onContentChanged:  NoteDatabase.model.setContent(index, content)
            }
        }

    }


    MessageDialog {
        id: messageDialog
        title: qsTr("May I have your attention, please?")

        function show(caption) {
            messageDialog.text = caption;
            messageDialog.open();
        }
    }
}
