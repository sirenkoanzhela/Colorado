import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15
import QtQml.Models 2.15

Item {
    implicitWidth: 1600
    implicitHeight: 50

    property alias colorName: colorThread.colorName
    property alias colorHex: colorThread.colorName
    property int rowIndex: 0

    Row {
        ColorThread {
            id: colorThread
        }
        BaseButton {
            id: removeHighlightedButton
            iconSourceEnabled: "icons/trash_icon.png"
            iconSourceDisabled: "icons/trash_icon_disabled.png"
            enabled: colorSectorsCollection.rowCount() > 1 && colorThread.currentIndex !== -1;

            onBaseButtonClicked: {
                colorSectorsCollection.removeSector(colorThread.currentIndex);
                console.log("Remove highlighted sector. Now color sectors count is", colorSectorsCollection.rowCount());

            }
        }
        CircleButton {
            id: removeSectorButton
            buttonText: "-"
            enabled: threadColor.rowCount() > 1;
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
            removeHighlightedButton.enabled = colorSectorsCollection.rowCount() > 1 && colorThread.currentIndex !== -1;
        }
    }
}
