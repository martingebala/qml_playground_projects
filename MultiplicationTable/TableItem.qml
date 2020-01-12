import QtQuick 2.0

Rectangle {
    property alias value: textContent.text
    property int size: 50
    width: size;
    height: size;
    Text {
        id: textContent
        anchors.centerIn: parent
    }
}
