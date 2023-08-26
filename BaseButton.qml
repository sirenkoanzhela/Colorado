import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: _parent

    property alias text: _label.text

    //default values
    color: "transparent"
    border.color: "white"

    Text {
        id: _label
        anchors.centerIn: parent

        font.pixelSize: 16
        font.bold: false
        font.family: "Arial"
    }
}
