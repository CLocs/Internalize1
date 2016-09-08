import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.2
import QtWebView 1.1
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

        WebView {
            id: sourceView
            width: parent.width / 3
           //url: "https://drive.google.com/open?id=0B3Ej2lncGdJQT1hSY0FVand3aEk"
            // TODO: binding this URL right away shows a blank window - report race condition bug
            Component.onCompleted: sourceView.url = "http://slatestarcodex.com/"
        }

        ScrollView {
            width: parent.width / 3
            Image {
                source: "Internalize-Demo1.svg"
            }
        }

        ListView {
            model: NoteDatabase.model
            delegate: Note {
                title: model.title
                content: model.content

                onTitleChanged:  NoteDatabase.model.setTitle(index, title)
                onContentChanged:  {

                    NoteDatabase.model.setContent(index, content)
                    Repository.store(content);
                }
            }
        }

        ColumnLayout {
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
    }


/*    MessageDialog {
        id: messageDialog
        title: qsTr("May I have your attention, please?")

        function show(caption) {
            messageDialog.text = caption;
            messageDialog.open();
        }
    }*/
}
