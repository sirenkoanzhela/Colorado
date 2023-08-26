import QtQuick 2.0
import QtQuick.Controls 2.15

Item {
    id: _parent
    property alias labelText: _label.text
    property alias buttonText: _button.text

    Column{
        anchors.centerIn: _parent
        spacing: 10

        Text {
            id: _label

            color: "white"

            font.pixelSize: 16
            font.bold: false
            font.family: "Arial"
        }

        CircleButton {
            id: _button
        }

    }
}
