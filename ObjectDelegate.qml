import QtQuick 2.7
import QtQuick.Controls 2.2
import QtWebView 1.1
import colin.das.Internalize 1.0

Loader {
    id: currentPage
    property var model
    property var modelIndex

    // inform the component being loaded how large the viewport can be,
    // in case it wants to wrap itself to fit better
    property int viewportWidth
    property int viewportHeight

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

    sourceComponent: {
        if(model) switch(model.objectType) {
        case ObjectType.Note: return noteComponent;
        case ObjectType.WebPage: return webComponent;
        case ObjectType.Image: return imageComponent;
        }
        return busyComponent
    }
}
