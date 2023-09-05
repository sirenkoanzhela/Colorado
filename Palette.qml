import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15
import QtQml.Models 2.15

Item {
    id: _parent
    //property bool isPaletteVisible: container.count > 0

    width: Screen.width / 2
    height: Screen.height / 2

    GridView {
        id: _palette

        anchors.fill: parent
        cellWidth: 100
        cellHeight: 100
        model: container

        visible: false

        delegate: ColorSpectrum {
            width: _palette.cellWidth
            height: _palette.cellHeight
            topColorName: ""
            topColorHex: ""
            bottomColorName: ""
            bottomColorHex: ""

            radius: 10

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    _сolorSegment.state = _сolorSegment.state === "pressed" ? "" : "pressed"
                }
            }
        }
    }

    Notification {
        id: _paletteEmpty
        visible: true
        anchors.centerIn: _parent

        buttonText: "+"
        notificationText: "Click to add new color spectrum"
    }
}
