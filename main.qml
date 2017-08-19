import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.2
import QtWebView 1.1
import colin.das.Internalize 1.0
import Qt.labs.settings 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    id: window

    Settings {
        id: settings
        category: "ApplicationWindow"
        property int visibility: Window.Windowed
        property alias width: window.width
        property alias height: window.height
    }

    Component.onDestruction: {
        if(window.visibility === Window.Maximized || window.visibility === Window.Fullscreen) {
            settings.visibility = window.visibility
        } else {
            settings.visibility = Window.Windowed
        }
    }

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
            width: parent.width / 4
            url: "http://slatestarcodex.com/"
        }

        ScrollView {
            width: parent.width / 4
            Image {
                source: "Internalize-Demo1.svg"
            }
        }

        ListView {
            width: parent.width / 4
            id: notesView
            model: NoteDatabase.model
            delegate: Note {
                title: model.title
                content: model.content
                width: notesView.width

                onTitleChanged:  NoteDatabase.model.setTitle(index, title)
                onSave:  {
                    NoteDatabase.model.setContent(index, content)
                    Repository.store(content);
                }
            }
        }

        ColumnLayout {
            width: parent.width / 4
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
