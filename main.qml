import QtQuick 2.5
import QtQuick.Controls 1.4 as Controls1
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.2
import QtQuick.Window 2.2
import QtQml.Models 2.2
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

        property alias lastSection: sectionList.currentIndex
        property alias lastPage: pageList.currentIndex
    }

    Component.onDestruction: {
        if(window.visibility === Window.Maximized || window.visibility === Window.Fullscreen) {
            settings.visibility = window.visibility
        } else {
            settings.visibility = Window.Windowed
        }
    }

    property var tocModel: TableOfContents

    Component {
        id: noteComponent
        Note {
            title: model.title
            content : model.content
            width: viewportWidth
            // do not bind height, let it work itself from implicitHeight based on word-wrapping

            onTitleChanged: tocModel.setData(modelIndex, title, TableOfContents.Title)
            onContentChanged: tocModel.setData(modelIndex, content, TableOfContents.Content)
            //TODO: do we still want onSave for expensive serialization?
            // If so it can't be based on Component.onDestruction, since the component might just get rebound to a new index instead of recreated
        }
    }

    Component {
        id: webComponent
        WebView {
            width: viewportWidth
            height: viewportHeight
            url: model.url
        }
    }

    Component {
        id: imageComponent
        Image {
            source: model.url
            fillMode: Image.Pad
        }
    }

    Component {
        id: busyComponent
        BusyIndicator { }
    }

    ColumnLayout {
        anchors.fill: parent

        ListView {
            id: sectionList
            Layout.fillWidth: true
            implicitHeight: sectionPlaceholder.implicitHeight

            orientation: Qt.Horizontal

            Component {
                id: sectionListDelegate
                Rectangle {
                    border.color: "gray"
                    border.width: 1

                    color: ListView.isCurrentItem ? "lightblue" : "white"

                    implicitHeight: sectionText.implicitHeight + 10
                    implicitWidth: sectionText.implicitWidth + 10
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            sectionList.currentIndex = index
                        }
                    }

                    Text {
                        id: sectionText
                        anchors.fill: parent
                        anchors.margins: 4
                        text: model.title
                    }
                }
            }

            model: DelegateModel {
                model: tocModel
                delegate: sectionListDelegate
            }

            Loader { // load the delegate with dummy data to get a sizeHint
                id: sectionPlaceholder
                property var model: { return { "title": "Placeholder"}; }
                sourceComponent: sectionListDelegate
                visible: false
            }

            readonly property var currentModelIndex: {
                if(currentIndex >= 0) {
                    return model.modelIndex(currentIndex)
                } else {
                    return null
                }
            }
        }

        Controls1.SplitView {
            Layout.fillHeight: true
            Layout.fillWidth: true
            orientation: Qt.Horizontal

            ScrollView {
                id: pageScroll
                Layout.fillHeight: true
                Layout.fillWidth: true
                clip: true
                Loader {
                    id: currentPage
                    property var model: pageList.currentModel
                    property var modelIndex: pageList.currentModelIndex

                    // inform the component being loaded how large the viewport can be,
                    // in case it wants to wrap itself to fit better
                    property int viewportWidth: pageScroll.width
                    property int viewportHeight: pageScroll.height

                    sourceComponent: {
                        if(model) switch(model.objectType) {
                        case ObjectType.Note: return noteComponent;
                        case ObjectType.WebPage: return webComponent;
                        case ObjectType.Image: return imageComponent;
                        }
                        return busyComponent
                    }
                    active:true
                }
            }

            ListView {
                id: pageList
                clip: true

                Component {
                    id: pageListDelegate
                    Rectangle {
                        border.color: "gray"
                        border.width: 1

                        color: ListView.isCurrentItem ? "lightblue" : "white"

                        implicitHeight: pageText.implicitHeight + 10
                        implicitWidth: pageText.implicitWidth + 10

                        anchors.left: parent.left
                        anchors.right: parent.right

                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                pageList.currentIndex = index
                            }

                            hoverEnabled: true
                            ToolTip.delay: 1000
                            ToolTip.visible: containsMouse && pageText.implicitWidth > pageText.width
                            ToolTip.text: model.title
                        }

                        Text {
                            id: pageText
                            anchors.fill: parent
                            anchors.margins: 4
                            text: model.title
                            elide: Text.ElideRight
                        }
                    }
                }


                Layout.minimumWidth: 100
                Layout.fillHeight: true
                model: DelegateModel {
                    model: tocModel
                    rootIndex: sectionList.currentModelIndex
                    delegate: pageListDelegate
                }

                readonly property var currentModelIndex: {
                    if(currentIndex >= 0) {
                        return model.modelIndex(currentIndex)
                    } else {
                        return null
                    }
                }

                readonly property var currentModel: {
                    if(currentIndex >= 0) {
                        model.rootIndex; /* just peeking at so QML sees the dependency, DelegateModel doesn't seem to signal the way it impacts model.items.get */
                        return model.items.get(currentIndex).model
                    } else {
                        return null;
                    }
                }
            }
        }
    }
}
