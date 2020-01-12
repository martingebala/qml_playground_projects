import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    property int tableItemSize: 38
    property int tableMargin: 30
    property int tableColumnCount: (width - 2 * tableMargin) / tableItemSize - 1
    property int tableRowCount: (height - 2 * tableMargin) / tableItemSize - 1

    property string tableColor1: "lightGray"
    visible: true
    width: 480
    height: 480
    title: qsTr("Multiplication Table")

    Grid {
        columns: 2
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

        Rectangle {
            width: multiplicand.width
            height: multiplier.height
            color: "gray"
        }

        Row {
            id: multiplier
            Repeater {
                model: tableColumnCount
                TableItem {
                    color: tableColor1
                    value: index + 1
                    size: tableItemSize
                }
            }
        }

        Column {
            id: multiplicand
            Repeater {
                id: items
                model: tableRowCount
                TableItem {
                    color: tableColor1
                    value: index + 1
                    size: tableItemSize
                }
            }
        }

        Grid {
            id: mtable
            columns: tableColumnCount
            rows: tableRowCount

            Repeater {
                model: mtable.columns * mtable.rows

                TableItem {
                    id: delegate
                    value: ((index % tableColumnCount) + 1)
                           * (Math.floor(index / tableColumnCount) + 1)
                    size: tableItemSize
                    color: ((index % (tableColumnCount + 1)) == 0)
                           && (index < tableColumnCount * tableColumnCount) ? "red" : "white"
                }
            }
        }
    }
}
