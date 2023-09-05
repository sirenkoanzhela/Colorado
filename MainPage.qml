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

            spacing: 15

            Palette {
                id: _mainPalette
            }
            Palette {
                id: _additionalPalette
            }
        }

        ThreadPanel {
            id: _threadHolder
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
