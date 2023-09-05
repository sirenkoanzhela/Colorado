import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    property string topColorName: ""
    property string bottomColorName: ""

    property string topColorHex: ""
    property string bottomColorHex: ""

    id: _colorSpcectrum
    width: 100
    height: 100

    Color {
        id: _top
        width: parent.width
        height: parent.width/2
        colorName: topColorName
        colorHex: topColorHex
    }
    Color {
        id: _bottom
        width: parent.width
        height: parent.width/2
        anchors.top: _top.bottom
        colorName: bottomColorName
        colorHex: bottomColorHex
    }

}
