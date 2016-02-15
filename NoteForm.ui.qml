import QtQuick 2.4
import QtQuick.Controls 1.3

Item {
    id: item1
    width: 400
    height: 400
    property alias titleArea: titleArea
    property alias textArea: textArea

    Rectangle {
        id: border
        color: "#ffffff"
        radius: 10
        anchors.fill: parent
        z: -1
        border.width: 2
    }

    TextArea {
        id: textArea
        text: ""
        anchors.top: titleArea.bottom
        anchors.topMargin: 6
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.rightMargin: 6
        anchors.leftMargin: 6
        anchors.bottomMargin: 6
    }

    TextInput {
        id: titleArea
        height: 20
        text: qsTr("Text Input")
        anchors.right: parent.right
        anchors.rightMargin: 6
        anchors.left: parent.left
        anchors.leftMargin: 6
        anchors.top: parent.top
        anchors.topMargin: 6
        font.pixelSize: 12
    }
}
