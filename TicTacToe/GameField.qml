import QtQuick 2.0
import qml.enums 1.0

Item {

    id: gamefield
    width: 25
    height: width

    Rectangle {
        id: background
        anchors.fill: parent
        border.color: "lightGray"

        states: [
            State {
                name: "normal"
                when: !highlightField
                PropertyChanges { target: background; color: "white" }
            },
            State {
                name: "highlight"
                when: highlightField
                PropertyChanges { target: background; color: "yellow" }
            }
        ]

        Text {
            id: symbol
            text: highlightField ? "h" : "d"
            anchors.centerIn: parent
            font.bold: true
            states: [
                State {
                    name: "empty"
                    when: mark === Marks.Empty
                    PropertyChanges { target: symbol; text: "" }
                },
                State {
                    name: "nought"
                    when: mark === Marks.Nought
                    PropertyChanges { target: symbol; color: "green" }
                    PropertyChanges { target: symbol; text: "○" }
                },
                State {
                    name: "cross"
                    when: mark === Marks.Cross
                    PropertyChanges { target: symbol; color: "red" }
                    PropertyChanges { target: symbol; text: "X" }
                }
            ]
        }

    }
}

