import QtQuick 2.12
import QtQuick.Window 2.12

import qml.enums 1.0

Window {
    visible: true
    width: 800
    height: 600
    title: qsTr("Hello World")

    Grid {
        columns: 32
        Repeater{
            model: game_board_model
            delegate: GameField
            {
                MouseArea {
                    anchors.fill: parent
                    enabled: mark === Marks.Empty
                    onClicked:
                    {
                        game_engine.clickedField(game_board_model.index(index, 0));
                    }
                }
            }
        }
    }

    Text {
        id: popup
        visible: false
        text: ""
        anchors.fill: parent
        font.bold: true
        font.pixelSize: 100
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        MouseArea {
            anchors.fill: parent
            onClicked:
            {
                game_engine.resetGame();
                popup.visible = false;
            }
        }
    }

    Connections {
        target: game_engine
        onCrossesWins:
        {
            popup.text = "Crosses wins!";
            popup.visible = true;
        }
        onNoughtsWins:
        {
            popup.text = "Noughts wins!"
            popup.visible = true;
        }
    }

}
