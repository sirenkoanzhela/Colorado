import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15
import QtQml.Models 2.15


ApplicationWindow {
    id: application

    width: Screen.width
    height: Screen.height

    title: "Colorado App"
    visible: true
    color: "#231c17"
    ColumnLayout {
        id: _layout
        anchors.fill: parent
        spacing: 15
        Row {
            id: _paletteHolder

            width: Screen.width
            height: Screen.height / 2

            Palette {
                id: _mainPalette
                paletteSize: 24
                columns: 4
            }
            Palette {
                id: _additionalPalette
                paletteSize: 8
                columns: 2
            }
        }

        ThreadPanel {
            id: _threadHolder
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
