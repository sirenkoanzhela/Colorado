import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15
import QtQml.Models 2.15

Rectangle {
    id: thread
    width: 200*5
    height: 50
    border.color: "grey"
    color: "transparent"

    property int currentIndex: -1
    property int rowIndex: 0

    Row {
        id: mainThread
        Repeater {
            model: colorSectorsCollection.columnCount(colorSectorsCollection.createIndex(rowIndex, 0))

            delegate: Rectangle {
                width: thread.width / colorSectorsCollection.columnCount(colorSectorsCollection.createIndex(rowIndex, 0))
                height: parent.height

                Color {
                    id: color
                    anchors.fill: parent
                    color: colorSectorsCollection.data(colorSectorsCollection.createIndex(rowIndex, index), colorSectorsCollection.colorRole)
                    border.color: currentIndex === index ? "red" : "black"
                }
            }
        }

        BaseButton {
            id: removeHighlightedButton
            iconSourceEnabled: "icons/trash_icon.png"
            iconSourceDisabled: "icons/trash_icon_disabled.png"
            //enabled: colorSectorsCollection.rowCount() > 1 && colorSectorsCollection.currentIndex !== -1;
            //enabled: colorSectorsCollection.getThreadCount(colorSectorsCollection.currentIndex) > 1 && colorSectorsCollection.currentIndex !== -1;
            //enabled: colorSectorsCollection.canRemoveSector(colorSectorsCollection.currentIndex) && colorSectorsCollection.currentIndex !== -1;
            enabled: colorSectorsCollection.canRemoveSector(colorSectorsCollection.currentIndex) && colorSectorsCollection.currentIndex !== -1;

            onBaseButtonClicked: {
                colorSectorsCollection.removeSector(colorSectorsCollection.currentIndex);
                console.log("Remove highlighted sector. Now color sectors count is", colorSectorsCollection.rowCount());

            }
        }
        CircleButton {
            id: removeSectorButton
            buttonText: "-"
            enabled: colorSectorsCollection.rowCount() > 1;
            onCircleButtonClicked: {
                colorSectorsCollection.removeSector(colorSectorsCollection.createIndex(rowIndex,0));
            }
        }
        CircleButton {
            id: addSectorButton
            buttonText: "+"

            onCircleButtonClicked: {
                colorSectorsCollection.addSector(colorSectorsCollection.createIndex(rowIndex,0));
            }
        }
    }

    Connections {
        target: colorSectorsCollection
        function onSectorsCountChanged() {
            removeSectorButton.enabled = colorSectorsCollection.rowCount() > 1;
            addSectorButton.enabled = colorSectorsCollection.rowCount() < 5;
            removeHighlightedButton.enabled = colorSectorsCollection.rowCount() > 1 && colorSectorsCollection.currentIndex !== -1;
        }
    }
}


/*
old implementation


    ListView {
        orientation: ListView.Horizontal
        anchors.fill: parent
        interactive: false
        spacing: 2

        model: threadColor

        delegate: Rectangle {
            anchors.fill: parent
            Color {
                id: color
                width: thread.width / threadColor.rowCount() - 2

                height: parent.height

                colorName: model.color
                colorHex: model.color

                border.color: currentIndex === index ? "red" : "black"

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        currentIndex = index;
                    }
                }
            }
        }
    }
*/
