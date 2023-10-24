import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15
import QtQml.Models 2.15

Item {
    id: _parent

    property alias paletteSize: _palette.model
    property int columns

    width: Screen.width / 2
    height: Screen.height / 2

    GridView {
        id: _palette

        cellWidth: 300
        cellHeight: 80

        width: cellWidth * _parent.columns
        height: _parent.height
        anchors.leftMargin: 50
        anchors.topMargin: 20
        anchors.left: _parent.left
        anchors.top: _parent.top

        interactive: false
        Layout.column: _parent.columns

        //model: paletteModel

        delegate: Rectangle {
            id: sector
            property int indexOfThisDelegate: index

            width: _palette.cellWidth
            height: _palette.cellHeight

            Color {
                id: color
                anchors.fill: parent
                color: "#ffffff"
                border.color: "#000000"
            }

            Text {
                id: colorText
                anchors.fill: sector
                text: index +1
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    console.log("Click color", colorText.text )
                }
            }
        }
    }
    Rectangle {
        id: test
        color: "#ff0000"
        opacity: 0.5
        anchors.fill: _palette
        visible: false
    }

    Notification {
        id: _paletteEmpty
        visible: !_palette.visible
        anchors.centerIn: _parent

        buttonText: "+"
        notificationText: "Click to add new color spectrum"
    }
}
