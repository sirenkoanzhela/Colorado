import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15
import QtQml.Models 2.15

Rectangle {
    id: thread
    width: Screen.width / 2
    height: 50
    border.color: "grey"
    color: "transparent"

    property int currentIndex: -1
    property int rowIndex: -1
    signal colorSelected(int threadIndex, int colorIndex)

    Row {
        id: mainThread
        anchors.fill: parent
        Repeater {
            model: colorSectorsCollection.data( colorSectorsCollection.createIndex(rowIndex, 0), 257 )
            delegate: Rectangle {
                id: sector
                property int indexOfThisDelegate: index

                width: thread.width / colorSectorsCollection.getThreadSize(rowIndex)
                height: parent.height

                Color {
                    id: color
                    anchors.fill: parent
                    color: colorSectorsCollection.getColorForIndices(rowIndex, parent.indexOfThisDelegate)
                    border.color: currentIndex === indexOfThisDelegate ? "red" : "black"
                }

                Text {
                    anchors.fill: sector
                    text: colorSectorsCollection.getColorForIndices(rowIndex, parent.indexOfThisDelegate)
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if(currentIndex === index)
                        {
                            currentIndex = -1;
                        }
                        else
                        {
                            currentIndex = index;
                        }
                        colorSelected(rowIndex, indexOfThisDelegate);
                    }
                }

                TextField {
                    id: changeColorTextField

                    width: parent.width / 2
                    height: parent.height / 2
                    anchors.centerIn: parent

                    visible: currentIndex === indexOfThisDelegate

                    color: "black"
                    placeholderText: "Enter hex of color"


                    background: Rectangle {
                        color: "transparent"
                        border.color: "black"
                        border.width: 1
                    }
                    onAccepted: {
                        if(colorSectorsCollection.tryChangeSectorColor(rowIndex, parent.indexOfThisDelegate, text))
                        {
                            placeholderText = "Enter hex of color"
                        }
                        else
                        {
                            placeholderText = "Try again. Hex is invalid"
                        }
                        text = ""
                    }
                }
            }
        }

        Item {
            id: controlButtons
            width: removeHighlightedButton.width + removeSectorButton.width + addSectorButton.width
            height: parent.height
            Row {
                anchors.fill: parent
                spacing: 5
                BaseButton {
                    id: removeHighlightedButton
                    iconSourceEnabled: "icons/trash_icon.png"
                    iconSourceDisabled: "icons/trash_icon_disabled.png"

                    enabled: colorSectorsCollection.isRemoveSectorEnable(rowIndex, currentIndex)

                    onBaseButtonClicked: {
                        colorSectorsCollection.removeSector(rowIndex, currentIndex);
                    }
                }
                CircleButton {
                    id: removeSectorButton
                    buttonText: "-"
                    enabled: colorSectorsCollection.isRemoveSectorEnable(rowIndex)
                    onCircleButtonClicked: {
                        colorSectorsCollection.removeSector(rowIndex);
                    }
                }
                CircleButton {
                    id: addSectorButton
                    buttonText: "+"
                    enabled: colorSectorsCollection.isAddSectorEnable(rowIndex)

                    onCircleButtonClicked: {
                        colorSectorsCollection.addSector(rowIndex);
                    }
                }
            }
        }
    }

    Connections {
        target: colorSectorsCollection
        function onSectorsCountChanged() {
            removeSectorButton.enabled = colorSectorsCollection.isRemoveSectorEnable(rowIndex);
            addSectorButton.enabled = colorSectorsCollection.isAddSectorEnable(rowIndex);
            removeHighlightedButton.enabled = colorSectorsCollection.isRemoveSectorEnable(rowIndex, currentIndex);
        }
    }

    onColorSelected: {
        removeHighlightedButton.enabled = colorSectorsCollection.isRemoveSectorEnable(rowIndex, currentIndex);
    }
}
