import QtQuick 2.0


Rectangle {
    property string colorName: ""
    property string colorHex: ""

    width: 100
    height: width/2

    color: colorHex
    Text {
        id: _colorName
        text: colorName
    }

}
