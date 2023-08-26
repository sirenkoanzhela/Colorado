import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Window 2.13
import QtQml.Models 2.13


ApplicationWindow {
    id: application

    width: 720
    height: 480

    title: "Colorado App"
    visible: true
    color: "#231c17"

    Row {
        id: _paletteHolder
        width: parent.width
        height: width/2
        spacing: 10

        Palette {
            id: _mainPalette
        }
        Palette {
            id: _additionalPalette
        }
    }


}
